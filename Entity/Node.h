//
// Created by 徐豪 on 2017/4/12.
//

#ifndef DRAWPAD_NODE_H
#define DRAWPAD_NODE_H


#include <QWidget>
#include <vector>

class Edge;
class ExternalForce;

class Node {

public:
    Node(QWidget * widget, int x , int y);
    void paint();
    void paintExterForces();
    int getX() { return x; }
    int getY() { return y;}
    void setX(int x) {this->x = x;}
    void setY(int y) { this->y = y;}
    int Id() {return id;}
    bool containPoint(QPoint);//given a point, judge whether the this node object contains the point.
    QPoint center(){ return QPoint(x+RADIUS/2,y+RADIUS/2); } // get the center position of the node
    void addEdge(Edge*);//回调函数，在边添加节点时被调用
    void addExterForce(ExternalForce*);//回调函数，在添加外力时被调用
    std::vector<Edge*> getEdges(){return connEdges;}
    std::vector<ExternalForce*> getExterForce(){return exterForces;}
    void setSupport();
    bool isSupport(){return is_support;}
    int getSupportId(){return supportId;}
    void setSupportForce(double force){this->support_force = force;}
    double getSupportForce(){return support_force;}

public:
    const int RADIUS = 15;
    static int index;
    static int support_num;//拥有地面支撑力的节点的个数

private:
    QWidget *widget;
    int x; int y;
    int id;//id of the node
    int supportId;
    bool is_support = false;//标识此点是否与地面接触，即是否地面支撑。
    double support_force;//支撑力，前提是此节点为支撑节点
    std::vector<Edge*> connEdges; // 表示与其相连的边
    std::vector<ExternalForce*> exterForces;//边上所受外力
};


#endif //DRAWPAD_NODE_H
