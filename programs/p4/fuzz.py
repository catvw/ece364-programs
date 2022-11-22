import random
import string

MERGES = 1000
LENGTH = 5
ERROR_RATE = .1

order = [1 for _ in range(LENGTH)] + [0 for _ in range(LENGTH)]

def random_letter():
	return random.choice(string.ascii_lowercase)

def gen_string(length):
	return ''.join(random_letter() for _ in range(length))

def random_merge(a, b):
	global order

	a_index = 0
	b_index = 0
	merge = ''

	random.shuffle(order)
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

	i = random.choice(range(LENGTH))
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
		for _ in range(MERGES):
			a = gen_string(LENGTH)
			b = gen_string(LENGTH)
			merge = random_merge(a, b)
			expected_out = shove_runs(merge)

			is_error = random.random() < ERROR_RATE
			if is_error:
				merge = screw_up(merge)
				expected_out = '*** NOT A MERGE ***'

			infile.write(f'{a}\n{b}\n{merge.lower()}\n')
			outfile.write(f'{expected_out}\n')
