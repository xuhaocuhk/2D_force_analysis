//
// Created by 徐豪 on 2017/4/18.
//
#include "Header/PaintWidget.h"


/**
 * Book sample
 */
void PaintWidget::data1() {
    //Strategy two
    int p_x = 300,p_y = 300;
    Node *node1 = new Node(this,p_x,p_y);//node A
    Node *node2 = new Node(this,p_x+120,p_y);//node B
    Node *node3 = new Node(this,p_x+240,p_y);//node C
    Node *node4 = new Node(this,p_x+60,p_y+80);//node D
    Node *node5 = new Node(this,p_x+180,p_y+80);//node E

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);

    Edge *edge1 = new Edge(this,node1,node2);
    Edge *edge2 = new Edge(this,node2,node3);
    Edge *edge3 = new Edge(this,node1,node4);
    Edge *edge4 = new Edge(this,node2,node4);
    Edge *edge5 = new Edge(this,node2,node5);
    Edge *edge6 = new Edge(this,node3,node5);
    Edge *edge7 = new Edge(this,node4,node5);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
    /**
     * initialize the external force
     */
    ExternalForce *force1 = new ExternalForce(Force(Vector2d(0, 1.0),20),node1);//给node1一个向右下的200N的力
    ExternalForce *force2 = new ExternalForce(Force(Vector2d(0, 1.0),10),node2);//给node2一个向右下的100N的力
    ExternalForce *force3 = new ExternalForce(Force(Vector2d(0, -1.0),100),node5);
    ExternalForce *force4 = new ExternalForce(Force(Vector2d(0, 1.0),70),node3);
    e_forceList.push_back(force1);
    e_forceList.push_back(force2);
    e_forceList.push_back(force3);
    e_forceList.push_back(force4);
}


/**
 * test with gravity and external forces
 */
void PaintWidget::data2(){
    Node *node1 = new Node(this,200,200);
    Node *node2 = new Node(this,100,300);
    Node *node3 = new Node(this,200,300);
    Node *node4 = new Node(this,370,300);
    Node *node5 = new Node(this,200,400);node5->setSupport();
    Node *node6 = new Node(this,370,400);node6->setSupport();
    Node *node7 = new Node(this,100,400);node7->setSupport();


    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);
    nodeList.push_back(node6);
    nodeList.push_back(node7);

    Edge *edge = new Edge(this,node1,node2);
    Edge *edge1 = new Edge(this,node1,node3);
    Edge *edge2 = new Edge(this,node1,node4);
    Edge *edge3 = new Edge(this,node2,node3);
    Edge *edge4 = new Edge(this,node3,node4);
    Edge *edge5 = new Edge(this,node5,node2);
    Edge *edge6 = new Edge(this,node5,node3);
    Edge *edge7 = new Edge(this,node5,node6);
    Edge *edge8 = new Edge(this,node6,node4);
    Edge *edge9 = new Edge(this,node7,node2);
    Edge *edge10 = new Edge(this,node7,node5);

    edgeList.push_back(edge);
    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
    edgeList.push_back(edge8);
    edgeList.push_back(edge9);
    edgeList.push_back(edge10);

    ExternalForce *force1 = new ExternalForce(Force(Vector2d(0, 1.0),100),node1);//给node1一个向下的力
    e_forceList.push_back(force1);
}

/**
 * gravity test complex sample
 */
void PaintWidget::data3(){
    Node *node1 = new Node(this,200,200);
    Node *node2 = new Node(this,100,300);
    Node *node3 = new Node(this,200,300);
    Node *node4 = new Node(this,370,300);
    Node *node5 = new Node(this,200,400);node5->setSupport();
    Node *node6 = new Node(this,370,400);node6->setSupport();
    Node *node7 = new Node(this,100,400);node7->setSupport();


    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);
    nodeList.push_back(node6);
    nodeList.push_back(node7);

    Edge *edge = new Edge(this,node1,node2,0.3);
    Edge *edge1 = new Edge(this,node1,node3,0.2);
    Edge *edge2 = new Edge(this,node1,node4,0.5);
    Edge *edge3 = new Edge(this,node2,node3,0.8);
    Edge *edge4 = new Edge(this,node3,node4,0.1);
    Edge *edge5 = new Edge(this,node5,node2,0.6);
    Edge *edge6 = new Edge(this,node5,node3,0.05);
    Edge *edge7 = new Edge(this,node5,node6,0.02);
    Edge *edge8 = new Edge(this,node6,node4,0.1);
    Edge *edge9 = new Edge(this,node7,node2,0.3);
    Edge *edge10 = new Edge(this,node7,node5,0.1);

    edgeList.push_back(edge);
    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
    edgeList.push_back(edge8);
    edgeList.push_back(edge9);
    edgeList.push_back(edge10);
}

