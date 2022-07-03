# ----------------------------
# Makefile Options
# ----------------------------

NAME = CEDIT2RA
ICON = icon.png
DESCRIPTION = "CEdit editor"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
