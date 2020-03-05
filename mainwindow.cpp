#include "mainwindow.h"
#include <QString>

#define ITEM_WIDTH 150
#define ITEM_HEIGHT 150
#define FACE_WIDTH 100
#define FACE_HEIGHT 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initUserList(10);
    initView();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initView()
{
    userView = new QWidget(this);
    userView->resize(ITEM_WIDTH*5,);

    for(int i=0;i<5;i++)
    {
        QWidget *widget = new QWidget(this);
        widget->setGeometry(ITEM_WIDTH*i,0,FACE_WIDTH,FACE_HEIGHT);
    }
}

void MainWindow::initUserList(int count)
{
    for(int i=0;i<count;i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setText(QString::number(i*100));
        userList.append(button);
    }
}

void MainWindow::alignedView()
{


}
