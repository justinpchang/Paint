//
//  Rectangle.h
//  Paint
//
//  Created by Justin on 6/29/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef Rectangle_h
#define Rectangle_h
#include "SDL2/SDL.h"
#include "Shape.h"
#include "Color.h"

class Rectangle : public Shape {
    bool isSet = false;
    bool doneDrawing = false;
    int *v1, *v2;
    int tempx1, tempy1;
    int cx, cy;
    SDL_Rect r;
    void move() {
        int xDiff = tempx1 - v1[0];
        int yDiff = tempy1 - v1[1];
        v2[0] += xDiff;
        v2[1] += yDiff;
    }
public:
    Rectangle(SDL_Renderer* r, Color ccolor): Shape(r, ccolor) {
        v1 = new int[2];
        v1[0] = 0;
        v1[1] = 0;
        v2 = new int[2];
        v2[0] = 0;
        v2[1] = 0;
    }
    Rectangle(): Shape(nullptr, Color(0,0,0)) {
        v1 = new int[2];
        v1[0] = 0;
        v1[1] = 0;
        v2 = new int[2];
        v2[0] = 0;
        v2[1] = 0;
    }
    ~Rectangle() {
        v1 = new int[0];
        v2 = new int[0];
        if(v1 != nullptr)
            delete[] v1;
        if(v2 != nullptr)
            delete[] v2;
    }
    void setXY(int x, int y) { // going to be used for moving
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
    }
    void setV1(int x, int y) {
        v1[0] = x;
        v1[1] = y;
    }
    void setV2(int x, int y) {
        v2[0] = x;
        v2[1] = y;
        doneDrawing = true;
    }
    int* getV1() {
        return v1;
    }
    int* getV2() {
        return v2;
    }
    void draw() {
        if(doneDrawing) {
            SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
            SDL_RenderDrawLine(renderer, v1[0], v1[1], v2[0], v1[1]);
            SDL_RenderDrawLine(renderer, v2[0], v1[1], v2[0], v2[1]);
            SDL_RenderDrawLine(renderer, v2[0], v2[1], v1[0], v2[1]);
            SDL_RenderDrawLine(renderer, v1[0], v2[1], v1[0], v1[1]);
        }
    }
    SDL_Rect* getRectObj() {
        r = {v1[0], v1[1], v2[0]-v1[0], v2[1]-v1[1]};
        return &r;
    }
};

#endif Rectangle_h