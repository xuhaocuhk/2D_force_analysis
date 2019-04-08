//
// Created by 徐豪 on 2017/4/12.
//

#include <QPainter>
#include <cmath>
#include "Node.h"
#include "Edge.h"
#include "Force/ExternalForce.h"
#include "Util.cpp"
#include "Shape/Arrow.h"


using namespace std;

int Node::index;
int Node::support_num;

Node::Node(QWidget *widget, int x = 0, int y = 0) {
    this->widget = widget;
    this->x = x;
    this->y = y;
    this->id = index++;
}

void Node::paint() {
    //Draw node circle
    QPainter painter(widget);
    if(is_support){
        painter.setBrush(Qt::red);
        painter.drawEllipse(x,y,RADIUS,RADIUS);
    }else{
        painter.setBrush(Qt::black);
        painter.drawEllipse(x,y,RADIUS,RADIUS);
    }
    painter.setBrush(Qt::blue);
    /**
     * Draw Arrows indicate the force
     */
   // indicate force on each edge is compress or stretch
//    QPixmap pix_stretch_arrow;
//    QPixmap pix_compress_arrow;
//    pix_compress_arrow.load("../images/compress_arrow.png");
//    pix_stretch_arrow.load("../images/stretch_arrow.png");
//    for(int i =0;i<connEdges.size();i++){
//        if(connEdges.at(i)->getForce().getMagnitude()==0){continue;}
//        int center_x = (connEdges.at(i)->getStartNode()->getX()+connEdges.at(i)->getEndNode()->getX())/2;
//        int center_y = (connEdges.at(i)->getStartNode()->getY()+connEdges.at(i)->getEndNode()->getY())/2;
//        if(connEdges.at(i)->getStartNode()->Id() == Id()){//如果自己是startnode则方向统一，不是则是相反方向
//            if(connEdges.at(i)->getForce().getMagnitude()>0){
//                painter.drawPixmap(center_x, center_y,40,14,pix_compress_arrow);
//            }else{
//                painter.drawPixmap(center_x, center_y,40,14,pix_stretch_arrow);
//            }
//        }
//    }
//
//    //Draw arrows around a node
//    for(int i =0;i<connEdges.size();i++){
//        if(connEdges.at(i)->getStartNode()->Id() == Id()){//如果自己是startnode则方向统一，不是则是相反方向
////            Arrow arrow(x,y,x+connEdges.at(i)->getForce().getUnitVec()(0)*connEdges.at(i)->getForce().getMagnitude()/3,y+connEdges.at(i)->getForce().getUnitVec()(1)*connEdges.at(i)->getForce().getMagnitude()/3);
//            Arrow arrow(x,y,x+connEdges.at(i)->getForce().getUnitVec()(0)*25,y+connEdges.at(i)->getForce().getUnitVec()(1)*25);
//            arrow.paint(widget);
//        }else{
////            Arrow arrow(x,y,x-connEdges.at(i)->getForce().getUnitVec()(0)*connEdges.at(i)->getForce().getMagnitude()/3,y-connEdges.at(i)->getForce().getUnitVec()(1)*connEdges.at(i)->getForce().getMagnitude()/3);
//            Arrow arrow(x,y,x-connEdges.at(i)->getForce().getUnitVec()(0)*25,y-connEdges.at(i)->getForce().getUnitVec()(1)*25);
//            arrow.paint(widget);
//        }
//    }
}

void Node::paintExterForces() {
    //Draw external forces
    QPainter painter(widget);
    painter.setPen(QPen(Qt::blue,5));
    for(int i = 0;i<exterForces.size();i++){
        painter.drawLine(x,y,x+exterForces.at(i)->getForce().getUnitVec()(0)*exterForces.at(i)->getForce().getMagnitude(),y+exterForces.at(i)->getForce().getUnitVec()(1)*exterForces.at(i)->getForce().getMagnitude());
    }
    if(this->isSupport()){
        painter.setPen(QPen(Qt::green,5));
        painter.drawLine(x,y,x,y+this->support_force);
    }
}

bool Node::containPoint(QPoint p){
    double a = pow(abs(center().x()-p.x()),2) + pow(abs(center().y()-p.y()),2);
    return a < RADIUS*RADIUS;
}

void Node::addEdge(Edge * edge) {
    connEdges.push_back(edge);
}

void Node::addExterForce(ExternalForce * force) {
    exterForces.push_back(force);
}

void Node::setSupport(){
    this->is_support = true;
    supportId = support_num++;
}