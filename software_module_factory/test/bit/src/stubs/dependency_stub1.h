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
#ifndef TEST_SRC_STUBS_DEPENDENCY_STUB1_H_
#define TEST_SRC_STUBS_DEPENDENCY_STUB1_H_

#include "common/software_module_factory/inc/registration.h"

namespace config {
namespace server {

class SoftwareModuleFactory;
class DependencyStub2;

class DependencyStub1 {
 public:
  DependencyStub1(const DependencyStub2& dependencyStub2);
  virtual ~DependencyStub1() = default;

  static std::shared_ptr<void> create(::config::SoftwareModuleFactory& moduleFactory);

 private:
  const DependencyStub2& dependencyStub2;
};

}  // namespace server
}  // namespace config

#endif /* TEST_SRC_STUBS_DEPENDENCY_STUB1_H_ */
