#include "WorkingCar.h"

#include "VectorMath.h"
#include <iostream>
#define _ACCELERATION 10.0f
using namespace std;
WorkingCar::WorkingCar(float routeRadius, float velocity, int run) : _loopPosition(0.0f),rotateDegree(0.f), armRotateDegree(-30.f),armRotateIncrease(0),stopRotating(0),mouseY(0),mouseX(0)
{
#ifdef __APPLE__
    texID = Scene::GetTexture("./solarPanel.bmp");
    texCamera = Scene::GetTexture("./camera.bmp");
#else
    texID = Scene::GetTexture("./Textures/solarPanel.bmp");
    texCamera = Scene::GetTexture("./Textures/camera.bmp");
#endif
    _routeRadius = routeRadius;
    _velocity = velocity;
    status = run;

}


WorkingCar::~WorkingCar()
{

}
void WorkingCar::drawPillar(float h, float r, float incline, int cone)
{
    
    float th = 2.0f * M_PI;
    float res = 2.0f * M_PI / 20.0f;
    float x = r, z = 0.0f;
    do
    {
        glBegin(GL_QUADS);
        
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
        glVertex3f(x+incline, h, z);    // top
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
        glNormal3f(x, 0.f, z);
        glTexCoord2f(0.f, 1.f);
        if(cone != 1){
            glVertex3f(x, 0.f, z);  // bottom
        }
        else{
            glVertex3f(0.f, 0.f, 0.f);
        }
        glTexCoord2f(1.f, 0.f);  // (s,t) = (1,1)
        glVertex3f(x+incline, h, z);    // top
        glEnd();
    } while (th >= 0);
    
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
void WorkingCar::drawCube(float width, int textureID, int camera){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    // draw the front face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.f, width, 0.f);
    
    float holdTexture = 1.f;
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
    
    //left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(0.f, width, width);
    
    //right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(width, width, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width, 0.f, width);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, width, 0.f);
    
    //top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, width, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, width, width);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, width, width);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, width, 0.f);

    //bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, holdTexture);
    glVertex3f(0.f, 0.f, width);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glTexCoord2f(holdTexture, 0.0f);
    glVertex3f(width, 0.f, 0.f);
    glTexCoord2f(holdTexture, holdTexture);
    glVertex3f(width, 0.f, width);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
}

void WorkingCar::Display()
{
    
//    cout<<status<<endl;
//    glDisable(GL_LIGHTING);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
////    
    GLfloat wow[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, wow);
//    cout<<wow[12]<<" "<<wow[13]<<" "<<wow[14]<<endl;
    
	glTranslatef(pos[0], pos[1], pos[2]);
    glRotated(rotation[1], 0.f, 1.f, 0.f);
	glScalef(scale[0], scale[1], scale[2]);
    glTranslatef(_routeRadius, 0.0f, 0.0f);

	glPushMatrix();
	{
		glScalef(1.0f, 0.05f, 2.0f);
//		glColor3f(0.7f, 0.0f, 0.0f);
		drawCube(3.0, texID, 0);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.f, 0.f, 1.8f);
		DrawWheel();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.f, 0.f, 4.5f);
		DrawWheel();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(3.f, 0.f, 1.8f);
		DrawWheel();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(3.f, 0.f, 4.5f);
		DrawWheel();
	}
	glPopMatrix();

    //draw camera
    glPushMatrix();
        drawPillar(2.f, 0.1f, 0.f, 0);
        glTranslated(-0.2f, 2.f, -0.2f);
        drawCube(0.5f, texCamera,1);
    glPopMatrix();
    //car arm
    glPushMatrix();
        glTranslated(1.5f, 0.f, 0.5f);
    
    glScaled(0.5f, 0.5f, 0.5f);
    
        glPushMatrix();
            glRotated(armRotateDegree, 1.f, 0.f, 0.f);
            drawPillar(6.f, 0.3f, 0.f, 0);
            glTranslated(0.f, 6.f, 0.f);
            glutSolidSphere(0.5f, 20.f, 20.f);

            glRotated(-90.f, 1.f, 0.f, 0.f);
            drawPillar(6.f, 0.3f, 0.f, 0.f);
            glTranslated(-0.8f, 6.f, 0.f);
            glRotated(0.f, 1.f, 0.f, 0.f);
            glScaled(1.f, 0.1f, 1.f);
            drawCube(2.f, 0, 0);
        glPopMatrix();
    glPopMatrix();
    
    //acceptor
    glPushMatrix();
        glTranslated(1.5f, 0.f, 5.5f);
        drawPillar(2.f, 0.1f, 0.f, 0.f);
        glTranslated(0.f, 2.f, 0.f);
        glRotated(70.f, 0.f, 0.f, 1.f);
        glRotated(rotateDegree, 1.f, 0.f, 0.f);
        drawPillar(0.8f, 0.8f, 0.f, 1);
    glPopMatrix();
    
    //seat
    glPushMatrix();
        glColor3f(0.8f, 0.8f, 0.8f);
        glTranslated(0.5f, 0.f, 1.2f);
        glPushMatrix();
            glScaled(0.7f, 0.2f, 1.f);
            drawCube(2.5f, 0, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.f, 0.f, 3.f);
            glRotated(-90.f, 1.f, 0.f, 0.f);
            glScaled(0.7f, 0.2f, 1.f);
            drawCube(2.5f, 0,0);
        glPopMatrix();
        //steering
        glPushMatrix();
            glTranslated(0.8f, 0.f, 0.5f);
            glRotated(-90.f, 0.f, 1.f, 0.f);
            drawPillar(1.6f, 0.08f, 1.f, 0.f);
            glTranslated(1.f, 1.6f, 0.f);
            glutSolidSphere(0.5f, 2.f, 10.f);
        glPopMatrix();
        //astronaut
        glColor3f(1.f, 1.f, 1.f);
        glPushMatrix();
            glTranslated(0.4f, 0.f, 2.5f);
            //body
            glPushMatrix();
                glRotated(-90.f, 1.f, 0.f, 0.f);
                glScaled(0.4f, 0.2f,1.f);
                drawCube(2.f, 0,0);
            glPopMatrix();
            //head
            glPushMatrix();
                glTranslated(0.17f, 2.f, -0.4f);
                drawCube(0.4f, 0,0);
                //mask
                glColor3f(0.f, 0.f, 0.f);
                glTranslated(0.05f, 0.07f, -0.01f);
                drawCube(0.3f, 0,0);
            glPopMatrix();
            glColor3f(1.f, 1.f, 1.f);
            //right arm
            glPushMatrix();
                glTranslated(0.8f, 1.3f, -0.4f);
                glPushMatrix();
                    glScaled(1.f, 3.f, 1.f);
                    drawCube(0.2f, 0,0);
                glPopMatrix();
                glPushMatrix();
                    glRotated(-90.f, 1.f, 0.f, 0.f);
                    glScaled(1.f, 3.f, 1.f);
                    drawCube(0.2f, 0,0);
                glPopMatrix();
            glPopMatrix();
            //left arm
            glPushMatrix();
                glTranslated(-0.1f, 1.3f, -0.4f);
                glPushMatrix();
                    glScaled(1.f, 3.f, 1.f);
                    drawCube(0.2f, 0,0);
                glPopMatrix();
                glPushMatrix();
                    glRotated(-90.f, 1.f, 0.f, 0.f);
                    glScaled(1.f, 3.f, 1.f);
                    drawCube(0.2f, 0,0);
                glPopMatrix();
            glPopMatrix();
    
            //right leg
            glPushMatrix();
                glTranslated(0.5f, 0.5f, -0.4f);
                glRotated(-90.f, 1.f, 0.f, 0.f);
                glScaled(1.f, 5.f, 1.f);
                drawCube(0.2, 0,0);
            glPopMatrix();
    
            //left leg
            glPushMatrix();
                glTranslated(0.1f, 0.5f, -0.4f);
                glRotated(-90.f, 1.f, 0.f, 0.f);
                glScaled(1.f, 5.f, 1.f);
                drawCube(0.2, 0,0);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
	

	glPopAttrib();
	glPopMatrix();
}

