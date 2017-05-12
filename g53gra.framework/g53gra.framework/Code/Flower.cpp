//
//  Flower.cpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/10.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "Flower.hpp"
#include <iostream>
using namespace std;
Flower::Flower(GLfloat r, GLfloat g, GLfloat b, int boxneed){
#ifdef __APPLE__
    texSoil = Scene::GetTexture("./soil.bmp");
#else
    texSoil = Scene::GetTexture("./Textures/soil.bmp");
#endif
    flowerr = r;
    flowerg = g;
    flowerb = b;
    box = boxneed;
}

Flower::~Flower(){
}

void Flower::drawPlane(float r){
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
void Flower::drawFlower(){
    glColor3f(3/255.f, 93/255.f, 0.f);
    glPushMatrix();
        glScaled(1.f, 4.f, 1.f);
        glutSolidCube(2.f);
    glPopMatrix();
    
    glTranslated(0.f, 0.5f, 0.f);
    glPushMatrix();
        glRotated(90.f, 0.f, 0.f, 1.f);
        glScaled(1.f,8.f, 1.f);
        glutSolidCube(1.f);
    glPopMatrix();
    glPushMatrix();
        glRotated(90.f, 1.f, 0.f, 0.f);
        glScaled(1.f, 8.f, 1.f);
        glutSolidCube(1.f);
    glPopMatrix();
    glTranslated(0.f, 4.f, 0.f);
    glColor3f(flowerr/255.f, flowerg/255.f, flowerb/255.f);
    glutSolidCube(3.f);
}

void Flower::Display(){
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    
    //flower
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
        glTranslated(5.f, 3.f, 5.f);
        drawFlower();
    glPopMatrix();
    //box
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.f, 1.f, 1.f);
    glBindTexture(GL_TEXTURE_2D, texSoil);
        drawPlane(10.f);
    glDisable(GL_TEXTURE_2D);
    if(box == 0){
    glColor4f(1.f, 1.f, 1.f, 0.5);
        
        //front
    glPushMatrix();
        glTranslated(-70.f, 16.f, 10.f);
        glRotated(90.f, 1.f, 0.f, 0.f);
        glScaled(1.f, 1.f, 0.2f);
        drawPlane(80.f);
    glPopMatrix();
        //left
    glPushMatrix();
        glTranslated(10.f, 16.f, -70.f);
        glRotated(-90.f, 0.f, 0.f, 1.f);
        glScaled(0.2f, 1.f, 1.f);
        drawPlane(80.f);
    glPopMatrix();
        //right
        glPushMatrix();
        glTranslated(-70.f, 0.f, -70.f);
        glRotated(90.f, 0.f, 0.f, 1.f);
        glScaled(0.2f, 1.f, 1.f);
        drawPlane(80.f);
        glPopMatrix();
        //back
    glPushMatrix();
        glTranslated(-70.f, 0.f, -70.f);
        glRotated(-90.f, 1.f, 0.f, 0.f);
        glScaled(1.f, 1.f, 0.2f);
        drawPlane(80.f);
    glPopMatrix();
        //top
    glPushMatrix();
        glTranslated(-70.f, 16.f, -70.f);
        drawPlane(80.f);
    glPopMatrix();
    }
    glPopAttrib();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void Flower::Update(const double &deltaTime){

}
