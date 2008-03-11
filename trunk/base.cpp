#include "base.h"

//Helper function, takes the first & second rectangles (x,y,width,height) and finds
// if they are currently inside of each other or not
BOOL rectCollision(int r1x,int r1y,int r1w,int r1h,int r2x,int r2y,int r2w,int r2h)
{
    // top-left point
    if ( r1x < r2x && r2x < r1x+r1w && r1y < r2y && r2y < r1y+r1h )
    {
        return true;
    }
    // bottom-left point
    else if ( r1x < r2x && r2x < r1x+r1w && r1y < r2y+r2h && r2y+r2h < r1y+r1h )
    {
        return true;
    }
    // top-right point
    else if ( r1x < r2x+r2w && r2x+r2w < r1x+r1w && r1y < r2y && r2y < r1y+r1h )
    {
        return true;
    }
    // bottom-right point
    else if ( r1x < r2x+r2w && r2x+r2w < r1x+r1w && r1y < r2y+r2h && r2y+r2h < r1y+r1h )
    {
        return true;
    }
    return false;
}
