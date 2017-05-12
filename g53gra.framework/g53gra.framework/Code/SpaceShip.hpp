//
//  SpaceShip.hpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#ifndef SpaceShip_hpp
#define SpaceShip_hpp
// Rate of rotation around y (18 degrees per second)
#define _ROTV 18.0f
// Pointer index for vertex 0
#define _VERTEX0 0
// Pointer index for vertex 1
#define _VERTEX1 3
// Pointer index for vertex 2
#define _VERTEX2 6
// Pointer index for vertex 3
#define _VERTEX3 9
// Pointer index for vertex 4
#define _VERTEX4 12
// Pointer index for vertex 5
#define _VERTEX5 15
// Cap subdivisons at 7
#define _MAX_RES 7
#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>
#include "VectorMath.h"
class SpaceShip :
public DisplayableObject,
public Animation,
public Input
{
public:
    SpaceShip(int id, float x, float y);
    ~SpaceShip();
    
    
    void Display();
    
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int mx, int my);
    void HandleSpecialKey(int key, int state, int mx, int my);
    // Manually set resolution
    inline void SetResolution(int r) { _resolution = r >= 0 ? (r > _MAX_RES ? _MAX_RES : r) : 0; }
    // Toggle wire frame model
    inline void ToggleWireFrame() { _flagWireFrame = !_flagWireFrame; }
    // Toggle rotation animation
    inline void ToggleAnimation() { _flagAnimation = !_flagAnimation; }
    
protected:
    void DrawSphere();
    void FixSeam(float &a, float &b, float &c);
    void DrawFace(float *a, float *b, float *c);
    void SubDivide(int recurse_idx, float *a, float *b, float *c);
    void UFOCompo(float h, float r, float incline, int cone);
    float leg;
    int texID;
    int texID2;
    int status;
    int _resolution;
    GLboolean _flagWireFrame;
    GLboolean _flagAnimation;
    float* _initV;
    int launchId;
    float initialx;
    float initialy;

    
};
#endif /* SpaceShip_hpp */
