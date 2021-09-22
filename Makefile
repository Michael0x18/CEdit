# ----------------------------
# Makefile Options
# ----------------------------

NAME = CEDIT
ICON = icon.png
DESCRIPTION = "CEdit editor"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
