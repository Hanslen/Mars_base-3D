//
//  LightHouse.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/13.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "LightHouse.hpp"
#include <iostream>
using namespace std;
#define M_PI 3.1415926
LightHouse::LightHouse(GLenum id):zPos(0),delay(0),zPosHelp(1)
{
    lightId = id;
    static GLfloat ambient[] =
    {
        0.1f, 0.1f, 0.1f, 1.0f
    };
    
    static GLfloat diffuse[] =
    {
        //		0.9f, 0.8f, 0.4f, 1.0f
        1.0f, 1.0f, 1.0f, 1.0f
    };
    
    static GLfloat specular[] =
    {
        1.0f, 1.0f, 0.0f, 1.0f
    };
    
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
}

LightHouse::~LightHouse()
{
    
}

void LightHouse::drawPillar(float h, float r, float incline, int cone)
{
    
    float th = 2.0f * M_PI;
    float res = 2.0f * M_PI / 20.0f;
    float x = r, z = 0.0f;
    do
    {
        glBegin(GL_QUADS);
        // Create first points
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
        glEnd();                    // end shape
    } while (th >= 0);
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

void LightHouse::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glPushMatrix();
        drawPillar(200.f, 30.f, 0.f, 0);
        glTranslated(0.f,20.f,0.f);
        glColor3f(1.f, 0.f, 0.f);
        drawPillar(30.f, 31.f, 0.f, 0.f);
        glTranslated(0.f, 50.f, 0.f);
        drawPillar(30.f, 31.f, 0.f, 0.f);
        glTranslated(0.f, 50.f, 0.f);
        drawPillar(30.f, 31.f, 0.f, 0.f);
        glTranslated(0.f, 50.f, 0.f);
        drawPillar(30.f, 31.f, 0.f, 0.f);
        glTranslated(0.f, 30.f, 0.f);
        glColor3f(1.f, 1.f, 1.f);
        drawPillar(10.f, 70.f, 0.f, 0.f);
        glTranslated(0.f, 10.f, 0.f);
        glColor3f(1.f, 0.f, 0.f);
        drawPillar(20.f, 30.f, 0.f, 0.f);
        glTranslated(0.f, 20.f, 0.f);
        glColor3f(1.f, 1.f, 1.f);
        //light
        glDisable(GL_LIGHTING);
        drawPillar(30.f, 30.f, 0.f, 0.f);
        glEnable(GL_LIGHTING);
        glTranslated(0.f, 30.f, 0.f);
        glColor3f(1.f, 0.f, 0.f);
        drawPillar(30.f, 50.f, 0.f, 1);
    glPopMatrix();
    glPopAttrib();
    glPopMatrix();
}
void LightHouse::Update(const double& deltaTime){
    glEnable(GL_LIGHTING);
    
    glLightfv(lightId, GL_AMBIENT, _ambient);
    glLightfv(lightId, GL_DIFFUSE, _diffuse);
    glLightfv(lightId, GL_SPECULAR, _specular);
    
    
    GLfloat lightpos[] = { pos[0], pos[1]+270, pos[2], 1.0f };
    
    glLightfv(lightId, GL_POSITION, lightpos);
    //define different direction of lights to perform a rotating animation
    static GLfloat direction[8][3] = {{1.f,0.f,0.f},{1.f,0.f,1.f},{0.f,0.f,1.f},{-1.f,0.f,1.f},{-1.f,0.f,0.f},{-1.f,0.f,-1.f},{0.f,0.f,-1.f},{1.f,0.f,-1.f}};
    glLightfv(lightId, GL_SPOT_DIRECTION, direction[zPos]);
    
    //adjust the rotating speed
    if(delay == 5){
        if(zPos < 7){
            zPos += 1;
            
        }
        else{
            zPos = 0;
        }
        delay = 0;
    }
    else{
        delay += 1;
    }
    //set the radius/cutoff of the light
    glLightf(lightId, GL_SPOT_EXPONENT, 0.1f);
    glLightf(lightId, GL_SPOT_CUTOFF, 60.f);
    
    //attenuation
    glLightf(lightId, GL_CONSTANT_ATTENUATION, 1); //default is 1 as well
    glLightf(lightId, GL_LINEAR_ATTENUATION, 0.00001 );
    glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.00001);
    glEnable(lightId);
}
