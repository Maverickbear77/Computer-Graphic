/*********************************************************************************
*
* Name: main.cpp
* Author: Changxuan Zhao
* Date: Oct 26, 2020
* Purpose: This program is the implementation of a simple ray-tracing algorithm. 
*
**********************************************************************************/

#include "Model.h"
#include "Matrix.h"
#include "Rays.h"
#include "Intersection.h"
#include "Shading.h"

int main()
{
    vec3 vrp, vpn, vup;
	ofstream outData;
	outData.open("image.raw", ios::out | ios::binary);
    
    if (!outData.is_open())
    {
        cout<<"Cannot open file."<<endl;
        exit(1);
    }
    
    for (int i = 0; i < 3; i++)
    {
        vrp.vector[i] = VRP[i];
        vpn.vector[i] = VPN[i];
        vup.vector[i] = VUP[i];
    }
    //Initialize world to camera and camera to world coordinates
    WorldToCamera(Mwc, vrp, vpn, vup);
    CameraToWorld(Mcw, vrp, vpn, vup);
    
	//Calculate shading value for each ray if applicable
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            float V0[3] = {0}, N[3] = {0}, P[3] = {0};
            float kd;
			//Construct ray
            ray_construction(i, j, V0);
			//Find intersection between ray and objects
            bool found = ray_object_intersection(V0, P, N, kd);
			//If the intersection is found, calculate shading value at this point
            if (found)
            {
                int c = shading(P, N, kd);
                if(c != 0)
                {
                    img[i][j] = c;
                }
            }
        }
    }
    
	//Write data into file from the last row to sitisfied Windows machine rendering
    for (int i = ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < COLS; j++)
        {
            outData.write((char *)&img[i][j], sizeof(img[i][j]));
        }
    }
 
    outData.close();
    
    return 0;
}
