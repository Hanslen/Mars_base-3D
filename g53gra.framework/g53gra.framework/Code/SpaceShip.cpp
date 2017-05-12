//
//  SpaceShip.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/9.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "SpaceShip.hpp"
#include <iostream>
using namespace std;

const float DEG2RAD = 3.14159/180;
SpaceShip::SpaceShip(int id, float x, float y):leg(20.f),status(0),_resolution(4), _flagWireFrame(false), _flagAnimation(true)
{
#ifdef __APPLE__
    texID = Scene::GetTexture("./spaceShip.bmp");
    texID2 = Scene::GetTexture("./spaceShip.bmp");
#else
    texID = Scene::GetTexture("./Textures/spaceShip.bmp");
    texID2 = Scene::GetTexture("./Textures/spaceShip.bmp");
#endif
    // Octahedron vertices (used for initial triangle faces)
    static float vertices[] =
    {
        1.0f, 0.0f, 0.0f,   // VERTEX 0
        0.0f, 0.0f, -1.0f,  // VERTEX 1
        -1.0f, 0.0f, 0.0f,  // VERTEX 2
        0.0f, 0.0f, 1.0f,   // VERTEX 3
        0.0f, 1.0f, 0.0f,   // VERTEX 4
        0.0f, -1.0f, 0.0f   // VERTEX 5
    };
    // Globalise vertices
    _initV = vertices;
    launchId = id;
    initialx = x;
    initialy = y;
}


SpaceShip::~SpaceShip()
{
    
}

void drawCircle(float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    
    for (int i=0; i < 360; i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
    }
    
    glEnd();
}

void SpaceShip::UFOCompo(float h, float r, float incline, int cone)
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

void SpaceShip::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID2);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glPushMatrix();
        glPushMatrix();
            glScaled(15.f, 15.f, 15.f);
            DrawSphere();
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, 10.f, 0.f);
            UFOCompo(15.f, 4.f, 0.f, 1);
            glTranslated(0.f, 15.f, 0.f);
            glPushMatrix();
                glScaled(3.f, 3.f, 3.f);
                DrawSphere();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, -1.f, 0.f);
            UFOCompo(1.f, 40.f, 0.f, 0);
            glTranslated(0.f, -4.f, 0.f);
            UFOCompo(4.f, 30.f, 0.f, 0);
            glPushMatrix();
                glRotatef(180.f, 0.f, 0.f, 1.f);
                UFOCompo(leg, 1.f, 20.f, 0);
                UFOCompo(leg, 1.f, -20.f, 0);
                glRotatef(90.f, 0.f, 1.f, 0.f);
                UFOCompo(leg, 1.f, 20.f, 0);
                UFOCompo(leg, 1.f, -20.f, 0);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();
}

void SpaceShip::DrawSphere()
{
    // Top half
    SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX0], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX1], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX2], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX3], &_initV[_VERTEX4]);
    // Bottom half
    SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX3], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX0], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX1], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX2], &_initV[_VERTEX5]);
    
}

void SpaceShip::SubDivide(int recurse_idx, float *a, float *b, float *c)
{
    if (recurse_idx > 0)
    {
        float ab[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
        float bc[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
        float ca[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };
        
        norm(ab);
        norm(bc);
        norm(ca);

        SubDivide(recurse_idx - 1, a, ab, ca);
        SubDivide(recurse_idx - 1, ab, b, bc);
        SubDivide(recurse_idx - 1, ca, bc, c);
        SubDivide(recurse_idx - 1, ca, ab, bc);
    }
    else
    {
        DrawFace(a, b, c);
    }
}

void SpaceShip::DrawFace(float *a, float *b, float *c)
{
    float sa = 0.5f + atan2f(a[0], a[2]) / (2.0f*M_PI);
    float ta = 0.5f + asinf(a[1]) / M_PI;
    
    float sb = 0.5f + atan2f(b[0], b[2]) / (2.0f*M_PI);
    float tb = 0.5f + asinf(b[1]) / M_PI;
    
    float sc = 0.5f + atan2f(c[0], c[2]) / (2.0f*M_PI);
    float tc = 0.5f + asinf(c[1]) / M_PI;
    
    FixSeam(sa, sb, sc);
    
    _flagWireFrame ? glBegin(GL_LINE_LOOP) : glBegin(GL_TRIANGLES);

    glTexCoord2f(sa, ta);
    glNormal3fv(a); glVertex3fv(a);

    glTexCoord2f(sb, tb);
    glNormal3fv(b); glVertex3fv(b);

    glTexCoord2f(sc, tc);
    glNormal3fv(c); glVertex3fv(c);
    glEnd();
}

void SpaceShip::FixSeam(float &a, float &b, float &c)
{
    if (b < 0.75f && a > 0.75f)
        b += 1.0f;
    else if (b > 0.75f && a < 0.75f)
        b -= 1.0f;
    
    if (c < 0.75f && a > 0.75f)
        c += 1.0f;
    else if (c > 0.75f && a < 0.75f)
        c -= 1.0f;
}


void SpaceShip::Update(const double& deltaTime)
{
    if(status == 100){
        if(leg > 0){
            leg -= 0.1f;
        }
        else if(pos[1] < 0.f){
            pos[1] += 1.f;
        }
        else{
//            cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
            pos[1] += 3.f;
            pos[2] += 6.f;
        }
        if(pos[2]>= 4400.f){
            pos[0] = initialx;
            pos[1] = -50.f;
            pos[2] = initialy;
            status = 0;
            leg = 20;
        }
    }
    
    
    
}

void SpaceShip::HandleKey(unsigned char key, int state, int mx, int my)
{
    //when the user press 'l', some spaceship will launch. And it depends on their launchId.
    if(state && key == 'l'){
        if(launchId == 0){//when launchId = 0, that row of spaceship will launch.
            status = 100;
        }
        else{
            launchId -= 1;//change the waiting spaceship
        }
    }
}

void SpaceShip::HandleSpecialKey(int key, int state, int mx, int my)
{

    
}
