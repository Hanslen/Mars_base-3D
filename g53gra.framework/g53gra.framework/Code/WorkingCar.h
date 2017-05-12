#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

class WorkingCar :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	WorkingCar(float routeRadius, float velocity, int run);
	~WorkingCar();

	void Display();
	
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int mx, int my);
	void HandleSpecialKey(int key, int state, int mx, int my);
    void HandleMouse(int button, int state, int x, int y);
    void HandleMouseDrag(int x, int y);

protected:
	
	float _loopPosition, _velocity;
    float driverHead[3];
    float rotateDegree;
    float armRotateDegree;
    float _routeRadius;
    int armRotateIncrease;
    int texID;
    int texCamera;
	void DrawWheel();
    void drawCube(float width, int textureID, int camera);
    void drawPillar(float h, float r, float incline, int cone);
    int status;
    int stopRotating;
    int mouseX;
    int mouseY;
    
};

