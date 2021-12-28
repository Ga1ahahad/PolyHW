#pragma once
#include <iostream>
#include <fstream>
#define halfG 4.905

struct Bullet{
    double h, x, vx, vy;
    Bullet(double, double, double);
    void rebound();
    void moveTo(Bullet, Wall, int){};
};

struct Wall{
    double x,h;
    Wall(double, double){};
};

int getFileLength(const char*);

double* readFile(const char*, int);

int* getWalls(Bullet, Wall*, int);