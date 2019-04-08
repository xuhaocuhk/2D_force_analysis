//
// Created by 徐豪 on 2017/4/13.
//

#ifndef DRAWPAD_EDGE_H
#define DRAWPAD_EDGE_H

#include "Node.h"
#include "Force/Force.h"
#include <Eigen/Dense>

using namespace Eigen;

class Edge {

public:
    Edge(QWidget * widget, Node * start, Node * end);
    Edge(QWidget * widget, Node * start, Node * end, double diameter);
    int Id(){ return id;}
    Vector2d getUnitVec();//get the unit vector base on the edge direction
    Node* getStartNode() { return  start;}
    Node* getEndNode(){ return end;}
    void setForce(Force force) {this->force = force;}
    Force getForce(){return force;}
    double getGravity();
    void paint();
    int getF1XId(){ return 4*id;};
    int getF1YId(){ return 4*id+1;};
    int getF2XId(){ return 4*id+2;};
    int getF2YId(){ return 4*id+3;};

public:
    static int index;
    int id;
    const double g = 9.8;
    double diameter = 0.1;//thickness of the rod
    double length;
    double density = 1;

    double f1x;
    double f1y;
    double f2x;
    double f2y;

    double a;//两个参数，代表抛物线y=ax^2+b的两个参数
    double b;

private:
    Node * start;
    Node * end; //note for two end of a node
    QWidget * widget;
    Force force;
    double gravity;
};

#endif //DRAWPAD_EDGE_H
