#include <iostream>
#include <fstream>
#define halfG 4.905
#include <string.h>
#include <iterator>
#define G 9.81

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
    // walls = arrangeByX(walls, (len-3)/2);
    int id{}, last_id{};
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
        last_id = id;
        if (bullet.h<=0){
            if (bullet.vx>0){
                cout << id << endl;
                break;
            };
            if (bullet.vx<0){
                cout << id+1 << endl;
                break;
            };
        };
        if (walls[id].h>=bullet.h){
            bullet.rebound();
        };
        delete[] wallIds;
    };
    cout << "bullet coord: " << bullet << endl;
    return 0;
}
