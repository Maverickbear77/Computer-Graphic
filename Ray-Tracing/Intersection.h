/***************************************************************************************************************************
*
* Name: Intersection.h
* Author: Changxuan Zhao
* Date: Oct 26, 2020
* Purpose: This module is to calculate intersections between each ray and objects.
*
****************************************************************************************************************************/

#include "Rays.h"
#ifndef Intersection_h
#define Intersection_h

//Calculation for dot product
float dot_product (const float v1[3], const float v2[3])
{
    
    return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

//Calculation for cross product
void cross_product(const float v1[3], const float v2[3], float N[3])
{
    N[0] = v1[1] * v2[2] - v1[2] * v2[1];
    N[1] = v1[2] * v2[0] - v1[0] * v2[2];
    N[2] = v1[0] * v2[1] - v1[1] * v2[0];
    
    //Remove the minus sign in front of zero
    for (int i = 0; i < 3; i++)
    {
        if (N[i] == -0)
        {
            N[i] = 0;
        }
    }
    
    return;
}

//Convert 3D coordinate into 2D coordinate
void convert_to_twod (float vl2[4][2], const float P[3], float P2[2], int index, POLY4 object)
{
    switch (index)
    {
		//Drop x
        case 0:
            for (int i = 0; i < 4; i++)
            {
                vl2[i][0] = object.v[i][1];
                vl2[i][1] = object.v[i][2];
            }
            P2[0] = P[1];
            P2[1] = P[2];
            break;
		//Drop y
        case 1:
            for (int i = 0; i < 4; i++)
            {
                vl2[i][0] = object.v[i][0];
                vl2[i][1] = object.v[i][2];
            }
            P2[0] = P[0];
            P2[1] = P[2];
            break;
		//Drop z
        case 2:
            for (int i = 0; i < 4; i++)
            {
                vl2[i][0] = object.v[i][0];
                vl2[i][1] = object.v[i][1];
            }
            P2[0] = P[0];
            P2[1] = P[1];
            break;
    }
    return;
}

//Calculationg for intersection between each edge of polygon with positive x axis
int calculate_edge_intersection (const float P2[2], const float vl2[4][2])
{
    int counter = 0;
    float intersection[2];
    
    for (int i = 0; i < 4; i++)
    {
        int index = (i + 1) % 4;
        
        if ((P2[0] == vl2[i][0] && P2[1] == vl2[i][1]) || (P2[0] == vl2[index][0] && P2[1] == vl2[index][1]))
        {
            counter = 1;
            break;
        }
        
        if (vl2[i][1] == vl2[index][1] || (vl2[i][1] < 0 && vl2[index][1] < 0) || (vl2[i][1] > 0 && vl2[index][1] > 0))
        {
            continue;
        }
        else
        {
            intersection[0] =vl2[i][0] - (vl2[i][1] / (vl2[index][1] - vl2[i][1]) * (vl2[index][0] - vl2[i][0]));
            intersection[1] = 0.0;
            
            if (intersection[0] < 0)
            {
                continue;
            }
            else if (intersection[0] == 0)
            {
                counter = 1;
                break;
            }
            else
            {
                if (intersection[0] == vl2[i][0] && intersection[1] == vl2[i][1])
                {
                    if (vl2[i][1] > vl2[index][1])
                    {
                        continue;
                    }
                    else
                    {
                        counter++;
                    }
                }
                else if (intersection[0] == vl2[index][0] && intersection[1] == vl2[index][1])
                {
                    if (vl2[i][1] > vl2[index][1])
                    {
                        counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    counter++;
                }
            }
        }
    }
    
    return counter;
}

//Check if the point inside polygon
bool is_inside_polygon (const float P[3], const float N[3], POLY4 object)
{
    int index, counter;
    float P2[2], vl2[4][2];
    if ((N[0] * N[0] >= N[1] * N[1]) && (N[0] * N[0] >= N[2] * N[2]))
    {
        index = 0;
    }
    else if ((N[1] * N[1] >= N[0] * N[0]) && (N[1] * N[1] >= N[2] * N[2]))
    {
        index = 1;
    }
    else
    {
        index = 2;
    }
    
    convert_to_twod(vl2, P, P2, index, object);
    
    for (int i = 0; i < 4; i++)
    {
        vl2[i][0] -= P2[0];
        vl2[i][1] -= P2[1];
    }
    
    P2[0] = 0;
    P2[1] = 0;
    
    counter = calculate_edge_intersection(P2, vl2);
    
    
    if (counter % 2 == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Calculation intercections between each ray and polygon
float ray_polygon_intersection (const float V0[3], float N[3], POLY4 object)
{
    float v1[3] = {0.0}, v2[3] = {0.0}, P[3] = {0.0};
    float D, t;
    
    for (int i = 0; i < 3; i++)
    {
        v1[i] = object.v[1][i] - object.v[0][i];
        v2[i] = object.v[2][i] - object.v[0][i];
    }
	
    
    cross_product(v1, v2, N);
    unit_vector(N);
    
    if (dot_product(N, V0) == 0)
    {
        return 10000;
    }
    
    D = -(N[0] * object.v[0][0] + N[1] * object.v[0][1] + N[2] * object.v[0][2]);
    t = (-(dot_product(N, VRP) + D)) / (dot_product(N, V0));

    for (int i = 0; i < 3; i++)
    {
        P[i] = VRP[i] + t * V0[i];
    }
    
    if (is_inside_polygon(P, N, object))
    {
        return t;
    }
    else
    {
        return 10000;
    }
}

//Calculation intercections between each ray and sphere
float ray_sphere_intercection (const float V0[3], float N[3], SPHERE object)
{
    float L[3] = {0.0};
    float Tca, d, length;
    float radius = object.radius * object.radius;
    
    L[0] = object.x - VRP[0];
    L[1] = object.y - VRP[1];
    L[2] = object.z - VRP[2];
    
    length = L[0] * L[0] + L[1] * L[1] + L[2] * L[2];
    
    Tca = dot_product(L, V0);
    d = length - Tca * Tca;
    
    if (d > radius)
    {
        return 10000;
    }
    else
    {
        float Thc = sqrt(radius - d);
        N[0] = VRP[0] + (Tca - Thc) * V0[0] - object.x;
        N[1] = VRP[1] + (Tca - Thc) * V0[1] - object.y;
        N[2] = VRP[2] + (Tca - Thc) * V0[2] - object.z;
        unit_vector(N);
        
        return (Tca - Thc);
    }
}

//Calculation intercections between each ray and objects
//Choose the point that has the smallest t value and return t value to main function
bool ray_object_intersection(const float V0[3], float P[3], float N[3], float &kd)
{
    float N0[3] = {0.0}, N1[3] = {0.0}, N2[3] = {0.0}, N3[3] = {0.0}, N4[3] = {0.0}, N5[3] = {0.0};
    float t[6];
    int index = 0;
    
    t[0] = ray_sphere_intercection(V0, N0, small_sphere);
    t[1] = ray_sphere_intercection(V0, N1, big_sphere);
    t[2] = ray_polygon_intersection(V0, N2, bottom_floor);
    t[3] = ray_polygon_intersection(V0, N3, top_ceiling);
    t[4] = ray_polygon_intersection(V0, N4, left_wall);
    t[5] = ray_polygon_intersection(V0, N5, right_wall);
    
    float result = t[0];
    
    for (int i = 0; i < 6; i++)
    {
        if (t[i] != 10000 && t[i] < result)
        {
            index = i;
            result = t[i];
        }
    }
    
    if (result == 10000)
    {
        return false;
    }
    else
    {
        switch (index)
        {
            case 0:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N0[i];
                }
                kd = small_sphere.kd;
                break;
            case 1:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N1[i];
                }
                kd = big_sphere.kd;
                break;
            case 2:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N2[i];
                }
                kd = bottom_floor.kd;
                break;
            case 3:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N3[i];
                }
                kd = top_ceiling.kd;
                break;
            case 4:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N4[i];
                }
                kd = left_wall.kd;
                break;
            case 5:
                for (int i = 0; i < 3; i++)
                {
                    P[i] = VRP[i] + t[index] * V0[i];
                    N[i] = N5[i];
                }
                kd = right_wall.kd;
                break;
            default:
                cout<<"Something wrong with calculating intersections!"<<endl;
                exit(2);
        }
        return true;
    }
}

#endif /* Intersection_h */
