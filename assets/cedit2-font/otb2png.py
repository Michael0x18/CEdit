#!/usr/bin/python
# Convert otb font to format used by CEdit

from PIL import Image, ImageDraw, ImageFont

font = ImageFont.truetype("Bm437_IBM_EGA_9x14.otb", 16, encoding='utf-8')
image = Image.new("RGB", (8*16, 16*8), "white")
draw = ImageDraw.Draw(image)

for i in range(0,8):
    #column
    for j in range(0,16):
        #row
        w,h = font.getoffset(chr(i*16+j))
        pos = (j*8,i*16)
        draw.text(pos, chr(i*16+j), "black", font=font)

# Save png file
image.save("CEdit_Font.png")
