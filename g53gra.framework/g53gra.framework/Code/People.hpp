//
//  People.hpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef People_hpp
#define People_hpp

#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>
#include "VectorMath.h"
class People :
public DisplayableObject,
public Animation,
public Input
{
public:
    People(int id, int start,float y);
    ~People();
    
    void Display();
    void Update(const double& deltaTime);
    
    
protected:
    void drawCube(float width, int front, int left,int right,int back, int top, int bottom);
    int peopleSkin, peopleShoes, peopleLegSide,peopleLegFront,peopleHeadFront,peopleHeadBack,peopleBodySide,peopleBodyFront, peopleArm,peopleLeg;
    float armRotation;
    float legRotation;
    int increase;
    int status;
    int jump;
    int walk;
    float faceRotation;
    float initialY;
};
#endif /* People_hpp */
