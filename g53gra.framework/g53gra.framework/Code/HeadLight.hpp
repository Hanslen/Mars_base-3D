//
//  HeadLight.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/17.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef HeadLight_hpp
#define HeadLight_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include <stdio.h>
#include <math.h>
class HeadLight :
public DisplayableObject,
public Animation,
public Input
{
public:
    HeadLight(GLenum id);
    ~HeadLight();
    void Display();
    void Update(const double& deltaTime);
    
protected:
    GLfloat *_ambient, *_diffuse, *_specular;
    GLenum lightId;
    void drawPillar(float h, float r, float incline, int cone, int base);
};
#endif /* HeadLight_hpp */
