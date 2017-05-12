//
//  SolarPanel.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/17.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef SolarPanel_hpp
#define SolarPanel_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include <math.h>
class SolarPanel :
public DisplayableObject,
public Animation,
public Input
{
public:
    SolarPanel();
    ~SolarPanel();
    void Display();
    void Update(const double& deltaTime);
    
protected:
    int texID;
    void drawCube(float width, int textureID);
};
#endif /* SolarPanel_hpp */
