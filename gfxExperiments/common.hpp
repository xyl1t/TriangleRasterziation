//
//  common.h
//  WaterRipple3
//
//  Created by Marat Isaw on 30.11.19.
//  Copyright © 2019 Marat Isaw. All rights reserved.
//

#ifndef common_h
#define common_h

#define WIDTH 800
#define HEIGHT 600

float lerp(float v0, float v1, float t);
float clamp(float x, float lowerlimit, float upperlimit);
float smoothstep(float edge0, float edge1, float x);
float fade(float x);
float fadeControl(float x, float a, float b);
float fadeControlEndHeight(float x, float a, float b, float c);
float fadeEnd(float x);

#endif /* common_h */
