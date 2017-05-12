//
//  BaseBuilding.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/13.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef BaseBuilding_hpp
#define BaseBuilding_hpp
#include "DisplayableObject.h"
#include "Animation.h"
#include <stdio.h>
#include <math.h>
class BaseBuilding :
public DisplayableObject,
public Animation,
public Input
{
public:
    BaseBuilding();
    ~BaseBuilding();
    void Display();
    void Update(const double& deltaTime);
    
protected:
    void drawPillar(float h, float r, float incline, int cone, int base);
    void drawPlane(float r);
    void drawCube(float width);
    void drawChiken();
    float rotateDegree;
    int texID;
    int texID2;
    float wingAngle;
    int wingStatus;
    int chickenJump;
    float chickHeight;
    
};

#endif /* BaseBuilding_hpp */
