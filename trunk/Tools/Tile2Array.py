#usr/bin/env python

import Image
import sys
import os

FALSE = 0
TRUE = 1
tileName="tile4.bmp"

def main():
    """ Wooo """
    im = Image.open(tileName)
    outFile = open(os.path.splitext(tileName)[0]+".h","w")
    outFile.write("BOOL " + os.path.splitext(tileName)[0] + " = {\n")
    for y in range(0,64):
        outFile.write("\t");
        for x in range(0,32):
            pixel = im.getpixel((x,y))
            if ( pixel[0] == 0 and pixel[1] == 255 and pixel[2] == 0 ):
                outFile.write(str(FALSE)+",")
            else:
                outFile.write(str(TRUE)+",")
        outFile.write("\n")
    outFile.write("};")
    outFile.close()

if __name__ == '__main__': main()
