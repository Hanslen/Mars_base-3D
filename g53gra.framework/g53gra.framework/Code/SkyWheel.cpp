//
//  SkyWheel.cpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/8.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "SkyWheel.hpp"
SkyWheel::SkyWheel(){
    rotateWheel = 0.f;
#ifdef __APPLE__
    texDoor = Scene::GetTexture("./skyWheelDoor.bmp");
    texSide = Scene::GetTexture("./skyWheelSide.bmp");
    texTop = Scene::GetTexture("./skyWheelTop.bmp");
#else
    texDoor = Scene::GetTexture("./Textures/skyWheelDoor.bmp");
    texSide = Scene::GetTexture("./Textures/skyWheelSide.bmp");
    texTop = Scene::GetTexture("./Textures/skyWheelTop.bmp");

#endif
}

SkyWheel::~SkyWheel(){
}

void SkyWheel::drawPillar(float h, float r, float incline, int cone)
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
void SkyWheel::drawCube(float width, int textureID){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texTop);
    glBegin(GL_QUADS);
    
    // draw the front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, width, width);
    glEnd();
    
    // draw the back face
    glBindTexture(GL_TEXTURE_2D, texSide);
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
    
    // draw the left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.f, width, width);
    
    // draw the right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, width, 0.f);
    glEnd();
    
    // draw the top face
    glBindTexture(GL_TEXTURE_2D, texDoor);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, width, width);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, width, width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, width, 0.f);
    
    // draw the bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, 0.f, width);
    glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, NULL);
    
    glDisable(GL_TEXTURE_2D);
}

void SkyWheel::drawHalfSphere(int scaley, int scalex, GLfloat r) {
    int i, j;
    GLfloat v[30*30][3];
    
    for (i=0; i<scalex; ++i) {
        for (j=0; j<scaley; ++j) {
            v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
            v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
            v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
        }
    }
    
    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i) {
        for (j=0; j<scaley; ++j) {
            glVertex3fv(v[(i+1)*scaley+j]);
            glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
            glVertex3fv(v[i*scaley+(j+1)%scaley]);
            glVertex3fv(v[i*scaley+j]);
        }
    }
    glEnd();
}
void SkyWheel::drawCircle(float radius){
    const float DEG2RAD = 3.14159/180;
    for(float height = 0; height < 2;height+=0.1f){
    glBegin(GL_LINE_LOOP);
    for (int i=0; i < 360; i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,height);
    }
    
    glEnd();
    }
}

void SkyWheel::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glScalef(scale[0], scale[1], scale[2]);
    
    //draw the skywheel base
    glPushMatrix();
        drawPillar(50.f, 1.f, 15.f, 0);
        glTranslated(30.f, 0.f, 0.f);
        drawPillar(50.f, 1.f, -15.f, 0);
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.f, 0.f, 12.f);
        drawPillar(50.f, 1.f, 15.f, 0);
        glTranslated(30.f, 0.f, 0.f);
        drawPillar(50.f, 1.f, -15.f, 0);
    glPopMatrix();
    glTranslated(15.f, 50.f, -4.f);
    glPushMatrix();
        glRotatef(90.f, 1.f, 0.f, 0.f);
        drawPillar(18.f, 4.f, 0, 0);
    glPopMatrix();
    
    
    glPushMatrix();
    glRotatef(rotateWheel, 0.f, 0.f, 1.f);
    
    //main framework and the carriage
    glTranslated(0.f, 0.f, 15.f);
    glPushMatrix();
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(0.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(30.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(60.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(90.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
            glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(120.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(150.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(180.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(210.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(240.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(270.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(300.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glPushMatrix();
            glTranslated(0.f, 35.f, 0.f);
            glRotatef(-90.f, 1.f, 0.f, 0.f);
            drawPillar(10.f, 1.f, 0.f, 0.f);
            glRotatef(330.f+rotateWheel, 0.f, 1.f, 0.f);
            glTranslated(-5.f, 0.f, -10.f);
            drawCube(10.f,0);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        drawCircle(35.f);
    glPopMatrix();
    glTranslated(0.f, 0.f, -25.f);
    
    //backbone of the skywheel
    glTranslated(0.f, 0.f, 15.f);
    glPushMatrix();
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
        glRotatef(30.f, 0.f, 0.f, 1.f);
        drawPillar(35.f, 1.f, 0.f, 0.f);
    glPopMatrix();
    glPushMatrix();
        drawCircle(35.f);
    glPopMatrix();
    
    glPopMatrix();
    glPopAttrib();
    glPopMatrix();
    
}

void SkyWheel::Update(const double& deltaTime){
    rotateWheel += 0.2f;
}

