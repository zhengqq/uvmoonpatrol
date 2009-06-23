#ifndef __BASE_H__
#define __BASE_H__

#define BOOL    unsigned char
#define FALSE   0
#define TRUE    1
#define COLORKEY 0,255,0 // transparent color
#define KEY_R 0
#define KEY_G 255
#define KEY_B 0
// Physics iterations per second
#define PHYSICSFPS 30

BOOL rectCollision(int,int,int,int,int,int,int,int);

#endif // __BASE_H__
