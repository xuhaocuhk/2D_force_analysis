//
// Created by 徐豪 on 2017/4/26.
//

#include <QPainter>
#include "Arrow.h"
#include <iostream>
#include <cmath>
#include "Entity/Util.cpp"

Arrow::Arrow(double start_x,double start_y,double end_x,double end_y){
    this->start_x = start_x;
    this->start_y = start_y;
    this->end_x = end_x;
    this->end_y = end_y;
}

void Arrow::paint(QWidget * widget,QColor color) {
    using namespace std;
    QPainter painter(widget);
    double p_x = start_x+(end_x-start_x)/4*3;
    double p_y = start_y+(end_y-start_y)/4*3;//四分之一点
    double k = (end_x-start_x)/(start_y-end_y);
    double b = p_y - k*p_x;
    double right_p_x = p_x+sqrt(length()/(1+k*k));
    double right_p_y = k* right_p_x+b;
    double left_p_x = p_x-sqrt(length()/(1+k*k));
    double left_p_y = k*left_p_x+b;
    if(abs(end_y-start_y)<0.000001){
        right_p_y = p_y+length()/3;
        left_p_y =  p_y -length()/3;
    }

    QPainterPath path;
    path.moveTo (end_x, end_y);
    path.lineTo (right_p_x, right_p_y);
    path.lineTo (left_p_x,   left_p_y);
    path.lineTo (end_x, end_y);

    painter.setPen (QPen(color,3));
    painter.fillPath (path, QBrush (color));

    painter.drawLine(start_x,start_y,p_x,p_y);

    //paint text of length
    int length = (int)sqrt((start_x-end_x)*(start_x-end_x)+(start_y-end_y)*(start_y-end_y));
    QString text = QString::fromStdString(ConvertToString(length));
    painter.drawText((start_x+end_x)/2,(start_y+end_y)/2,text);
}

double Arrow::length() {
    return sqrt((start_x-end_x)*(start_x-end_x)+(start_y-end_y)*(start_y-end_y));
}