CPP_FILES=$(wildcard *.cpp)
OBJECTS=$(CPP_FILES:.cpp=.o)

.PHONY: all
all: $(OBJECTS)

%.o: %.cpp %.h
	g++ -c -g $<

.PHONY: clean
clean:
	rm -f *.o

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
