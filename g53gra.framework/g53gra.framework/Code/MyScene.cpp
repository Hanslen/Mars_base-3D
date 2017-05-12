#include "MyScene.h"
#include "WorkingCar.h"
#include "Skybox.h"
#include "SpaceShip.hpp"
#include "Plane.hpp"
#include "LightHouse.hpp"
#include "BaseBuilding.hpp"
#include "HeadLight.hpp"
#include "SolarPanel.hpp"
#include "DisposeOil.hpp"
#include "SkyWheel.hpp"
#include "Water.h"
#include "OilTank.hpp"
#include "People.hpp"
#include "Flower.hpp"
#include <stdlib.h>


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
#ifdef __APPLE__
    GLuint tf = Scene::GetTexture("./red_up.bmp");
    GLuint bf = Scene::GetTexture("./red_dn.bmp");
    GLuint lf = Scene::GetTexture("./red_bk.bmp");
    GLuint rf = Scene::GetTexture("./red_ft.bmp");
    GLuint nf = Scene::GetTexture("./red_lf.bmp");
    GLuint ff = Scene::GetTexture("./red_rt.bmp");
#else
    GLuint tf = Scene::GetTexture("./Textures/red_up.bmp");
    GLuint bf = Scene::GetTexture("./Textures/red_dn.bmp");
    GLuint lf = Scene::GetTexture("./Textures/red_bk.bmp");
    GLuint rf = Scene::GetTexture("./Textures/red_ft.bmp");
    GLuint nf = Scene::GetTexture("./Textures/red_lf.bmp");
    GLuint ff = Scene::GetTexture("./Textures/red_rt.bmp");
#endif
    Skybox *skybox = new Skybox(tf, bf, lf, rf, nf, ff);
    skybox->size(10000.0f, 2000.0f, 10000.0f);
    AddObjectToScene(skybox);
    //Walking staff left row
    for(int i = 0; i < 4; i++){
        People *people = new People(1,0, -20.f);
        people->size(3.f);
        people->orientation(0.f,180.f,180.f);
        people->position(-450.f,-20.f,-500.f-i*300);
        AddObjectToScene(people);
    }
    //Walking staff right row
    for(int i = 0; i < 4; i++){
        People *people = new People(1,400, -20.f);
        people->size(3.f);
        people->orientation(0.f,180.f,180.f);
        people->position(163.f,-20.f,-800.f-i*300);
        AddObjectToScene(people);
    }
    
    //LightHouse
    LightHouse *lightHouse = new LightHouse(GL_LIGHT0);
    lightHouse->position(700.f, -100.f, -600.0f);
    AddObjectToScene(lightHouse);
    
    LightHouse *lightHouse2 = new LightHouse(GL_LIGHT1);
    lightHouse2->position(100.f, -100.f, -600.0f);
    AddObjectToScene(lightHouse2);
    
    LightHouse *lightHouse3 = new LightHouse(GL_LIGHT2);
    lightHouse3->position(-500.f, -100.f, -600.0f);
    AddObjectToScene(lightHouse3);
    
    for(int i = 0; i < 5; i++){
        LightHouse *lightHouse4 = new LightHouse(GL_LIGHT3);
        lightHouse4->position(700.f, -100.f, -900.0f-300*i);
        AddObjectToScene(lightHouse4);
    
        LightHouse *lightHouse5 = new LightHouse(GL_LIGHT4);
        lightHouse5->position(100.f, -100.f, -900.0f-300*i);
        AddObjectToScene(lightHouse5);
    
        LightHouse *lightHouse6 = new LightHouse(GL_LIGHT5);
        lightHouse6->position(-500.f, -100.f, -900.0f-300*i);
        AddObjectToScene(lightHouse6);
    }
    //chicken Farm
    for(int i = 0; i < 5; i++){
        BaseBuilding *baseBuilding = new BaseBuilding();
        baseBuilding->size(5.f);
        baseBuilding->position(-50.f,-100.f, -500.f-300*i);
        AddObjectToScene(baseBuilding);
        
        BaseBuilding *baseBuilding2 = new BaseBuilding();
        baseBuilding2->size(5.f);
        baseBuilding2->position(500.f,-100.f, -500.f-300*i);
        AddObjectToScene(baseBuilding2);
    }
    
    
    //OilTank
