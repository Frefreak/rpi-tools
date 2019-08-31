import struct
import sys
import argparse
from collections import namedtuple

import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('file')

Pulses = namedtuple('Pulses', ['pin', 'interval', 'length', 'data'])

PREFIX_SZ = 16

def read_file(fn):
    with open(fn, 'rb') as f:
        prefix = f.read(PREFIX_SZ)
        (pin, interval, length) = struct.unpack('<IIQ', prefix)
        data = f.read(length)
    return Pulses(pin, interval, length, data)

def main():
    args = parser.parse_args(sys.argv[1:])
    pulses = read_file(args.file)
    y = np.array(bytearray(pulses.data))
    x = range(len(y))
    #  plt.figure(figsize=(10 * len(y), 480))
    plt.step(x, y)
    plt.show()
    #  plt.savefig('test.png')



if __name__ == "__main__":
    main()
