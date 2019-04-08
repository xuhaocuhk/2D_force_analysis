//
// Created by 徐豪 on 2017/4/26.
//

#ifndef DRAWPAD_ARROW_H
#define DRAWPAD_ARROW_H


#include <QWidget>

class Arrow {
public:
    Arrow(double start_x,double start_y,double end_x,double end_y);
    void paint(QWidget * widget,QColor color);
    double length();

private:
    double start_x;
    double start_y;
    double end_x;
    double end_y;
};

#endif //DRAWPAD_ARROW_H
