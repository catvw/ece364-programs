#!/bin/bash
mkdir -p tmp/
if [ $# -eq 2 ]; then # we should call this with a debugger
	lldb $1 -- ref/test_graph v1 out_v1
else
	echo -e 'ref/test_graph\nv1\ntmp/out_v1' | ./$1
	echo -e 'ref/test_graph\nv5\ntmp/out_v5' | ./$1
	echo
	diff ref/out_v1 tmp/out_v1
	diff ref/out_v5 tmp/out_v5
	echo
fi

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
