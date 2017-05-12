//
//  BaseBuilding.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/13.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "BaseBuilding.hpp"
#include <iostream>
using namespace std;
#define M_PI 3.1415926
BaseBuilding::BaseBuilding():rotateDegree(0.f),wingAngle(0.f),wingStatus(1),chickenJump(1),chickHeight(0.f)
{
#ifdef __APPLE__
    texID = Scene::GetTexture("./grass.bmp");
    texID2 = Scene::GetTexture("./chickenSkin.bmp");
#else
    texID = Scene::GetTexture("./Textures/grass.bmp");
    texID2 = Scene::GetTexture("./Textures/chickenSkin.bmp");
#endif
}

BaseBuilding::~BaseBuilding()
{
    
}
void BaseBuilding::drawPlane(float r){
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0f, 1.f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.0f, 0.f, 0.0f);
        glTexCoord2f(0.f, 1.f);
        glVertex3f(0.0f, 0.f, r);
        glTexCoord2f(1.f, 1.f);
        glVertex3f(r, 0.f, r);
        glTexCoord2f(1.f, 0.f);
        glVertex3f(r, 0.f, 0.0f);

    }
    glEnd();
}
void BaseBuilding::drawCube(float width){
    
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, texID2);
    glBegin(GL_QUADS);
    
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, width, width);
    
    // draw the back face
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
    
    // draw the top face
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

void BaseBuilding::drawChiken(){
    
    glPushMatrix();
        glTranslated(0.f, chickHeight, 0.f);
        glPushMatrix();
            glColor3f(1.f, 1.f, 1.f);
            glTranslated(-0.5f, 0.f, -1.f);
            glScaled(1.f, 1.f, 1.5f);
            drawCube(4.f);
            //left eye
            glScaled(1.f, 1.f, 1/1.5f);
            glColor3f(0.f, 0.f, 0.f);
            glTranslated(0.6f, 6.4f, 5.1f);
            drawCube(1.f);
            //right eye
            glTranslated(1.8f, 0.f, 0.f);
            drawCube(1.f);
            glColor3f(190/255.f, 145/255.f, 53/255.f);
            glTranslated(-2.0f, -0.75f, 1.f);
            glScaled(1.5f, 0.4f, 0.5f);
            drawCube(2.f);
            //mouth
            glColor3f(190/255.f, 5/255.f, 1/255.f);
            glScaled(1.f, 2.f, 1.f);
            glTranslated(0.6f, -1.f, 0.f);
            drawCube(1.f);
        glPopMatrix();
    
        glColor3f(1.f, 1.f, 1.f);
        glPushMatrix();
            glTranslated(3.5f, 4.f, -1.f);
            glRotated(180.f, 0.f, 0.f, 1.f);
            glRotated(wingAngle, 0.f, 0.f, 1.f);
            glScaled(0.3f, 1.f, 1.8f);
            drawCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-0.5f, 3.8f, -1.f);
            glRotated(180-wingAngle, 0.f, 0.f, 1.f);
            glScaled(0.3f, 1.f, 1.8f);
            drawCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glColor3f(0.9f, 0.9f, 0.9f);
            glTranslated(0.f, 4.2f, 2.f);
            glScaled(1.f, 1.3f, 1.f);
            drawCube(3.f);
        glPopMatrix();
        //claws
        glPushMatrix();
            glColor3f(220/255.f, 200/255.f, 91/255.f);
            glTranslated(0.1f, -2.8f,2.2f);
            //left
            glPushMatrix();
                glScaled(1.f, 5.f, 1.f);
                drawCube(0.5f);
                glScaled(1.f, 0.2f, 1.f);
                glTranslated(-0.5f, -0.5f, 0.f);
                glScaled(1.f, 0.5f, 1.f);
                drawCube(1.f);
            glPopMatrix();
            //right
            glPushMatrix();
                glTranslated(2.f, 0.f, 0.f);
                glScaled(1.f, 5.f, 1.f);
                drawCube(0.5f);
                glScaled(1.f, 0.2f, 1.f);
                glTranslated(0.f, -0.5f, 0.f);
                glScaled(1.f, 0.5f, 1.f);
                drawCube(1.f);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void BaseBuilding::drawPillar(float h, float r, float incline, int cone, int base)
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
//        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
//        }
//        else{
//            glVertex3f(0.f, h, 0.0f);
//        }
        glTexCoord2f(0.f, 0.f);
        if(cone != 1){
        glVertex3f(x, 0.f, z);  // bottom
        }
        else{
            glVertex3f(0.f, 0.f, 0.f);  // bottom
        }
        // Iterate around circle
        th -= res;               // add increment to angle
        x = r*cos(th);           // move x and z around circle
        z = r*sin(th);
        // Close quad
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(0.f, 1.f);  // (s,t) = (1,1)
        if(cone != 1){
        glVertex3f(x, 0.f, z);  // bottom
        }
        else{
            glVertex3f(0.f, 0.f, 0.f);
        }
        glTexCoord2f(1.f, 0.f);  // (s,t) = (1,1)
