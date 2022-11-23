.PHONY: test debug
test: merge
	./test.sh merge

fuzz: merge ref/fuzz_in
	./test.sh merge --fuzz

ref/fuzz_in:
	python fuzz.py

debug: merge
	lldb merge

merge: merge.cpp
	g++ -g -o merge merge.cpp

.PHONY: clean
clean:
	rm -rf merge tmp/ ref/fuzz_*

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
