#!/usr/bin/env python
"""

Implement the following routine:

	Integer invm(Integer, Integer)

such that invm(m, a) computes the inverse of a modulo m.
- Note that this routine will not always produce a result.
- If your programming language supports exceptions, 
then you should throw an exception if the inverse of a modulo m does not exist.
"""

import p2_egcd

def invm(m, a):
	g, x, y = p2_egcd.egcd(a, m)
	if g != 1:
		return None  # modular inverse does not exist
	else:
		return x % m

#####################################################################
# Tests
	
if __name__ == "__main__":
	print "Practical 3"
	print invm(42, 56)
	print invm(23, 67)	
	print invm(48, 180)
	print invm(48, 18)
	print invm(7, 3)
	print invm(3120, 17)
	print invm(216, 37)
	print invm(3, 7373)

	print "Done."