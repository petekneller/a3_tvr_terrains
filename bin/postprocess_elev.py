#! /bin/env python

# Converts terrain elevation from the format exported from Arma into the format required by TV
# Reads stdin and writes stdout

import sys

for line in sys.stdin:
    values = line.split(',')
    try:
        h = int(round(float(values[2]) + 1000))
        sys.stdout.buffer.write(h.to_bytes(2, 'little', signed=True))
    except Exception as ex:
        print("Line [{}]:, exception: ".format(line, ex), file=sys.stderr)
