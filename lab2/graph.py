import numpy as np
import math
from matplotlib import pyplot as plt
import sys

def histogram(numbers): 
	data = numbers 
	plt.hist(data, bins=1000, density=True, histtype='step')
	plt.title('Распределение для '+str(len(data))+' чисел')
	plt.xlabel('Значение')
	plt.ylabel('Количество')

	plt.show() 


def main():
    filename = sys.argv[1]
    mylist = []
    with open(filename,'r') as file:
        for row in file:
            mylist.append(float(row))
    histogram(mylist)

if __name__ == "__main__":
    main()
