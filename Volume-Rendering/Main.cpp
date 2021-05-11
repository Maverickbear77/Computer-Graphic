/***************************************************************************************
*
* Name: Volume rendering
* Author: Changxuan Zhao
* Date: Nov 23, 2020
* Purpose: This program is to implement the basic volume rendering algorithm based on
*		   Marc Levoy¡¯s paper ¡°Display of Surfaces from Volume Data¡±.
*
****************************************************************************************/


#include "Mymodel.h"
#include "Shading.h"
#include "Matrix.h"
#include "Intersection.h"
#include "Volume.h"
#include "Rays.h"

int main ()
{
    vec3 vrp, vpn, vup;
    int n;
	FILE *infid;
	ofstream outData;
	outData.open("image.raw", ios::out | ios::binary);
  
    if ((infid = fopen("smallHead.den", "rb")) == NULL)
    {
        cout<<"Cannot open CT DATA file."<<endl;
        exit(1);
    }
    
	//Read data from smallHead.den file
    for (int i = 0; i < SLCS; i++)
    {
        float temp = fread(&CT[i][0][0], sizeof(char), ROWS * COLS, infid);
        if (temp < ROWS * COLS * sizeof(char))
        {
            cout<<"Read data error"<<endl;
            exit(2);
        }
    }
    
	//Initialize world to camera and camera to world coordinates
    for (int i = 0; i < 3; i++)
    {
        vrp.vector[i] = VRP[i];
        vpn.vector[i] = VPN[i];
        vup.vector[i] = VUP[i];
    }
    
    WorldToCamera(Mwc, vrp, vpn, vup);
    CameraToWorld(Mcw, vrp, vpn, vup);
    
	//Calculate shding value
    compute_shading_volume();
    
	//Calculate final image
    for (int i = 0; i < IMG_ROWS; i++)
    {
        for (int j = 0; j < IMG_COLS; j++)
        {
            float ts[3], V[3] = {0.0};
			//Construct ray for eax pixel
            ray_construction(i, j, V);
			//Check intersection for this ray
            n = ray_box_intersection(VRP, V, ts);
            
			//If it has two intercection points, compute color
            if (n == 2)
            {
                out_img[i][j] = volume_ray_tracing(V, ts);
            }
                
        }
    }
   
	//Write data into file from the last row to sitisfied Windows machine rendering
	for (int i = IMG_ROWS - 1; i >= 0; i--)
	{
		for (int j = 0; j < IMG_COLS; j++)
		{
			outData.write((char *)&out_img[i][j], sizeof(out_img[i][j]));
		}
	}

	//Close files
	outData.close();
	fclose(infid);

    return 0;
}
