//
//  main.cpp
//  gfxExperiments
//
//  Created by Marat Isaw on 03.03.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "common.hpp"
#include "gfx.hpp"

struct Point {
    int x;
    int y;
};
struct Triangle {
    Point p[3];
};

size_t GFX_WIDTH;
size_t GFX_HEIGHT;

void gfx_clear(uint32_t* pixels, uint32_t color);
void gfx_init(size_t w, size_t h);

void gfx_drawPoint(uint32_t* pixels, uint32_t color, int x, int y);
void gfx_drawLine(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2);

void gfx_drawTriangle(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);
void gfx_fillTriangle(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void gfx_drawCircle(uint32_t* pixels, uint32_t color, int x, int y, int radius);
void gfx_fillCircle(uint32_t* pixels, uint32_t color, int x, int y, int radius);

void gfx_drawRectangle(uint32_t* pixels, uint32_t color, int x, int y, int width, int height);
void gfx_fillRectangle(uint32_t* pixels, uint32_t color, int x, int y, int width, int height);

void _gfx_drawLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int y1, int x2, int y2);
void __gfx_drawTriangleLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int y1, int x2, int y2);
void _gfx_drawScanLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int x2, int y);
void _gfx_fillTriangle(uint32_t* pixels, uint32_t color1, uint32_t color2, uint32_t color3, int x1, int y1, int x2, int y2, int x3, int y3);
void _gfx_fillTriangleBarycentric(uint32_t* pixels, uint32_t color1, uint32_t color2, uint32_t color3, int x1, int y1, int x2, int y2, int x3, int y3);

inline float util_lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}
inline int util_lerpi(int a, int b, float t) {
    return a + (b - a) * t;
}
uint32_t _util_getColorLerpBetweenPoints(int tx, int ty, int x1, int y1, int x2, int y2, uint32_t color1, uint32_t color2);
void util_swap(int* a, int* b);

