//
//  LightHouse.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/13.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef LightHouse_hpp
#define LightHouse_hpp
#include "DisplayableObject.h"
#include "Animation.h"
#include <stdio.h>
#include <math.h>
class LightHouse :
public DisplayableObject,
public Animation,
public Input
{
public:
    LightHouse(GLenum id);
    ~LightHouse();
    void Display();
    void Update(const double& deltaTime);
    
protected:
    void drawPillar(float h, float r, float incline, int cone);
    GLfloat *_ambient, *_diffuse, *_specular;
    int zPos;
    int delay;
    int zPosHelp;
    GLenum lightId;
};

#endif /* LightHouse_hpp */
