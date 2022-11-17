#!/bin/bash

# archive program 1
make -C p1/ clean
tar acvf p1.tar.gz p1/Makefile p1/test.sh p1/main.cpp p1/hash/ p1/spell/ p1/ref/

# archive program 2
make -C p2/ clean
tar acvf p2.tar.gz p1/hash/ p2/Makefile p2/heap/ p2/targ/

# archive program 3
make -C p3/ clean
tar acvf p3.tar.gz p1/hash/ p2/heap/ p3/Makefile p3/test.sh p3/ref p3/dijkstra p3/target

# archive program 4
make -C p4/ clean
tar acvf p4.tar.gz p4/merge.cpp p4/ref/ p4/test.sh p4/Makefile

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
