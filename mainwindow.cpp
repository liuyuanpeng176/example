#include "mainwindow.h"
#include <QString>

#define ITEM_WIDTH 150
#define ITEM_HEIGHT 150
#define FACE_WIDTH 100
#define FACE_HEIGHT 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(ITEM_WIDTH*5,ITEM_HEIGHT);
    initUserList(10);
    initView();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initView()
{
    userView = new QWidget(this);
    userView->resize(ITEM_WIDTH*5,ITEM_HEIGHT);

    setCurrentUser(0);
}

void MainWindow::initUserList(int count)
{
    for(int i=0;i<count;i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setText(QString::number(i*1000));
        button->hide();
        userlist.append(button);
    }
}

void MainWindow::setCurrentUser(int user)
{
    if(userlist.count() == 0)
        return ;

    if(user < 0 || user > userlist.count())
        user = 0;

    for(int i=0;i<userlist.count();i++)
        userlist.at(i)->hide();

    userlist.at(user) -> setGeometry(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
    userlist.at(user)->show();

    for(int i = user + 1; i < userlist.count(); ++i)
    {
        if(i - user<3){
            userlist.at(i)->setGeometry(ITEM_WIDTH*(2+i-user)+ITEM_WIDTH-FACE_WIDTH,
                                        ITEM_HEIGHT-FACE_WIDTH,
                                        FACE_WIDTH,
                                        FACE_HEIGHT);
            userlist.at(i)->show();
        }
    }


}
