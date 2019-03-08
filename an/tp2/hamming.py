import math
import numpy as np

def hamming(l=1024):
    w = []
    for i in range(0,l):
        w+= [.54 - .46*math.cos(2*math.pi*i/(l-1))]
    w = np.array(w)
    return w

