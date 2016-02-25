from pylab import *
import numpy
def main():
    import matplotlib.pyplot 
    print(1)
    a=[3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 19,20]
    b=numpy.array([0.1214, 0.1569, 0.2131, 0.3056, 0.4231, 0.5627, 0.6972, 0.8, 0.865, 0.924, 0.967, 0.978, 0.983, 0.993, 0.677, 1, 0.999, 1])
    plot (a,b,'ro')
    show()
    import time
    time.sleep(500000)
if __name__ == '__main__':
	main()