//        if(cone != 1){
            glVertex3f(x+incline, h, z);    // top
//        }
//        else{
//            glVertex3f(0.f, h, 0.0f);
//        }
        glEnd();                    // end shape
    } while (th >= 0);        // for a full circle (360 degrees)
    
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

void BaseBuilding::Display(){
//    glDisable(GL_LIGHTING);
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    
    glPushMatrix();
        glTranslated(0.f, 3.f, 0.f);
        drawPillar(12.f, 8.f, 0.f, 0.f, 1);
        glPushMatrix();
            glTranslated(-13.f, -3.f, 0.f);
            drawPillar(5.f, 1.f, 6.f, 0,1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(13.f, -3.f, 0.f);
            glRotated(180.f, 0.f, 1.f, 0.f);
            drawPillar(5.f, 1.f, 6.f, 0,1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, -3.f, 13.f);
            glRotated(90.f, 0.f, 1.f, 0.f);
            drawPillar(5.f, 1.f, 6.f, 0,1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, -3.f, -13.f);
            glRotated(-90.f, 0.f, 1.f, 0.f);
            drawPillar(5.f, 1.f, 6.f, 0,1);
        glPopMatrix();
    //window
        glPushMatrix();
            glColor3f(0.6f, 0.6f, 0.6f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(45.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(90.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(135.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(-45.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(-90.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(-135.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glRotated(180.f, 0.f, 1.f, 0.f);
            glTranslated(0.f, 9.f, 7.f);
            glutSolidCube(3.f);
        glPopMatrix();
        glPushMatrix();
            glColor3f(1.f, 1.f, 1.f);
            glTranslated(4.f, 12.f, 0.f);
            drawPillar(8.f, 0.3f, 0.f, 0.f,0);
            glTranslated(0.f, 7.f, 0.f);
            glRotated(70.f, 0.f, 0.f, 1.f);
            glRotated(rotateDegree, 1.f, 0.f, 0.f);
            drawPillar(4.f, 3.f, 0.f, 1,0);
        glPopMatrix();
    
    //farmyard
        glPushMatrix();
            glTranslated(-8.f, 5.f, 0.f);
            glPushMatrix();
                glRotated(90.f, 0.f, 0.f, 1.f);
                drawPillar(20.f, 1.f, -5.f, 0.f, 0.f);
            glPopMatrix();
    
    glDisable(GL_LIGHTING);
            glPushMatrix();
            //animal in side
                glTranslated(-45.f, -5.f,5.f);
                glColor3f(1.f, 1.f, 0.f);
                drawChiken();
                glTranslated(15.f, 0.f, 0.f);
                drawChiken();
                glTranslated(0.f, 0.f, -20.f);
                drawChiken();
                glTranslated(-15.f, 0.f, 0.f);
                drawChiken();
            glPopMatrix();
            glTranslated(-50.f, -10.f, -15.f);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texID);
            drawPlane(30.f);
            glDisable(GL_TEXTURE_2D);
            glColor4f(1.f, 1.f, 1.f, 0.5);
            glPushMatrix();
                glTranslated(0.f, 30.f, 30.f);
                glRotated(90.f, 1.f, 0.f, 0.f);
                drawPlane(30.f);
            glPopMatrix();
            glPushMatrix();
                glTranslated(0.f, 0.f, 0.f);
                glRotated(90.f, 0.f, 0.f, 1.f);
                drawPlane(30.f);
            glPopMatrix();
            glPushMatrix();
                glTranslated(30.f, 30.f, 0.f);
                glRotated(-90.f, 0.f, 0.f, 1.f);
                drawPlane(30.f);
            glPopMatrix();
            glPushMatrix();
                glTranslated(0.f, 0.f, 0.f);
                glRotated(-90.f, 1.f, 0.f, 0.f);
                drawPlane(30.f);
            glPopMatrix();
            glPushMatrix();
                glTranslated(0.f, 30.f, 0.f);
                drawPlane(30.f);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    
    
    glPopAttrib();
    glPopMatrix();
}
void BaseBuilding::Update(const double& deltaTime){
    //rotating the acceptor
    if(rotateDegree == 360.f){
        rotateDegree = 0;
    }
    else{
        rotateDegree += 1.f;
    }
    
    //perform a chicken animation, the wings of chicken can rotate
    if(wingStatus == 1){
        if(wingAngle == 90.f){
            wingAngle -= 1.f;
            wingStatus = 0;
        }
        else{
            wingAngle += 1.f;
        }
    }
    else{
        if(wingAngle == 0.f){
            wingAngle += 1.f;
            wingStatus = 1;
        }
        else{
            wingAngle -= 1.f;
        }
    }
    //perform an chicken jump animation
    if(chickenJump == 1){
        if(chickHeight >= 5.f){
            chickenJump = 0;
            chickHeight -= 0.1f;
        }
        else{
            chickHeight += 0.1f;
        }
    }
    else{
        if(chickHeight <= 0.f){
            chickenJump = 1;
            chickHeight += 0.1f;
        }
        else{
            chickHeight -= 0.1f;
        }
    }
    
}
