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

#predefine
LEVEL_LENGTH = 1000
SECTION_LENGTH = LEVEL_LENGTH/5 # 5 sections, A-E, F-J, etc.

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

tileList = []
enemyList = []
boulderList = []
specialList = []

def initTiles():
    global tileList
    global enemyList
    global boulderList
    global specialList
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
    enemyList.append(moonman)
    enemyList.append(bus)
    enemyList.append(ship1)
    enemyList.append(jetman)
    enemyList.append(ship2)
    boulder1,null = load_image('boulder1.bmp',(0,255,0))
    boulder2,null = load_image('boulder2.bmp',(0,255,0))
    boulderList.append(boulder1)
    boulderList.append(boulder2)
    return tile1,tile2,tile3,tile4,tileList,pit1,pit2,pit3,moonman,jetman,ship1,ship2,bus,boulder1,boulder2

def defaultSaveLevel(name):
    levelFile = open(name, 'wb')
    levelFile.write(struct.pack('d',LEVEL_LENGTH)) # load A-E
    levelFile.write(struct.pack('c',name[0]))
    levelFile.write(struct.pack('c',chr(0)))
    for i in range(2500):
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
        levelFile.write(struct.pack('c',chr(0)))
    levelFile.close()
    print "Finished saving DEFAULT level " + name

def saveLevel(name,length,bg,tiles,boulders,enemies,special):
    '''This function takes in the name of the level,
        the length of the level, the background,
        and a set of arrays in this order:
        sky, ground, tiles, special. 
    '''
    if len(name) > 0:
        levelFile = open(name, 'wb')
        levelFile.write(struct.pack('d',length)) # unsigned int
        levelFile.write(struct.pack('c',name[0]))
        levelFile.write(struct.pack('c',bg))
        for i in range(length):
            levelFile.write(struct.pack('c',tiles[i]))
            levelFile.write(struct.pack('c',boulders[i]))
            levelFile.write(struct.pack('c',enemies[i]))
            levelFile.write(struct.pack('c',special[i]))
        levelFile.close()
        print "Finished saving level " + name
    else:
        print "Could not save " + name
        print "Invalid file name.."

def loadLevel(name):
    '''This function takes in a name, and returns all the
        appropriate structures.
    '''
    if len(name) > 0:
        if not os.path.exists(name):
            print "Creating a default save level for %s"%(name)
            defaultSaveLevel(name)
        levelFile = open(name, 'rb')
        charSize = struct.calcsize('c')
        dblSize = struct.calcsize('d')
        length = int(struct.unpack('d',levelFile.read(dblSize))[0])
        tmpName = struct.unpack('c',levelFile.read(charSize))[0]
        bg = struct.unpack('c',levelFile.read(charSize))[0]
        tiles = []
        boulders = []
        enemies = []
        special = []        
        for i in range(length):
            tiles.append(struct.unpack('c',levelFile.read(charSize))[0])
            boulders.append(struct.unpack('c',levelFile.read(charSize))[0])
            enemies.append(struct.unpack('c',levelFile.read(charSize))[0])
            special.append(struct.unpack('c',levelFile.read(charSize))[0])
        return (length,bg,tiles,boulders,enemies,special)
    else:
        print "Could not load " + name
        print "Invalid file name..."
        return (0,0,0,0,0,0)

def addTileUp(mousePos,xOff,cTiles, maxLen):
    mx,my = mousePos
    mx += xOff
    ox = int(mx/32)
    tile = ord(cTiles[ox]) + 1
    if (tile == maxLen):
        tile = 0
    cTiles[ox] = chr(tile)

def nextLevel(name):
    if name == 'ae':
        name = 'fj'
    elif name == 'fj':
        name = 'ko'
    elif name == 'ko':
        name = 'pt'
    elif name == 'pt':
        name = 'uy'
    return name

def prevLevel(name):
    if name == 'fj':
        name = 'ae'
    elif name == 'ko':
        name = 'fj'
    elif name == 'pt':
        name = 'ko'
    elif name == 'uy':
        name = 'pt'
    return name

def drawText(screen, name, layer, xOffset):
    #Put Text On The Background, Centered
    if pygame.font:
        font = pygame.font.Font(None, 14)
        text = font.render("Moon Patrol Editor 0.1", 1, (255, 255, 255))
        nameText = font.render("Level: "+name, 1, (255, 0, 0))
        layerText = font.render("Layer: "+layer, 1, (255, 128, 0))
        xTile = font.render("X Tile: " + str(xOffset/32), 1, (255, 200, 160))
        xOffsetText = font.render("X Offset: "+str(xOffset), 1, (255, 255, 128))

        screen.blit(text, (0,0))
        screen.blit(nameText,(0,12))
        screen.blit(layerText,(0,24))
        screen.blit(xTile, (0, 36))
        screen.blit(xOffsetText,(0,48))

        # check to see if we should show A, B, C, D, E, etc..
        xTileOff = (xOffset/32)
        if ((xTileOff % SECTION_LENGTH ) ==  0):
            displayChar = chr(ord(name[0]) + (xTileOff/SECTION_LENGTH))
            letterText = font.render(displayChar, 1, (255, 255, 255))
            screen.blit(letterText, (5, 168))
        elif ((xTileOff % SECTION_LENGTH ) > SECTION_LENGTH-8):
            xOff = SECTION_LENGTH - (xTileOff % SECTION_LENGTH)
            displayChar = chr(ord(name[0]) + (xTileOff+(xOff))/SECTION_LENGTH)
            letterText = font.render(displayChar, 1, (255, 255, 255))
            screen.blit(letterText, (xOff*32+5, 168))
        
