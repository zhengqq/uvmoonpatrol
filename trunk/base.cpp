#include "base.h"

//Helper function, takes the first & second rectangles (x,y,width,height) and finds
// if they are currently inside of each other or not
// Help from ilikecake and http://www.gamedev.net/reference/articles/article735.asp
BOOL rectCollision(int r1x,int r1y,int r1w,int r1h,int r2x,int r2y,int r2w,int r2h)
{
    if ( (r1y + r1h) < (r2y) ) return FALSE;
    if ( (r1y) > (r2y+r2h) ) return FALSE;

    if ( (r1x+r1w) < (r2x) ) return FALSE;
    if ( (r1x) > (r2x+r2w) ) return FALSE;

    return TRUE;
}
