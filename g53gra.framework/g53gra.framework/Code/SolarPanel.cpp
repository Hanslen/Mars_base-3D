//
//  SolarPanel.cpp
//  G53GRA.Framework
//
//  Created by Hanslen Chen on 2017/4/17.
//  Copyright © 2017年 w.o.c.ward. All rights reserved.
//

#include "SolarPanel.hpp"
SolarPanel::SolarPanel(){
#ifdef __APPLE__
    texID = Scene::GetTexture("./solarPanel.bmp");
#else
    texID = Scene::GetTexture("./Textures/solarPanel.bmp");
#endif
}
SolarPanel::~SolarPanel(){
}

void SolarPanel::drawCube(float width, int textureID){
    
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

void SolarPanel::Display(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotated(rotation[1], 0.f, 1.f, 0.f);
    glScalef(scale[0], scale[1], scale[2]);
    
    //backbone
    glPushMatrix();
        glPushMatrix();
            glScaled(1.f, 10.f, 1.f);
            drawCube(5.f, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, 0.f, 70.f);
            glScaled(1.f, 10.f, 1.f);
            drawCube(5.f, 0);
        glPopMatrix();
    
        glTranslated(65.f, 0.f, 0.f);
        glPushMatrix();
            glScaled(1.f, 5.f, 1.f);
            drawCube(5.f, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, 0.f, 70.f);
            glScaled(1.f, 5.f, 1.f);
            drawCube(5.f, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-65.f, 50.f, 0.f);
            glRotated(-20.f, 0.f, 0.f, 1.f);
            glScaled(8.f, 0.1f, 7.5f);
            drawCube(10.f, texID);
        glPopMatrix();
    
    glPopMatrix();
    
    glPopAttrib();
    glPopMatrix();
}
void SolarPanel:: Update(const double& deltaTime){
}
