//
//  SkyWheel.hpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/8.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef SkyWheel_hpp
#define SkyWheel_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>
#include "VectorMath.h"
class SkyWheel :
public DisplayableObject,
public Animation,
public Input
{
public:
    SkyWheel();
    ~SkyWheel();
    
    
    void Display();
    void Update(const double& deltaTime);
    
    
protected:
    void drawCube(float width, int textureID);
    void drawHalfSphere(int scaley, int scalex, GLfloat r);
    void drawPillar(float h, float r, float incline, int cone);
    void drawCircle(float radius);
    int texDoor;
    int texSide;
    int texTop;
    float rotateWheel;
    
};
#endif /* SkyWheel_hpp */
