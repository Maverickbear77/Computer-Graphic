/***************************************************************************************************************************
*
* Name: Rays.h
* Author: Changxuan Zhao
* Date: Oct 26, 2020
* Purpose: This module is to generate each ray based on i and j in screen coordinate and translate them to world coordinate.
*
****************************************************************************************************************************/

#include "Matrix.h"
#ifndef Rays_h
#define Rays_h

void ray_construction(int i, int j, float V0[3])
{
    float temp[4];
    temp[0] = (xmax - xmin) * (float)j / (IMG_COLS - 1) + xmin;
    temp[1] = (ymax - ymin) * (float)i / (IMG_ROWS - 1) + ymin;
    temp[2] = focal;
    temp[3] = 1.0;
    
    float position[4] = {0.0};
    
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j++)
        {
            position[i] += Mcw[i][j] * temp[j];
        }
    }
    
    
    for (int i = 0; i < 3; i++)
    {
        V0[i] = position[i] - VRP[i];
    }

	//Reverse x axis to simulate human vision system such that positive x axis is on the right and negative x axis is on the left
	V0[0] *= -1;
    
    unit_vector(V0);
    
    return;
}

#endif /* Rays_h */
