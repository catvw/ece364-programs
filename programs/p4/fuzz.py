import random
import string

MERGES = 100000
LENGTH = 1000
ERROR_RATE = .1

def gen_string(length):
	subset = string.ascii_lowercase[:random.choice(range(1, 26))]
	return ''.join(random.choice(subset) for _ in range(length))

def one_error(s):
	s = list(s)

	# try to swap two letters
	i = 0
	j = 0
	tries = 0
	if len(s) > 1: # this is actually maybe possible
		while s[i] == s[j] and abs(i - j) > 1 and tries < len(s):
			i = random.choice(range(len(s)))
			j = random.choice(range(len(s)))
			tries = tries + 1

	if s[i] == s[j]: # just get one character wrong
		new_letter = s[i]
		while new_letter == s[i]:
			new_letter = random.choice(string.ascii_lowercase)
		s[i] = new_letter
	else:
		t = s[i]
		s[i] = s[j]
		s[j] = t

	return ''.join(s)

def random_merge(a, b, correct=True):
	bias = random.random()

	if not correct: # screw something up in one of the strings
		if random.random() > .5:
			a = one_error(a)
		else:
			b = one_error(b)

	a_index = 0
	b_index = 0
	merge = ''

	def add_a():
		nonlocal merge, a_index
		merge = merge + a[a_index].upper()
		a_index = a_index + 1

	def add_b():
		nonlocal merge, b_index
		merge = merge + b[b_index]
		b_index = b_index + 1

	# add randomly assigned characters from each string
	while a_index < len(a) and b_index < len(b):
		if random.random() > bias or b[b_index] == a[a_index]:
			add_a()
		else:
			add_b()

	# finish them off
	while a_index < len(a):
		add_a()

	while b_index < len(b):
		add_b()

	return merge

if __name__ == "__main__":
	random.seed()
	with open('ref/fuzz_in', 'w') as infile, open('ref/fuzz_out', 'w') as outfile:
		print('generating:   0%', end='', flush=True)
		for i in range(MERGES):
			if i % int(max(MERGES/100, 1)) == 0:
				print(f'\x1b[4D{int(100*(i + 1)/MERGES):3}%', end='', flush=True)

			a = gen_string(random.choice(range(LENGTH)))
			b = gen_string(random.choice(range(max(0, 2 - len(a)), LENGTH)))

			correct = random.random() > ERROR_RATE or min(len(a), len(b)) == 0
			merge = random_merge(a, b, correct)
			infile.write(f'{a}\n{b}\n{merge.lower()}\n')

			if correct:
				outfile.write(f'{merge}\n')
			else:
				outfile.write('*** NOT A MERGE ***\n')

		print(' generated.')

# Copyright (C) 2022  Catherine Van West
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
