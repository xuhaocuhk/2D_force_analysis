//
// Created by 徐豪 on 2017/4/13.
//

#include <QPainter>
#include "Edge.h"
#include "Util.cpp"
#include "Shape/Arrow.h"
#include "Header/PaintWidget.h"

int Edge::index;

Edge::Edge(QWidget * widget,Node *start, Node *end) {
    this->start = start;
    this->end = end;
    this->widget = widget;
    this->id = index++;
    start->addEdge(this);
    end->addEdge(this);
}
Edge::Edge(QWidget * widget, Node * start, Node * end, double diameter){
    new(this) Edge(widget,start,end);
    this->diameter = diameter;
}

void Edge::paint() {
    QPainter painter(widget);
    QPen pen = painter.pen();
    pen.setWidth(60*diameter);
    pen.setColor(QColor(90,90,90));
    painter.setPen(pen);
    painter.drawLine(start->center(),end->center());

    if(((PaintWidget*)widget)->isShowBending()){
        //Draw bending stress text
        Vector2d weight(0,getGravity());
        Vector2d edgeVec(start->center().x()-end->center().x(),start->center().y()-end->center().y());
        double y_component = (weight.x()*edgeVec.y()-weight.y()*edgeVec.x())/edgeVec.norm();
        QString text = QString::fromStdString(ConvertToString(fabs(y_component)*length/10));
        painter.drawText((start->getX()+end->getX())/2,(start->getY()+end->getY())/2,text);

        //visualization using color
        double last_x = start->center().x();
        double last_y = start->center().y();
        for(double t = 0.0;t<=1.0;t+=0.05){
            double p_x = start->center().x()+t*(end->center().x()-start->center().x());
            double p_y = start->center().y()+t*(end->center().y()-start->center().y());
            double stress_max = t*fabs(y_component)*length/10;
            a = -4*stress_max/(length*length);
            b = 4*stress_max/length;
            double stress = a*length*t*length*t+b*length*t;
            if(stress<400){
                painter.setPen (QPen(QColor(0,0,255),3));
            }else if(stress>400&&stress<=800){
                painter.setPen (QPen(QColor(0,255,200),3));
            }else if(stress>800&&stress<=1200){
                painter.setPen (QPen(QColor(255,255,0),3));
            }else if(stress>1200&&stress<=1600){
                painter.setPen (QPen(QColor(255,126,0),3));
            }else if(stress>1600){
                painter.setPen (QPen(QColor(255,0,0),3));
            }
            painter.drawLine(last_x,last_y,p_x,p_y);
            last_x = p_x;
            last_y = p_y;
        }
    }


    //Draw gravity
    Arrow arrow((start->getX()+end->getX())/2,(start->getY()+end->getY())/2,(start->getX()+end->getX())/2,(start->getY()+end->getY())/2+getGravity());
    arrow.paint(widget,QColor(0,0,0));
    //Draw forces
    if(((PaintWidget*)widget)->isShowResultantForce()){
        Arrow arrow1x(start->center().x(),start->center().y(),start->center().x()+f1x,start->center().y()+f1y);
        Arrow arrow2x(end->center().x(),end->center().y(),end->center().x()+f2x,end->center().y()+f2y);
        arrow1x.paint(widget,QColor(0,0,0));
        arrow2x.paint(widget,QColor(0,0,0));
    }else{
        Arrow arrow1x(start->center().x(),start->center().y(),start->center().x()+f1x,start->center().y());
        Arrow arrow1y(start->center().x(),start->center().y(),start->center().x(),start->center().y()+f1y);
        Arrow arrow2x(end->center().x(),end->center().y(),end->center().x()+f2x,end->center().y());
        Arrow arrow2y(end->center().x(),end->center().y(),end->center().x(),end->center().y()+f2y);
        arrow1x.paint(widget,QColor(0,0,0));
        arrow1y.paint(widget,QColor(0,0,0));
        arrow2x.paint(widget,QColor(0,0,0));
        arrow2y.paint(widget,QColor(0,0,0));
    }
}

Vector2d Edge::getUnitVec() {
    Vector2d vec(start->getX()-end->getX(),start->getY()-end->getY());
    vec = vec/vec.norm();
    return vec;
}

double Edge::getGravity() {
    using namespace std;
    Vector2d vec(start->getX()-end->getX(),start->getY()-end->getY());
    length = vec.norm();
    return density*M_PI*pow((diameter/2),2)*length*g;
}