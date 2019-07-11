#pragma once
#include<math.h>
class Utilities
{

public:
    static double rad_to_degree(double rad){
        return rad/M_PI*180.0;
    }
    static double degree_to_rad(double degree){
        return degree/180.0*M_PI;
    }
};

