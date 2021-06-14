
# ----------------------------
# Program Options
# ----------------------------

NAME         ?= CEDIT
ICON         ?= icon.png
DESCRIPTION  ?= "CEdit editor"
COMPRESSED   ?= YES
ARCHIVED     ?= YES

# ----------------------------
# Compile Options
# ----------------------------

CFLAGS   ?= -Oz -W -Wall -Wextra -Wwrite-strings
CXXFLAGS ?= -Oz -W -Wall -Wextra -Wwrite-strings

# ----------------------------
# Debug Options
# ----------------------------
FONTDIR ?= $(SRCDIR)/fonts
FONT ?= $(FONTDIR)/drmono-10-normal.fnt
FONT_INC ?= $(FONTDIR)/drmono-10-normal.inc

DEPS ?= $(FONT_INC)
# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

# ----------------------------

$(FONT_INC): $(FONT)
	$(Q)$(call MKDIR,$(@D))
	$(Q)convfont -o carray -f $< -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@

#font stuff

# This is a roundabout way to tell make that myfonts.c depends on the .inc files.
# It does it by saying the compiled object code depends on the .inc files.
#$(OBJDIR)/myfonts.src: $(SRCDIR)/drmono-10-normal.inc

# Convert a .fnt file into a .inc file
#$(SRCDIR)/myfont1.inc: $(SRCDIR)/myfont1.fnt
#    convfont -o carray -f $(SRCDIR)/myfont1.fnt $(SRCDIR)/myfont1.inc

#$(SRCDIR)/myfont2.inc: $(SRCDIR)/myfont2.fnt
#    convfont -o carray -f $(SRCDIR)/myfont2.fnt $(SRCDIR)/myfont2.inc
