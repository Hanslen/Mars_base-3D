//
//  DisposeOil.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/5/4.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "DisposeOil.hpp"
#include "VectorMath.h"
#include <iostream>
using namespace std;
int DisposeOil::deliverOil = 0;
DisposeOil::DisposeOil(){
#ifdef __APPLE__
    wheelId = Scene::GetTexture("./wheel.bmp");
    wheelRId = Scene::GetTexture("./wheelR.bmp");
    truckFront = Scene::GetTexture("./truckFront.bmp");
    truckSide = Scene::GetTexture("./truckSide.bmp");
    truckSide2 = Scene::GetTexture("./truckSide2.bmp");
#else
    wheelId = Scene::GetTexture("./Textures/wheel.bmp");
    wheelRId = Scene::GetTexture("./Textures/wheelR.bmp");
    truckFront = Scene::GetTexture("./Textures/truckFront.bmp");
    truckSide = Scene::GetTexture("./Textures/truckSide.bmp");
    truckSide2 = Scene::GetTexture("./Textures/truckSide2.bmp");
#endif
};
DisposeOil::~DisposeOil(){
};

void DisposeOil::startDeliverOil(){
    DisposeOil::deliverOil = 1;
}
void DisposeOil::TankPillar(float h, float r, float incline, int cone)
{
    
    float th = 2.0f * M_PI;
    float res = 2.0f * M_PI / 20.0f;
    float x = r, z = 0.0f;
    do
    {
        glBegin(GL_QUADS);          // new QUAD
        // Create first points
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
        }
        else{
            glVertex3f(0.f, h, 0.0f);
        }
        glTexCoord2f(0.f, 0.f);
        glVertex3f(x, 0.f, z);  // bottom
        // Iterate around circle
        th -= res;               // add increment to angle
        x = r*cos(th);           // move x and z around circle
        z = r*sin(th);
        // Close quad
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(0.f, 1.f);  // (s,t) = (1,1)
        glVertex3f(x, 0.f, z);  // bottom
        glTexCoord2f(1.f, 0.f);  // (s,t) = (1,1)
        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
        }
        else{
            glVertex3f(0.f, h, 0.0f);
        }
        glEnd();                    // end shape
    } while (th >= 0);        // for a full circle (360 degrees)
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
void DisposeOil::drawCube(float width, int textureID, int camera){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glEnd();
    if(camera == 1){
        glBindTexture(GL_TEXTURE_2D, truckSide);
    }
    glBegin(GL_QUADS);
    float holdTexture = 1.f;
    // left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(0.f, width, width);
    glEnd();
    if(camera == 1){
        glBindTexture(GL_TEXTURE_2D, truckSide2);
    }
    glBegin(GL_QUADS);
    // right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(width, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, width, 0.f);
    
    if(camera == 1){
        holdTexture = 0.f;
    }

    //back
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, width, width);
    
    // draw the top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, width, width);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, width, width);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, width, 0.f);
    // draw the bottom face
    // set the colour of the front face
    // set the normal of the front face
    glNormal3f(0.0f, -1.0f, 0.0f);
    // define texture coordinates for the 4 vertices
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, 0.f, width);
    glEnd();
    // Stop blending textures and colours
    glDisable(GL_COLOR_MATERIAL);
    // Bind to the blank buffer to stop ourselves accidentaly
    // using the wrong texture in the next draw call
    glBindTexture(GL_TEXTURE_2D, NULL);
    // Stop performing texturing
    glDisable(GL_TEXTURE_2D);
}
void DisposeOil::DrawWheel()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glScalef(0.2f, 0.5f, 0.5f);
    float th = 0.0f;
    float res = 2.0f * M_PI / 20.0f;
    float y = 1.0f, z = 0.0f;
