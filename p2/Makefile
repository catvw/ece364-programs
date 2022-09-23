# copied shamelessly from http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

SRCS=$(wildcard *.c *.cpp *.c++)

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CC = g++
CPPFLAGS = -std=c++11
COMPILE = $(CC) $(DEPFLAGS) $(CPPFLAGS)

%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)

$(DEPDIR):
	@mkdir -p $@

DEPFILES := $(SRCS:%.c=$(DEPDIR)/%.d)
$(DEPFILES): # empty!

include $(wildcard $(DEPFILES))

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
