//
//  OilTank.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef OilTank_hpp
#define OilTank_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "DisposeOil.hpp"
#include "Animation.h"
#include "Input.h"
class OilTank :
public DisplayableObject,
public Animation,
public Input
{
public:
    OilTank();
    ~OilTank();
    
    
    void Display();
    
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int mx, int my);
    void HandleSpecialKey(int key, int state, int mx, int my);
    
protected:
    void TankPillar(float h, float r, float incline, int cone);
    float rotatePillar;
    int down;
    int texID;
    int texID2;
    float boxred,boxgreen,boxblue;
    int boxShow;
    float oilLevel;
    
};
#endif /* OilTank_hpp */