def drawLevel(screen,bgImage,tiles,boulders,enemies,special,xOffset):
    global tileList
    global enemyList
    global boulderList
    global specialList
    screen.blit(bgImage,(0,0))
    # lets draw the tiles first
    xGrid = int(xOffset/32)
    for idx in range(xGrid,xGrid+8):
        value = ord(tiles[idx])
        screen.blit(tileList[value],((idx-xGrid)*32,128))
        value = ord(boulders[idx])
        if ( value == 1 ): # first boulder
            screen.blit(boulderList[value-1],((idx-xGrid)*32,112))
        elif ( value == 2 ): # second boulder
            screen.blit(boulderList[value-1],((idx-xGrid)*32,128))
        value = ord(enemies[idx])
        if ( value == 1 ): # running man
            screen.blit(enemyList[value-1],((idx-xGrid)*32,128))
        elif ( value == 2 ): # bus
            screen.blit(enemyList[value-1],((idx-xGrid)*32,118))
        elif ( value == 3 ): # ship 1
            screen.blit(enemyList[value-1],((idx-xGrid)*32,20))
        elif ( value == 4 ): # jet man
            screen.blit(enemyList[value-1],((idx-xGrid)*32,20))
        elif ( value == 5 ): # saucer
            screen.blit(enemyList[value-1],((idx-xGrid)*32,20))
        # eventually print the special stuff

def main():
    """this function is called when the program starts.
       it initializes everything it needs, then runs in
       a loop until the function returns."""
#Initialize Everything
    pygame.init()
    screen = pygame.display.set_mode((256, 192))
    pygame.display.set_caption('UV Moon Patrol Level Editor')
    pygame.mouse.set_visible(1)

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
    fileName = 'ae'
    length, bg, tiles, boulders, enemies, special = loadLevel(fileName)

#names
    layerNames = [ "Ground Type", "Boulders", "Enemies", "Non-Interactive"]
    tileNames = [ "tile1", "tile2", "tile3", "tile4", "pit1", "pit2", "pit3"]
    boulderNames = [ "boulder1","boulder2" ]
    enemyNames = ["Running Man", "Bus", "Ship", "Jet Man", "Saucer" ]
    specialNames = ["base", "burning house"]
    cLayer = 0
    cTile = 0

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

#        31 - 24          23 - 16      15 - 8         7 - 0
# [  Non-Interactive  ] [ Enemies ] [ Boulders ] [ Layer Type ]

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
                    saveLevel(fileName, length, bg, tiles, boulders, enemies, special )
                elif event.key == K_PAGEDOWN:
                    tmp = fileName
                    fileName = nextLevel(fileName)
                    if tmp != fileName:
                        print "Moved to level " + fileName
                        length,bg,sky,ground,tiles,special = loadLevel(fileName)
                    cLayer = cTile = xOffset = 0
                elif event.key == K_PAGEUP:
                    tmp = fileName
                    fileName = prevLevel(fileName)
                    if tmp != fileName:
                        print "Moved to level " + fileName
                        length,bg,sky,ground,tiles,special = loadLevel(fileName)
                    cLayer = cTile = xOffset = 0
                elif event.key == K_RIGHT:
                    if xOffset < ((length-8)*32):
                        xOffset += 32
                elif event.key == K_LEFT:
                    if xOffset > 0:
                        xOffset -= 32
                elif event.key == K_UP:
                    cLayer -= 1                    
                    if cLayer < 0:
                        cLayer = 2
                elif event.key == K_DOWN:
                    cLayer += 1                    
                    if cLayer > 2:
                        cLayer = 0
                elif event.key == ord('g'):
                    displayGrid = not displayGrid
            elif event.type == MOUSEBUTTONDOWN:
                #print "Mouse Down!"
                pass
            elif event.type is MOUSEBUTTONUP:
                if ( cLayer == 0 ):
                    addTileUp(pygame.mouse.get_pos(),xOffset,tiles, len(tileNames))
                elif ( cLayer == 1 ):
                    addTileUp(pygame.mouse.get_pos(),xOffset,boulders, len(boulderNames)+1)
                elif ( cLayer == 2 ):
                    addTileUp(pygame.mouse.get_pos(),xOffset,enemies, len(enemyNames)+1)
                elif ( cLayer == 3 ):
                    addTileUp(pygame.mouse.get_pos(),xOffset,special, len(specialNames)+1)

        allsprites.update()

    #Draw Everything
        screen.blit(background, (0, 0))
        drawLevel(screen,bgImage,tiles,boulders,enemies,special,xOffset)
        allsprites.draw(screen)
        if displayGrid == True:
            screen.blit(gridImage, (0,0))
        if ( cLayer == 0 ):
            drawText(screen, fileName, layerNames[cLayer], xOffset)
        elif ( cLayer == 1 ):
            drawText(screen, fileName, layerNames[cLayer], xOffset)
        elif ( cLayer == 2 ):
            drawText(screen, fileName, layerNames[cLayer], xOffset)
        elif ( cLayer == 3 ):
            drawText(screen, fileName, layerNames[cLayer], xOffset)
        pygame.display.flip()
#Game Over

#this calls the 'main' function when this script is executed
if __name__ == '__main__': main()
