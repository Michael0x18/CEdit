# ----------------------------
# Makefile Options
# ----------------------------

NAME = CEDIT2RA
ICON = icon.png
DESCRIPTION = "CEdit editor"
COMPRESSED = YES
ARCHIVED = NO

CFLAGS = -Wall -Wextra -O3
CXXFLAGS = -Wall -Wextra -O3

# ----------------------------

include $(shell cedev-config --makefile)
