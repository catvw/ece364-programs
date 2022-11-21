import random
import string

MERGES = 20
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
	new_letter = merge[i]
	while new_letter == merge[i]:
		new_letter = random_letter()
	merge[i] = new_letter

	return ''.join(merge)

random.seed()
with open('ref/fuzz_in', 'w') as infile, open('ref/fuzz_out', 'w') as outfile:
	for _ in range(MERGES):
		a = gen_string(LENGTH)
		b = gen_string(LENGTH)
		merge = random_merge(a, b)
		expected_out = merge

		is_error = random.random() < ERROR_RATE
		if is_error:
			merge = screw_up(merge)
			expected_out = '*** NOT A MERGE ***'

		infile.write(f'{a}\n{b}\n{merge.lower()}\n')
		outfile.write(f'{expected_out}\n')
