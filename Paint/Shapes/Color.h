//
//  Color.h
//  Paint
//
//  Created by Justin on 6/28/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef Color_h
#define Color_h

class Color {
    int r, g, b;
    
public:
    // ctor
    Color(int red, int green, int blue): r(red), g(green), b(blue) {};
    // setters and getters
    void setRed(int red) {
        r = red;
    }
    void setGreen(int green) {
        g = green;
    }
    void setBlue(int blue) {
        b = blue;
    }
    int getRed() {
        return r;
    }
    int getGreen() {
        return g;
    }
    int getBlue() {
        return b;
    }
};

#endif /* Color_h */
