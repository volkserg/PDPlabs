import numpy as np
import math
from matplotlib import pyplot as plt
import sys

def calculate(numbers):
	M = sum(numbers)/len(numbers)/max(numbers)
	D = math.sqrt(M)
	return (M,D)


def main():
	filename = sys.argv[1]
	mylist = []
	with open(filename,'r') as file:
		for row in file:
			mylist.append(int(row))
	M,D = calculate(mylist)
	print('M = %s'%M)
	print('D = %s'%D)

if __name__ == "__main__":
    main()
