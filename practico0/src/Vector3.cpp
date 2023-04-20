#include <headers/Vector3.h>
#include <math.h>

Vector3::Vector3(float x, float y, float z){
    coordX = x;
    coordY = y;
    coordZ = z;
    norma = sqrt(x*x + y*y + z*z);
};

float Vector3::getX(){
    return coordX;
};
float Vector3::getY(){
    return coordY;
};
float Vector3::getZ(){
    return coordZ;
};
void Vector3::setX(float x){
    coordX = x;
};
void Vector3::setX(float y){
    coordY = y;
};
void Vector3::setX(float z){
    coordZ = z;
};