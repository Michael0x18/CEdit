# ----------------------------
# Makefile Options
# ----------------------------

NAME = CEDIT2RA
ICON = icon.png
DESCRIPTION = "CEdit editor"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -O3
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