//test gravity simple
void PaintWidget::data4(){
    //Strategy two
    int p_x = 300,p_y = 300;
    Node *node2 = new Node(this,p_x+120,p_y);//node B
    Node *node4 = new Node(this,p_x+60,p_y+60);node4->setSupport();//node D
    Node *node5 = new Node(this,p_x+180,p_y+60);node5->setSupport();//node E

    nodeList.push_back(node2);
    nodeList.push_back(node4);
    nodeList.push_back(node5);

    Edge *edge4 = new Edge(this,node2,node4,0.5);
    Edge *edge5 = new Edge(this,node2,node5,0.5);
    Edge *edge7 = new Edge(this,node4,node5,0.5);

    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge7);
}
/**
 * test unstable consition
 */
void PaintWidget::data5() {
    int p_x = 300,p_y = 300;
    Node* node1 = new Node(this,p_x,p_y);
    Node* node2 = new Node(this,p_x+100,p_y);
    Node* node3 = new Node(this,p_x+100,p_y+100);node3->setSupport();
    Node* node4 = new Node(this,p_x,p_y+100);node4->setSupport();

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge = new Edge(this,node1,node2,0.3);
    Edge *edge1 = new Edge(this,node2,node3,0.2);
    Edge *edge2 = new Edge(this,node3,node4,0.5);
    Edge *edge3 = new Edge(this,node4,node1,0.8);

    edgeList.push_back(edge);
    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);

    ExternalForce *force1 = new ExternalForce(Force(Vector2d(0, 1.0),100),node1);//给node1一个向下的力
    e_forceList.push_back(force1);
}

/**
 *  stable condition based on data5
 */
void PaintWidget::data6() {
    int p_x = 300,p_y = 300;
    Node* node1 = new Node(this,p_x,p_y);
    Node* node2 = new Node(this,p_x+100,p_y);
    Node* node3 = new Node(this,p_x+100,p_y+100);node3->setSupport();
    Node* node4 = new Node(this,p_x,p_y+100);node4->setSupport();

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge = new Edge(this,node1,node2,0.3);
    Edge *edge1 = new Edge(this,node2,node3,0.2);
    Edge *edge2 = new Edge(this,node3,node4,0.5);
    Edge *edge3 = new Edge(this,node4,node1,0.8);
    Edge *edge4 = new Edge(this,node4,node2,0.2);

    edgeList.push_back(edge);
    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);

    ExternalForce *force1 = new ExternalForce(Force(Vector2d(0, 1.0),100),node1);//给node1一个向下的力
    e_forceList.push_back(force1);
}
/**
 * another unstable condition
 */
void PaintWidget::data7() {
    int p_x = 300,p_y = 300;
    Node* node1 = new Node(this,p_x,p_y);
    Node* node2 = new Node(this,p_x+100,p_y);
    Node* node3 = new Node(this,p_x+50,p_y+80);
    Node* node4 = new Node(this,p_x+50,p_y+200);node4->setSupport();

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge = new Edge(this,node1,node2,0.3);
    Edge *edge1 = new Edge(this,node2,node3,0.2);
    Edge *edge2 = new Edge(this,node3,node1,0.5);
    Edge *edge3 = new Edge(this,node4,node3,0.8);

    edgeList.push_back(edge);
    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);

//    ExternalForce *force1 = new ExternalForce(Force(Vector2d(0, 1.0),100),node1);//给node1一个向下的力
//    e_forceList.push_back(force1);
}

void PaintWidget::dataWithFriction() {
    int p_x = 300,p_y = 300;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x+160,p_y+160);node2->setSupport();//node D
    Node *node3 = new Node(this,p_x-160,p_y+160);node3->setSupport();//node E

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
}

