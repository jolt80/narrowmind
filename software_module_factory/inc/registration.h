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
#ifndef CONFIG_SERVER_SERVICE_REGISTRATION_HELPERS_H_
#define CONFIG_SERVER_SERVICE_REGISTRATION_HELPERS_H_

#include <functional>
#include <memory>

#include <type_traits>
#include <typeindex>

namespace config {

class SoftwareModuleFactory;

// The method that will be called to register into the SoftwareModuleFactory
extern bool registerSoftwareModuleInFactory(
    std::type_index moduleIndex,
    std::function<std::shared_ptr<void>(::config::SoftwareModuleFactory& moduleFactory)> factoryFunc);

// The method that will be called when an intrface implementer is registered
extern bool registerInterfaceImplementerInFactory(std::type_index interface, std::type_index implementer);

/**
 * Template struct used in registration to force compiler to not optimize away the function call
 * making the registration of the factory method.
 */
template <typename T>
struct Registration {
  static bool registered;
};

/**
 * Typedef for signature of the expected factory method used in registration.
 *
 * The registered factory method is expected to fetch references or construct new instances of all its dependencies
 * from the provided SoftwareModuleFactory and return a shared_ptr of an instance of the SoftwareModule.
 */
using SoftwareModuleFactoryFunc = std::function<std::shared_ptr<void>(::config::SoftwareModuleFactory& moduleFactory)>;
}

/**
 * Macro that automatically registers a factory method in SoftwareModuleFactory at application startup.
 *
 * This macro has to be included in one (and only one) of the translation units of the software module.
 */
#define REGISTER_SOFTWARE_MODULE_IN_FACTORY(className, factoryFunc) \
  template <>                                                       \
  bool ::config::Registration<className>::registered =              \
      registerSoftwareModuleInFactory(std::type_index(typeid(className)), factoryFunc)

/**
 * Macro that registers a type as implementer for an interface type.
 *
 * Enables creation/lookup of dependencies by interface instead of implementation when using SoftwareModuleFactory.
 * Useful if a factory method needs to be unaware of the concrete implementer of an interface and only one of the actual
 * implementations will be used in a program.
 *
 * This macro has to be included in one (and only one) of the translation units of the
 * software module that implements an interface.
 */
#define REGISTER_INTERFACE_IMPLEMENTER_IN_FACTORY(interface, implementer) \
  template <>                                                             \
  bool ::config::Registration<interface>::registered =                    \
      registerInterfaceImplementerInFactory(std::type_index(typeid(interface)), typeid(implementer))

#endif /* CONFIG_SERVER_SERVICE_REGISTRATION_HELPERS_H_ */