//    apply texture to the wheel
    glBindTexture(GL_TEXTURE_2D, wheelRId);
    do
    {
        glBegin(GL_QUADS);
        {
            glNormal3f(0.0f, y, z);
            glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
            glVertex3f(0.5f, y, z);
            glTexCoord2f(0.f, 1.f);  // (s,t) = (1,1)
            glVertex3f(-0.5f, y, z);
            th += res;
            y = cos(th); z = sin(th);
            glNormal3f(0.0f, y, z);
            glTexCoord2f(0.f, 0.f);  // (s,t) = (1,1)
            glVertex3f(-0.5f, y, z);
            glTexCoord2f(1.f, 0.f);  // (s,t) = (1,1)
            glVertex3f(0.5f, y, z);
        }
        glEnd();
    } while (th <= 2.0f * M_PI);
    y = 1.0f, z = 0.0f; th = 0.0f;
    glBindTexture(GL_TEXTURE_2D, wheelId);
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        do
        {
            glTexCoord2f(0.f, 1.f);
            glVertex3f(0.5f, y, z);
            th += res;
            y = cos(th); z = sin(th);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(0.5f, y, z);
        } while (th <= 2.0f * M_PI);
    }
    glEnd();
    y = 1.0f, z = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        do
        {
            glTexCoord2f(0.f, 1.f);
            glVertex3f(-0.5f, y, z);
            th -= res;
            y = cos(th); z = sin(th);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(-0.5f, y, z);
        } while (th >= 0.0f);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void DisposeOil::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    drawCube(5.f, truckFront, 1);
    glPushMatrix();
        glTranslated(0.f, 0.f, 3.f);
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(5.f, 0.f, 3.f);
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    
    glTranslated(0.f, 0.8f, 5.f);
    glColor3f(1.f, 1.f, 1.f);
    
    glPushMatrix();
        glScaled(1.f, 0.1f, 2.5f);
        drawCube(5.f, 0, 0);
    glPopMatrix();
    
    //oil tank
    glPushMatrix();
        glTranslated(2.5f, 2.5f, 0.5f);
        glRotated(90.f, 1.f, 0.f, 0.f);
        glScaled(1.f, 2.2f, 1.f);
        TankPillar(5.f, 2.5f, 0, 0);
    glPopMatrix();
    glColor3f(1.f, 0.f, 0.f);
    glPushMatrix();
        glTranslated(-0.1f, 2.f, 0.5f);
        glScaled(0.1f, 0.1f, 2.2f);
        drawCube(5.f, 0, 0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(4.7f, 2.f, 0.5f);
        glScaled(0.1f, 0.1f, 2.2f);
        drawCube(5.f, 0, 0);
    glPopMatrix();
    glColor3f(1.f, 1.f, 1.f);
    
    //draw wheel
    glTranslated(0.f, -0.8f, 8.f);
    glPushMatrix();
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    glPushMatrix();
        glTranslated(5.1f, 0.f, 0.f);
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    glTranslated(0.f, 0.f, 2.3f);
    glPushMatrix();
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    glPushMatrix();
        glTranslated(5.1f, 0.f, 0.f);
        glScaled(2.f, 2.f, 2.f);
        DrawWheel();
    glPopMatrix();
    
    glPopAttrib();
    glPopMatrix();
}

//define truck path
void DisposeOil::Update(const double& deltaTime){
    if(DisposeOil::deliverOil != 0){
        if(DisposeOil::deliverOil < 40){
            pos[0] += 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 50){
            rotation[1]-=9.f;
            pos[2] += 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil<170){
            pos[2]+= 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 180){
            rotation[1]-=9.f;
            pos[0] -= 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil< 480){
            pos[0] -= 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil<490){
            rotation[1]-=9.f;
            pos[2] -= 10.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil< 630){
            pos[2] -= 5.0f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 640){
            pos[0] += 5.f;
            rotation[1]-= 9.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 740){
            pos[0] += 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 840){
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 940){
            pos[0] += 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 1040){
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil < 1120){
            pos[0] += 5.0f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil< 1130){
            pos[2] += 5.f;
            rotation[1]-=9.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil< 1150){
            pos[2]+=5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil<1160){
            rotation[1]+= 9.f;
            pos[0] -= 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil<1170){
            pos[0] -= 5.f;
            DisposeOil::deliverOil++;
        }
        else if(DisposeOil::deliverOil<1190){
            DisposeOil::deliverOil++;
        }
        else{
            DisposeOil::deliverOil = 0;
        }
    }
};
void DisposeOil::HandleKey(unsigned char key, int state, int mx, int my){
};
void DisposeOil::HandleSpecialKey(int key, int state, int mx, int my){
};
