#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PaintWidget.h"
#include <QtGui>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>

class QButtonGroup;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(){
        setWindowTitle(tr("Force Analysis for skeletal structure"));
        setFixedHeight(HEIGHT);
        setFixedWidth(WIDTH);
        QWidget *widget = new QWidget(this);
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        QVBoxLayout *vLayout = new QVBoxLayout();
        vLayout->setAlignment(Qt::AlignTop);
        pwidget = new PaintWidget();
        hLayout->addWidget(pwidget,1);
        hLayout->addLayout(vLayout);
        /**
         * 添加组件
         */
        error_label = new QLabel(widget);

        QCheckBox *check_gravity = new QCheckBox(widget);
        check_gravity->setChecked(false);
        check_gravity->setText(QStringLiteral("开启重力"));

        QCheckBox *check_extern_force = new QCheckBox(widget);
        check_extern_force->setChecked(false);
        check_extern_force->setText(QStringLiteral("开启外力"));

        QCheckBox *check_deformation = new QCheckBox(widget);
        check_deformation->setChecked(false);
        check_deformation->setText(QStringLiteral("显示合力"));

        QCheckBox *stress_type = new QCheckBox(widget);
        stress_type->setChecked(true);
        stress_type->setText(QStringLiteral("显示压力"));

        vLayout->addWidget(error_label);
        vLayout->addWidget(check_gravity);
        vLayout->addWidget(check_extern_force);
        vLayout->addWidget(check_deformation);
        vLayout->addWidget(stress_type);

        setCentralWidget(widget);

        QObject::connect(check_gravity, &QCheckBox::stateChanged,
                         pwidget, &PaintWidget::enableGravity);
        QObject::connect(check_extern_force, &QCheckBox::stateChanged,
                         pwidget, &PaintWidget::enableExternalForce);
        QObject::connect(pwidget, &PaintWidget::errorChanged,
                         this, &MainWindow::setErrorLabel);
        QObject::connect(stress_type, &QCheckBox::stateChanged,
                         pwidget, &PaintWidget::changeStressType);
        QObject::connect(check_deformation, &QCheckBox::stateChanged,
                             pwidget, &PaintWidget::enableResultantForce);
    }

public:
    static const int HEIGHT = 800;
    static const int WIDTH = 1200;

private:
    PaintWidget * pwidget;
    QLabel* error_label; //显示当前误差

public slots:
    void setErrorLabel(QString text){
        error_label->setText(text);
    };


};

#endif // MAINWINDOW_H
