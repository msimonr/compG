#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3{
    private:
    float coordX;
    float coordY;
    float coordZ;
    float norma;

    public:
    
    Vector3(float x, float y, float z);
    ~Vector3();

    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setX(float y);
    void setX(float z);
    void suma(Vector3 u);
    void resta(Vector3 u);
    void multi(Vector3 u);
};

#endif