
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
#ifndef TEST_SRC_STUBS_DEPENDENCY__STUB2_H_
#define TEST_SRC_STUBS_DEPENDENCY_STUB2_H_

#include <memory>

namespace config {
class SoftwareModuleFactory;

namespace server {

class DependencyStub2 {
 public:
  DependencyStub2() = default;
  virtual ~DependencyStub2() = default;

  static std::shared_ptr<void> create(::config::SoftwareModuleFactory& moduleFactory);
};

}  // namespace server
}  // namespace config

#endif /* TEST_SRC_STUBS_DEPENDENCY_STUB2_H_ */
