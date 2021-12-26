#include <iostream>
#include "functions.cpp"
#include <fstream>

using namespace std;

int main(){
    int vectorsAmount;                                            // количество векторов включая нулевой
    const char* path = "in.txt";
    Vector2D* vectors = new Vector2D;
    int* vectors_left = new int;
    int* vectors_righ = new int;
    Vector2D* vectors_turned = new Vector2D;
    Vector2D vertical{_x:0, _y:1};

    vectorsAmount = getFileLength(path);
    vectors = readFile(path);
    vectors_turned = readFile(path);

    int q = getQuadrant(vectors[0]);    // q stands for quadrant
    double angle = getAngle(vectors[0],vertical);
    if (q==2||q==3){
        angle = 2*3.14-angle;
    }
    for (int i=0; i<vectorsAmount; i++){
        vectors_turned[i].turn(vectors_turned[i], angle);
    }
    vectors_left = getLeftVectorsId(vectors_turned, vectorsAmount);
    int leftVectorsAmount {getLength(vectors, vectorsAmount, true)};
    int leftmostId{0};
    for (int i=0; i<leftVectorsAmount; i++){
        if (vectors[vectors_left[i]]._x < vectors[vectors_left[leftmostId]]._x){
            leftmostId = i;
        };
    };
    vectors_righ = getRightVectorsId(vectors_turned, vectorsAmount);
    int righVectorsAmount {getLength(vectors, vectorsAmount, false)};
    int righmostId{};
    for (int i=0; i<righVectorsAmount; i++){
        if (vectors[vectors_righ[i]]._x > vectors[vectors_righ[righmostId]]._x){
            righmostId = i;
        };
    };
    cout << "Leftmost: " << vectors[vectors_left[leftmostId]] << endl;
    cout << "Rightmost: " << vectors[vectors_righ[righmostId]] << endl;
    return 0;
}