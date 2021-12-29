#pragma once
#include <iostream>
#include <fstream>
#define halfG 4.905

using namespace std;

struct Wall{
    double x,h;
    Wall(double b, double c){
        x = b;
        h = c;
    };
    friend ostream& operator<<(ostream &s, const Wall a){
        return s << a.x << " " << a.h;
    };
};

struct Bullet{
    double h, x, vx, vy;
    Bullet(double a, double b, double c){
        x = 0;
        h = a;
        vx = b;
        vy = c;
    };
    friend ostream& operator<<(ostream &s, const Bullet a){
        return s << a.x << " " << a.h << " " << a.vx << " " << a.vy;
    };
    void rebound(){
        vx = -vx;
    };
    void moveTo(Wall targetWall){
        double t{abs((targetWall.x-x)/vx)};
        x = targetWall.x;
        h = h + vy*t - halfG*t*t;
        vy = vy - 2*halfG*t;
    }
};

int getFileLength(const char* path){
    ifstream infile(path);
    int len{};
    double x{};
    while (infile >> x){
        len++;
    }
    return len;
}

double* readFile(const char* path, int len){
    double x;
    double* data = new double[len];
    std::ifstream infile(path);
    for (int i=0; i<len; i++){
        infile >> x;
        data[i] = x;
    }
    return data;
}

int* getWalls(Bullet b, Wall* walls, int size){
    int amount{0};
    int* wallIds = new int;
    if (b.vx<0){
        for (int i=0; i<size; i++){
            if (walls[i].x<b.x) {
                amount++;
                wallIds[amount]=i;
            };
        };
        wallIds[0] = amount;
    } else {
        for (int i=0; i<size; i++){
            if (walls[i].x>b.x) {
                amount++;
                wallIds[amount]=i;
            };
        };
        wallIds[0] = amount;
    };
    return wallIds;
}

int getClosestWallId(Bullet b, Wall* walls, int* wallIds){
    int closestWallId = wallIds[1];
    for (int i=1; i<wallIds[0]; i++){
        if (abs(walls[closestWallId].x-b.x)>abs(walls[wallIds[i]].x-b.x)){ closestWallId = wallIds[i]; }
    };
    // cout << "closest wall id: " << closestWallId << endl;
    return closestWallId;
}

Wall* arrangeByX(Wall* walls, int size){
    Wall temp(0,0);
    for (int i=0; i<(size-1); i++){
        for (int j=i; j<size; j++){
            if (walls[j].x < walls[i].x){
                temp = walls[j];
                walls[j] = walls[i];
                walls [i] = temp;
            };
        };
    };
    return walls;
}

/*

int getLength(Vector2D arr[], const int size, bool neg){
    int len{};
    if (neg){
        for (int i=0; i<size; i++){
            if (arr[i]._x<0) {
                len++;
            }
        }
    } else {
        for (int i=0; i<size; i++){
            if (arr[i]._x>0) {
                len++;
            }
        }
    };
    return len;
}

int* getLeftVectorsId(Vector2D arr[], const int size){
    int len{getLength(arr, size, true)};
    int* left = new int[len];
    int count_l{};
    for (int i=0; i<size; i++){
        if (arr[i]._x<0) {
            left[count_l]=i;
            count_l++;
        }
    }
    return left;
}

int* getRightVectorsId(Vector2D arr[], const int size){
    int len{getLength(arr, size, false)};
    int* right = new int[len];
    int count_r{};
    for (int i=0; i<size; i++){
        if (arr[i]._x>0) {
            right[count_r]=i;
            count_r++;
        }
    }
    return right;
}
*/