int main(int argc, char** argv) {
//    uint32_t testColor = 0xABCDEF11;
//
//    std::cout << std::hex << ((testColor >> 24) & 0xff) << "\n";
//    std::cout << std::hex << ((testColor >> 16) & 0xff) << "\n";
//    std::cout << std::hex << ((testColor >>  8) & 0xff) << "\n";
//    std::cout << std::hex << ((testColor >>  0) & 0xff) << "\n";
//
//    std::cout << "-----\n";
//
//    std::cout << std::hex << (int)((uint8_t*)&testColor)[3] << "\n";
//    std::cout << std::hex << (int)((uint8_t*)&testColor)[2] << "\n";
//    std::cout << std::hex << (int)((uint8_t*)&testColor)[1] << "\n";
//    std::cout << std::hex << (int)((uint8_t*)&testColor)[0] << "\n";
    
    SDL_Init(SDL_INIT_EVERYTHING);
    gfx_init(WIDTH, HEIGHT);
    __gfx_init__(WIDTH, HEIGHT);
    
    SDL_Window* window = SDL_CreateWindow("gfx experiments", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
//    uint32_t* pixels = new uint32_t[WIDTH * HEIGHT];
    uint32_t pixels[WIDTH * HEIGHT];
    
    Point mouse;
    
    int currentPoint = 2;
    int triX1 = 78, triY1 = 10; // int triX1 = 78, triY1 = 10;
    int triX2 = 32, triY2 = 500;
    int triX3 = 200, triY3 = 200;
    
    const int triangleCount = 14;
    
    Triangle tris[triangleCount];
    tris[0].p[0]  = {(int)(0.0f * 99.875f), (int)(0.0f * 99.875f)};
    tris[0].p[1]  = {(int)(2.0f * 99.875f), (int)(2.0f * 99.875f)};
    tris[0].p[2]  = {(int)(3.5f * 99.875f), (int)(0.0f * 99.875f)};
    tris[1].p[0]  = {(int)(3.5f * 99.875f), (int)(0.0f * 99.875f)};
    tris[1].p[1]  = {(int)(2.0f * 99.875f), (int)(2.0f * 99.875f)};
    tris[1].p[2]  = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[2].p[0]  = {(int)(3.5f * 99.875f), (int)(0.0f * 99.875f)};
    tris[2].p[1]  = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[2].p[2]  = {(int)(8.0f * 99.875f), (int)(0.0f * 99.875f)};
    tris[3].p[0]  = {(int)(0.0f * 99.875f), (int)(0.0f * 99.875f)};
    tris[3].p[1]  = {(int)(0.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[3].p[2]  = {(int)(2.0f * 99.875f), (int)(2.0f * 99.875f)};
    tris[4].p[0]  = {(int)(2.0f * 99.875f), (int)(2.0f * 99.875f)};
    tris[4].p[1]  = {(int)(0.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[4].p[2]  = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[5].p[0]  = {(int)(2.0f * 99.875f), (int)(2.0f * 99.875f)};
    tris[5].p[1]  = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[5].p[2]  = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[6].p[0]  = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[6].p[1]  = {(int)(6.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[6].p[2]  = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[7].p[0]  = {(int)(6.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[7].p[1]  = {(int)(8.0f * 99.875f), (int)(2.5f * 99.875f)};
    tris[7].p[2]  = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[8].p[0]  = {(int)(0.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[8].p[1]  = {(int)(0.0f * 99.875f), (int)(6.0f * 99.875f)};
    tris[8].p[2]  = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[9].p[0]  = {(int)(0.0f * 99.875f), (int)(6.0f * 99.875f)};
    tris[9].p[1]  = {(int)(4.5f * 99.875f), (int)(6.0f * 99.875f)};
    tris[9].p[2]  = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[10].p[0] = {(int)(2.5f * 99.875f), (int)(4.5f * 99.875f)};
    tris[10].p[1] = {(int)(4.5f * 99.875f), (int)(6.0f * 99.875f)};
    tris[10].p[2] = {(int)(6.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[11].p[0] = {(int)(4.5f * 99.875f), (int)(6.0f * 99.875f)};
    tris[11].p[1] = {(int)(8.0f * 99.875f), (int)(6.0f * 99.875f)};
    tris[11].p[2] = {(int)(6.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[12].p[0] = {(int)(6.0f * 99.875f), (int)(3.5f * 99.875f)};
    tris[12].p[1] = {(int)(8.0f * 99.875f), (int)(6.0f * 99.875f)};
    tris[12].p[2] = {(int)(8.0f * 99.875f), (int)(2.5f * 99.875f)};
    tris[13].p[0] = {(int)(5.0f * 99.875f), (int)(1.5f * 99.875f)};
    tris[13].p[1] = {(int)(8.0f * 99.875f), (int)(2.5f * 99.875f)};
    tris[13].p[2] = {(int)(8.0f * 99.875f), (int)(0.0f * 99.875f)};

    int current = 0;
    int last = 0;
    float delta = 0.0f;
    double whole = 0.0f;
    int frames = 0;
    int timer = 0;
    SDL_Event event;
    bool alive = true;
    while(alive) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) alive = false;
            if(event.key.keysym.sym == SDLK_1) {
                currentPoint = 0;
            }
            if(event.key.keysym.sym == SDLK_2) {
                currentPoint = 1;
            }
            if(event.key.keysym.sym == SDLK_3) {
                currentPoint = 2;
            }
        }
        SDL_GetMouseState(&(mouse.x), &(mouse.y));
//        std::cout << "mouseX: " << mouse.x << " | mouseY: " << mouse.y << std::endl;
        current = SDL_GetTicks();
        delta = current - last;
        frames++;
        
        if(SDL_GetTicks() > timer) {
            std::cout << "fps: " << frames << std::endl;
            frames = 0;
            timer += 1000;
        }
        
        last = current;
        
        
        gfx_clear(pixels, 0xff);
        
//        tris[1].p[2].x = mouse.x;
//        tris[1].p[2].y = mouse.y;
//        tris[2].p[1].x = mouse.x;
//        tris[2].p[1].y = mouse.y;
//        tris[5].p[2].x = mouse.x;
//        tris[5].p[2].y = mouse.y;
//        tris[6].p[2].x = mouse.x;
//        tris[6].p[2].y = mouse.y;
//        tris[7].p[2].x = mouse.x;
//        tris[7].p[2].y = mouse.y;
//        tris[13].p[0].x = mouse.x;
//        tris[13].p[0].y = mouse.y;
        
        float size = 128.f;
        float offsetX = GFX_WIDTH / 2.f;
        float offsetY = GFX_HEIGHT / 2.f;
        

//        _gfx_fillTriangle(pixels,
//                          0xff0000ff,
//                          0x00ff00ff,
//                          0x0000ffff,
//                          1 + 0, 0,
//                          1 + 16, 0,
//                          1 + 0, 16);
        
//        _gfx_fillTriangle(pixels,
//                          0xff0000ff,
//                          0x00ff00ff,
//                          0x0000ffff,
//                          GFX_WIDTH / 2, GFX_HEIGHT / 2 - GFX_HEIGHT / 4,
//                          GFX_WIDTH / 2 - GFX_WIDTH / 4, GFX_HEIGHT / 2 + GFX_HEIGHT / 4,
//                          GFX_WIDTH / 2 + GFX_WIDTH / 4, GFX_HEIGHT / 2 + GFX_HEIGHT / 4);

//        _gfx_fillTriangle(pixels,
//                          0xff0000ff,
//                          0x00ff00ff,
//                          0x0000ffff,
//                          mouse.x, mouse.y,
//                          GFX_WIDTH / 2 - GFX_WIDTH / 4, GFX_HEIGHT / 2 + GFX_HEIGHT / 4,
//                          GFX_WIDTH / 2 + GFX_WIDTH / 4, GFX_HEIGHT / 2 + GFX_HEIGHT / 4);

//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x810081ff,
//                          200 + 0, 0,
//                          200 + 100, 200,
//                          200 + 200, 200);
//        __gfx_drawTriangle__(pixels, 0xff0000ff, 0x00ff00ff, 0x810081ff,
//                          0, 0,
//                          100, 200,
//                          200, 200);

//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x810081ff,
//                    100, 0,
//                    0, 200,
//                    200, 200);
        
        
//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                          0, 0,
//                          mouse.x, mouse.y,
//                          0, 512);
//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                          0, 0,
//                          mouse.x, mouse.y,
//                          512, 0);
//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                          512, 512,
//                          mouse.x, mouse.y,
//                          512, 0);
//        _gfx_fillTriangle(pixels, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                          512, 512,
//                          mouse.x, mouse.y,
//                          0, 512);

        
        for (int re = 0; re < 1; re++) {
            for (int i = 0; i < triangleCount; i++) {
                
//                __gfx_drawTriangle__(pixels, 0xd02010ff, 0x10e033ff, 0x1030f0ff,
//                                     tris[i].p[0].x, tris[i].p[0].y,
//                                     tris[i].p[1].x, tris[i].p[1].y,
//                                     tris[i].p[2].x, tris[i].p[2].y);
                
                _gfx_fillTriangle(pixels, 0xd02010ff, 0x10e033ff, 0x1030f0ff,
                                  tris[i].p[0].x, tris[i].p[0].y,
                                  tris[i].p[1].x, tris[i].p[1].y,
                                  tris[i].p[2].x, tris[i].p[2].y);
                
//                gfx_drawLine(pixels, 0xff0000ff, tris[i].p[0].x, tris[i].p[0].y, tris[i].p[1].x, tris[i].p[1].y);
//                gfx_drawLine(pixels, 0x00ff00ff, tris[i].p[1].x, tris[i].p[1].y, tris[i].p[2].x, tris[i].p[2].y);
//                gfx_drawLine(pixels, 0x0000ffff, tris[i].p[2].x, tris[i].p[2].y, tris[i].p[0].x, tris[i].p[0].y);
//
//                gfx_drawPoint(pixels, 0x00ff00ff, tris[i].p[0].x, tris[i].p[0].y);
//                gfx_drawPoint(pixels, 0x00ff00ff, tris[i].p[1].x, tris[i].p[1].y);
//                gfx_drawPoint(pixels, 0x00ff00ff, tris[i].p[2].x, tris[i].p[2].y);
            }
        }
        
//        if(currentPoint == 0) {
//            triX1 = mouse.x;
//            triY1 = mouse.y;
//        }
//        else if(currentPoint == 1) {
//            triX2 = mouse.x;
//            triY2 = mouse.y;
//        }
//        else if(currentPoint == 2) {
//            triX3 = mouse.x;
//            triY3 = mouse.y;
//        }
        
        
//        _gfx_drawTriangleLine(pixels, 0xff0000ff, 10, 10, mouse.x, mouse.y);
//        std::cout << "x: " << mouse.x << std::endl;
//        std::cout << "y: " << mouse.y << std::endl;
//        _gfx_drawTriangleLine(pixels, 0xff0000ff, 0x00ff00ff, 78, 10, 32, 155);
//        _gfx_drawTriangleLine(pixels, 0x00ff00ff, 0x0000ffff, 32, 155, 200, 200);
//        _gfx_drawTriangleLine(pixels, 0x0000ffff, 0xff0000ff, 200, 200, 78, 10);

//        _gfx_drawLine(pixels, 0xff0000ff, 0x00ff00ff, triX2, triY2, triX3, triY3);
//        if((triX2-triX3) + (triY2-triY3) == 0) {
//            std::cout << "AAA";
//        }
        
//        _gfx_fillTriangle(pixels,
//                          0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                          triX1, triY1,
//                          triX2, triY2,
//                          triX3, triY3);
//
//
//        gfx_drawPoint(pixels, 0xffffffff - (pixels[triX1 + triY1 * GFX_WIDTH]) + 0xff, triX1, triY1);
//        gfx_drawPoint(pixels, 0xffffffff - (pixels[triX2 + triY2 * GFX_WIDTH]) + 0xff, triX2, triY2);
//        gfx_drawPoint(pixels, 0xffffffff - (pixels[triX3 + triY3 * GFX_WIDTH]) + 0xff, triX3, triY3);

//        gfx_drawPoint(pixels, 0x00ff00ff, GFX_WIDTH - 1, GFX_HEIGHT - 1);
//        gfx_drawPoint(pixels, 0x00ff00ff, 20, 21);
//        gfx_drawPoint(pixels, 0x00ff00ff, 20, 22);
//        gfx_drawPoint(pixels, 0x00ff00ff, 20, 23);
//        gfx_drawPoint(pixels, 0x00ff00ff, 20, 24);
        
        pixels[100 + GFX_WIDTH*(GFX_HEIGHT-1)] = 0xff0000ff;
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));
        
        // FOR LOCKING/UNLOCKING USE DYNAMIC PIXEL ARRAY INSTEAD OF STATIC (uint32_t* pixel = new uint32_t[w * h])
//        SDL_UnlockTexture(texture);
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
//        int pitch = 0;
//        SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);
//        pixels[100 + GFX_WIDTH*100] = 0xff0000ff;
//        SDL_Delay(1);
    }
    
    SDL_Quit();
    
    
    return 0;
}

void gfx_clear(uint32_t* pixels, uint32_t color) {
    for (uint32_t i = 0; i < GFX_WIDTH * GFX_HEIGHT; i++) {
        pixels[i] = color;
    }
}
void gfx_init(size_t w, size_t h) {
    GFX_WIDTH = w;
    GFX_HEIGHT = h;
}

void gfx_drawPoint(uint32_t* pixels, uint32_t color, int x, int y) {
    pixels[x + y * GFX_WIDTH] = color;
}
void gfx_drawLine(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2 = 0;

    int x = x1;
    int y = y1;

    while (1) {
        pixels[x + y * GFX_WIDTH] = color;
        if (x == x2 && y == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x += sx; }
        if (e2 <= dx) { err += dx; y += sy; }
    }
}

void gfx_drawTriangle(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);
void gfx_fillTriangle(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void gfx_drawCircle(uint32_t* pixels, uint32_t color, int x, int y, int radius);
void gfx_fillCircle(uint32_t* pixels, uint32_t color, int x, int y, int radius);

void gfx_drawRectangle(uint32_t* pixels, uint32_t color, int x, int y, int width, int height);
void gfx_fillRectangle(uint32_t* pixels, uint32_t color, int x, int y, int width, int height);

void _gfx_drawLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int y1, int x2, int y2) {
//    if(x1 > x2 && y1 > y2) {
//        int tempX = x1;
//        x1 = x2;
//        x2 = tempX;
//        int tempY = y1;
//        y1 = y2;
//        y2 = tempY;
//
//        uint32_t temp = color1;
//        color1 = color2;
//        color2 = temp;
//    }
    float max = sqrt((float)((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2)));
//    float max = (float)((x1-x2) + (y1-y2));
    
        
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2 = 0;
    
    int x = x1;
    int y = y1;

    int r1 = (color1 >> 24) & 0xff;
    int g1 = (color1 >> 16) & 0xff;
    int b1 = (color1 >>  8) & 0xff;
    
    int r2 = (color2 >> 24) & 0xff;
    int g2 = (color2 >> 16) & 0xff;
    int b2 = (color2 >>  8) & 0xff;

    while (1) {
        
        float distance = sqrt((x1-x) * (x1-x) + (y1-y) * (y1-y)) / max;
//        float distance = ((x1-x) + (y1-y)) / max;
        
//        uint32_t c = _util_getColorLerpBetweenPoints(x, y, x1, y1, x2, y2, color1, color2);
 
        pixels[x + y * GFX_WIDTH] = (util_lerpi(r1, r2, distance) << 24) +
                                    (util_lerpi(g1, g2, distance) << 16) +
                                    (util_lerpi(b1, b2, distance) <<  8) + 0xff;
        if (x == x2 && y == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x += sx; }
        if (e2 <= dx) { err += dx; y += sy; }
    }
}

void __gfx_drawTriangleLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int y1, int x2, int y2) {
    if(y1 > y2) {
        uint32_t tempColor = color1;
        int tempX = x1;
        int tempY = y1;
        x1 = x2;
        x2 = tempX;
        y1 = y2;
        y2 = tempY;
        color1 = color2;
        color2 = tempColor;
    }
    
    int r1 = (color1 >> 24) & 0xff;
    int g1 = (color1 >> 16) & 0xff;
    int b1 = (color1 >>  8) & 0xff;
    
    int r2 = (color2 >> 24) & 0xff;
    int g2 = (color2 >> 16) & 0xff;
    int b2 = (color2 >>  8) & 0xff;
        
    float max = (x1 - x2) + (y1 - y2);
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    float m = dx / (float)dy;
    
    float x = x1;
    for (int y = y1; y < y2; y++) {
        
        float distance = ((x1-x) + (y1-y)) / max;
        
        uint32_t color = (util_lerpi(r1, r2, distance) << 24) +
                        (util_lerpi(g1, g2, distance) << 16) +
                        (util_lerpi(b1, b2, distance) <<  8) + 0xff;
        
        gfx_drawPoint(pixels, color, x, y);
        
        x += m;
    }
}

void _gfx_drawScanLine(uint32_t* pixels, uint32_t color1, uint32_t color2, int x1, int x2, int y) {
    const int _y = y * (int)GFX_WIDTH;
    if(x1 > x2) {
        util_swap(&x1, &x2);
        uint32_t tempColor = color1;
        color1 = color2;
        color2 = tempColor;
    }
    
    float r = ((((int64_t)color2 >> 24) & 0xff) - (((int64_t)color1 >> 24) & 0xff)) / (float)(x2 - x1);
    float g = ((((int64_t)color2 >> 16) & 0xff) - (((int64_t)color1 >> 16) & 0xff)) / (float)(x2 - x1);
    float b = ((((int64_t)color2 >>  8) & 0xff) - (((int64_t)color1 >>  8) & 0xff)) / (float)(x2 - x1);
    float a = ((((int64_t)color2 >>  0) & 0xff) - (((int64_t)color1 >>  0) & 0xff)) / (float)(x2 - x1);
    float rr = (color1 >> 24) & 0xff;
    float gg = (color1 >> 16) & 0xff;
    float bb = (color1 >>  8) & 0xff;
    float aa = (color1 >>  0) & 0xff;
    uint32_t color = color1;
    for(int i = x1; i < x2; i++) {
//        uint32_t color = (util_lerpi((color1 >> 24) & 0xff, (color2 >> 24) & 0xff, (x1 - i) / (float)(x1 - x2)) << 24) +
//                         (util_lerpi((color1 >> 16) & 0xff, (color2 >> 16) & 0xff, (x1 - i) / (float)(x1 - x2)) << 16) +
//                         (util_lerpi((color1 >>  8) & 0xff, (color2 >>  8) & 0xff, (x1 - i) / (float)(x1 - x2)) <<  8) +
                             0xff;//(util_lerpi((color1 >>  0) & 0xff, (color2 >>  0) & 0xff, (x1 - i) / (float)(x1 - x2)) <<  0);


//        int _r = ((colora >> 24) & 0xff);
//        int _g = ((colora >> 16) & 0xff);
//        int _b = ((colora >>  8) & 0xff);
        
//        color = ((int)(rr) << 24) +
//                ((int)(gg) << 16) +
//                ((int)(bb) <<  8) +
//                ((int)(aa) <<  0);
        
        pixels[i + _y] = ((int)(rr) << 24) +
                ((int)(gg) << 16) +
                ((int)(bb) <<  8) +
                ((int)(aa) <<  0);
        
        rr += r;
        gg += g;
        bb += b;
        aa += a;

        
//        color = ((((color >> 24) & 0xff) - ((colora >> 24) & 0xff)) << 24) +
//                ((((color >> 16) & 0xff) - ((colora >> 16) & 0xff)) << 16) +
//                ((((color >>  8) & 0xff) - ((colora >>  8) & 0xff)) <<  8) + 0xff;
        
        
        
//        pixels[i + _y] = util_lerpi(color1, color2, i / (float)(x2));
    }
}

void _gfx_fillTriangle(uint32_t* pixels, uint32_t color1, uint32_t color2, uint32_t color3, int x1, int y1, int x2, int y2, int x3, int y3) {
    if(y1 > y3) {
        int tempX = x1;
        x1 = x3;
        x3 = tempX;
        int tempY = y1;
        y1 = y3;
        y3 = tempY;
        uint32_t tempColor = color1;
        color1 = color3;
        color3 = tempColor;
    }
    if(y1 > y2) {
        int tempX = x1;
        x1 = x2;
        x2 = tempX;
        int tempY = y1;
        y1 = y2;
        y2 = tempY;
        uint32_t tempColor = color1;
        color1 = color2;
        color2 = tempColor;
    }
    else if(y2 > y3) {
        int tempX = x2;
        x2 = x3;
        x3 = tempX;
        int tempY = y2;
        y2 = y3;
        y3 = tempY;
        uint32_t tempColor = color2;
        color2 = color3;
        color3 = tempColor;
    }
    
    
    float x_1 = x1;
    float m1 = (x3 - x1) / (float)(y3 - y1);
    
    if(y1 != y2) {
        float x_2 = x1;
        float m2 = (x2 - x1) / (float)(y2 - y1);
        
        for(int scanline = y1; scanline < y2; scanline++) {
//        uint32_t lerpColor1 = _util_getColorLerpBetweenPoints(x_1, scanline, x1, y1, x3, y3, color1, color3);
//        uint32_t lerpColor2 = _util_getColorLerpBetweenPoints(x_2, scanline, x1, y1, x2, y2, color1, color2);
            
            _gfx_drawScanLine(pixels, _util_getColorLerpBetweenPoints(x_1, scanline, x1, y1, x3, y3, color1, color3), _util_getColorLerpBetweenPoints(x_2, scanline, x1, y1, x2, y2, color1, color2), x_1, x_2, scanline);
//        _gfx_drawLine(pixels, lerpColor1, lerpColor2, x_1, scanline, x_2, scanline);
            
            x_1 += m1;
            x_2 += m2;
        }
    }
    
    if(y2 != y3) {
        float x_3 = x2;
        float m3 = (x3 - x2) / (float)(y3 - y2);
        for(int scanline = y2; scanline <= y3; scanline++) {
//        uint32_t lerpColor1 = _util_getColorLerpBetweenPoints(x_1, scanline, x1, y1, x3, y3, color1, color3);
//        uint32_t lerpColor2 = _util_getColorLerpBetweenPoints(x_3, scanline, x2, y2, x3, y3, color2, color3);
            
            _gfx_drawScanLine(pixels, _util_getColorLerpBetweenPoints(x_1, scanline, x1, y1, x3, y3, color1, color3), _util_getColorLerpBetweenPoints(x_3, scanline, x2, y2, x3, y3, color2, color3), x_1, x_3, scanline);
//        _gfx_drawLine(pixels, lerpColor1, lerpColor2, x_1, scanline, x_3, scanline);
            
            x_1 += m1;
            x_3 += m3;
        }
    }
}

struct Vector2 {
    float x;
    float y;
};

inline float edgeF(const Vector2& a, const Vector2& b, const Vector2& c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}
void _gfx_fillTriangleBarycentric(uint32_t* pixels, uint32_t color1, uint32_t color2, uint32_t color3, int x1, int y1, int x2, int y2, int x3, int y3) {
    int minX = std::min({x1, x2, x3});
    int maxX = std::max({x1, x2, x3});
    int minY = std::min({y1, y2, y3});
    int maxY = std::max({y1, y2, y3});

    Vector2 p1{ float(x1), float(y1) };
    Vector2 p2{ float(x2), float(y2) };
    Vector2 p3{ float(x3), float(y3) };
    float k = edgeF(p1, p2, p3);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            Vector2 p{ float(x), float(y) };
            float w1 = edgeF(p2, p3, p),
                  w2 = edgeF(p3, p1, p),
                  w3 = edgeF(p1, p2, p);

            if (w1 >= 0.0f && w2 >= 0.0f && w3 >= 0.0f) {
                w1 /= k;
                w2 /= k;
                w3 /= k;

                int r, g, b, a;
                r = w1 * ((color1 >> 24) & 0xff) + w2 * ((color2 >> 24) & 0xff) + w3 * ((color3 >> 24) & 0xff);
                g = w1 * ((color1 >> 16) & 0xff) + w2 * ((color2 >> 16) & 0xff) + w3 * ((color3 >> 16) & 0xff);
                b = w1 * ((color1 >>  8) & 0xff) + w2 * ((color2 >>  8) & 0xff) + w3 * ((color3 >>  8) & 0xff);
                a = w1 * ((color1 >>  0) & 0xff) + w2 * ((color2 >>  0) & 0xff) + w3 * ((color3 >>  0) & 0xff);

                pixels[x + y * GFX_WIDTH] = (r << 24) + (g << 16) + (b << 8) + (a << 0);
            }
        }
    }
}

//float util_getDistance(int x1, int y1, int x2, int y2) {
//    return 0;
//}
uint32_t _util_getColorLerpBetweenPoints(int tx, int ty, int x1, int y1, int x2, int y2, uint32_t color1, uint32_t color2) {
//    uint32_t color = 0;
    
//    float max = (float)(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
//    float distance = sqrt((x1 - tx) * (x1 - tx) + (y1 - ty) * (y1 - ty)) / max;

//    float max = (float)((x1-x2) + (y1-y2));
//    float distance = ((x1-tx) + (y1-ty)) / max;

//    float max = (float)((x1-x2) + (y1-y2));
//    float distancex = ((x1 - tx) / (float)(x1 - x2));
//    float distancey = ((y1 - ty) / (float)(y1 - y2));
    const float distance = (y1 - ty) / (float)(y1 - y2);

    return uint32_t((util_lerpi((color1 >> 24) & 0xff, (color2 >> 24) & 0xff, distance) << 24) + // red
                    (util_lerpi((color1 >> 16) & 0xff, (color2 >> 16) & 0xff, distance) << 16) + // green
                    (util_lerpi((color1 >>  8) & 0xff, (color2 >>  8) & 0xff, distance) <<  8) + // blue
                    (util_lerpi((color1 >>  0) & 0xff, (color2 >>  0) & 0xff, distance) <<  0)); // alpha
    
//    return color;
}
void util_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
