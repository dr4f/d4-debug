from __future__ import print_function
import sys
import struct

"""
Allows easy generation of test DR4 documents
"""



if __name__ == '__main__':
	user_args = sys.argv[1:]
	if len(user_args) < 1:
		print("Argument Error: Need name of target file as argument.")
		sys.exit(2)
	target_file = open(user_args[0], 'wb')
	target_file.write(struct.pack('bb', 66, 66))
	target_file.close()
	print("Wrote a generated dr4 document to path:" + user_args[0])
