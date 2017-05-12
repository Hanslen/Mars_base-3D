//
//  DisposeOil.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/5/4.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef DisposeOil_hpp
#define DisposeOil_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
class DisposeOil :
public DisplayableObject,
public Animation,
public Input
{
public:
    DisposeOil();
    ~DisposeOil();
    
    
    void Display();
    
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int mx, int my);
    void HandleSpecialKey(int key, int state, int mx, int my);
    void startDeliverOil();
    static int deliverOil;
    
protected:
    void TankPillar(float h, float r, float incline, int cone);
    void drawCube(float width, int textureID, int camera);
    void DrawWheel();
    int wheelId;
    int wheelRId;
    int truckFront;
    int truckSide;
    int truckSide2;
    
};
#endif /* DisposeOil_hpp */
