//
//  Triangle.h
//  Paint
//
//  Created by Justin on 6/29/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h
#include "SDL2/SDL.h"
#include "Shape.h"
#include "Color.h"

class Triangle : public Shape {
    bool isSet = false;
    bool doneDrawing = false;
    int *v1, *v2, *v3;
    int tempx1, tempy1;
    int cx, cy;
    SDL_Rect r;
    void move() {
        int xDiff = tempx1 - v1[0];
        int yDiff = tempy1 - v1[1];
        v2[0] += xDiff;
        v2[1] += yDiff;
        v3[0] += xDiff;
        v3[1] += yDiff;
    }
public:
    Triangle(SDL_Renderer* r, Color ccolor): Shape(r, ccolor) {
        v1 = new int[2];
        v1[0] = 0;
        v1[1] = 0;
        v2 = new int[2];
        v2[0] = 0;
        v2[1] = 0;
        v3 = new int[2];
        v3[0] = 0;
        v3[1] = 0;
    }
    Triangle(): Shape(nullptr, Color(0,0,0)) {
        v1 = new int[2];
        v1[0] = 0;
        v1[1] = 0;
        v2 = new int[2];
        v2[0] = 0;
        v2[1] = 0;
        v3 = new int[2];
        v3[0] = 0;
        v3[1] = 0;
    }
    ~Triangle() {
        v1 = new int[0];
        v2 = new int[0];
        v3 = new int[0];
        if(v1 != nullptr)
            delete[] v1;
        if(v2 != nullptr)
            delete[] v2;
        if(v3 != nullptr)
            delete[] v3;
    }
    void setXY(int x, int y) {
        tempx1 = v1[0];
        tempy1 = v1[1];
        v1[0] = x;
        v1[1] = y;
        move(); // update all other points
    }
    void moveBy(int x, int y) {
        v1[0] += x;
        v1[1] += y;
        v2[0] += x;
        v2[1] += y;
        v3[0] += x;
        v3[1] += y;
    }
    void setV1(int x, int y) {
        v1[0] = x;
        v1[1] = y;
    }
    void setV2(int x, int y) {
        v2[0] = x;
        v2[1] = y;
    }
    void setV3(int x, int y) {
        v3[0] = x;
        v3[1] = y;
        doneDrawing = true;
    }
    int* getV1() {
        return v1;
    }
    int* getV2() {
        return v2;
    }
    int* getV3() {
        return v3;
    }
    void draw() {
        if(doneDrawing) {
            SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
            SDL_RenderDrawLine(renderer, v1[0], v1[1], v2[0], v2[1]);
            SDL_RenderDrawLine(renderer, v2[0], v2[1], v3[0], v3[1]);
            SDL_RenderDrawLine(renderer, v1[0], v1[1], v3[0], v3[1]);
        }
    }
    SDL_Rect* getRectObj() {
        int leastX = v1[0];
        int greatestX = v1[0];
        int leastY = v1[1];
        int greatestY = v1[1];
        if(v2[0] > greatestX) greatestX = v2[0];
        else if(v3[0] > greatestX) greatestX = v3[0];
        if(v2[0] < leastX) leastX = v2[0];
        else if(v3[0] < leastX) leastX = v3[0];
        if(v2[1] > greatestY) greatestY = v2[1];
        else if(v3[1] > greatestY) greatestY = v3[1];
        if(v2[1] < leastY) leastY = v2[1];
        else if(v3[1] < leastY) leastY = v3[1];
        r = {leastX, leastY, greatestX-leastX, greatestY-leastY};
        return &r;
    }
};

#endif Triangle_h