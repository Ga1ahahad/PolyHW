#include <iostream>
#include "functions.cpp"
#include <string.h>
#include <iterator>
#define G 9.81

using namespace std;

int main(){
    const char* path{"in.txt"};
    Wall* walls = new Wall(0,0);

    int len{getFileLength(path)};
    double* data{readFile(path, len)};
    Bullet bullet(data[0], data[1], data[2]);
    for (int i=0; i<(len-3)/2; i++){
        walls[i].x = data[3+2*i];
        walls[i].h = data[4+2*i];
    };
    int id{};
    while (true){
        int* wallIds{getWalls(bullet, walls, (len-3)/2)};
        if (wallIds[0]==0){
            if (bullet.vx>0){
                cout << wallIds[0] << endl;
                break;
            };
            if (bullet.vx<0){
                cout << 0 << endl;
                break;
            };
        }
        id = getClosestWallId(bullet, walls, wallIds);
        bullet.moveTo(walls[id]);
        if (bullet.h<=0){
            if (bullet.vx>0){
                cout << id << endl;
                cout << bullet << endl;
                cout << walls[id];
                break;
            };
            if (bullet.vx<0){
                cout << id+1 << endl;
                break;
            };
        };
        if (walls[id].h>=bullet.h){
            bullet.rebound();
            cout << " at " << walls[id] << endl;
            cout << bullet << endl;
        };
        delete[] wallIds;
    };
    return 0;
}