#include "Water.h"
#include <cmath>

//learn from the lecture materials
Water::Water(const int& gridX, const int& gridZ, const std::string& filename)
	: xGridDims(gridX), zGridDims(gridZ), frozen(false), time(0.0)
{
	texID = Scene::GetTexture(filename);

	texCoords = new float[(xGridDims + 1) * (zGridDims + 1) * 2];

	matAmbient[0] = 0.9f;   // set the material properties of the grid
	matAmbient[1] = 0.95f;
	matAmbient[2] = 0.9f;
	matAmbient[3] = 1.0f;

	matDiffuse[0] = 1.0f;
	matDiffuse[1] = 1.0f;
	matDiffuse[2] = 1.0f;
	matDiffuse[3] = 1.0f;

	matSpecular[0] = 1.0f;
	matSpecular[1] = 1.0f;
	matSpecular[2] = 1.0f;
	matSpecular[3] = 1.0f;

	matShininess = 128;
}


Water::~Water()
{
	if (texCoords != NULL)
	{
		delete [] texCoords;
		texCoords = NULL;
	}
}


void Water::Display()
{
	float x, y, z;
	glPushAttrib(GL_ALL_ATTRIB_BITS);              // Set the material properties of the waters surface
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMateriali(GL_FRONT, GL_SHININESS, matShininess);
    glPushMatrix();
    
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glPushMatrix();
        glColor3f(121.f/255, 77.f/255, 63.f/255);
        glTranslated(50.f, 100.f, 0.f);
        glPushMatrix();
            glTranslated(-200.f, -95.f, 0.f);
            glScaled(1.f, 1.f, 30.f);
            glutSolidCube(10.f);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-50.f, -95.f, -150.f);
            glRotatef(90.f, 0.f, 1.f, 0.f);
            glScaled(1.f, 1.f, 31.f);
            glutSolidCube(10.f);
        glPopMatrix();
        glPushMatrix();
            glTranslated(100.f, -95.f, 0.f);
            glScaled(1.f, 1.f, 30.f);
            glutSolidCube(10.f);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-50.f, -95.f, 150.f);
            glRotatef(90.f, 0.f, 1.f, 0.f);
            glScaled(1.f, 1.f, 31.f);
            glutSolidCube(10.f);
        glPopMatrix();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
		glPushMatrix();
    
            glScalef(scale[0], scale[1], scale[2]);
    
//            glColor3f(121.f/255, 77.f/255, 63.f/255);

    
            glBindTexture(GL_TEXTURE_2D, texID);
            glColor4f(1.0f, 1.0f, 1.0f, 0.8f);

    
			y = 0.0f; z = -0.5f;
			glBegin(GL_QUADS);
			for (int j = 0; j < zGridDims; j++)
			{
				x = -0.5f;
				for (int i = 0; i < xGridDims; i++)
				{
					glNormal3f(0.0f, 1.0f, 0.0f);

					glTexCoord2fv(&texCoords[(i + j*(xGridDims + 1)) * 2]);
					glVertex3f(x, y, z);

                    
					glTexCoord2fv(&texCoords[(i + (j + 1)*(xGridDims + 1)) * 2]);
					glVertex3f(x, y, z + 1.0f / (float)zGridDims);

                    
					glTexCoord2fv(&texCoords[(i + 1 + (j + 1)*(xGridDims + 1)) * 2]);
					glVertex3f(x + 1.0f / (float)xGridDims, y, z + 1.0f / (float)zGridDims);

                    
					glTexCoord2fv(&texCoords[((i + 1) + j*(xGridDims + 1)) * 2]);
					glVertex3f(x + 1.0f / (float)xGridDims, y, z);

					x += 1.0f / (float)xGridDims;
				}
				z += 1.0f / (float)zGridDims;
			}
			glEnd();
			
		glPopMatrix();
    glPopMatrix();
	glPopAttrib();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_LIGHTING);
}

void Water::Update(const double& deltaTime)
{
	float radius;
	time += deltaTime*2;


	
    radius = sqrtf((1.0f / xGridDims)*(1.0f / xGridDims) + (1.0f / zGridDims)*(1.0f / zGridDims));
	radius /= 4.0f;
    
	
    if (frozen)
	{
		for (int j = 0; j <= zGridDims; j++)
		{
			for (int i = 0; i <= xGridDims; i++)
			{
				
                texCoords[(i + (xGridDims + 1) * j) * 2 + 0] = (float)i / (float)xGridDims;
				texCoords[(i + (xGridDims + 1) * j) * 2 + 1] = (float)j / (float)zGridDims;
			}
		}
	}
	else
	{
		for (int j = 0; j <= zGridDims; j++)
		{
			for (int i = 0; i <= xGridDims; i++)
			{
				
                texCoords[(i + (xGridDims + 1) * j) * 2 + 0] = (float)sin(time + (double)j) * radius + (float)i / (float)xGridDims;
				texCoords[(i + (xGridDims + 1) * j) * 2 + 1] = (float)cos(time + (double)i) * radius + (float)j / (float)zGridDims;
			}
		}
	}
}

void Water::HandleKey(unsigned char key, int state, int x, int y)
{
    
}
