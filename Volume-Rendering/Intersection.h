/***********************************************************************************************
*
* Name: Intersection.h
* Author: Changxuan Zhao
* Date: Nov 23, 2020
* Purpose: This module is to check intersection points between ray and each side of CT cube.
*
************************************************************************************************/

#include "Shading.h"
#ifndef Intersection_h
#define Intersection_h

int ray_box_intersection (float P0[3], float V0[3], float ts[3])
{
    int n = 0;
    
    for (int i = 0; i < 6; i++)
    {
        float t;
        if (i % 3 == 0)
        {
            int y, z;
			//x = 0
            if (i < 3)
            {
                t = -P0[0] / V0[0];
                y = P0[1] + V0[1] * t;
                z = P0[2] + V0[2] * t;
                if (y > 0 && y < ROWS - 1 && z > 0 && z < SLCS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
			//x = 127
            else
            {
                t = (127 - P0[0]) / V0[0];
                y = P0[1] + V0[1] * t;
                z = P0[2] + V0[2] * t;
                if (y > 0 && y < ROWS - 1 && z > 0 && z < SLCS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
        }
        else if (i % 3 == 1)
        {
            int x, z;
			//y = 0
            if (i < 3)
            {
                t = -P0[1] / V0[1];
                x = P0[0] + V0[0] * t;
                z = P0[2] + V0[2] * t;
                if (x > 0 && x < COLS - 1 && z > 0 && z < SLCS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
			//y = 127
            else
            {
                t = (127 - P0[1]) / V0[1];
                x = P0[0] + V0[0] * t;
                z = P0[2] + V0[2] * t;
                if (x > 0 && x < COLS - 1 && z > 0 && z < SLCS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
        }
        else
        {
            int x, y;
			//z = 0
            if (i < 3)
            {
                t = -P0[2] / V0[2];
                x = P0[0] + V0[0] * t;
                y = P0[1] + V0[1] * t;
                if (x > 0 && x < COLS - 1 && y > 0 && y < ROWS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
			//z = 127
            else
            {
                t = (127 - P0[2]) / V0[2];
                x = P0[0] + V0[0] * t;
                y = P0[1] + V0[1] * t;
                if (x > 0 && x < COLS - 1 && y > 0 && y < ROWS - 1)
                {
                    ts[n] = t;
                    n++;
                }
            }
        }
    }
    
	//If there are more than two intersection points, ignore this ray
    if (n > 2)
    {
        n = 0;
    }
    
    if (n == 2)
    {
		//Swap ts[0] and ts[1] if ts[0] is greater than ts[1]
        if (ts[0] > ts[1])
        {
            float temp = ts[0];
            ts[0] = ts[1];
            ts[1] = temp;
        }
    }
    
    return n;
}

#endif /* Intersection_h */
