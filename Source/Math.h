#ifndef MATH_H
#define MATH_H



static const double PI = 3.141592654;
static const double TWOPI = 6.283185307;
static const int HILBERT_DIVISIONS = 16;


 
//rotate/flip a quadrant appropriately
static void hilbert_rotate(int n, int *x, int *y, int rx, int ry)
{
    if (ry == 0)
    {
        if (rx == 1)
        {
            *x = n-1 - *x;
            *y = n-1 - *y;
        }
 
        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}

static int xy_to_hilbert(int x, int y, int n = HILBERT_DIVISIONS)
{
    int rx, ry, s, d= 0;

    for (s = n / 2; s > 0; s /= 2)
    {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        hilbert_rotate(s, &x, &y, rx, ry);
    }

    return d;
}
 
//convert d to (x,y)
static void hilbert_to_xy(int n, int d, int *x, int *y)
{
    int rx, ry, s, t=d;

    *x = *y = 0;

    for (s = 1; s < n; s *= 2)
    {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        hilbert_rotate(s, x, y, rx, ry);
        *x += s * rx;
        *y += s * ry;
        t /= 4;
    }
}



#endif