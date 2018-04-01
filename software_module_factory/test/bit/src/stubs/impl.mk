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
include $(realpath $(MODULE_DIR)/../../../..)/if.mk
include $(CONFIG_ROOT)/common/trace/if.mk

# Source code directories for the current module
SRC_DIRS_$(MODULE_ID) += $(MODULE_DIR)

include $(FOOTER_MK)
