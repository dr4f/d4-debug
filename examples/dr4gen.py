from __future__ import print_function
import sys
import struct
import random

"""
Allows easy generation of test DR4 documents
"""

ROW_LENGTH = 5


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

class Dr4Body(object):

	def __init__(self, sizer):
		self.sizer = sizer
		if sizer not in (8, 16, 32):
			raise ValueError("Invalid sizer chosen:" + str(sizer))


	def gen_row(self):
		pass

if __name__ == '__main__':
	user_args = sys.argv[1:]
	if len(user_args) < 1:
		print("Argument Error: Need name of target file as argument.")
		sys.exit(2)
	target_file = open(user_args[0], 'wb')
	target_file.write(str(Dr4Header(8)))
	target_file.close()
	print("Wrote a generated dr4 document to path:" + user_args[0])