void PaintWidget::dataWithFriction1() {
    int p_x = 300,p_y = 300;
    Node *node1 = new Node(this,p_x,p_y);//node 0
    Node *node2 = new Node(this,p_x+60,p_y+60);node2->setSupport();//node 1
    Node *node3 = new Node(this,p_x-60,p_y+60);node3->setSupport();//node 2
    Node *node4 = new Node(this,p_x,p_y-40);

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);
    Edge *edge3 = new Edge(this,node1,node4,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
}

void PaintWidget::dataWithFriction2() {
    int p_x = 300,p_y = 300;
    Node *node1 = new Node(this,p_x,p_y);//node 0
    Node *node2 = new Node(this,p_x+60,p_y+60);node2->setSupport();//node 1
    Node *node3 = new Node(this,p_x-60,p_y+60);node3->setSupport();//node 2
    Node *node4 = new Node(this,p_x+120,p_y+60);node4->setSupport();

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);
    Edge *edge3 = new Edge(this,node1,node4,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
}

void PaintWidget::dataWithFriction3() {
    int p_x = 300,p_y = 300;
    double diameter = 0.1;
    Node *node = new Node(this,p_x,p_y);node->setSupport();
    Node *node1 = new Node(this,p_x+60,p_y-60);//node 0
    Node *node2 = new Node(this,p_x+120,p_y);node2->setSupport();
    Node *node3 = new Node(this,p_x+240,p_y);node3->setSupport();
    Node *node4 = new Node(this,p_x+300,p_y-60);
    Node *node5 = new Node(this,p_x+240,p_y-120);
    Node *node6 = new Node(this,p_x+200,p_y-60);
    Node *node7 = new Node(this,p_x+120,p_y-120);
    Node *node8 = new Node(this,p_x+200,p_y-180);
    Node *node9 = new Node(this,p_x+90,p_y-180);
    Node *node10 = new Node(this,p_x+60,p_y-120);
    Node *node11 = new Node(this,p_x,p_y-220);

    nodeList.push_back(node);
    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);
    nodeList.push_back(node6);
    nodeList.push_back(node7);
    nodeList.push_back(node8);
    nodeList.push_back(node9);
    nodeList.push_back(node10);
    nodeList.push_back(node11);

    Edge *edge1 = new Edge(this,node,node1,diameter);
    Edge *edge2 = new Edge(this,node,node2,diameter);
    Edge *edge3 = new Edge(this,node1,node2,diameter);
    Edge *edge4 = new Edge(this,node2,node6,diameter);
    Edge *edge5 = new Edge(this,node2,node3,diameter);
    Edge *edge6 = new Edge(this,node1,node6,diameter);
    Edge *edge7 = new Edge(this,node3,node6,diameter);
    Edge *edge8 = new Edge(this,node3,node4,diameter);
    Edge *edge9 = new Edge(this,node6,node4,diameter);
    Edge *edge10 = new Edge(this,node5,node4,diameter);
    Edge *edge11 = new Edge(this,node6,node5,diameter);
    Edge *edge12 = new Edge(this,node6,node7,diameter);
    Edge *edge13 = new Edge(this,node7,node5,diameter);
    Edge *edge14 = new Edge(this,node5,node8,diameter);
    Edge *edge15 = new Edge(this,node7,node8,diameter);
    Edge *edge16 = new Edge(this,node8,node9,diameter);
    Edge *edge17 = new Edge(this,node7,node9,diameter);
    Edge *edge18 = new Edge(this,node7,node10,diameter);
    Edge *edge19 = new Edge(this,node9,node10,diameter);
    Edge *edge20 = new Edge(this,node10,node11,diameter);
    Edge *edge21 = new Edge(this,node9,node11,diameter);
    //
    Edge *edge22 = new Edge(this,node1,node7,diameter);
    Edge* edge23 = new Edge(this,node1,node10,diameter);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
    edgeList.push_back(edge8);
    edgeList.push_back(edge9);
    edgeList.push_back(edge10);
    edgeList.push_back(edge11);
    edgeList.push_back(edge12);
    edgeList.push_back(edge13);
    edgeList.push_back(edge14);
    edgeList.push_back(edge15);
    edgeList.push_back(edge16);
    edgeList.push_back(edge17);
    edgeList.push_back(edge18);
    edgeList.push_back(edge19);
    edgeList.push_back(edge20);
    edgeList.push_back(edge21);
    edgeList.push_back(edge22);
    edgeList.push_back(edge23);
}

