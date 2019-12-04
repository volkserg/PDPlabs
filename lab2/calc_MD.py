import numpy as np
import math
import sys

def calculate(numbers):
	M = sum(numbers)/len(numbers)#/max(numbers)
	D = np.var(numbers)#/max(numbers)
	return (M,D)


def main():
	filename = sys.argv[1]
	mylist = []
	with open(filename,'r') as file:
		for row in file:
			mylist.append(float(row))
	M,D = calculate(np.array(mylist))
	print('M = %s'%M)
	print('D = %s'%D)

if __name__ == "__main__":
    main()
