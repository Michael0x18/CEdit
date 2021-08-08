
# ----------------------------
# Program Options
# ----------------------------

NAME         ?= CEDIT
ICON         ?= icon.png
DESCRIPTION  ?= "CEdit editor"
#COMPRESSED   ?= YES
#ARCHIVED     ?= YES

# ----------------------------
# Compile Options
# ----------------------------

CFLAGS   ?= -Oz -W -Wall -Wextra -Wwrite-strings -DBOS_BUILD
<<<<<<< HEAD
CXXFLAGS ?= -Oz -W -Wall -Wextra -Wwrite-strings -DBOS_BUILD
=======
CXXFLAGS ?= -Oz -W -Wall -Wextra -Wwrite-strings
>>>>>>> a2733d9936e6407ef6208361bc49dcbd14415d64

# ----------------------------
# Debug Options
# ----------------------------

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/bos/meta/makefile.mk

