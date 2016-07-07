//
//  Shape.h
//  Paint
//
//  Created by Justin on 6/29/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include "Color.h"
#include "SDL2/SDL.h"

class Shape {
protected:
    Color color;
    SDL_Renderer* renderer;
    int cx, cy, x, y;
    virtual void move() = 0; // meant to be called after setXY() to update all other points
public:
    Shape(SDL_Renderer* r, Color ccolor): renderer(r), color(ccolor) {};
    Shape(const Shape& model): renderer(model.renderer), x(model.x), y(model.y), color(model.color) {};
    virtual void setXY(int x, int y) = 0;
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setColor(Color c) {
        color = c;
    }
    Color getColor() {
        return color;
    }
    virtual void draw() = 0;
};

#endif Shape_h