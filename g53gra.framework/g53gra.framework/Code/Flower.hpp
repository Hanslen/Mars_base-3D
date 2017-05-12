//
//  Flower.hpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/10.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef Flower_hpp
#define Flower_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include <stdio.h>
#include <math.h>
class Flower :
public DisplayableObject,
public Animation,
public Input
{
public:
    Flower(GLfloat r, GLfloat g, GLfloat b, int boxneed);
    ~Flower();
    void Display();
    void Update(const double& deltaTime);
    
protected:
    void drawPillar(float h, float r, float incline, int cone, int base);
    void drawPlane(float r);
    void drawFlower();
    int texSoil;
    GLfloat flowerr, flowerg, flowerb;
    int box;
};


#endif /* Flower_hpp */
