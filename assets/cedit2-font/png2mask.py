#!/usr/bin/python3
# Converts an image to a bitmask for use with x4 engine fonts
from PIL import Image

char_width=8
char_height=16

im = Image.open('CEdit_Font.png')
p = im.load()
chars = list()
for i in range(0,8):#row
    for j in range(0,16):#col
        #Extract a character
        a = list()
        for k in range(0,char_width):
            b = list()#list of columns - yes or no
            for l in range(0,char_height):
                if p[j*char_width+k,i*char_height+l][0]==0:
                    b.append(1)
                elif p[j*char_width+k,i*char_height+l][0]==255:
                    b.append(0)
                else:
                    b.append(0)
            a.append(b)
        chars.append(a)

#for stuff in chars:
#    for i in range(0,char_height):
#        for j in range(0,char_width):
#            print(stuff[j][i],end='')
#        print('')
#    print('')

out = list()

for c in chars:
    a = list()
    for i in range(0,char_width):
        b = list()
        for j in range(0,char_height//8):
            v=0
            for k in range(0,8):
                v+=c[i][j*8+k];
                if k != 7:
                    v = v<<1
            b.append(v)
            
            
            #v = 15 * c[i][j*2]
            #v = v<<4
            #v+=15*c[i][j*2+1];
            #b.append(v)
        a.append(b)
    out.append(a)

print('uint8_t topaz_font[128]['+str(char_width)+']['+str(char_height//2)+']={')
for c in out:
    print('{',end='')
    for i in range(0,char_width):
        print('{',end='')
        for j in range(0,char_height//8):
            print(c[i][j],end=', ')
        print('},',end='')
        if i == char_width-1:
            print('},',end='')
    print('')
print('};')

