//
//  People.cpp
//  g53gra.framework
//
//  Created by Hanslen Chen on 2017/5/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "People.hpp"
#include <iostream>
using namespace std;
People::People(int id, int start, float y):increase(1),jump(1),faceRotation(0.f){
    walk = start;
#ifdef __APPLE__
    peopleSkin = Scene::GetTexture("./peopleSkin.bmp");
    peopleShoes = Scene::GetTexture("./peopleShoes.bmp");
    peopleLegSide = Scene::GetTexture("./peopleLegSide.bmp");
    peopleLegFront = Scene::GetTexture("./peopleLegFront.bmp");
    peopleHeadFront = Scene::GetTexture("./peopleHeadFront.bmp");
    peopleHeadBack = Scene::GetTexture("./peopleHeadBack.bmp");
    peopleBodySide = Scene::GetTexture("./peopleBodySide.bmp");
    peopleBodyFront = Scene::GetTexture("./peopleBodyFront.bmp");
    peopleArm = Scene::GetTexture("./peopleArm.bmp");
    peopleLeg = Scene::GetTexture("./peopleLeg.bmp");
#else
    peopleSkin = Scene::GetTexture("./Textures/peopleSkin.bmp");
    peopleShoes = Scene::GetTexture("./Textures/peopleShoes.bmp");
    peopleLegSide = Scene::GetTexture("./Textures/peopleLegSide.bmp");
    peopleLegFront = Scene::GetTexture("./Textures/peopleLegFront.bmp");
    peopleHeadFront = Scene::GetTexture("./Textures/peopleHeadFront.bmp");
    peopleHeadBack = Scene::GetTexture("./Textures/peopleHeadBack.bmp");
    peopleBodySide = Scene::GetTexture("./Textures/peopleBodySide.bmp");
    peopleBodyFront = Scene::GetTexture("./Textures/peopleBodyFront.bmp");
    peopleArm = Scene::GetTexture("./Textures/peopleArm.bmp");
    peopleLeg = Scene::GetTexture("./Textures/peopleLeg.bmp");
#endif
    status = id;
    if(status == 2){
        armRotation = -90.f;
    }
    initialY = y;
}
People::~People(){
    
}

void People::drawCube(float width, int front, int left,int right,int back, int top, int bottom){
    
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, front);
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
    
    glBindTexture(GL_TEXTURE_2D, back);
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
    // draw the left face
    
    glBindTexture(GL_TEXTURE_2D, left);
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.f, width, width);
    glEnd();
    // draw the right face
    glBindTexture(GL_TEXTURE_2D, right);
    glBegin(GL_QUADS);
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
    glBindTexture(GL_TEXTURE_2D, top);
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
    glEnd();
    // draw the bottom face
    glBindTexture(GL_TEXTURE_2D, bottom);
    glBegin(GL_QUADS);
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

void People::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotated(rotation[0], 1.f, 0.f, 0.f);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glRotated(rotation[2], 0.f, 0.f, 1.f);
    glScalef(scale[0], scale[1], scale[2]);
//    glTranslated(0.f, 28.f, 0.f);
    
    
    glRotated(faceRotation, 0.f, 1.f, 0.f);
    //head
    glPushMatrix();
        drawCube(10.f, peopleHeadFront, peopleHeadBack, peopleHeadBack, peopleHeadBack, peopleSkin, peopleHeadBack);
    glPopMatrix();
    
    glTranslated(0.f, 10.f, 0.f);
    
    //body
    glPushMatrix();
        glTranslated(0.f, 0.f, 2.5f);
        glScaled(1.f, 1.3f, 0.5f);
        drawCube(10.f, peopleBodyFront, peopleBodySide, peopleBodySide, peopleBodySide, peopleSkin, peopleBodySide);
    glPopMatrix();
    
    //left arm
    glPushMatrix();
        glTranslated(10.f, 0.f, 2.5f);
        if(status == 1){
            glRotated(armRotation, 1.f, 0.f, 0.f);
        }
        if(status == 2){
            glRotated(armRotation, 0.f, 0.f, 1.f);
        }
        glScaled(0.5f, 1.3f, 0.5f);
        drawCube(10.f, peopleArm, peopleArm, peopleArm, peopleArm, peopleSkin, peopleArm);
    glPopMatrix();
    
    //right arm
    glPushMatrix();
        glTranslated(-5.f, 0.f, 5.f);
        if(status == 1){
            glRotated(-armRotation, 1.f, 0.f, 0.f);
        }
        if(status == 2){
            glTranslated(5.f, 0.f, 0.f);
            glRotated(180.f, 0.f, 1.f, 0.f);
            glRotated(armRotation, 0.f, 0.f, 1.f);
        }
        glScaled(0.5f, 1.3f, 0.5f);
        drawCube(10.f, peopleArm, peopleArm, peopleArm, peopleArm, peopleSkin, peopleArm);
    glPopMatrix();
    
    glTranslated(0.f, 13.f, 2.5f);
    //right leg
    glPushMatrix();
        if(status == 1){
            glRotated(legRotation, 1.f, 0.f, 0.f);
        }
        if(status == 2){
            glRotated(legRotation, 0.f, 0.f, 1.f);
        }
        glScaled(0.5f, 1.5f, 0.5f);
        drawCube(10.f, peopleLegFront, peopleLegSide, peopleLegSide, peopleLegSide, peopleShoes, peopleLeg);
    glPopMatrix();
    //left leg
    glPushMatrix();
        glTranslated(5.f, 0.f, 0.f);
        if(status == 1){
            glRotated(-legRotation, 1.f, 0.f, 0.f);
        }
        if(status == 2){
            glRotated(-legRotation, 0.f, 0.f, 1.f);
        }
        glScaled(0.5f, 1.5f, 0.5f);
        drawCube(10.f, peopleLegFront, peopleLegSide, peopleLegSide, peopleLegSide, peopleShoes, peopleLeg);
    glPopMatrix();
    glPopAttrib();
    glPopMatrix();
}
void People::Update(const double& deltaTime){
    //status = 1: people will be the walking one. And the arm and leg will rotating with the reverse direction
    if(status == 1){
        if(increase == 1){
            if(armRotation < 60.f){
                armRotation += 3.f;
                legRotation +=2.8f;
            }
            else{
                increase = 0;
            }
        }
        else{
            if(armRotation > -60.f){
                armRotation -= 3.f;
                legRotation -= 2.8f;
            }
            else{
                increase = 1;
            }
        }
        //define their walking path
        if(walk < 400){
            pos[2] -= 1.f;
            walk += 1;
        }else if(walk < 800){
            if(walk == 400){
                faceRotation = 180.f;
            }
            pos[2] += 1.f;
            walk += 1;
        }
        else{
            walk = 0;
            faceRotation = 0.f;
        }
    }
    //when status = 2, the people will be the cheering one.
    if(status == 2){
        if(increase == 1){
            if(armRotation< 0-90.f){
                armRotation += 3.f;
            }else{
                increase = 0;
            }
        }
        else{
            if(armRotation > -60.f-90.f){
                armRotation -= 3.f;
            }
            else{
                increase = 1;
            }
        }
        //perform a jump action
        if(jump){
            if(pos[1] < initialY+20){
                pos[1] += 1.f;
            }
            else{
                jump = 0;
            }
        }
        else{
            if(pos[1] > initialY){
                pos[1] -= 1.f;
            }
            else{
                jump = 1;
            }
        }
    }
    
}
