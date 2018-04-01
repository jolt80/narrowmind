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
#ifndef COMMON_SOFTWARE_MODULE_FACTORY_TEST_BIT_SRC_STUBS_SINGLETON_STUB_H_
#define COMMON_SOFTWARE_MODULE_FACTORY_TEST_BIT_SRC_STUBS_SINGLETON_STUB_H_

#include "common/software_module_factory/inc/registration.h"
#include "common/software_module_factory/test/bit/src/stubs/interface1.h"
#include "common/software_module_factory/test/bit/src/stubs/interface2.h"

namespace config {
namespace server {

class SoftwareModuleFactory;

class SingletonStub : public Interface1, public Interface2 {
 public:
  SingletonStub() = default;
  virtual ~SingletonStub() = default;

  virtual void interface1Method() override;
  virtual void interface2Method() override;

  static std::shared_ptr<void> create(::config::SoftwareModuleFactory& moduleFactory);
};

}  // namespace server
}  // namespace config

#endif /* COMMON_SOFTWARE_MODULE_FACTORY_TEST_BIT_SRC_STUBS_SINGLETON_STUB_H_ */
