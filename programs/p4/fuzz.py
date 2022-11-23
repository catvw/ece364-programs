import random
import string

MERGES = 100000
LENGTH = 66
ERROR_RATE = .1

def random_letter():
	return random.choice(string.ascii_lowercase)

def gen_string(length):
	return ''.join(random_letter() for _ in range(length))

def random_merge(a, b):
	order = [1 for _ in range(len(a))] + [0 for _ in range(len(b))]
	random.shuffle(order)

	a_index = 0
	b_index = 0
	merge = ''

	for which in order:
		if which == 1:
			merge = merge + a[a_index].upper()
			a_index = a_index + 1
		else:
			merge = merge + b[b_index]
			b_index = b_index + 1

	return merge

def screw_up(merge):
	merge = list(merge)
	indices = random.sample(range(len(merge)), k=random.choice(range(1, len(merge))))

	for i in indices:
		new_letter = merge[i].lower()
		while new_letter == merge[i].lower():
			new_letter = random_letter()
			if random.random() > .5:
				new_letter = new_letter.upper()
		merge[i] = new_letter

	return ''.join(merge)

# look for lowercase runs that can be pushed back and do so
def shove_runs(merge):
	# I *know* -- this is not efficient... but it's fast enough!
	for _ in range(len(merge)):
		i = 0
		while i < len(merge):
			j = len(merge) - i
			while j > 0:
				run = merge[i:(i + j)]
				next_sect = merge[(i + j):(i + 2*j)]
				if run.islower() and next_sect.isupper() and run == next_sect.lower():
					# swap the two
					merge = f'{merge[:i]}{next_sect}{run}{merge[(i + 2*j):]}'
				j = j - 1
			i = i + 1

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
			merge = random_merge(a, b)
			expected_out = shove_runs(merge)

			is_error = random.random() < ERROR_RATE
			if is_error:
				merge = screw_up(merge)
				expected_out = '*** NOT A MERGE ***'

			infile.write(f'{a}\n{b}\n{merge.lower()}\n')
			outfile.write(f'{expected_out}\n')
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