void WorkingCar::DrawWheel()
{

	glScalef(0.2f, 0.5f, 0.5f);
	glColor3f(1.0f, 1.0f, 1.0f);

	float th = 0.0f;
	float res = 2.0f * M_PI / 20.0f;
	float y = 1.0f, z = 0.0f;

	do
	{
		glBegin(GL_QUADS);
		{
			glNormal3f(0.0f, y, z);
			glVertex3f(0.5f, y, z);
			glVertex3f(-0.5f, y, z);

			th += res;
			y = cos(th); z = sin(th);

			glNormal3f(0.0f, y, z);
			glVertex3f(-0.5f, y, z);
			glVertex3f(0.5f, y, z);
		}
		glEnd();
	} while (th <= 2.0f * M_PI);

	y = 1.0f, z = 0.0f; th = 0.0f;
	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		do
		{
			glVertex3f(0.5f, y, z);
			th += res;
			y = cos(th); z = sin(th);
			glVertex3f(0.5f, y, z);
		} while (th <= 2.0f * M_PI);
	}
	glEnd();

	y = 1.0f, z = 0.0f;

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);

		do
		{
			glVertex3f(-0.5f, y, z);
			th -= res;
			y = cos(th); z = sin(th);
			glVertex3f(-0.5f, y, z);
		} while (th >= 0.0f);
	}
	glEnd();
}


void WorkingCar::Update(const double& deltaTime)
{
    if(status == 100 || status == 1000){
        rotation[1] += static_cast<float>(deltaTime) *_velocity;
        if(status != 1000){
            Scene::GetCamera()->setDriverRotate(rotation[1], static_cast<float>(deltaTime) *_velocity);
        }
        if(rotateDegree == 360.f){
            rotateDegree = 0;
        }
        else{
            rotateDegree += 1.f;
        }
        if(stopRotating == 0){
        if(armRotateIncrease){
            if(armRotateDegree == -30.f){
                armRotateDegree -= 0.5f;
                armRotateIncrease = 0;
            }
            else{
                armRotateDegree += 0.5f;
            }
        }
        else{
            if(armRotateDegree == -60.f){
                armRotateDegree += 0.5f;
                armRotateIncrease = 1;
            }
            else{
                armRotateDegree -= 0.5f;
            }
        }
        }
    }
}
void WorkingCar::HandleMouse(int button, int state, int x, int y){
    if(status == 100){
        if(state == 0){
            stopRotating = 1;
        }
        else if(state == 1){
            stopRotating = 0;
        }
        mouseX = x;
        mouseY = y;
    }
}

void WorkingCar::HandleMouseDrag(int x, int y){
    if(status == 100){
        if(y-mouseY < 0){
            _velocity += 1.f;
        }
        else{
            if(_velocity > 1.f){
                _velocity -= 1.f;
            }
        }
        mouseY = y;
        mouseX = x;
    }
}
void WorkingCar::HandleKey(unsigned char key, int state, int mx, int my)
{
    if(state && key == 'r'){
        if(status == 100){
            status = 0;
        }
        if(status != 1000){
            if(status == 100){
                Scene::GetCamera()->setDriver(100);
            }
            status = 100;
        }
    }
    if(state && key == ' '){
        if(status != 1000){
            status = 0;
        }
    }
}

void WorkingCar::HandleSpecialKey(int key, int state, int mx, int my)
{

}
