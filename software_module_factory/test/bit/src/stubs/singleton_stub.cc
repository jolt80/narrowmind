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
#include "common/software_module_factory/test/bit/src/stubs/singleton_stub.h"
#include "common/software_module_factory/inc/registration.h"
#include "common/trace/inc/assert.h"
#include "common/trace/inc/trace.h"

namespace config {
namespace server {

std::shared_ptr<void> SingletonStub::create(::config::SoftwareModuleFactory& moduleFactory) {
  (void)moduleFactory;
  /*
   * Keep track of the instance with a weak_ptr
   * This way a new instance can be created when this instance has expired
   * (i.e. the last shared_ptr has been deleted).
   *
   * Thus this is a "soft" singleton, this method will return the same instance as long as there
   * instances tracked somewhere in the application.
   */
  static std::weak_ptr<SingletonStub> instance;
  if (instance.expired()) {
    auto newInstance = std::make_shared<SingletonStub>();
    instance = newInstance;
    return newInstance;
  }
  else {
    return instance.lock();
  }
}

void SingletonStub::interface1Method() { CONFIG_TRACE_DEBUG("SingletonStub::interface1Method called"); }
void SingletonStub::interface2Method() { CONFIG_TRACE_DEBUG("SingletonStub::interface2Method called"); }

REGISTER_SOFTWARE_MODULE_IN_FACTORY(::config::server::SingletonStub,
                                    std::bind(&::config::server::SingletonStub::create, std::placeholders::_1));
REGISTER_INTERFACE_IMPLEMENTER_IN_FACTORY(::config::server::Interface1, ::config::server::SingletonStub);
REGISTER_INTERFACE_IMPLEMENTER_IN_FACTORY(::config::server::Interface2, ::config::server::SingletonStub);

}  // namespace server
}  // namespace config
