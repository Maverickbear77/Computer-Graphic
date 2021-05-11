/***********************************************************************************************
*
* Name: Shading.h
* Author: Changxuan Zhao
* Date: Nov 23, 2020
* Purpose: This module is to calculate shading value at each voxel.
*
************************************************************************************************/

#include "Rays.h"
#ifndef Shading_h
#define Shading_h

//Calculation for dot product
float dot_product(const float v1[3], const float v2[3])
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

void compute_shading_volume ()
{
    for (int z = 1; z < (LAYS - 1); z++)
    {
        for (int y = 1; y < (ROWS - 1); y++)
        {
            for (int x = 1; x < (COLS - 1); x++)
            {
				float N[3] = {0.0};

				//Find normal vector
				N[0] = 0.5 * (CT[z][y][x+1] - CT[z][y][x-1]);
				N[1] = 0.5 * (CT[z][y+1][x] - CT[z][y-1][x]);
				N[2] = 0.5 * (CT[z+1][y][x] - CT[z-1][y][x]);

				//Check the magnitude of the gradient
				if (sqrt(N[0]*N[0]+N[1]*N[1]+N[2]*N[2]) < 0.00001)
				{
					SHADING[z][y][x] = 0;
				}
				else 
				{
					unit_vector(N);
					
					//Calculate shading
					SHADING[z][y][x] = Ip * 0.75 * dot_product(N, Light);

					//If shading is less than 0, set it to 0
					if (SHADING[z][y][x] < 0)
					{
						SHADING[z][y][x] = 0;
					}	
				}
            }
        }
    }
    
    return;
}
#endif /* Shading_h */
