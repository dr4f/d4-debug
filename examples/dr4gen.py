from __future__ import print_function
import sys
import struct

"""
Allows easy generation of test DR4 documents
"""
# Length of generated row
ROW_LENGTH = 5
ROW_AMOUNT = 10
# Some sample dr4 types
DR4_TYPE_STOP = 0
DR4_TYPE_BOOL = 2

DEF_SIZER = 8


class Dr4Header(object):
	"""
	Writes the header for the document.
	"""
	def __init__(self, sizer=32):
		self.sizer = sizer
		self.version = (1, 0, 0)
		self.magic = (83, 94, 121)
		if sizer not in (8, 16, 32):
			raise ValueError("Invalid sizer chosen:" + str(sizer))

	def __repr__(self):
		return struct.pack('bbbbbbbb', 
			                self.magic[0],
			                self.magic[1],
			                self.magic[2],
			                self.version[0],
			                self.version[1],
			                self.version[2],
			                self.sizer,
			                0)

def make_data(amount):
	# Generates a tuple of the data to pack into the row body
	# Always adds the stop byte
	rdx_func = lambda a, b: a + b
	return reduce(rdx_func, [(2, 1) for x in range(amount)]) + (DR4_TYPE_STOP,)

def make_offset_data(amount):
	# makes offsets for bools, 
	return [x for x in range(amount * 2) if x % 2 == 0]

def make_row(sizer, length=ROW_LENGTH):
	# Always uses the bool type 
	data_fmt = 'B' * (1 + length * 2)
	data_gend = make_data(length)
	data_bytes = struct.pack(data_fmt, *data_gend)
	offset_bytes = make_offset_data(length)
	if sizer == 8:
		base_fmt = 'B' * (length + 1)
		base_data = [length] + offset_bytes
		base_bytes = struct.pack(base_fmt, *base_data)
		return struct.pack('B', len(base_bytes)) + base_bytes
	elif sizer == 16:
		base_fmt = 'H' * (length + 1)
		base_data = [length] + offset_bytes
		base_bytes = struct.pack(base_fmt, *base_data)
		return struct.pack('H', len(base_bytes)) + base_bytes
	elif sizer == 32:
		base_fmt = 'I' * (length + 1)
		base_data = [length] + offset_bytes
		base_bytes = struct.pack(base_fmt, *base_data)
		return struct.pack('I', len(base_bytes)) + base_bytes
	else:
		raise ValueError("Invalid sizer chosen:" + str(sizer))

class Dr4Body(object):

	def __init__(self, sizer=32, amount=ROW_AMOUNT, row_length=ROW_LENGTH):
		self.sizer = sizer
		if sizer not in (8, 16, 32):
			raise ValueError("Invalid sizer chosen:" + str(sizer))
		self.amount = amount
		self.row_length = row_length

	def __len__(self):
		return self.row_length

	def __repr__(self):
		return ''.join([make_row(self.sizer, self.row_length) for i in range(self.amount)])

class Dr4Doc(object):

	def __init__(self, sizer):
		self.head = Dr4Header(sizer)
		self.body = Dr4Body(sizer)

	def __repr__(self):
		return str(self.head) + str(self.body)


if __name__ == '__main__':
	user_args = sys.argv[1:]
	if len(user_args) < 1:
		print("Argument Error: Need name of target file as argument.")
		sys.exit(2)
	target_file = open(user_args[0], 'wb')
	gen_dr4 = str(Dr4Doc(DEF_SIZER))
	print("Generated the dr4 doc: " + gen_dr4)
	target_file.write(gen_dr4)
	target_file.close()
	print("Wrote a generated dr4 document to path:" + user_args[0])
