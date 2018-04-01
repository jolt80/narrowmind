/*
 * Copyright Ericsson AB 2017
 *
 * The copyright to the computer programs herein is the property of
 * Ericsson AB. The programs may be used and/or copied only with the
 * written permission from Ericsson AB or in accordance with the terms
 * conditions stipulated in the agreement/contract under which the
 * programs have been supplied.
 *
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "common/printable/inc/printable.h"
#include "common/software_module_factory/inc/software_module_factory.h"
#include "common/software_module_factory/test/bit/src/stubs/dependency_stub1.h"
#include "common/software_module_factory/test/bit/src/stubs/dependency_stub2.h"
#include "common/software_module_factory/test/bit/src/stubs/service_stub.h"
#include "common/software_module_factory/test/bit/src/stubs/singleton_stub.h"

// Needed for instantiation of a Casper R3 Engine
#include "test/bit/ns/inc/ns_wrapper.h"

#include "common/printable/test/helper/inc/json_test_helpers.h"

#include <casper/engine.h>
#include <casper/itc_util.h>

using ::testing::InSequence;
using ::testing::_;
using ::testing::Return;
using ::testing::Eq;
using ::testing::Not;
using ::testing::SetArgReferee;
using ::testing::AnyNumber;
using ::testing::Ref;
using ::testing::Value;
using ::testing::Matches;
using ::testing::ExplainMatchResult;
using ::testing::Not;
using ::testing::An;
using ::testing::ReturnRef;
using ::testing::StrictMock;
using ::testing::AtLeast;
using ::testing::SaveArg;
using ::testing::AnyNumber;
using ::testing::Throw;
using ::testing::DoAll;
using ::testing::KilledBySignal;

namespace config {
namespace server {

class SoftwareModuleFactoryTest : public ::testing::Test {
 public:
  std::unique_ptr<::config::bit::NsWrapper> ns;
  ::casper_r3::ItcMailbox mailboxId;
  std::string mailboxName = "testMailbox";

  std::unique_ptr<::config::SoftwareModuleFactory> moduleFactory;

  void SetUp() {
    ::casper_r3::itc_util::initItcDefault();
    mailboxId = ::casper_r3::itc_util::createItcMailbox(mailboxName);
    moduleFactory.reset(new ::config::SoftwareModuleFactory());
    CONFIG_TRACE_DEBUG("ServiceFactory after construction:\n%s\n", CONFIG_FORMATSTRINGS(*moduleFactory));
    //    ns.reset(new ::config::bit::NsWrapper());
  }

  void TearDown() {
    moduleFactory.reset();
    CONFIG_TRACE_DEBUG("ServiceFactory after construction:\n%s\n", CONFIG_FORMATSTRINGS(*moduleFactory));

    //    ns.reset();
    ::casper_r3::itc_util::deleteItcMailbox(mailboxId);
    ::casper_r3::itc_util::itcExit();
  }
};

TEST_F(SoftwareModuleFactoryTest, CreateSoftwareModuleFactory) {
  auto& dependencyStub2 = moduleFactory->getInstance<DependencyStub2>();
  (void)dependencyStub2;
}

TEST_F(SoftwareModuleFactoryTest, CreateSoftwareModuleFactory2) {

  auto& dependencyStub2 = moduleFactory->getInstance<DependencyStub2>();
  (void)dependencyStub2;

  auto& dependencyStub1 = moduleFactory->getInstance<DependencyStub1>();
  (void)dependencyStub1;

  CONFIG_TRACE_DEBUG("ServiceFactory after construction of dependencyStub2:\n%s\n",
                     CONFIG_FORMATSTRINGS(*moduleFactory));

  auto& engineR3 = moduleFactory->getInstance<::casper_r3::Engine>();
  (void)engineR3;

  CONFIG_TRACE_DEBUG("ServiceFactory after construction of engineR3:\n%s\n", CONFIG_FORMATSTRINGS(*moduleFactory));

  auto& serviceStub = moduleFactory->getInstance<ServiceStub>();
  serviceStub.publish();

  VERIFY_PARSABLE_JSON(moduleFactory);
}

TEST_F(SoftwareModuleFactoryTest, SingletonStub) {
  // Test that singletonstub behaves as expected

  // Fetch a singletonStub from the factory
  auto& singletonStub = moduleFactory->getInstance<SingletonStub>();

  // Reset the factory, thus throwing away the last instance of the just fethed sigletonStub
  moduleFactory.reset(new ::config::SoftwareModuleFactory());

  // Fetch a singletonStub from the new factory instance
  auto& newSingletonStub = moduleFactory->getInstance<SingletonStub>();

  // Expect that a new instance of singletonStub is created when the moduleFactory is reset
  ASSERT_NE(&singletonStub, &newSingletonStub);

  // Also create a shared_ptr instance of singletonStub
  auto singletonStub2 = moduleFactory->createInstance<SingletonStub>();

  // Expect the same instance to be returner while the moduleFactory exists
  ASSERT_EQ(&newSingletonStub, singletonStub2.get());
}

TEST_F(SoftwareModuleFactoryTest, Get_SingletonStub_instance_by_one_of_the_implemented_interfaces) {
  auto& if1 = moduleFactory->getInstance<Interface1>();
  if1.interface1Method();
}
}
}
