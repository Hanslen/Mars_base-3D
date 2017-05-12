//
//  OilTank.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "OilTank.hpp"
#include "VectorMath.h"
#include <iostream>
using namespace std;
OilTank::OilTank():rotatePillar(30.f), down(1),boxred(1.f),boxgreen(1.f),boxblue(1.f),oilLevel(0.f),boxShow(1)
{
#ifdef __APPLE__
    texID = Scene::GetTexture("./OilTankBody.bmp");
    texID2 = Scene::GetTexture("./oilTank.bmp");
#else
    texID = Scene::GetTexture("./Textures/OilTankBody.bmp");
    texID2 = Scene::GetTexture("./Textures/oilTank.bmp");
#endif
    
}


OilTank::~OilTank()
{
    
}
void OilTank::TankPillar(float h, float r, float incline, int cone)
{
    
    float th = 2.0f * M_PI;
    float res = 2.0f * M_PI / 20.0f;
    float x = r, z = 0.0f;
    do
    {
        glBegin(GL_QUADS);
        
        glNormal3f(x, 0.f, z);
        glTexCoord2f(1.f, 1.f);
        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
        }
        else{
            glVertex3f(0.f, h, 0.0f);
        }
        glTexCoord2f(0.f, 0.f);
        glVertex3f(x, 0.f, z);  // bottom
        // Iterate around circle
        th -= res;
        x = r*cos(th);
        z = r*sin(th);
        // Close quad
        glNormal3f(x, 0.f, z);
        glTexCoord2f(0.f, 1.f);
        glVertex3f(x, 0.f, z);  // bottom
        glTexCoord2f(1.f, 0.f);
        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
        }
        else{
            glVertex3f(0.f, h, 0.0f);
        }
        glEnd();
    } while (th >= 0);
    if(cone != 1){
    x = r, z = 0.0f; th = 2.0f * M_PI;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0f, 1.f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.0f, h, 0.0f);
        do
        {
            glTexCoord2f(0.f, 1.f);
            glVertex3f(x, h, z);
            th -= res;
            x = r*cos(th); z = r*sin(th);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(x, h, z);
        } while (th >= 0);
    }
    glEnd();
    }
    x = r, z = 0.0f;th = 0.0f;
    
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        do
        {
            glTexCoord2f(0.f, 1.f);
            glVertex3f(x, 0.0f, z);
            th += res;
            x = r*cos(th); z = r*sin(th);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(x, 0.0f, z);
        } while (th <= 2.0f * M_PI);
    }
    glEnd();
    
}


void OilTank::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    
    //core framework
    glPushMatrix();
        TankPillar(100.f,10.f, 0.f,0);
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(50.f, 0.f, 0.f);
        TankPillar(100.f, 5.f, -50.f,0);
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(-50.f, 0.f, 0.f);
        TankPillar(100.f, 5.f, 50.f,0);
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.f, 95.f, 0.f);
        glPushMatrix();
            glPushMatrix();
                glRotated(-(180.f-rotatePillar), 0.f, 0.f, 1.f);
                TankPillar(40.f, 5.f, 0.f,0);
            glPopMatrix();
    
            glPushMatrix();
                glRotated(rotatePillar, 0.f, 0.f, 1.f);
                TankPillar(110.f, 5.f, 0.f,0);
                glPushMatrix();
                    glTranslated(0.f, 110.f, 0.f);
                    glPushMatrix();
                        glRotated(-90.f, 0.f, 0.f, 1.f);
                        TankPillar(30.f, 10.f, 0.f,1);
                    glPopMatrix();
                    glPushMatrix();
                        glRotated(90.f, 0.f, 0.f, 1.f);
                        TankPillar(30.f, 10.f, 0.f,1);
                    glPopMatrix();
                    glTranslated(-29.f, 0.f, 0.f);
                    glRotated(-rotatePillar, 0.f, 0.f, 1.f);
                    glRotated(180.f, 1.f, 0.f, 0.f);
                    TankPillar(110.f, 1.f, 0.f,0);
                    glPushMatrix();
                        glDisable(GL_TEXTURE_2D);
                        glColor4f(boxred, boxgreen, boxblue,boxShow);
                        glTranslated(0.f, 110.f, 0.0f);
                        glutSolidCube(20.f);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    
    //oil bottle
    glPushMatrix();
        glColor3f(1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texID2);
        glTranslated(100.f, 0.f, 0.f);
        TankPillar(50.f, 50.f, 0.f,0);
        glColor3f(1.0f, 1.f, 0.f);
        TankPillar(oilLevel, 50.f, 0.f,0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPopAttrib();
    glPopMatrix();
}



void OilTank::Update(const double& deltaTime)
{
    //when the oil tank is full, it will stop and waiting for the DisposeOil(Truck) to collect.
    if(oilLevel >=50.f){
        if(DisposeOil::deliverOil == 0){
            DisposeOil::deliverOil = 1;
            oilLevel = 0.f;
        }
        else{
            oilLevel = 50.f;
        }
        
    }
    else{//collecting oil
        if(rotatePillar > 70.f){//when the box is below the water, it will not appear.
            boxShow = 0;
        }
        else{
            boxShow = 1;
        }
        switch (down) {//rotating the pillar, change the box color and increase the oil tank level.
            case 0:
                if(rotatePillar < 30.f){
                    rotatePillar += 1.f;
                    down = 1;
                    boxblue = 1.f;
                    oilLevel += 10.f; //2.f
                }
                else{
                    rotatePillar -= 1.f;
                }
                break;
            case 1:
                if(rotatePillar > 100.f){
                    rotatePillar -= 1.f;
                    down = 0;
                    boxblue = 0.f;
                }
                else{
                    rotatePillar += 1.f;
                }
            case 2:
                break;
            default:
                break;
        }
    }
    
}

void OilTank::HandleKey(unsigned char key, int state, int mx, int my)
{

}

void OilTank::HandleSpecialKey(int key, int state, int mx, int my)
{
    
}
