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
#include "common/software_module_factory/test/bit/src/stubs/dependency_stub2.h"
#include "common/software_module_factory/inc/registration.h"

namespace config {
namespace server {

std::shared_ptr<void> DependencyStub2::create(::config::SoftwareModuleFactory& moduleFactory) {
  (void)moduleFactory;
  return std::make_shared<DependencyStub2>();
}

REGISTER_SOFTWARE_MODULE_IN_FACTORY(::config::server::DependencyStub2,
                                    std::bind(&::config::server::DependencyStub2::create, std::placeholders::_1));

}  // namespace server
}  // namespace config
