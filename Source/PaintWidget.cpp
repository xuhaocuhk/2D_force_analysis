#include <iostream>
#include <QtGui>
#include <Header/PaintWidget.h>
#include <Header/mainwindow.h>
#include "Entity/Node.h"
#include "Eigen/Dense"
#include "Force/ExternalForce.h"
#include "Entity/Util.cpp"

using namespace std;

PaintWidget::PaintWidget()
{
    /**
     * initalize the Nodes
     */
    Node::index = 0;
    Node::support_num = 0;
    Edge::index = 0;
    dataWithFriction8();
    /**
     * calculate force on each edge
     */
    calForceWithFriction();
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    for (auto iter = nodeList.cbegin(); iter != nodeList.cend(); iter++){
        if ((*iter)->containPoint(event->pos())){
            currentNode = (*iter);
            drag = true;
            return;
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent * event){
    if (drag == true){
        currentNode->setX(event->x());
        currentNode->setY(event->y());
        calForceWithFriction();
        update();
    }
}

/**
* calculate force on each edge
*/
void PaintWidget::calForceOnEdge() {

    MatrixXd A = MatrixXd::Zero(nodeList.size() * 2, edgeList.size()+Node::support_num);

    cout<<"edgeList.size(): "<<edgeList.size()<<endl;
    for(int j=0; j <edgeList.size(); j++){
            Edge * c_edge = edgeList.at(j);
            int first_n_i = c_edge->getStartNode()->Id();
            int second_n_i = c_edge->getEndNode()->Id();
            A.block(first_n_i*2,j,2,1) = c_edge->getUnitVec();
            A.block(second_n_i*2,j,2,1) = -c_edge->getUnitVec();//对一个edge，对两个node的力方向相同，大小相反。
        }
    for(int j = 0;j<nodeList.size();j++){
        Node* c_node = nodeList.at(j);
        if (c_node->isSupport()){
            A.block(c_node->Id()*2,edgeList.size()+c_node->getSupportId(),2,1) = Eigen::Vector2d(0,-1.0);//将支撑节点都加上支撑力的方向
        }
    }
    /**
     * Ax = b 中的b向量
    */
    VectorXd b = VectorXd::Zero(nodeList.size() * 2);

/**
 * 添加外力
 */
    if(enable_exter_force){
        for(int i = 0; i < e_forceList.size(); i++){
                ExternalForce *c_force = e_forceList.at(i);
                b(c_force->getNode()->Id()*2) = -c_force->getForce().getUnitVec()(0)* c_force->getForce().getMagnitude();
                b(c_force->getNode()->Id()*2+1) = -c_force->getForce().getUnitVec()(1)* c_force->getForce().getMagnitude();
            }
    }
/**
 * 添加重力
 */
    if(enable_gravity){
        for(int i = 0;i<nodeList.size();i++){
            Node * c_node = nodeList.at(i);
            double weight = 0;
            for(int j = 0;j<c_node->getEdges().size();j++){
                weight+=c_node->getEdges().at(j)-> getGravity();
            }
            weight/=2;
            b(c_node->Id()*2+1) -= weight;
        }
    }
    cout<<"------------------------A and b------------------------------------------------------"<<endl;
    cout<<A<<endl<<b<<endl;
    forceVec = A.fullPivHouseholderQr().solve(b);
    cout<<"resultforce:"<<forceVec<<endl;
    emit errorChanged(QString::fromStdString("error:||Ax-b||/||b||:").append(QString::fromStdString(ConvertToString((A*forceVec-b).norm()/b.norm()))));
    cout<<"error||Ax-b||/||b||:"<<(A*forceVec-b).norm()/b.norm()<<"----------------------------------"<<endl;

    for(int i = 0; i < edgeList.size(); i++){
            Edge* c_edge = edgeList.at(i);
            edgeList.at(i)->setForce(Force(c_edge->getUnitVec(), forceVec(c_edge->Id())));
        }
    double total_support = 0;
    for(int i = 0;i<nodeList.size();i++){
        Node * c_node = nodeList.at(i);
        if(c_node->isSupport()){
            c_node->setSupportForce(forceVec(edgeList.size()+c_node->getSupportId()));//根据id设置支撑力大小
            total_support+=fabs(forceVec(edgeList.size()+c_node->getSupportId()));
        }
    }
    /*
     * add friction
     */




    //validation
    double total_weight = 0;
    for(int i = 0; i < edgeList.size(); i++){
        total_weight+=edgeList.at(i)->getGravity();
    }
    cout<<"total_weight:"<<total_weight<<endl;
    cout<<"total_support"<<total_support<<endl;


}
/**
 * new mathod to calculate force on edge
 */
void PaintWidget::calForceWithFriction() {
    MatrixXd A = MatrixXd::Zero(nodeList.size()*2+edgeList.size()*3,edgeList.size()*4+Node::support_num*2);
    int row = 0;
    //构造节点处力的平衡 共2*节点数 行
    for(int i = 0;i<nodeList.size();i++) {
        Node *c_node = nodeList.at(i);
        std::vector<Edge *> edges = c_node->getEdges();
        if (c_node->isSupport() || edges.size() > 1) {//只有一个节点连接大于一条边才进行节点处力的平衡计算
            //构造X方向力相等
            for (int j = 0; j < edges.size(); j++) {
                Edge *c_edge = edges.at(j);
                if (c_edge->getStartNode() == c_node) {//如果连接的节点是这条边的start节点则采用F1,否则为F2
                    A(row, c_edge->getF1XId()) = 1;
                } else {
                    A(row, c_edge->getF2XId()) = 1;
                }
            }
            if (c_node->isSupport()) {
                //加上这个节点上的重力X分量
                A(row, edgeList.size() * 4 + 2 * c_node->getSupportId()) = 1;
            }
            row++;
            //构造Y方向力相等
            for (int j = 0; j < edges.size(); j++) {
                Edge *c_edge = edges.at(j);
                if (c_edge->getStartNode() == c_node) {//如果连接的节点是这条边的start节点则采用F1,否则为F2
                    A(row, c_edge->getF1YId()) = 1;
                } else {
                    A(row, c_edge->getF2YId()) = 1;
                }
            }
            if (c_node->isSupport()) {
                //加上这个节点上的重力Y分量
                A(row, edgeList.size() * 4 + 2 * c_node->getSupportId() + 1) = 1;
            }
            row++;
        }
    }
    //构造每条边受力平衡，共2*边数行
    for(int i = 0;i<edgeList.size();i++){
        Edge* c_edge = edgeList.at(i);
        A(row, c_edge->getF1XId()) = 1;
        A(row, c_edge->getF2XId()) = 1;
        row++;
        A(row, c_edge->getF1YId()) = 1;
        A(row, c_edge->getF2YId()) = 1; //这一项在b那里要相应的加上重力
        row++;
    }

    //构造torque为零，共 1*边数 行
    for(int i = 0;i<edgeList.size();i++){
        Edge* c_edge = edgeList.at(i);
        double start_x = c_edge->getStartNode()->getX();
        double start_y = c_edge->getStartNode()->getY();
        double end_x = c_edge->getEndNode()->getX();
        double end_y = c_edge->getEndNode()->getY();
        double ox = end_x+(start_x-end_x)*3/4;//o是支点
        double oy = end_y+(start_y-end_y)*3/4;
        double oax = start_x-ox;//向量OA
        double oay = start_y-oy;
        double obx = end_x - ox;//向量OB
        double oby = end_y - oy;
        double center_x = (start_x+end_x)/2;
        double center_y = (start_y+end_y)/2;
        double owx = center_x-ox;//向量OW
        double owy = center_y-oy;

        A(row, c_edge->getF1XId()) = -oay;
        A(row, c_edge->getF1YId()) = oax;
        A(row, c_edge->getF2XId()) = -oby;
        A(row, c_edge->getF2YId()) = obx;//记得这里在对应的b中要有所体现
        row++;
    }
    /**
     * form b
     */
    VectorXd b = VectorXd::Zero(nodeList.size()*2+edgeList.size()*3);
    row = 0;
    //构造节点处力的平衡 共2*节点数 行
    for(int i = 0;i<nodeList.size();i++){
        Node * c_node = nodeList.at(i);
        std::vector<Edge*> edges = c_node->getEdges();
        if(c_node->isSupport()||edges.size()>1){//只有一个节点连接大于一条边才进行节点处力的平衡计算
            b(row) = 0;
            row++;
            b(row) = 0;
            row++;
        }else if(c_node->isSupport()){
            b(row) = 0;
            row++;
            b(row) = 0;
            row++;
        }
    }
    //构造每条边受力平衡，共2*边数行
    for(int i = 0;i<edgeList.size();i++){
        b(row) = 0;
        row++;
        b(row) = -edgeList.at(i)->getGravity();
        row++;
    }
    //构造torque为零，共 1*边数 行
    for(int i = 0;i<edgeList.size();i++){
        Edge* c_edge = edgeList.at(i);
        double start_x = c_edge->getStartNode()->getX();
        double end_x = c_edge->getEndNode()->getX();
        double ox = end_x+(start_x-end_x)*3/4;//o是支点
        double center_x = (start_x+end_x)/2;
        double owx = center_x-ox;//向量OW
        b(row) = -owx*edgeList.at(i)->getGravity();
        row++;
    }

    VectorXd x = A.fullPivHouseholderQr().solve(b);
    cout<<"x:"<<x<<endl;
    cout<<"error||Ax-b||/||b||:"<<(A*x-b).norm()/b.norm();
    emit errorChanged(QString::fromStdString("error:||Ax-b||/||b||:").append(QString::fromStdString(ConvertToString((A*x-b).norm()/b.norm()))));
    //将结果set进edge中
    for(int i = 0;i<edgeList.size();i++){
        Edge * c_edge = edgeList.at(i);
        c_edge->f1x = x(c_edge->Id()*4);
        c_edge->f1y = x(c_edge->Id()*4+1);
        c_edge->f2x = x(c_edge->Id()*4+2);
        c_edge->f2y = x(c_edge->Id()*4+3);
    }

}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event){
    drag = false;
}
void PaintWidget::paintEvent(QPaintEvent *event)
{
    for (auto iter = nodeList.cbegin(); iter != nodeList.cend(); iter++){
        (*iter)->paint();
        if(this->enable_exter_force){
            (*iter)->paintExterForces();
        }
    }
    for (auto iter = edgeList.cbegin(); iter != edgeList.cend(); iter++){
        (*iter)->paint();
    }
    drawGround();
}

void PaintWidget::enableGravity(bool enabled) {
    enable_gravity = enabled;
    calForceOnEdge();
    update();
}

void PaintWidget::enableExternalForce(bool enabled) {
    enable_exter_force = enabled;
    calForceOnEdge();
    update();
}

void PaintWidget::changeStressType(bool isbending) {
    is_show_bending = isbending;
    calForceWithFriction();
    update();
}

void PaintWidget::enableResultantForce(bool enable_resultant){
    this->is_show_resultant_force = enable_resultant;
    calForceWithFriction();
    update();
}

void PaintWidget::drawGround() {
    int max_y = 0;
    for(int i = 0;i<nodeList.size();i++){
        if(nodeList.at(i)->getY()>max_y){
            max_y = nodeList.at(i)->getY();
        }
    }
    QPainter painter(this);
    QPixmap pix_ground;
    pix_ground.load("../images/ground.png");
    painter.drawPixmap(0, max_y+10,800,30,pix_ground);
}


