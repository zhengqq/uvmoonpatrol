#/usr/bin/env python
"""
This simple example is used for the line-by-line tutorial
that comes with pygame. It is based on a 'popular' web banner.
Note there are comments here, but for the full explanation, 
follow along in the tutorial.
"""


#Import Modules
import os, pygame, struct
from pygame.locals import *

if not pygame.font: print 'Warning, fonts disabled'
if not pygame.mixer: print 'Warning, sound disabled'

#functions to create our resources
def load_image(name, colorkey=None):
    fullname = os.path.join('data', name)
    try:
        image = pygame.image.load(fullname)
    except pygame.error, message:
        print 'Cannot load image:', fullname
        raise SystemExit, message
    image = image.convert()
    if colorkey is not None:
        if colorkey is -1:
            colorkey = image.get_at((0,0))
        image.set_colorkey(colorkey, RLEACCEL)
    return image, image.get_rect()

def load_sound(name):
    class NoneSound:
        def play(self): pass
    if not pygame.mixer or not pygame.mixer.get_init():
        return NoneSound()
    fullname = os.path.join('data', name)
    try:
        sound = pygame.mixer.Sound(fullname)
    except pygame.error, message:
        print 'Cannot load sound:', fullname
        raise SystemExit, message
    return sound

def initTiles():
    tileList = []
    tile1,null = load_image('tile1.bmp',(0,255,0))
    tile2,null = load_image('tile2.bmp',(0,255,0))
    tile3,null = load_image('tile3.bmp',(0,255,0))
    tile4,null = load_image('tile4.bmp',(0,255,0))
    pit1,null = load_image('pitfall1.bmp',(0,255,0))
    pit2,null = load_image('pitfall2.bmp',(0,255,0))
    pit3,null = load_image('pitfall3.bmp',(0,255,0))
    tileList.append(tile1)
    tileList.append(tile2)
    tileList.append(tile3)
    tileList.append(tile4)
    tileList.append(pit1)
    tileList.append(pit2)
    tileList.append(pit3)
    moonman,null = load_image('running1_1.bmp',(0,255,0))
    jetman,null = load_image('flyingman.bmp',(0,255,0))
    ship1,null = load_image('ship.bmp',(0,255,0))
    ship2,null = load_image('trianglesaucer.bmp',(0,255,0))
    bus,null = load_image('bus1_1.bmp',(0,255,0))
    boulder1,null = load_image('boulder1.bmp',(0,255,0))
    boulder2,null = load_image('boulder2.bmp',(0,255,0))
    return tile1,tile2,tile3,tile4,tileList,pit1,pit2,pit3,moonman,jetman,ship1,ship2,bus,boulder1,boulder2

def defaultSaveLevel(name):
    levelFile = open(name, 'wb')
    levelFile.write(struct.pack('d',500)) # unsigned int
    levelFile.write(struct.pack('c',name))
    levelFile.write(struct.pack('c',chr(0)))
    for i in range(500):
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
    levelFile.close()
    print "Finished saving DEFAULT level " + name

def saveLevel(name,length,bg,sky,ground,tiles,special):
    '''This function takes in the name of the level,
        the length of the level, the background,
        and a set of arrays in this order:
        sky, ground, tiles, special. 
    '''
    if len(name) == 1:
        levelFile = open(name, 'wb')
        levelFile.write(struct.pack('d',length)) # unsigned int
        levelFile.write(struct.pack('c',name))
        levelFile.write(struct.pack('c',chr(bg)))
        for i in range(length):
            levelFile.write(struct.pack('c',chr(sky[i])))
            levelFile.write(struct.pack('c',chr(ground[i])))
            levelFile.write(struct.pack('c',chr(tiles[i])))
            levelFile.write(struct.pack('c',chr(special[i])))
        levelFile.close()
        print "Finished saving level " + name
    else:
        print "Could not save " + name
        print "Invalid file name.."

def loadLevel(name):
    '''This function takes in a name, and returns all the
        appropriate structures.
    '''
    if len(name) == 1:
        if not os.path.exists(name):
            defaultSaveLevel(name)
        levelFile = open(name, 'rb')
        charSize = struct.calcsize('c')
        dblSize = struct.calcsize('d')
        length = int(struct.unpack('d',levelFile.read(dblSize))[0])
        tmpName = struct.unpack('c',levelFile.read(charSize))[0]
        bg = struct.unpack('c',levelFile.read(charSize))[0]
        sky = []
        ground = []
        tiles = []
        special = []        
        for i in range(length):
            sky.append(struct.unpack('c',levelFile.read(charSize))[0])
            ground.append(struct.unpack('c',levelFile.read(charSize))[0])
            tiles.append(struct.unpack('c',levelFile.read(charSize))[0])
            special.append(struct.unpack('c',levelFile.read(charSize))[0])
        return (length,bg,sky,ground,tiles,special)
    else:
        print "Could not load " + name
        print "Invalid file name..."
        return (0,0,0,0,0,0)

def nextLevel(name):
    if name < 'z':
        name = chr(ord(name) + 1)
    return name

def prevLevel(name):
    if name > 'a':
        name = chr(ord(name) - 1)
    return name

