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
#include "common/software_module_factory/inc/registration.h"
#include "common/software_module_factory/inc/software_module_factory.h"

#include <casper/engine.h>
#include <casper/engine_factory.h>

static std::shared_ptr<void> createEngineR3(::config::SoftwareModuleFactory&) {
  return std::move(::casper_r3::EngineFactory().create());
}

REGISTER_SOFTWARE_MODULE_IN_FACTORY(::casper_r3::Engine, createEngineR3);
