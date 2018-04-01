/* Copyright Ericsson AB
 ***********************************************************************************
 *                                                                                 *
 * The copyright to the computer programs herein is the property of Ericsson AB.   *
 * The programs may be used and/or copied only with the written permission from    *
 * Ericsson AB or in accordance with the terms conditions stipulated in the        *
 * agreement/contract under which the programs have been supplied.                 *
 *                                                                                 *
 ***********************************************************************************
 */
#include "common/software_module_factory/inc/software_module_factory.h"
#include "common/software_module_factory/inc/registration.h"

#include <boost/variant.hpp>

#include <cxxabi.h>
#include <map>
#include <ostream>
#include <sstream>
#include "common/printable/inc/printable.h"
#include "common/trace/inc/assert.h"
#include "common/trace/inc/trace.h"

namespace {
// Lazy initialized map containing all  SoftwareModule factory functions
static std::map<std::type_index, ::config::SoftwareModuleFactoryFunc>& getSoftwareModuleFactoryMap() {
  static std::map<std::type_index, ::config::SoftwareModuleFactoryFunc> softwareModuleFactories;
  return softwareModuleFactories;
}

// Lazy initialized map containing mapping from registered interface types to implementing types
static std::map<std::type_index, std::type_index>& getInterfaceImplementerMap() {
  static std::map<std::type_index, std::type_index> getInterfaceImplementerMap;
  return getInterfaceImplementerMap;
}
}

namespace config {

/**
 * For a software module or interface return the implementing software module module_index.
 */
static std::type_index lookupSmIndex(std::type_index requestedIndex) {
  auto& interfaceImplementerMap = getInterfaceImplementerMap();
  auto it = interfaceImplementerMap.find(requestedIndex);
  if (interfaceImplementerMap.end() != it)
    return interfaceImplementerMap.at(requestedIndex);
  else
    return requestedIndex;
}

/**
 * Return a nice string representation of a mangled typne name.
 *
 */
std::string demangleTypeName(const char* mangledTypeName) {
  int status;
  char* realname;
  realname = ::abi::__cxa_demangle(mangledTypeName, 0, 0, &status);
  if (status == 0) {
    std::string ret{realname};
    free(realname);
    return std::move(ret);
  }
  else if (status == -1) {                                              // LCOV_EXCL_LINE
    return std::string{"failed_to_demangle_name(memory_alloc_error)"};  // LCOV_EXCL_LINE
  }
  else if (status == -2) {                                                // LCOV_EXCL_LINE
    return std::string{"failed_to_demangle_name(invalid_mangled_name)"};  // LCOV_EXCL_LINE
  }
  return std::string{"failed_to_demangle_name(invalid_arguments)"};  // LCOV_EXCL_LINE
}

bool registerSoftwareModuleInFactory(std::type_index moduleIndex, ::config::SoftwareModuleFactoryFunc factoryFunc) {
  CONFIG_TRACE_DEBUG("registerSoftwareModuleInFactory called for %s", demangleTypeName(moduleIndex.name()).c_str());
  CONFIG_ASSERT(getSoftwareModuleFactoryMap().count(moduleIndex) == 0,
                "%s already  in ::config::SoftwareModuleFactory",
                demangleTypeName(moduleIndex.name()).c_str());
  getSoftwareModuleFactoryMap().insert({moduleIndex, factoryFunc});
  return true;
}

bool registerInterfaceImplementerInFactory(std::type_index interface, std::type_index implementer) {
  CONFIG_TRACE_DEBUG("registerInterfaceImplementer called for %s : %s",
                     demangleTypeName(interface.name()).c_str(),
                     demangleTypeName(implementer.name()).c_str());
  CONFIG_ASSERT(getSoftwareModuleFactoryMap().count(interface) == 0,
                "%s already  in ::config::SoftwareModuleFactory",
                demangleTypeName(interface.name()).c_str());
  getInterfaceImplementerMap().insert({interface, implementer});
  return true;
}

std::shared_ptr<void> SoftwareModuleFactory::createSoftwareModuleInstance(std::type_index requestedIndex,
                                                                          bool registered) {
  CONFIG_ASSERT(registered, "Factory is not initialized for %s", demangleTypeName(requestedIndex.name()).c_str());
  auto index = lookupSmIndex(requestedIndex);

  CONFIG_TRACE_DEBUG("createSoftwareModuleInstance for %s", demangleTypeName(index.name()).c_str());
  auto& softwareModuleFactoryMap = getSoftwareModuleFactoryMap();
  CONFIG_ASSERT(softwareModuleFactoryMap.find(index) != softwareModuleFactoryMap.end(),
                "No  factory method for %s!\n%s",
                demangleTypeName(index.name()).c_str(),
                CONFIG_FORMATSTRINGS(*this));
  return softwareModuleFactoryMap.at(index)(*this);
}

std::shared_ptr<void> SoftwareModuleFactory::getSoftwareModuleInstance(std::type_index requestedIndex,
                                                                       bool registered) {
  CONFIG_ASSERT(registered, "Factory is not initialized for %s", demangleTypeName(requestedIndex.name()).c_str());
  auto index = lookupSmIndex(requestedIndex);

  CONFIG_TRACE_DEBUG("getSoftwareModule for %s", demangleTypeName(index.name()).c_str());
  if (instances.find(index) == instances.end()) {
    instances[index] = createSoftwareModuleInstance(index, registered);
  }
  return instances.at(index);
}

std::ostream& operator<<(std::ostream& os, const SoftwareModuleFactory& moduleFactory) {
  if (nullptr == &moduleFactory) {
    serializeAsJson(os, "null");
    return os;
  }
  auto& df = getSoftwareModuleFactoryMap();
  auto& ii = getInterfaceImplementerMap();
  os << "{\"ptr\":";
  serializeAsJsonPtr(os, &moduleFactory);
  os << ",\"softwareModuleFactories\":{";
  const char* separator = ::config::printable_helpers::empty;
  for (const auto& elem : df) {
    os << separator;
    serializeAsJson(os, demangleTypeName(elem.first.name()));
    os << ':';
    serializeAsJsonPtr(os, &(elem.second));
    separator = ::config::printable_helpers::comma;
  }
  os << '}';
  os << ",\"interfaceImpementers\":{";
  separator = ::config::printable_helpers::empty;
  for (const auto& elem : ii) {
    os << separator;
    serializeAsJson(os, demangleTypeName(elem.first.name()));
    os << ':';
    serializeAsJson(os, demangleTypeName(elem.second.name()));
    separator = ::config::printable_helpers::comma;
  }
  os << '}';
  os << ",\"instances\":{";
  separator = ::config::printable_helpers::empty;
  for (const auto& elem : moduleFactory.instances) {
    os << separator;
    serializeAsJson(os, demangleTypeName(elem.first.name()));
    os << ':';
    serializeAsJsonPtr(os, &(elem.second));
    separator = ::config::printable_helpers::comma;
  }
  os << "}}";
  return os;
}

}  // namespace config
