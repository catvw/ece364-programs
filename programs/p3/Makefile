# copied in part from http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

.SUFFIXES:
VPATH = ../p1:../p2

TARGET_SOURCES := $(wildcard target/*.cpp)
OBJECT_SOURCES := $(wildcard dijkstra/*.cpp ../p1/hash/*.cpp ../p2/heap/*.cpp)
SOURCES := $(TARGET_SOURCES) $(OBJECT_SOURCES)

TARGETS := $(TARGET_SOURCES:%.cpp=%.out)
OBJECTS := $(OBJECT_SOURCES:%.cpp=%.o)
DEPENDS := $(SOURCES:%.cpp=%.d)

ALL_OBJECTS := $(SOURCES:%.cpp=%.o) # mostly for cleaning

COMPILER = g++
DEBUGGER = lldb
FLAGS = -g -std=c++11 -I. -I../p1/ -I../p2/ -Iheap
DEP_FLAGS = -MT $@ -MMD -MP -MF $*.d
C++ = $(COMPILER) $(FLAGS)
C++.o = $(C++) -c $(DEP_FLAGS)

.PHONY: all test debug-test debug-manual
all: $(TARGETS)

test: target/main.out
	./test.sh $<

debug-test: target/main.out
	./test.sh $< -d

debug-manual: target/main.out
	$(DEBUGGER) $<

$(TARGETS): %.out: %.o $(OBJECTS)
	$(C++) -o $@ $^

%.o: %.cpp %.d
	$(C++.o) -o $@ $<

$(DEPENDS): # empty! (and explicit, so make won't delete them)

.PHONY: clean
clean:
	rm -rf $(TARGETS) $(ALL_OBJECTS) $(DEPENDS)
	rm -rf tmp/

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
