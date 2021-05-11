/***************************************************************************************************************************
*
* Name: Matrix.h
* Author: Changxuan Zhao
* Date: Oct 26, 2020
* Purpose: This module is to generate transformation matrix from camera to world coordinate, from light to world coordinate,
*		   from world to camera coordinate, and from world to light coordinate respectively.
*
****************************************************************************************************************************/

#include "Model.h"
#ifndef Matrix_h
#define Matrix_h

const unsigned int SIZE = 3;
const unsigned int LINES = 4;

//The new data type vec3
struct vec3
{
    float vector[SIZE];
};

void unit_vector (float vector[3])
{
    float length = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
 
    return;
}
  
vec3 CrossProduct(vec3 v1, vec3 v2)
{
    vec3 vector;
    //Calculate the values for cross product
    vector.vector[0] = v1.vector[1] * v2.vector[2] - v1.vector[2] * v2.vector[1];
    vector.vector[1] = v1.vector[2] * v2.vector[0] - v1.vector[0] * v2.vector[2];
    vector.vector[2] = v1.vector[0] * v2.vector[1] - v1.vector[1] * v2.vector[0];
    
    //Remove the minus sign in front of zero
    for (int i = 0; i < SIZE; i++)
    {
        if (vector.vector[i] == -0)
        {
            vector.vector[i] = 0;
        }
    }
    
    return vector;
}

vec3 CalculateN(vec3 v)
{
    vec3 vector;
    float length;

    length = sqrt(v.vector[0] * v.vector[0] + v.vector[1] * v.vector[1] + v.vector[2] * v.vector[2]);
    vector.vector[0] = v.vector[0] / length;
    vector.vector[1] = v.vector[1] / length;
    vector.vector[2] = v.vector[2] / length;

    return vector;
}

vec3 CalculateU (vec3 v1, vec3 v2)
{
    vec3 vector;
    float length;

    vector = CrossProduct(v1, v2);
    length = sqrt(vector.vector[0] * vector.vector[0] + vector.vector[1] * vector.vector[1] + vector.vector[2] * vector.vector[2]);
    vector.vector[0] = vector.vector[0] / length;
    vector.vector[1] = vector.vector[1] / length;
    vector.vector[2] = vector.vector[2] / length;

    return vector;
}

vec3 CalculateV (vec3 n, vec3 u)
{
    return CrossProduct(n, u);
}

bool IsCollinear(vec3 v1, vec3 v2)
{
    vec3 vector = CrossProduct(v1, v2);
    if (vector.vector[0] == 0 && vector.vector[1] == 0 && vector.vector[2] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CalculateMatrix (float matrix[LINES][LINES], const float m1[LINES][LINES], const float m2[LINES][LINES])
{
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            for (int k = 0; k < LINES; k++)
            {
                matrix[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return;
}

void WorldToCamera (float matrix[LINES][LINES], vec3 vrp, vec3 vpn, vec3 vup)
{
    if (IsCollinear(vpn, vup))
    {
        cout<<"The two vectors VPN and VUP are collinear! Try other vectors."<<endl;
        exit(1);
    }

    vec3 n, v, u;
    n = CalculateN(vpn);
    u = CalculateU(vup, vpn);
    v = CalculateV(n, u);

    float rotation[LINES][LINES] = {{u.vector[0], u.vector[1], u.vector[2], 0},
                                    {v.vector[0], v.vector[1], v.vector[2], 0},
                                    {n.vector[0], n.vector[1], n.vector[2], 0},
                                    {0, 0, 0, 1}};
    float translation[LINES][LINES] = {{1, 0, 0, -vrp.vector[0]},
                                       {0, 1, 0, -vrp.vector[1]},
                                       {0, 0, 1, -vrp.vector[2]},
                                       {0, 0, 0, 1}};

    CalculateMatrix(matrix, rotation, translation);

    return;
}

void CameraToWorld (float matrix[LINES][LINES], vec3 vrp, vec3 vpn, vec3 vup)
{
    vec3 n, v, u;
    n = CalculateN(vpn);
    u = CalculateU(vup, vpn);
    v = CalculateV(n, u);

    float translation[LINES][LINES] = {{1, 0, 0, vrp.vector[0]},
                                       {0, 1, 0, vrp.vector[1]},
                                       {0, 0, 1, vrp.vector[2]},
                                       {0, 0, 0, 1}};
    
    float rotation[LINES][LINES] = {{u.vector[0], v.vector[0], n.vector[0], 0},
                                    {u.vector[1], v.vector[1], n.vector[1], 0},
                                    {u.vector[2], v.vector[2], n.vector[2], 0},
                                    {0, 0, 0, 1}};

    CalculateMatrix(matrix, translation, rotation);

    return;
}

void WorldToLight (float matrix[LINES][LINES], vec3 lrp, vec3 lpn, vec3 lup)
{
    if (IsCollinear(lpn, lup))
    {
        cout<<"The two vectors LPN and LUP are collinear! Try other vectors."<<endl;
        exit(1);
    }

    vec3 n, v, u;
    n = CalculateN(lpn);
    u = CalculateU(lup, lpn);
    v = CalculateV(n, u);

    float rotation[LINES][LINES] = {{u.vector[0], u.vector[1], u.vector[2], 0},
                                    {v.vector[0], v.vector[1], v.vector[2], 0},
                                    {n.vector[0], n.vector[1], n.vector[2], 0},
                                    {0, 0, 0, 1}};
    float translation[LINES][LINES] = {{1, 0, 0, -lrp.vector[0]},
                                       {0, 1, 0, -lrp.vector[1]},
                                       {0, 0, 1, -lrp.vector[2]},
                                       {0, 0, 0, 1}};

    CalculateMatrix(matrix, rotation, translation);

    return;
}

void LightToWorld (float matrix[LINES][LINES], vec3 lrp, vec3 lpn, vec3 lup)
{
    vec3 n, v, u;
    n = CalculateN(lpn);
    u = CalculateU(lup, lpn);
    v = CalculateV(n, u);

    float translation[LINES][LINES] = {{1, 0, 0, lrp.vector[0]},
                                       {0, 1, 0, lrp.vector[1]},
                                       {0, 0, 1, lrp.vector[2]},
                                       {0, 0, 0, 1}};
    
    float rotation[LINES][LINES] = {{u.vector[0], v.vector[0], n.vector[0], 0},
                                    {u.vector[1], v.vector[1], n.vector[1], 0},
                                    {u.vector[2], v.vector[2], n.vector[2], 0},
                                    {0, 0, 0, 1}};

    CalculateMatrix(matrix, translation, rotation);

    return;
}

void PrintMatrix (const float matrix[LINES][LINES])
{
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            cout<<setw(12)<<matrix[i][j];
        }
        cout<<endl;
    }

    return;
}

#endif /* Matrix_h */
