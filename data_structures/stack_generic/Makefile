# stack_generic Makefile
# ======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

PROG    := stack_generic
SOURCES := $(wildcard *.c)
OBJECTS	 = $(subst .c,.o,$(SOURCES))
DEPENDS	 = $(subst .c,.d,$(SOURCES))
CLNGLOB  = $(PROG) $(OBJECTS) $(DEPENDS) tags
CC      := gcc
CFLAGS  := -std=c99 -pedantic -Wall -Wextra -ggdb -DDEBUG -DDEBUG_ALL
LDFLAGS :=
RM      := rm -f
SED     := sed
CTAGS   := ctags

default: main

# Main program

main: $(OBJECTS)
	$(CC) -o $(PROG) $^ $(LDFLAGS)

# clean - removes ancilliary files from working directory

.PHONY: clean
clean:
	-@$(RM) $(CLNGLOB) 2>/dev/null

# tags - makes tags file

.PHONY: tags
tags:
	@$(CTAGS) *.c

# Dependencies

-include $(DEPENDS)

%.d: %.c
	@echo "Building dependencies for $<..."
	@$(CC) -M $(CFLAGS) $< > $@.tmp; \
		$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		$(RM) $@.tmp