#ifdef __APPLE__
    Water *water = new Water(20, 20, "./oil.bmp");
#else
    Water *water = new Water(20, 20, "./Textures/oil.bmp");
#endif
    water->position(350.f, -100.0f,320.0f);
    water->size(300.0f);
    water->orientation(0.f,90.f,0.f);
    AddObjectToScene(water);
    
    OilTank *oiltank1 = new OilTank();
    oiltank1->size(1.2);
    oiltank1->position(150.0f+200.f,-100.f, 100.0f);
    oiltank1->orientation(0.f,90.f,0.f);
    AddObjectToScene(oiltank1);
    
    DisposeOil *disposeOil = new DisposeOil();
    disposeOil->position(570.f, -100.f,-50.f);
    disposeOil->orientation(0.f,-90.f,0.f);
    disposeOil->size(10.f);
    AddObjectToScene(disposeOil);
    
    //SolarPanel
    HeadLight *headLight2 = new HeadLight(GL_LIGHT7);
    headLight2->size(6.f);
    headLight2->position(250.f,-100.f,1000.f);
    AddObjectToScene(headLight2);
    for(int i =0; i < 6;i++){
        for(int j = 0; j < 3; j++){
            SolarPanel *solarPanel = new SolarPanel();
            solarPanel->position(-1000.f-150*j, -100.f, 1400.0-100*i);
            AddObjectToScene(solarPanel);
        }
    }
    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++){
            People *people = new People(1,1,-20.f);
            people->size(3.f);
            people->orientation(0.f,180.f,180.f);
            people->position(0-i*100,-20.f,1500.f+j*100);
            AddObjectToScene(people);
        }
    }
    
    //SkyWheel
    SkyWheel *skyWheel = new SkyWheel();
    skyWheel->size(5.f);
    skyWheel->position(-1000.f, -100.f, -400.f);
    skyWheel->orientation(0.f, 30.f, 0.f);
    AddObjectToScene(skyWheel);
    
    SkyWheel *skyWheel2 = new SkyWheel();
    skyWheel2->size(5.f);
    skyWheel2->position(900.f, -100.f, -400.f);
    skyWheel2->orientation(0.f, -30.f, 0.f);
    AddObjectToScene(skyWheel2);
    
    //Skywheel waiting people
    People *People2 = new People(2, 0,-10.f);
    People2->size(2.f);
    People2->orientation(0.f,-30.f,180.f);
    People2->position(-600,-10.f,-400.f);
    AddObjectToScene(People2);
    
    People *People3 = new People(2, 0,-10.f);
    People3->size(2.f);
    People3->orientation(0.f,-30.f,180.f);
    People3->position(-550,-10.f,-400.f);
    AddObjectToScene(People3);
    
    People *People4 = new People(2, 0,-10.f);
    People4->size(2.f);
    People4->orientation(0.f,30.f,180.f);
    People4->position(700.f,-10.f,-400.f);
    AddObjectToScene(People4);
    
    People *People5 = new People(2, 0,-10.f);
    People5->size(2.f);
    People5->orientation(0.f,30.f,180.f);
    People5->position(650.f,-10.f,-400.f);
    AddObjectToScene(People5);

    //Launch Spaceship
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4;j++){
            SpaceShip *spaceShip = new SpaceShip(j, -1000.0f-i*200,100.0f+j*200);
            spaceShip->size(2.f);
            spaceShip->position(-1000.0f-i*200, -50.0f,100.0f+j*200);//x=20.f
            AddObjectToScene(spaceShip);
        }
    }
    
    
    WorkingCar *workingCar2 = new WorkingCar(10.f, 10.f, 0);
    workingCar2->size(20.0f);
    workingCar2->position(-50.0f, -100.0f,0.0f); //z:0.0f
    workingCar2->orientation(0.f,90.f,0.f);
    AddObjectToScene(workingCar2);
    WorkingCar *workingCar3 = new WorkingCar(12.f, 50.f , 1000);
    workingCar3->size(20.0f);
    workingCar3->position(900.f, -100.0f,1000.0f); //z:0.0f
    workingCar3->orientation(0.f,-90.f,0.f);
    AddObjectToScene(workingCar3);
    WorkingCar *workingCar5 = new WorkingCar(15.f, 30.f , 1000);
    workingCar5->size(20.0f);
    workingCar5->position(950.0f, -100.0f,300.0f); //z:0.0f
    workingCar5->orientation(0.f,-90.f,0.f);
    AddObjectToScene(workingCar5);

    WorkingCar *workingCar7 = new WorkingCar(10.f, 30.f , 1000);
    workingCar7->size(20.0f);
    workingCar7->position(400.f, -100.0f,1400.0f); //z:0.0f
    workingCar7->orientation(0.f,-90.f,0.f);
    AddObjectToScene(workingCar7);
    
    WorkingCar *workingCar8 = new WorkingCar(10.f, 40.f , 1000);
    workingCar8->size(20.0f);
    workingCar8->position(800.f, -100.0f,1300.0f); //z:0.0f
    workingCar8->orientation(0.f,-90.f,0.f);
    AddObjectToScene(workingCar8);
    
    //Plane
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            Plane *plane = new Plane();
            plane->size(2.f);
            plane->position(-3000.f+i*(1500.f), 1300.f, 1500.f-j*1000.f);
            plane->orientation(0.f, 0.f, 180.f);
            AddObjectToScene(plane);
        }
    }
    GLfloat flowerColor[6][3] = {{171.f,37.f,188.f},{254.f,253.f,246.f},{41.f,146.f,193.f},{194.f, 0.f,0.f},{219.f,181.f,0.f},{223.f,130.f,177.f}};

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            int nonbox = 1;
            int color = rand()%6;
            if(i == 7 && j == 7){
                nonbox = 0;
            }
            Flower *flower = new Flower(flowerColor[color][0],flowerColor[color][1],flowerColor[color][2], nonbox);
            flower->size(2.f);
            flower->position(-80.f+20*j, -100.f, -60.f+20*i);
            AddObjectToScene(flower);
        }
    }
    
    People *peopleA = new People(2,0,-40);
    peopleA->position(-110.f, -40.f, 0.f);
    peopleA->orientation(0.f, 90.f, 180);
    peopleA->size(2.f);
    AddObjectToScene(peopleA);
    
    People *peopleB = new People(2,0,-40);
    peopleB->position(110.f, -40.f, 0.f);
    peopleB->orientation(0.f, -90.f, 180);
    peopleB->size(2.f);
    AddObjectToScene(peopleB);
    
    People *peopleC = new People(2,0,-40);
    peopleC->position(0.f, -40.f, -80.f);
    peopleC->orientation(0.f, 0.f, 180);
    peopleC->size(2.f);
    AddObjectToScene(peopleC);
    
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            int nonbox = 1;
            int color = rand()%6;
            if(i == 7 && j == 7){
                nonbox = 0;
            }
            Flower *flower = new Flower(flowerColor[color][0],flowerColor[color][1],flowerColor[color][2], nonbox);
            flower->size(2.f);
            flower->position(-400.f+20*j, -100.f, 700.f+20*i);
            AddObjectToScene(flower);
        }
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            int nonbox = 1;
            int color = rand()%6;
            if(i == 7 && j == 7){
                nonbox = 0;
            }
            Flower *flower = new Flower(flowerColor[color][0],flowerColor[color][1],flowerColor[color][2], nonbox);
            flower->size(2.f);
            flower->position(-100.f+20*j, -100.f, 700.f+20*i);
            AddObjectToScene(flower);
        }
    }

}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 30000.0);
}
