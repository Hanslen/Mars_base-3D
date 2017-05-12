//
//  Plane.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/5/8.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "Plane.hpp"
#include <iostream>
using namespace std;
Plane::Plane():returnPlane(0){
#ifdef __APPLE__
    texID = Scene::GetTexture("./plane.bmp");
#else
    texID = Scene::GetTexture("./Textures/plane.bmp");
#endif
}

Plane::~Plane(){

}

void Plane::drawCube(float width, int textureID){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, textureID);
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

void Plane::drawHalfSphere(int scaley, int scalex, GLfloat r) {
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
void Plane::drawTriangularPrism(float width, int textureID){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_TRIANGLES);
        //bottom
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.f, 0.f, 0.f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(width, 0.f, 0.f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(width/2, 0.f, -width);
    glEnd();
    glBegin(GL_QUADS);
    //front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width, width, 0.f);

    //left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width/2, width, -width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width/2, 0.f, -width);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    
    //right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width/2, 0.f, -width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width/2, width, -width);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    //top
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, width, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width/2, width, -width);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
}
void Plane::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glRotated(rotation[2], 0.f, 0.f, 1.f);
    glScalef(scale[0], scale[1], scale[2]);
    
    glPushMatrix();
        glScaled(1.f, 0.2f, 3.f);
        drawCube(20.f, texID);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0.f, 0.f, 30.f);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        glScaled(1.f, 0.2f, 1.5f);
        drawTriangularPrism(20.f,texID);
    glPopMatrix();
    //front
    glPushMatrix();
        glTranslated(0.f, 0.f, 45.f);
        glRotatef(90.f, 0.f, 1.f, 0.f);
        glScaled(1.5f, 0.2f, 3.f);
        drawTriangularPrism(20.f, texID);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0.f, 0.f, 15.f);
        glRotatef(90.f, 0.f, 1.f, 0.f);
        glScaled(1.5f, 0.2f, 3.f);
        drawTriangularPrism(10.f, texID);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0.f, 0.f, 60.f);
        glRotatef(90.f, 0.f, 1.f, 0.f);
        glScaled(1.5f, 0.2f, 3.f);
        drawTriangularPrism(10.f, texID);
    glPopMatrix();
    
    
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(156/255.f, 26/255.f, 0.f, 0.9f);
    glPushMatrix();
        glTranslated(20.f, 0.f, 5.f);
        glScaled(0.8f, 0.2f, 1.f);
        drawCube(10.f, 0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(20.f, 0.f, 45.f);
        glScaled(0.8f, 0.2f, 1.f);
        drawCube(10.f, 0);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
        glColor3f(0.f, 0.f, 0.f);
        glTranslated(-12.f, 4.f, 31.f);
        drawHalfSphere(30.f,30.f,10.f);
    glPopMatrix();
    glPopAttrib();
    glPopMatrix();
}
void Plane:: Update(const double& deltaTime){
    
    //plane rotation
    rotation[1] += 1.f;
    
    //predefined the path for the plane
    if(pos[0] == -1000.f){
        if(pos[2]<900.f){
            if(returnPlane == 0){
                pos[2] +=5.f;
                returnPlane = 0;
                if(pos[2] == 895.f){
                    returnPlane = 1;
                }
                else{
                    returnPlane = 0;
                }
            }
            else if(pos[2] > -900.f){
                if(pos[2] == -895.f){
                    returnPlane = 0;
                }
                else{
                    returnPlane = 1;
                }
                pos[2] -= 5.f;
            }
            
        }
        
    }
    else{
    if((pos[0]<900.f && pos[2]<900.f) && ((pos[0]*pos[2]>=0))){
        if(pos[2] == -900.f){
            if(pos[0] == -900.f){
                pos[0]+=5.f;
                pos[2]+=5.f;
            }
            else{
                pos[0] -= 5.f;
            }
        }
        else{
            pos[0]+=5.f;
            pos[2]+=5.f;
        }
    }
    else if(pos[0] == 900.f&&pos[2]>-900.f){
        pos[2] -= 5.f;
    }
    else if(pos[2] == -900.f && pos[0]>-900.f){
        pos[0] -= 5.f;
    }
    }
}
