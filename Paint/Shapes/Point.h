//
//  Point.h
//  Paint
//
//  Created by Justin on 6/28/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include "Color.h"
#include "SDL2/SDL.h"
#include "MouseVars.h"

class Point {
    Color color;
    SDL_Renderer* renderer;
    int cx, cy, x, y;
    bool isSet = false;
public:
    Point(SDL_Renderer* r, Color ccolor): renderer(r), color(ccolor) {};
    Point(const Point& model): renderer(model.renderer), x(model.x), y(model.y), color(model.color) {};
    Point(): renderer(nullptr), x(0), y(0), color(Color(0,0,0)) {};
    void setX(int xx) {
        x = xx;
    }
    void setY(int yy) {
        y = yy;
    }
    void setXY(int xx, int yy) {
        x = xx;
        y = yy;
    }
    void setColor(Color ccolor) {
        color = ccolor;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    Color getColor() {
        return color;
    }
    Point operator+(const Point& b) {
        Point p(renderer, this->color);
        p.setXY(x+b.x, y+b.y);
        return p;
    }
    Point operator-(const Point& b) {
        Point p(renderer, this->color);
        p.setXY(x-b.x, y-b.y);
        return p;
    }
    void draw() {
        SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
        if(!isSet && x > 0 && y > 0) {
            SDL_RenderDrawPoint(renderer, x, y);
            cx = x;
            cy = y;
            isSet = true;
        } else {
            SDL_RenderDrawPoint(renderer, cx, cy);
        }
    }
    void sayHi() {
        std::cout << "HI" << std::endl;
    }
};

#endif /* Point_h */
