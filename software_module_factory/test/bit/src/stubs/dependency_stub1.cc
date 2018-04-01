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
#include "common/software_module_factory/test/bit/src/stubs/dependency_stub1.h"
#include "common/software_module_factory/inc/software_module_factory.h"
#include "common/software_module_factory/test/bit/src/stubs/dependency_stub2.h"
#include "common/trace/inc/assert.h"
#include "common/trace/inc/trace.h"

namespace config {
namespace server {

DependencyStub1::DependencyStub1(const DependencyStub2& dependencyStub2)
    : dependencyStub2(dependencyStub2) {}

std::shared_ptr<void> DependencyStub1::create(::config::SoftwareModuleFactory& moduleFactory) {
  auto& dependencyStub2 = moduleFactory.getInstance<DependencyStub2>();
  return std::make_shared<DependencyStub1>(dependencyStub2);
}

REGISTER_SOFTWARE_MODULE_IN_FACTORY(::config::server::DependencyStub1,
                                    std::bind(&::config::server::DependencyStub1::create, std::placeholders::_1));

}  // namespace server
}  // namespace config
