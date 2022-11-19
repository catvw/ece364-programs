#!/bin/bash
mkdir -p tmp/
echo -e 'ref/in\ntmp/out' | ./$1
echo -e 'ref/bonus_in\ntmp/bonus_out' | ./$1
echo
diff ref/out tmp/out
diff ref/bonus_out tmp/bonus_out
echo

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
