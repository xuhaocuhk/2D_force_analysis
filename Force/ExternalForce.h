//
// Created by 徐豪 on 2017/4/13.
//

#ifndef DRAWPAD_EXTERNALFORCE_H
#define DRAWPAD_EXTERNALFORCE_H
/**
 * 对某个节点的已知方向与大小的外力
 */
#include"Eigen/Dense"
#include"Force.h"
#include"Entity/Node.h"

using namespace Eigen;

class ExternalForce {

public:
    ExternalForce(Force force,Node *node){//external node to node, and unitVector of the magnitude is unitVec.
        this->force = force;
        this->node = node;
        node->addExterForce(this);
    }
    Force getForce(){ return force; }
    Node* getNode() { return node;  }

private:
    Force force;
    Node *node;
};

#endif //DRAWPAD_EXTERNALFORCE_H
