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
#ifndef CONFIG_SOFTWARE_MODULE_FACTORY_H_
#define CONFIG_SOFTWARE_MODULE_FACTORY_H_

#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include "common/software_module_factory/inc/registration.h"

namespace casper_r3 {
class Engine;
}

namespace config {

/**
 * Modular factory that can create instances of all 'software modules' (as defined in RC/RPC SWAD).
 *
 * In essence this is a generic Factory that can create any c++ object using a registered factory method.
 */
class SoftwareModuleFactory {
 public:
  SoftwareModuleFactory() = default;
  virtual ~SoftwareModuleFactory() = default;

  /**
   * Create a new shared_ptr instance of a object.
   *
   * Will use the registered factory method to create a new instance of type T.
   *
   * @return shared_ptr of type T.
   */
  template <typename T>
  std::shared_ptr<T> createInstance() {
    return std::static_pointer_cast<T>(
        createSoftwareModuleInstance(getModuleId<T>(), ::config::Registration<T>::registered));
  }

  /**
   * Get a reference to an existing instance of an object.
   *
   * SoftwareModuleFactory will allocate an instance on demand and keep memory ownership of
   * it until the instance of SoftwareModuleFactory goes out of scope.
   *
   * @return reference to an instance of type T.
   */
  template <typename T>
  T& getInstance() {
    return *std::static_pointer_cast<T>(
        getSoftwareModuleInstance(getModuleId<T>(), ::config::Registration<T>::registered));
  }

  friend std::ostream& operator<<(std::ostream& os, const SoftwareModuleFactory& moduleFactory);

 private:
  std::shared_ptr<void> getSoftwareModuleInstance(std::type_index moduleIndex, bool registered);
  std::shared_ptr<void> createSoftwareModuleInstance(std::type_index moduleIndex, bool registered);

  template <typename T>
  std::type_index getModuleId() {
    return std::type_index(typeid(T));
  }

  std::map<std::type_index, std::shared_ptr<void>> instances;
};

}  // namespace config

#endif /* CONFIG_SOFTWARE_MODULE_FACTORY_H_ */
