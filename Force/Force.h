//
// Created by 徐豪 on 2017/4/13.
//

#ifndef DRAWPAD_FORCE_H
#define DRAWPAD_FORCE_H
#include"Eigen/Dense"

using namespace Eigen;

class Force {
public:
    Force(){}

    Force(Vector2d unitVec,double magnitude){//unitVector and magnitude of magnitude
        this->unitVec = unitVec;
        this->magnitude = magnitude;
    }
    Vector2d getUnitVec() { return  unitVec;}
    double getMagnitude(){ return magnitude;}

private:
    Vector2d unitVec;//单位向量表示力的方向
    double magnitude;//力的大小

};
#endif //DRAWPAD_FORCE_H
