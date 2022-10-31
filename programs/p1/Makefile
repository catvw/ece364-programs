MAKE_PREFIX=-make.
CLEAN_PREFIX=-clean.

SUBDIRS=hash spell
SUBDIRS_MAKE=$(addprefix $(MAKE_PREFIX), $(SUBDIRS))
SUBDIRS_CLEAN=$(addprefix $(CLEAN_PREFIX),$(SUBDIRS))

SPELL_DEPS=$(addsuffix /*.o,$(SUBDIRS))

.DEFAULT .PHONY .NOTPARALLEL: spellcheck_all
spellcheck_all: -subdirs spellcheck

-subdirs: $(SUBDIRS_MAKE)

.PHONY: $(SUBDIRS_MAKE)
$(SUBDIRS_MAKE):
	$(MAKE) -C $(subst $(MAKE_PREFIX),,$@)

spellcheck: main.cpp $(wildcard $(SPELL_DEPS))
	g++ -g -o spellcheck $(SPELL_DEPS) main.cpp

.PHONY: test
test: spellcheck_all
	./test.sh

.PHONY: debug
debug: spellcheck_all
	mkdir -p tmp/
	lldb spellcheck

.PHONY: clean
clean: $(SUBDIRS_CLEAN)
	rm -rf spellcheck tmp/

.PHONY: $(SUBDIRS_CLEAN)
$(SUBDIRS_CLEAN):
	$(MAKE) -C $(subst $(CLEAN_PREFIX),,$@) clean

#Copyright (C) 2022  Catherine Van West
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <https://www.gnu.org/licenses/>.
