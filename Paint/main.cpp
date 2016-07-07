//
//  main.cpp
//  SDL Test
//
//  Created by Justin on 6/28/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

/*  T O D O :
    -multiple shapes drawn
 */

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "Shapes/Color.h"
#include "Shapes/Point.h"
#include "MouseVars.h"
#include "DynList/DynList.h"
#include "Shapes/Shape.h"
#include "Shapes/Triangle.h"
#include "Shapes/Rectangle.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *surface = nullptr;
SDL_Event event;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 480;
bool isRunning = true;
int num, cur = 0;
int prevX, prevY;

int hasToDrawRect = 0;
int hasToDrawTri = 0;
int hasToMove = 0;
int hasToDel = 0;

vector<Triangle> triangles(10);
vector<Rectangle> rectangles(10);
Point points[4];
Rectangle selectRect;
bool drawSelectRect = false;
SDL_Rect triButt, rectButt, inRectButt, moveButt, delButt;
SDL_Rect mouse = {0, 0, 1, 1};

Color triMenuColor(255,0,255);
Color rectMenuColor(255,0,255);
Color moveMenuColor(255,0,255);
Color delMenuColor(255,0,255);

int initSDL() {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[FATAL] Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }
    
    // Create window renderer, surface
    if(SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[FATAL] Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }
    surface = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 255);
    
    // Initialize buttons
    triButt.x = triButt.y = 0; triButt.w = triButt.h = 120;
    rectButt.x = 0; rectButt.y = 120; rectButt.w = rectButt.h = 120;
    inRectButt.x = 20; inRectButt.y = 140; inRectButt.w = inRectButt.h = 80;
    moveButt.x = 0; moveButt.y = 240; moveButt.w = moveButt.h = 120;
    delButt.x = 0; delButt.y = 360; delButt.w = delButt.h = 120;
    
    return 0;
}

void drawTriMenu(Color color) {
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
    SDL_RenderDrawRect(renderer, &triButt); // small triangle
        SDL_RenderDrawLine(renderer, 60, 30, 30, 90);
        SDL_RenderDrawLine(renderer, 30, 90, 90, 90);
        SDL_RenderDrawLine(renderer, 90, 90, 60, 30);
}

void drawRectMenu(Color color) {
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
    SDL_RenderDrawRect(renderer, &rectButt); // small rectangle
        SDL_RenderDrawRect(renderer, &inRectButt);
}

void drawMoveMenu(Color color) {
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
    SDL_RenderDrawRect(renderer, &moveButt); // 4-way arrow
        SDL_RenderDrawLine(renderer, 20, 300, 100, 300);
            SDL_RenderDrawLine(renderer, 20, 300, 30, 290);
            SDL_RenderDrawLine(renderer, 20, 300, 30, 310);
            SDL_RenderDrawLine(renderer, 100, 300, 90, 290);
            SDL_RenderDrawLine(renderer, 100, 300, 90, 310);
        SDL_RenderDrawLine(renderer, 60, 260, 60, 340);
            SDL_RenderDrawLine(renderer, 60, 260, 50, 270);
            SDL_RenderDrawLine(renderer, 60, 260, 70, 270);
            SDL_RenderDrawLine(renderer, 60, 340, 50, 330);
            SDL_RenderDrawLine(renderer, 60, 340, 70, 330);
}

void drawDelMenu(Color color) {
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
    SDL_RenderDrawRect(renderer, &delButt); // X
        SDL_RenderDrawLine(renderer, 20, 380, 100, 460);
        SDL_RenderDrawLine(renderer, 100, 380, 20, 460);
}

void clearScreen() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void drawAll() {
    // DRAW
    // draw points
    for(int i = 0; i < 4; i++) {
        points[i].draw();
    }
    // draw selectRect
    if(drawSelectRect) {
        selectRect.draw();
    }
    // draw triangles
    for(int i = 0; i < triangles.size(); i++) {
        triangles[i].draw();
    }
    // draw rectangles
    for(int i = 0; i < rectangles.size(); i++) {
        rectangles[i].draw();
    }
    
    // Render onto screen
    SDL_RenderPresent(renderer);

}

