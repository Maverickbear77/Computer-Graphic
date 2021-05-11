/***************************************************************************************************************************
*
* Name: Shading.h
* Author: Changxuan Zhao
* Date: Oct 26, 2020
* Purpose: This module is to calculate shading values for each intersection point.
*
****************************************************************************************************************************/

#include "Intersection.h"
#ifndef Shading_h
#define Shading_h

int shading(const float P[3], const float N[3], float kd)
{
    float L[3] = {0.0};
    int C;
    L[0] = LRP[0] - P[0];
    L[1] = LRP[1] - P[1];
    L[2] = LRP[2] - P[2];
    unit_vector(L);
    
	//If the dot product of N and L vectors is a negative value, set it to zero
    if (dot_product(N, L) < 0)
    {
        C = 0;
    }
    else
    {
        C = Ip * kd * dot_product(N, L);
		//If shading value is greater than 255, set it to 255
        if (C > 255)
        {
            C = 255;
        }
		//If shading value is less than one, set it to one
        if (C < 1)
        {
            C = 1;
        }
    }
    
    return C;
}

#endif /* Shading_h */
