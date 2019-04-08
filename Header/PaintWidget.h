#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QObject>
#include <QWidget>
#include "Entity/Node.h"
#include "Entity/Edge.h"
#include <vector>
#include "Force/ExternalForce.h"
#include "Eigen/Dense"


using namespace std;
class PaintWidget: public QWidget
{
    Q_OBJECT
public:
    PaintWidget();
    bool isShowBending(){return is_show_bending;}
    bool isShowResultantForce(){return is_show_resultant_force;}

protected:
   void paintEvent(QPaintEvent *event);
   void mousePressEvent(QMouseEvent *);
   void mouseMoveEvent(QMouseEvent *);
   void mouseReleaseEvent(QMouseEvent * event);

private:
    vector<Node*> nodeList;
    vector<Edge*> edgeList;
    vector<ExternalForce*> e_forceList;

    VectorXd forceVec;
    bool drag;//indicate whether it is in a drag state;
    Node* currentNode;// indicate current drag node

    bool enable_gravity = false;
    bool enable_exter_force = false;
    bool is_show_resultant_force = false;
    bool is_show_bending = true;

private:
    void calForceOnEdge();//old method
    void calForceWithFriction();//new method
    void drawGround();


private://test data
    void data1();
    void data2();
    void data3();
    void data4();
    void data5();
    void data6();
    void data7();
    void dataWithFriction();
    void dataWithFriction1();
    void dataWithFriction2();
    void dataWithFriction3();
    void dataWithFriction4();
    void dataWithFriction5();
    void dataWithFriction6();
    void dataWithFriction7();
    void dataWithFriction8();

public slots:
    void enableGravity(bool enabled);
    void enableExternalForce(bool enabled);
    void changeStressType(bool isbending);
    void enableResultantForce(bool enable_deformation);

signals:
    void errorChanged(QString text);

};

#endif // PAINTWIDGET_H
