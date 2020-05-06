//
//  common.cpp
//  WaterRipple3
//
//  Created by Marat Isaw on 30.11.19.
//  Copyright © 2019 Marat Isaw. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "common.hpp"

float lerp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

float fade(float x)
{
    return x * x * x * (x * (x * 6 - 15) + 10);
}
float fadeEnd(float x)
{
    float n = -(1-x)*(1-x)+1;
    return (1-x)*n+x*x;
}
float fadeControl(float x, float a, float b)
{
    float powXA = pow(x, a);
    return powXA / (powXA + pow(b - b * x, a));
}
float fadeControlEndHeight(float x, float a, float b, float c)
{
    float powXA = pow(x, a);
    return powXA / (powXA / c + pow(b - b * x, a));
}

float smoothstep(float edge0, float edge1, float x)
{
    // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    // Evaluate polynomial
    return x * x * x * (x * (x * 6 - 15) + 10);
}

float clamp(float x, float lowerlimit, float upperlimit)
{
    if (x < lowerlimit)
        x = lowerlimit;
    if (x > upperlimit)
        x = upperlimit;
    return x;
}