def drawText(screen, name, layer, tile, xOffset):
    #Put Text On The Background, Centered
    if pygame.font:
        font = pygame.font.Font(None, 14)
        text = font.render("Moon Patrol Editor 0.1", 1, (255, 255, 255))
        
        nameText = font.render("Level: "+name, 1, (255, 0, 0))
        layerText = font.render("Layer: "+layer, 1, (255, 128, 0))
        tileText = font.render("Tile: "+tile, 1, (255, 255, 0))
        xOffsetText = font.render("X Offset: "+str(xOffset), 1, (255, 255, 128))

        screen.blit(text, (0,0))
        screen.blit(nameText,(0,12))
        screen.blit(layerText,(0,24))
        screen.blit(tileText,(0,36))
        screen.blit(xOffsetText,(0,48))

def drawLevel(screen,bgImage,sky,ground,tiles,special,xOffset,tile1,tile2,tile3,tile4,tileList,pit1,pit2,pit3,moonman,jetman,ship1,ship2,bus,boulder1,boulder2):
    screen.blit(bgImage,(0,0))
    # lets draw the tiles first
    for i in range(xOffset/32,(xOffset/32)+8):
        idx = int(i + (xOffset/32))
        value = ord(tiles[idx])
        
        screen.blit(tileList[value],(i*32,128))

def main():
    """this function is called when the program starts.
       it initializes everything it needs, then runs in
       a loop until the function returns."""
#Initialize Everything
    pygame.init()
    screen = pygame.display.set_mode((256, 192))
    pygame.display.set_caption('UV Moon Patrol Level Editor')
    pygame.mouse.set_visible(0)

#Create The Backgound
    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill((255, 255, 255))

#Display The Background
    screen.blit(background, (0, 0))
    pygame.display.flip()

#Prepare Game Objects
    clock = pygame.time.Clock()
    allsprites = pygame.sprite.RenderPlain(())

#Predefined game definitions
    fileName = 'a'
    length, bg, sky, ground, tiles, special = loadLevel(fileName)

# Init the tiles
# our global tile images
    tile1,tile2,tile3,tile4,tileList,pit1,pit2,pit3,moonman,jetman,ship1,ship2,bus,boulder1,boulder2 = initTiles()

    bgImage = pygame.Surface(screen.get_size())
    bgImage = bgImage.convert()
    bgImage.fill((255,255,255))
    if ord(bg) == 0:
        bgImage1,null = load_image('spacebg1.bmp',(0,255,0))
        bgImage2,null = load_image('farbg1.bmp',(0,255,0)) 
        bgImage3,null = load_image('closebg1.bmp',(0,255,0))
        bgImage.blit(bgImage1,(0,0))
        bgImage.blit(bgImage2,(0,0))
        bgImage.blit(bgImage3,(0,0))
    xOffset = 0 # controls for where we are on the map
    displayGrid = False
    gridImage,null = load_image('overgrid.bmp',(0,255,0))

#Lets set up some images while we are at it as well
    

# File structure will work like this:

# first 2 bytes of the file tells us how big the file actually is
# next 1 byte of the file tells us which letter we're on
# next 1 byte tells us which environment to load [0 = basic, 1 = city, 2 = valley, 3 = final, etc.]

# we have a 32-bit integer (yes?)
# so we will break this up into 4 8-byte chunks

#  31 - 24    23 - 16   15 - 8     7 - 0
# [  Sky  ] [ Ground ] [ Tile ] [ Special ]

# All files will therefore be 32-bit aligned! woot

#Main Loop
    while 1:
        clock.tick(60)

    #Handle Input Events
        for event in pygame.event.get():
            if event.type == QUIT:
                return
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    return
                elif event.key == K_RETURN:
                    saveLevel(fileName, length, bg, sky, ground, tiles, special )
                elif event.key == K_PAGEDOWN:
                    tmp = fileName
                    fileName = nextLevel(fileName)
                    if tmp != fileName:
                        print "Moved to level " + fileName
                        length,bg,sky,ground,tiles,special = loadLevel(fileName)
                elif event.key == K_PAGEUP:
                    tmp = fileName
                    fileName = prevLevel(fileName)
                    if tmp != fileName:
                        print "Moved to level " + fileName
                        length,bg,sky,ground,tiles,special = loadLevel(fileName)
                elif event.key == K_LEFT:
                    if xOffset > 0:
                        xOffset -= 1
                elif event.key == K_RIGHT:
                    if xOffset < length:
                        xOffset += 1
                elif event.key == ord('g'):
                    displayGrid = not displayGrid
            elif event.type == MOUSEBUTTONDOWN:
                print "Mouse Down!"
            elif event.type is MOUSEBUTTONUP:
                print "Mouse Up!"

        allsprites.update()

    #Draw Everything
        screen.blit(background, (0, 0))
        drawLevel(screen,bgImage,sky,ground,tiles,special,xOffset,tile1,tile2,tile3,tile4,tileList,pit1,pit2,pit3,moonman,jetman,ship1,ship2,bus,boulder1,boulder2)
        allsprites.draw(screen)
        if displayGrid == True:
            screen.blit(gridImage, (0,0))
        drawText(screen, fileName, "Ground", "Pit1", xOffset)
        pygame.display.flip()

#Game Over


#this calls the 'main' function when this script is executed
if __name__ == '__main__': main()


