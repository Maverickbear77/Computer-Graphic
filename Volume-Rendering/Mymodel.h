//
//  Mymodel.h
//  Volume rendering
//
//  Created by Changxuan Zhao on 2020-11-14.
//

#ifndef Mymodel_h
#define Mymodel_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;
/* Definition of image buffers */

#define LAYS 128
#define ROWS 128
#define COLS 128
#define SLCS 128
unsigned char CT[SLCS][ROWS][COLS]; /* a 3D array for CT data */
unsigned char SHADING[SLCS][ROWS][COLS]; /* a 3D array for shading values */

#define IMG_ROWS 512
#define IMG_COLS 512
unsigned char    out_img[IMG_ROWS][IMG_COLS];

/* Camera parameters */
float VRP[3] = {64, -180.0, 64.0}; //64, -150, 64
float VPN[3] = {0.0, 1.0, 0.0}; //0,1,0
float VUP[3] = {0.0, 0.0, -1.0}; //0, 0, -1

/* Image Plane Sizes */
float focal = 0.05;    /* 50 mm lens */
float xmin = -0.0175;    /* 35 mm "film" */
float ymin = -0.0175;
float xmax = 0.0175;
float ymax = 0.0175;

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

/* Light direction (unit length vector) */
float Light[3] = {0.577, -0.577, -0.577};
/* Light Intensity */
float Ip = 255.0;
#endif /* Mymodel_h */