void PaintWidget::dataWithFriction4() {
    int p_x = 300,p_y = 300;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x+60,p_y+60);node2->setSupport();//node D
    Node *node3 = new Node(this,p_x-60,p_y+60);node3->setSupport();//node E

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);
    Edge *edge3 = new Edge(this,node2,node3,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
}

void PaintWidget::dataWithFriction5() {
    int p_x = 300,p_y = 200;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x+120,p_y+120);node2->setSupport();//node D
    Node *node3 = new Node(this,p_x-120,p_y+120);node3->setSupport();//node E
    Node *node4 = new Node(this,p_x-240,p_y);
    Node *node5 = new Node(this,p_x+240,p_y);

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);
    Edge *edge3 = new Edge(this,node2,node3,0.15);
    Edge *edge4 = new Edge(this,node1,node4,0.15);
    Edge *edge5 = new Edge(this,node1,node5,0.15);
    Edge *edge6 = new Edge(this,node3,node4,0.15);
    Edge *edge7 = new Edge(this,node2,node5,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
}

void PaintWidget::dataWithFriction6() {
    int p_x = 300,p_y = 400;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x+240,p_y+240);node2->setSupport();//node D
    Node *node3 = new Node(this,p_x-240,p_y+240);node3->setSupport();//node E
    Node *node4 = new Node(this,p_x-240,p_y);
    Node *node5 = new Node(this,p_x+240,p_y);
    Node *node6 = new Node(this,p_x-240,p_y-240);
    Node *node7 = new Node(this,p_x+240,p_y-240);

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);
    nodeList.push_back(node5);
    nodeList.push_back(node6);
    nodeList.push_back(node7);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node1,node3,0.15);
    Edge *edge3 = new Edge(this,node2,node3,0.15);
    Edge *edge4 = new Edge(this,node1,node4,0.15);
    Edge *edge5 = new Edge(this,node1,node5,0.15);
    Edge *edge6 = new Edge(this,node3,node4,0.15);
    Edge *edge7 = new Edge(this,node2,node5,0.15);
    Edge *edge8 = new Edge(this,node1,node6,0.15);
    Edge *edge9 = new Edge(this,node1,node7,0.15);
    Edge *edge10 = new Edge(this,node6,node7,0.15);
    Edge *edge11= new Edge(this,node4,node6,0.15);
    Edge *edge12= new Edge(this,node5,node7,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
    edgeList.push_back(edge6);
    edgeList.push_back(edge7);
    edgeList.push_back(edge8);
    edgeList.push_back(edge9);
    edgeList.push_back(edge10);
    edgeList.push_back(edge11);
    edgeList.push_back(edge12);
}
//正方形，不稳定
void PaintWidget::dataWithFriction7() {
    int p_x = 300,p_y = 200;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x,p_y+240);node2->setSupport();//node E
    Node *node3 = new Node(this,p_x+240,p_y+240);node3->setSupport();//node D
    Node *node4 = new Node(this,p_x+240,p_y);

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node2,node3,0.15);
    Edge *edge3 = new Edge(this,node3,node4,0.15);
    Edge *edge4 = new Edge(this,node1,node4,0.15);

    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
}

//加入一个棍的正方形
void PaintWidget::dataWithFriction8() {
    int p_x = 300,p_y = 200;
    Node *node1 = new Node(this,p_x,p_y);//node B
    Node *node2 = new Node(this,p_x,p_y+240);node2->setSupport();//node E
    Node *node3 = new Node(this,p_x+240,p_y+240);node3->setSupport();//node D
    Node *node4 = new Node(this,p_x+240,p_y);

    nodeList.push_back(node1);
    nodeList.push_back(node2);
    nodeList.push_back(node3);
    nodeList.push_back(node4);

    Edge *edge1 = new Edge(this,node1,node2,0.15);
    Edge *edge2 = new Edge(this,node2,node3,0.15);
    Edge *edge3 = new Edge(this,node3,node4,0.15);
    Edge *edge4 = new Edge(this,node1,node4,0.15);
    Edge *edge5 = new Edge(this,node1,node3,0.15);


    edgeList.push_back(edge1);
    edgeList.push_back(edge2);
    edgeList.push_back(edge3);
    edgeList.push_back(edge4);
    edgeList.push_back(edge5);
}

