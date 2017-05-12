//
//  HeadLight.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/17.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "HeadLight.hpp"
#define M_PI 3.1415926
HeadLight::HeadLight(GLenum id){
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
HeadLight::~HeadLight(){
}
void HeadLight::drawPillar(float h, float r, float incline, int cone, int base)
{
    
    float th = 2.0f * M_PI;
    float res = 2.0f * M_PI / 20.0f;
    float x = r, z = 0.0f;
    do
    {
        glBegin(GL_QUADS);
        glNormal3f(x, 0.f, z);
        glTexCoord2f(1.f, 1.f);
        glVertex3f(x+incline, h, z);
        glTexCoord2f(0.f, 0.f);
        if(cone != 1){
            glVertex3f(x, 0.f, z);  // bottom
        }
        else{
            glVertex3f(0.f, 0.f, 0.f);  // bottom
        }
        
        th -= res;
        x = r*cos(th);
        z = r*sin(th);
        glNormal3f(x, 0.f, z);
        glTexCoord2f(0.f, 1.f);
        if(cone != 1){
            glVertex3f(x, 0.f, z);
        }
        else{
            glVertex3f(0.f, 0.f, 0.f);
        }
        glTexCoord2f(1.f, 0.f);
        glVertex3f(x+incline, h, z);
        
        glEnd();                  
    } while (th >= 0);
    glDisable(GL_LIGHTING);
    x = r, z = 0.0f; th = 2.0f * M_PI;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0f, 1.f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.0f+incline, h, 0.0f);
        do
        {
            glTexCoord2f(0.f, 1.f);
            glVertex3f(x+incline, h, z);
            th -= res;
            x = r*cos(th); z = r*sin(th);
            glTexCoord2f(1.f, 1.f);
            glVertex3f(x+incline, h, z);
        } while (th >= 0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    
    if(cone != 1){
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
}

void HeadLight::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glTranslatef(pos[0], pos[1], pos[2]);
        glRotated(rotation[1], 0.f, 1.f, 0.f);
        glScalef(scale[0], scale[1], scale[2]);
        drawPillar(30.f, 1.f, 0.f, 0, 0);
        glPushMatrix();
            glTranslated(0.f, 0.f, 5.f);
            drawPillar(30.f, 1.f, 0.f, 0, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(4.f, 30.f, 2.5f);
            glRotated(110.f, 0.f, 0.f, 1.f);
            drawPillar(10.f, 5.f, 0.f, 0, 0);
        glPopMatrix();
    //debug light
//    glPushMatrix();
//        glTranslated(-50.f, 0.f, 0.f);
//        glPushMatrix();
//            glScaled(0.1f, 100.f, 3.f);
//            drawPillar(1.f, 10.f, 0, 0, 0);
//        glPopMatrix();
//    glPushMatrix();
//    glTranslated(50.f, 0.f, 50.f);
//        glRotated(90.f, 0.f, 1.f, 0.f);
//        glScaled(0.1f, 100.f, 3.f);
//        drawPillar(1.f, 50.f, 0, 0, 0);
//    glPopMatrix();
//    glTranslated(100.f, 0.f, 0.f);
//    glPushMatrix();
//    glScaled(0.1f, 100.f, 3.f);
//    drawPillar(1.f, 10.f, 0, 0, 0);
//    glPopMatrix();
//    glPopMatrix();
    
    glPopAttrib();
    glPopMatrix();
}
void HeadLight::Update(const double& deltaTime){
    glEnable(GL_LIGHTING);
    
    glLightfv(lightId, GL_AMBIENT, _ambient);
    glLightfv(lightId, GL_DIFFUSE, _diffuse);
    glLightfv(lightId, GL_SPECULAR, _specular);
    
    
    GLfloat lightpos[] = { pos[0], pos[1]+50.f, pos[2]+5.f, 1.0f };
//    glutSolidSphere(10.f, 10.f, 10.f);
    
    glLightfv(lightId, GL_POSITION, lightpos);
    static GLfloat direction[3] = {-1.f,0.f,0.f};
//    if(lightId == GL_LIGHT3){
//        direction[0] = -1.f;
//    }
    glLightfv(lightId, GL_SPOT_DIRECTION, direction);
    
    glLightf(lightId, GL_SPOT_EXPONENT, 1.f);
    glLightf(lightId, GL_SPOT_CUTOFF, 30.f);
    
    glLightf(lightId, GL_CONSTANT_ATTENUATION, 1); //default is 1 as well
    glLightf(lightId, GL_LINEAR_ATTENUATION, 0.000000000000000001 );
    glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.000000000000000001);
    glEnable(lightId);
}