int main(int argc, const char * argv[]) {
    
    x = 0, y = 0;
    
    // Initialize SDL
    initSDL();
    
    // Render loop
    while(isRunning) {
        // Draw menu
        clearScreen();
        drawTriMenu(triMenuColor);
        drawRectMenu(rectMenuColor);
        drawMoveMenu(moveMenuColor);
        drawDelMenu(delMenuColor);
        
        // Poll for events
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                prevX = x;
                prevY = y;
                SDL_GetMouseState(&x, &y);
                
                if(prevX != x && prevY != y) {
                    mouse.x = x;
                    mouse.y = y;
                    if(hasToMove) {
                        switch(hasToMove) {
                            case 2: { // set second selection point
                                Point q(renderer, Color(0,0,0));
                                q.setXY(0,0);
                                points[1] = q;
                                selectRect.setV2(x,y);
                                for(int i = 0; i < triangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*triangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        triangles[i].setColor(Color(128,255,0));
                                    }
                                }
                                for(int i = 0; i < rectangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*rectangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        rectangles[i].setColor(Color(128,255,0));
                                    }
                                }
                                drawSelectRect = true;
                                drawAll();
                                hasToMove++;
                                //cout << "Drawing second selectRect point" << endl;
                                break;
                            }
                            case 4: { // set second move point
                                Point s(renderer, Color(0,0,0));
                                s.setXY(x,y);
                                points[3] = s;
                                for(int i = 0; i < triangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*triangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        triangles[i].moveBy(points[3].getX()-points[2].getX(), points[3].getY()-points[2].getY());
                                        triangles[i].setColor(Color(0,0,0));
                                    }
                                }
                                for(int i = 0; i < rectangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*rectangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        rectangles[i].moveBy(points[3].getX()-points[2].getX(), points[3].getY()-points[2].getY());
                                        rectangles[i].setColor(Color(0,0,0));
                                    }
                                }
                                moveMenuColor = Color(255,0,255);
                                points[0].setXY(0,0);
                                points[1].setXY(0,0);
                                points[2].setXY(0,0);
                                points[3].setXY(0,0);
                                hasToMove = 0;
                                drawSelectRect = false;
                                break;
                            }
   
                        }
                    } else if(hasToDel) {
                        switch(hasToDel) {
                            case 2: { // set second point
                                Point q(renderer, Color(0,0,0));
                                q.setXY(0,0);
                                points[1] = q;
                                selectRect.setV2(x,y);
                                hasToDel++;
                                drawSelectRect = true;
                                drawAll();
                                
                                SDL_Delay(500);
                                
                                delMenuColor = Color(255,0,255);
                                for(int i = 0; i < rectangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*rectangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        rectangles.erase(rectangles.begin() + i);
                                    }
                                }
                                for(int i = 0; i < triangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*triangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        triangles.erase(triangles.begin() + i);
                                    }
                                }
                                
                                // reset everything
                                points[0].setXY(0,0);
                                points[1].setXY(0,0);
                                selectRect.setV1(0,0);
                                selectRect.setV2(0,0);
                                hasToDel = 0;
                                drawSelectRect = false;
                                break;
                                //cout << "Drawing second selectRect point" << endl;
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                // gets the current location of the mouse and sets it to extern vars x and y
                prevX = x;
                prevY = y;
                SDL_GetMouseState(&x, &y);
                
                if(prevX != x && prevY != y) {
                    mouse.x = x;
                    mouse.y = y;
                    if(hasToDrawRect) {
                        switch(hasToDrawRect) {
                            case 1: { // set first point
                                Point p(renderer, Color(0,0,0));
                                p.setXY(x,y);
                                points[0] = p;
                                rectangles[rectangles.size()-1].setV1(x,y);
                                hasToDrawRect++;
                                //cout << "Drawing first rectangle point" << endl;
                                break;
                            }
                            case 2: { // set second point
                                Point q(renderer, Color(0,0,0));
                                q.setXY(0,0);
                                points[1] = q;
                                rectangles[rectangles.size()-1].setV2(x,y);
                                hasToDrawRect = 0;
                                //cout << "Drawing second rectangle point" << endl;
                                rectMenuColor = Color(255,0,255);
                                break;
                            }
                            case 0: { // clear points
                                points[0].setXY(0,0);
                                points[1].setXY(0,0);
                                break;
                            }
                        }
                    } else if(hasToDrawTri) {
                        switch(hasToDrawTri) {
                            case 1: { // set first point
                                Point p(renderer, Color(0,0,0));
                                p.setXY(x,y);
                                points[0] = p;
                                triangles[triangles.size()-1].setV1(x,y);
                                hasToDrawTri++;
                                //cout << "Drawing first triangle point" << endl;
                                break;
                            }
                            case 2: { // set second point
                                Point q(renderer, Color(0,0,0));
                                q.setXY(x,y);
                                points[1] = q;
                                triangles[triangles.size()-1].setV2(x,y);
                                hasToDrawTri++;
                                //cout << "Drawing second triangle point" << endl;
                                break;
                            }
                            case 3: { // set third point
                                triMenuColor = Color(255,0,255);
                                points[0].setXY(0,0);
                                points[1].setXY(0,0);
                                triangles[triangles.size()-1].setV3(x,y);
                                hasToDrawTri = 0;
                                //cout << "Drawing third triangle point" << endl;
                                break;
                            }
                        }
                    } else if(hasToMove) {
                        switch(hasToMove) {
                            case 1: { // set first selection point
                                Point p(renderer, Color(0,0,0));
                                p.setXY(x,y);
                                points[0] = p;
                                selectRect.setV1(x,y);
                                selectRect.setColor(Color(255,0,0));
                                hasToMove++;
                                //cout << "Drawing first selectRect point" << endl;
                                break;
                            }
                            case 3: { // set first move point
                                Point r(renderer, Color(0,0,0));
                                r.setXY(x,y);
                                points[2] = r;
                                hasToMove++;
                                break;
                            }
                        }
                    } else if(hasToDel) {
                        switch(hasToDel) {
                            case 1: { // set first point
                                Point p(renderer, Color(0,0,0));
                                p.setXY(x,y);
                                points[0] = p;
                                selectRect.setV1(x,y);
                                selectRect.setColor(Color(255,0,0));
                                hasToDel++;
                                //cout << "Drawing first selectRect point" << endl;
                                break;
                            }
                            case 3: { // delete everything inside
                                delMenuColor = Color(255,0,255);
                                for(int i = 0; i < rectangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*rectangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        rectangles.erase(rectangles.begin() + i);
                                    }
                                }
                                for(int i = 0; i < triangles.size(); i++) {
                                    if(SDL_HasIntersection(&(*triangles[i].getRectObj()), &(*selectRect.getRectObj()))) {
                                        triangles.erase(triangles.begin() + i);
                                    }
                                }
                                
                                // reset everything
                                points[0].setXY(0,0);
                                points[1].setXY(0,0);
                                selectRect.setV1(0,0);
                                selectRect.setV2(0,0);
                                hasToDel = 0;
                                drawSelectRect = false;
                                break;
                            }
                        }
                    } else {
                        points[0].setXY(0,0);
                        points[1].setXY(0,0);
                    }

                    SDL_RenderDrawRect(renderer, &mouse);
                    if(SDL_HasIntersection(&mouse, &triButt)) { // need to create a triangle
                        //cout << "Clicked on triangle button!" << endl;
                        if(!hasToDrawTri) {
                            triMenuColor = Color(128,255,0);
                            Triangle t{renderer, Color(0,0,0)};
                            triangles.push_back(t);
                            hasToDrawTri = 1;
                        }
                    } else if(SDL_HasIntersection(&mouse, &rectButt)) { // need to create a rectangle
                        //cout << "Clicked on rectangle button!" << endl;
                        if(!hasToDrawRect) {
                            rectMenuColor = Color(128,255,0);
                            Rectangle r{renderer, Color(0,0,0)};
                            rectangles.push_back(r);
                            hasToDrawRect = 1;
                        }
                    } else if(SDL_HasIntersection(&mouse, &moveButt)) { // need to move an object
                        //cout << "Clicked on move button!" << endl;
                        if(!hasToMove) {
                            moveMenuColor = Color(128,255,0);
                            hasToMove = 1;
                        }
                    } else if(SDL_HasIntersection(&mouse, &delButt)) { // need to delete an object
                        //cout << "Clicked on delete button!" << endl;
                        if(!hasToDel) {
                            delMenuColor = Color(128,255,0);
                            Rectangle r(renderer, Color(0,0,0));
                            selectRect = r;
                            hasToDel = 1;
                        }
                    }
                    //cout << "x: " << x << " | y: " << y << " | count: " << triangles.getCount() << endl;
                    //for(int i = 0; i < triangles.getCount(); i++) {
                    //    cout << "Triangle " << i << ": " << triangles[i].getV1()[0] << endl;
                    //}
                }
                break;
        }
        drawAll();
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    
    return 0;
}
