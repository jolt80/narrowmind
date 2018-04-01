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
#ifndef TEST_SRC_STUBS_SERVICE_STUB_H_
#define TEST_SRC_STUBS_SERVICE_STUB_H_

#include <casper/engine.h>
#include "server/service/inc/service.h"

namespace config {

class SoftwareModuleFactory;

namespace server {

class Interface1;
class Interface2;

class ServiceStub : public ::config::server::Service {
 public:
  ServiceStub(::casper_r3::Engine& engine, Interface1& interface1, Interface2& interface2);
  virtual ~ServiceStub() = default;

  // Factory method
  static std::shared_ptr<void> create(::config::SoftwareModuleFactory& moduleFactory);

  virtual void publish() override;
  virtual void unPublish() override;

 private:
  ::casper_r3::Engine& engine;
  Interface1& interface1;
  Interface2& interface2;
};

}  // namespace server
}  // namespace config

#endif /* TEST_SRC_STUBS_SERVICE_STUB_H_ */
