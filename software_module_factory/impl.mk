#
# Copyright Ericsson AB 2017
#
# The copyright to the computer programs herein is the property of
# Ericsson AB. The programs may be used and/or copied only with the
# written permission from Ericsson AB or in accordance with the terms
# conditions stipulated in the agreement/contract under which the
# programs have been supplied.
#
include $(HEADER_MK)

# Interface dependencies for current module
include $(MODULE_DIR)/if.mk
include $(CONFIG_ROOT)/common/trace/if.mk
INC_DEPS_$(MODULE_ID) += casper_r3
INC_DIRS_$(MODULE_ID) += /proj/lte_twh/tools/boost/1.63.0-8/x86_64-vrcs/include

# Source code directories for the current module
SRC_DIRS_$(MODULE_ID) += $(MODULE_DIR)/src

include $(FOOTER_MK)
