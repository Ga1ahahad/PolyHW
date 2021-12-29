#include <iostream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Vector2D{
    double _x;
    double _y;
    friend Vector2D operator+(const Vector2D a, const Vector2D b){
        return Vector2D{_x: (a._x+b._x), _y: (a._y+b._y)};
    };
    friend double operator*(const Vector2D a, const Vector2D b){
        return double{(a._x*b._x)+(a._y*b._y)};
    };
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &a){
        os << a._x << " " << a._y;
        return os;
    }
    void turn(Vector2D& a, double b){
        double x1, y1;
        // std::cout << b << std::endl;
        x1 = (a._x*cos(b)-a._y*sin(b));
        y1 = (a._y*cos(b)+a._x*sin(b));
        a._x = x1;
        a._y = y1;
    }
};

double abs(const Vector2D v){
    return pow((v._x*v._x+v._y*v._y),0.5);
};

int getQuadrant(const Vector2D a){
    if (a._x>=0&&a._y>=0){
        return 1;
    } else if (a._x<0&&a._y>=0){
        return 2;
    }else if (a._x<0&&a._y<0){
        return 3;
    }else if (a._x>=0&&a._y<0){
        return 4;
    };
}

double getAngle(const Vector2D a, const Vector2D b){
    return acos(a*b/abs(a)/abs(b));
}

int getFileLength(const char* path){
    std::ifstream infile(path);
    int len;
    double x;
    while (infile >> x >> x){
        len++;
    }
    return len;
}

Vector2D* readFile(const char* path){
    std::ifstream infile0(path);
    double x, y;
    int len{getFileLength(path)};
    Vector2D* vectors = new Vector2D[len];
    std::ifstream infile(path);
    for (int i=0; i<len; i++){
        infile >> x >> y;
        vectors[i]._x = x;
        vectors[i]._y = y;
    }
    return vectors;
}

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

    int q = getQuadrant(vectors[0]);                              // q stands for quadrant
    double angle = getAngle(vectors[0],vertical);
    if (q==2||q==3){
        angle = 2*3.14-angle;
    }
    for (int i=0; i<vectorsAmount; i++){
        vectors_turned[i].turn(vectors_turned[i], angle);
    }
    vectors_left = getLeftVectorsId(vectors_turned, vectorsAmount);
    int leftVectorsAmount {getLength(vectors_turned, vectorsAmount, true)};
    int leftmostId{0};
    for (int i=0; i<leftVectorsAmount; i++){
        if (vectors_turned[vectors_left[i]]._x < vectors_turned[vectors_left[leftmostId]]._x){
            leftmostId = i;
        };
    };
    vectors_righ = getRightVectorsId(vectors_turned, vectorsAmount);
    int righVectorsAmount {getLength(vectors_turned, vectorsAmount, false)};
    int righmostId{};
    for (int i=0; i<righVectorsAmount; i++){
        if (vectors_turned[vectors_righ[i]]._x > vectors_turned[vectors_righ[righmostId]]._x){
            righmostId = i;
        };
    };
    cout << "Leftmost: " << vectors[vectors_left[leftmostId]] << endl;
    cout << "Rightmost: " << vectors[vectors_righ[righmostId]] << endl;
    return 0;
}
