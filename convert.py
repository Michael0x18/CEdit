# (c) commandblockguy

import png, os
from itertools import zip_longest

def grouper(n, iterable, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(fillvalue=fillvalue, *args)

f=open('cursor.png', 'rb')
r = png.Reader(file=f)
i = r.read()[2]
val = 0
length = 0
out = bytearray()
for row in i:
   for r,g,b,a in grouper(4, row):
      if a == 0:
         bits = 0b10
      elif (r,g,b)==(0,0,0):
         bits = 0b00
      elif (r,g,b)==(255,255,255):
         bits = 0b01
      else:
         bits = 0b11

      val = val << 2 | bits
      length += 2
      if length == 8:
         out.append(val)
         length = 0
         val = 0

outfile = open('cursor.bin', 'wb')
outfile.write(out)
outfile.close()

os.system('xxd -i cursor.bin > cursor.c')
