# copied in part from http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

.SUFFIXES:

SOURCES := $(wildcard *.cpp */*.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)
DEPENDS := $(SOURCES:%.cpp=%.d)

COMPILER = g++
FLAGS = -std=c++11
DEP_FLAGS = -MT $@ -MMD -MP -MF $*.d
C++ = $(COMPILER) $(FLAGS)
C++.o = $(C++) -c $(DEP_FLAGS)

useHeap: $(OBJECTS)
	$(C++) -o $@ $(OBJECTS)

%.o: %.cpp %.d
	$(C++.o) -o $@ $<

$(DEPENDS): # empty! (and explicit, so make won't delete them)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(DEPENDS)

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
