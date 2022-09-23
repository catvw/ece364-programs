# copied in part from http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

.SUFFIXES:
VPATH = ../p1/

TARGET_SOURCES := $(wildcard targ/*.cpp)
OBJECT_SOURCES := $(wildcard heap/*.cpp hash/*.cpp)
SOURCES := $(TARGET_SOURCES) $(OBJECT_SOURCES)

TARGETS := $(TARGET_SOURCES:%.cpp=%.out)
OBJECTS := $(OBJECT_SOURCES:%.cpp=%.o)
DEPENDS := $(SOURCES:%.cpp=%.d)

COMPILER = g++
FLAGS = -std=c++11 -I. -I../p1/ -Iheap
DEP_FLAGS = -MT $@ -MMD -MP -MF $*.d
C++ = $(COMPILER) $(FLAGS)
C++.o = $(C++) -c $(DEP_FLAGS)

.PHONY: all use test
all: $(TARGETS)

use: targ/useHeap.out
	./$<

test: targ/testHeap.out
	./$<

$(TARGETS): %.out: %.o $(OBJECTS)
	$(C++) -o $@ $^

%.o: %.cpp %.d
	$(C++.o) -o $@ $<

$(DEPENDS): # empty! (and explicit, so make won't delete them)

.PHONY: clean
clean:
	rm -rf $(TARGETS) $(OBJECTS) $(DEPENDS)

include $(wildcard $(DEPENDS))

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
