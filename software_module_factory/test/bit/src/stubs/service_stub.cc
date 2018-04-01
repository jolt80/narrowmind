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

#include "common/software_module_factory/test/bit/src/stubs/service_stub.h"
#include <casper/engine.h>
#include "common/software_module_factory/inc/software_module_factory.h"
#include "common/software_module_factory/test/bit/src/stubs/interface1.h"
#include "common/software_module_factory/test/bit/src/stubs/interface2.h"
#include "common/trace/inc/assert.h"
#include "common/trace/inc/trace.h"

namespace config {
namespace server {

ServiceStub::ServiceStub(::casper_r3::Engine& engine, Interface1& interface1, Interface2& interface2)
    : engine(engine)
    , interface1(interface1)
    , interface2(interface2) {}

void ServiceStub::publish() {
  CONFIG_TRACE_DEBUG("ServiceStub::publish() called");
  interface1.interface1Method();
  interface2.interface2Method();
}

void ServiceStub::unPublish() { CONFIG_TRACE_DEBUG("ServiceStub::unPublish() called"); }

std::shared_ptr<void> ServiceStub::create(::config::SoftwareModuleFactory& moduleFactory) {
  auto& engine = moduleFactory.getInstance<casper_r3::Engine>();
  auto& interface1 = moduleFactory.getInstance<Interface1>();
  auto& interface2 = moduleFactory.getInstance<Interface2>();
  return std::make_shared<::config::server::ServiceStub>(engine, interface1, interface2);
}

REGISTER_SOFTWARE_MODULE_IN_FACTORY(::config::server::ServiceStub,
                                    std::bind(&::config::server::ServiceStub::create, std::placeholders::_1));

}  // namespace server
}  // namespace config
