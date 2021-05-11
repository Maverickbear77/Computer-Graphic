//
//  mymodel.h
//  Ray Tracing
//
//  Created by Changxuan Zhao on 2020-10-18.
//

#ifndef mymodel_h
#define mymodel_h
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;



/* Definition of the structure for Sphere */
typedef struct {
	float x, y, z;	/* center of the circle */
	float radius;	/* radius of the circle */
	float kd;	/* diffuse reflection coefficient */
} SPHERE;

/* Definition of Polygon with 4 edges */
typedef struct {
	float v[4][3];	/* list of vertices */
	float N[3];	/* normal of the polygon */
	float kd;	/* diffuse reflection coefficient */
} POLY4;

/* create a small spherical object */
SPHERE small_sphere = { 6.0, 3.0, 4.0,	/* center of the circle */
				  1.0,		/* radius of the circle */
				  0.75 };		/* diffuse reflection coefficient */

/* create a big spherical object */
SPHERE big_sphere = {3.0, 2.0, 7.0,    /* center of the circle */
                      2.0,        /* radius of the circle */
                      0.75 };        /* diffuse reflection coefficient */

/* create floor */
POLY4 bottom_floor = { 0.0, 0.0, 0.0,	/* v0 */
                 0.0, 0.0, 10.0,	/* v1 */
                 10.0, 0.0, 10.0,	/* v2 */
			     10.0, 0.0, 0.0,	/* v3 */
			     0.0, 1.0, 0.0,	/* normal of the polygon */
			     0.8 };		/* diffuse reflection coefficient */

/* create celing */
POLY4 top_ceiling = { 0.0, 10.0, 0.0,    /* v0 */
              0.0, 10.0, 10.0,    /* v1 */
              10.0, 10.0, 10.0,    /* v2 */
              10.0, 10.0, 0.0,    /* v3 */
              0.0, 1.0, 0.0,    /* normal of the polygon */
              0.8 };        /* diffuse reflection coefficient */

/* create left wall */
POLY4 left_wall = { 0.0, 0.0, 10.0,    /* v0 */
               0.0, 10.0, 10.0,    /* v1 */
               10.0, 10.0, 10.0,    /* v2 */
               10.0, 0.0, 10.0,    /* v3 */
               0.0, 1.0, 0.0,    /* normal of the polygon */
               0.8 };        /* diffuse reflection coefficient */


/* create right wall */
POLY4 right_wall = { 0.0, 0.0, 0.0,    /* v0 */
                10.0, 0.0, 0.0,    /* v1 */
                10.0, 10.0, 0.0,    /* v2 */
                0.0, 10.0, 0.0,    /* v3 */
                0.0, 1.0, 0.0,    /* normal of the polygon */
                0.8 };        /* diffuse reflection coefficient */

#define ROWS 512
#define COLS 512

unsigned char img[ROWS][COLS] = { 0 };

/* definition of window on the image plane in the camera coordinates */
/* They are used in mapping (j, i) in the screen coordinates into */
/* (x, y) on the image plane in the camera coordinates */
/* The window size used here simulates the 35 mm film. */
float xmin = -0.0175;
float ymin = -0.0175;
float xmax = 0.0175;
float ymax = 0.0175;


/* definition of the camera parameters */
//Test 1: initial position
float VRP[3] = { 8.0, 5.0, 8.0 };
float VPN[3] = { -1.0, 0.0, 0.0 };
float VUP[3] = { 0.0, 1.0, 0.0 };

//Test 2: moveing camera
/*float VRP[3] = { -5.0, 4.0, 1.0 };
float VPN[3] = { -8.0, -3.0, 0.0 };
float VUP[3] = { 0.0, 1.0, 0.0 };*/

float focal = 0.05;	/* focal length simulating 50 mm lens */


					/* definition of light source */
float LRP[3] = { 5.0, 5.0, 5.0 };	/* light position */
float Ip = 200.0;	/* intensity of the point light source */


/* === transformation matrices (to be constructed) === */

/* Transformation from the world to the camera coordinates */
float Mwc[4][4] =
    {0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0};

/* Transformation from the camera to the world coordinates */
float Mcw[4][4] =
    {0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0};

#endif /* mymodel_h */
