/***********************************************************************************************
*
* Name: Volume.h
* Author: Changxuan Zhao
* Date: Nov 23, 2020
* Purpose: This module is to implement volume ray tracing.
*
************************************************************************************************/

#include "Intersection.h"
#ifndef Volume_h
#define Volume_h


float trilinear_interpolation (const unsigned char A[SLCS][ROWS][COLS], float P[3])
{
    float result = 0;
    
    int x1, y1, z1, x2, y2, z2;
    float dx, dy, dz;
    x1 = floor(P[0]);
    y1 = floor(P[1]);
    z1 = floor(P[2]);
    x2 = x1 + 1;
    y2 = y1 + 1;
    z2 = z1 + 1;

    dx = P[0] - x1;
    dy = P[1] - y1;
    dz = P[2] - z1;

    result = A[z1][y1][x1]*(1.0-dz)*(1.0-dy)*(1.0-dx) +
             A[z1][y1][x2]*(1.0-dz)*(1.0-dy)*(dx)  +
             A[z1][y2][x1]*(1.0-dz)*(dy)*(1.0-dx)  +
             A[z1][y2][x2]*(1.0-dz)*(dy)*(dx)   +
             A[z2][y1][x1]*(dz)*(1.0-dy)*(1.0-dx)  +
             A[z2][y1][x2]*(dz)*(1.0-dy)*(dx)   +
             A[z2][y2][x1]*(dz)*(dy)*(1.0-dx)   +
             A[z2][y1][x2]*(dz)*(dy)*(dx)   ;
    
    return result;
}

int volume_ray_tracing(float V0[3], float ts[2])
{
	float C = 0.0, T = 1.0, Dt = 1.0, fv = (101.0 + 255.0) / 2.0;
    
    for (float t = ts[0]; t <= ts[1]; t += Dt)
    {
        float P[3] = {0.0};
		//Calculate point
		P[0] = VRP[0] + V0[0] * t;
		P[1] = VRP[1] + V0[1] * t;
		P[2] = VRP[2] + V0[2] * t;
        
		//Get density value
        float a = trilinear_interpolation(CT, P);
		//Get shading value
        float c = trilinear_interpolation(SHADING, P);

		//Select bone only
		//Apply simple classification
		if (a >= 101 && a <= 255)
		{
			if (a == fv)
			{
				a = 1.0;
			}
			else if (a < fv)
			{
				a = (a - 101.0) * 1.0 / (fv - 101.0);
			}
			else
			{
				a = 1.0 - (a - fv) * 1.0 / (255.0 - fv);
			}
		}
		else
		{
			a = 0.0;
		}

		//Show everything, skin, bone, and tissue
		//Map density value between 0 and 1
		//a *= 1.0 / 255.0;

		//Accumulate color
		C += (T * a * c);
		//Update the accumulated transparency
		T *= (1.0 - a);
		
		//Early termination if T is very small
        if (T < 0.00001)
        {
            break;
        }
    }
    
    return C;
}

#endif /* Volume_h */
