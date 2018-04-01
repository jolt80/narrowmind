#
# Copyright Ericsson AB 2015
#
# The copyright to the computer programs herein is the property of
# Ericsson AB. The programs may be used and/or copied only with the
# written permission from Ericsson AB or in accordance with the terms
# conditions stipulated in the agreement/contract under which the
# programs have been supplied.
#

PLATFORM := vrcs
TARGET := x86_64-wrs-linux
TARGET_EXTENSION := bit
BIN_NAME  := softwareModuleFactory
BITEXE := $(ERBS_ROOT)/alfred-out/x86_64-wrs-linux-bit/bin/softwareModuleFactory
BITRUN := $(ERBS_ROOT)/tools/bit/bin/bit_run.sh
BITCMD := $(BITRUN) $(BITEXE)
VALGRIND := /app/vbuild/RHEL6-i686/valgrind/3.9.0/bin/valgrind
LTTNG_FILTER := "com_ericsson_test_config:*"

include $(ALFRED_ROOT)/include/init.mk
include $(HEADER_MK)

GCOV_INCLUDE := $(realpath $(MODULE_DIR)/../..)
GCOV_EXCLUDE := $(realpath $(MODULE_DIR)/../..)/test

#include Test data_model
include $(ERBS_ROOT)/test_deployment/intif/config/variant/fwk_test/build/data_model.mk

#include bit framework
include $(ERBS_ROOT)/tools/bit/include/bit.mk


################################################################
# Compiler flags
#################################################################
CXXFLAGS += -D_BITS_OPT_RANDOM_H -DGTEST_HAS_RTTI=0 -std=c++14
CXXFLAGS += -Wall -Wextra -pedantic -Werror
CXXFLAGS += -DBIT_USING_PROTOBUF
CXXFLAGS += -DUSE_REAL_NS_PROC_NAME_IN_BIT

LTTNG_CONTEXT = "-t vpid -t vtid"

#################################################################
# External
################################################################
include $(CONFIG_ROOT)/common/trace/impl.mk
include $(CONFIG_FWK_ROOT)/common/trace/impl.mk

################################################################
# Linker flags
#################################################################

LDFLAGS += -Wl,-unresolved-symbols=ignore-in-shared-libs
LDLIBS += -pthread -lrt -llttng-ust
INC_DEPS += casper_r3_mocks casper_r3
LIB_DEPS += protobuf xcm sdc
LIB_DEPS += casper_r3 casper_r3_mocks

include $(CONFIG_FWK_ROOT)/common/printable/test/helper/impl.mk
include $(CONFIG_FWK_ROOT)/common/printable/impl.mk

# Test dependendices
#include $(ERBS_ROOT)/test/bit/bit_observer/impl.mk
include $(CONFIG_FWK_ROOT)/test/bit/ns/impl.mk

# Include own implementation last
include $(CONFIG_FWK_ROOT)/common/software_module_factory/impl.mk

include $(CONFIG_FWK_ROOT)/common/software_module_factory/if.mk
include $(CONFIG_ROOT)/common/trace/if.mk

# Test code
SRC_DIRS_TEST += $(MODULE_DIR)/src
include $(MODULE_DIR)/src/stubs/impl.mk

################################################################
# Make rules to run bit
#################################################################

#pragma runlocal
bit-run: $(BITEXE)
	export GTEST_CATCH_EXCEPTIONS=0; \
	sdk_run.sh -t vrcs64_bit -l -o lttng.log -e $(LTTNG_FILTER) -s $(SDK) $(BITCMD)  --compact_trace

#	sdk_run.sh -t vrcs64_bit -s $(SDK) $(BITCMD)

.PHONY: bit-memcheck
#output of memcheck run in bitlog.log
#pragma runlocal
bit-memcheck: $(BITEXE)
	export VALGRIND_OPTS="--suppressions=$(CONFIG_FWK_ROOT)/test/bit/valgrind_filters/config_memcheck.txt\
	                      --suppressions=$(ERBS_ROOT)/test_deployment/config/test/bit/valgrind_filters/sys_service_memcheck.txt\
	                      --log-file=software_module_factory.valgrind.memcheck.log --leak-check=full --track-origins=yes --error-exitcode=1 --gen-suppressions=all";\
	sdk_run.sh -t vrcs64_bit -l -o lttng.log -e $(LTTNG_FILTER) $(ERBS_ROOT)/tools/bit/bin/bit_run.sh $(BITEXE) -v memcheck --compact_trace

#pragma runlocal
bit-helgrind: $(BITEXE)
	export VALGRIND_OPTS="-v --suppressions=$(CONFIG_IF_SHARED_ROOT)/test/bit/suppressions/valgrind-suppressions-helgrind.txt\
	                         --log-file=software_module_factory.valgrind.helgrind.log --gen-suppressions=all";\
	sdk_run.sh -t vrcs64_bit -l -o lttng.log -e $(LTTNG_FILTER) $(ERBS_ROOT)/tools/bit/bin/bit_run.sh $(BITEXE) -v helgrind --compact_trace

include $(FOOTER_MK)

