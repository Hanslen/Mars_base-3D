//
//  Plane.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/5/8.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>
#include "VectorMath.h"
class Plane :
public DisplayableObject,
public Animation,
public Input
{
public:
    Plane();
    ~Plane();
    
    
    void Display();
    void Update(const double& deltaTime);

    
protected:
    void drawCube(float width, int textureID);
    void drawHalfSphere(int scaley, int scalex, GLfloat r);
    void drawTriangularPrism(float width, int textureID);
    int texID;
    int returnPlane = 0;
    
};

#endif /* Plane_hpp */
