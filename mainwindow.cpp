#include "mainwindow.h"
#include <QString>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QPropertyAnimation>

#define ITEM_WIDTH 150
#define ITEM_HEIGHT 150
#define FACE_WIDTH 100
#define FACE_HEIGHT 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    currentUser(0)
{
    resize(ITEM_WIDTH*5,ITEM_HEIGHT);
    initUserList(6);
    initView();
    installEventFilter(this);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initView()
{
    userView = new QWidget(this);
    userView->resize(ITEM_WIDTH*5,ITEM_HEIGHT);
    userView->setFocusPolicy(Qt::NoFocus);
    userView->installEventFilter(this);

    setCurrentUser(0);
}

void MainWindow::initUserList(int count)
{
    for(int i=0;i<count;i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setText(QString::number(i*1000));
        button->hide();

        int prev = 0,next = 0;
        if(userlist.count() >= 1)
        {
            //第一个用户的上一个用户指向即将添加的下一个用户。
            userlist.last().second.second = userlist.count();
            //原来最后一个用户的下一个用户指向即将添加的下一个用户。
            userlist.first().second.first = userlist.count();
            //新添加的用户放在最后，所以上一个用户是原来的最后一个用户。
            prev = userlist.count() - 1;
        }

        QPair<int,int> index(prev,next);
        QPair<QPushButton*,QPair<int,int>> pair(button,index);
        userlist.append(pair);
    }
    for(int i = 0;i<userlist.count();i++){
        qDebug()<<"prev = " << userlist.at(i).second.first << "next = "<<userlist.at(i).second.second;
    }

    int usersCount = userlist.count();
    switch (usersCount) {
    case 0:
        return;
        break;
    case 1:
        leftCount = rightCount = 0;
        break;
    case 2:
        leftCount = 0;
        rightCount = 1;
        break;
    case 3:
        leftCount = rightCount = 1;
        break;
    case 4:
        leftCount = 1;
        rightCount = 2;
        break;
    default:
         leftCount = rightCount = 2;
        break;
    }

}

void MainWindow::leftKeyPressed()
{
    if(currentUser < 0 || userlist.count() <= 1)
       return;

    rightToRight();
    centerToRight();
    leftToRight();
    currentUser = userlist.at(currentUser).second.first;
}

void MainWindow::rightKeyPressed()
{
    if(currentUser < 0 || userlist.count() <= 1)
        return ;
   leftToLeft();
   centerToleft();
   rightToLeft();
   currentUser = userlist.at(currentUser).second.second;

}

void MainWindow::centerToleft()
{
    QPushButton *button = userlist.at(currentUser).first;
    if(leftCount >= 1){
        QRect rec1 = button->geometry();
        QRect rec2 = QRect(ITEM_WIDTH,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);
        moveAnimation(button,rec1,rec2);
    }
    else
        button->hide();
}

void MainWindow::centerToRight()
{

    QPushButton *button = userlist.at(currentUser).first;
    if(rightCount >= 1){
        QRect rec1 = button->geometry();
        QRect rec2 = QRect(ITEM_WIDTH*3+ITEM_WIDTH-FACE_WIDTH,
                           ITEM_HEIGHT-FACE_WIDTH,
                           FACE_WIDTH,
                           FACE_HEIGHT);
        moveAnimation(button,rec1,rec2);
    }
    else
        button->hide();
}

void MainWindow::leftToLeft()
{
    if(leftCount <= 0)
        return;
    if(leftCount == 1){
        int index = userlist.at(currentUser).second.first;
        userlist.at(index).first->hide();
        return ;
    }

    int swap = currentUser;
    swap = userlist.at(currentUser).second.first;
    QPushButton *button = userlist.at(swap).first;
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(0,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);
    moveAnimation(button,rec1,rec2);
    swap = userlist.at(swap).second.first;
    userlist.at(swap).first->hide();
}

void MainWindow::leftToRight()
{

    int swap = currentUser;
    for(int i = 0;i<=leftCount;i++){
         swap = userlist.at(swap).second.first;
         QPushButton *button = userlist.at(swap).first;
         button->show();
         QRect rec1 = button->geometry();
         QRect rec2;
         if(currentUser == userlist.at(swap).second.second){
             rec2 = QRect(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
         }else{
             int index = userlist.at(swap).second.second;
             rec2 = userlist.at(index).first->geometry();
         }
         moveAnimation(button,rec1,rec2);
    }

}

void MainWindow::rightToLeft()
{

    int swap = currentUser;
    for(int i = 0;i<=rightCount;i++){
         qDebug()<<"这是第"<<i<<"次";
         swap = userlist.at(swap).second.second;
         QPushButton *button = userlist.at(swap).first;
         button->show();
         QRect rec1 = button->geometry();
         QRect rec2;
         if(currentUser == userlist.at(swap).second.first){
             rec2 = QRect(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
         }else{
             int index = userlist.at(swap).second.first;
             rec2 = userlist.at(index).first->geometry();
         }
         moveAnimation(button,rec1,rec2);
    }
}

void MainWindow::rightToRight()
{

    if(rightCount <= 0)
        return;
    if(rightCount == 1){
        int index = userlist.at(currentUser).second.second;
        userlist.at(index).first->hide();
        return ;
    }

    int swap = currentUser;
    swap = userlist.at(currentUser).second.second;
    QPushButton *button = userlist.at(swap).first;
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH*4 + ITEM_WIDTH-FACE_WIDTH,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);
    moveAnimation(button,rec1,rec2);
    swap = userlist.at(swap).second.second;
    userlist.at(swap).first->hide();
}

void MainWindow::moveAnimation(QPushButton *button, QRect preRect, QRect nextRect)
{
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(button, "geometry");
    pScaleAnimation->setDuration(300);
    pScaleAnimation->setStartValue(preRect);
    pScaleAnimation->setEndValue(nextRect);
    pScaleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    pScaleAnimation->start();
}

void MainWindow::setCurrentUser(int user)
{
    if(userlist.count() == 0)
        return ;

    if(user < 0 || user >= userlist.count())
        user = 0;

    currentUser = user;

    for(int i=0;i<userlist.count();i++)
        userlist.at(i).first->hide();

    userlist.at(user).first -> setGeometry(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
    userlist.at(user).first ->show();


    qDebug()<<"leftcount  = "<<leftCount<<" rightcount = "<<rightCount;
    int swap = currentUser;
    for(int i = 0;i<leftCount;i++){
        swap = userlist.at(swap).second.first;

        userlist.at(swap).first->setGeometry(ITEM_WIDTH*(1-i),
                                             ITEM_HEIGHT-FACE_WIDTH,
                                             FACE_WIDTH,
                                             FACE_HEIGHT);
        userlist.at(swap).first->show();
        qDebug()<<"getmetry = "<<userlist.at(swap).first->geometry();
    }

    swap = currentUser;
    for(int i = 0;i<rightCount;i++){
        swap = userlist.at(swap).second.second;
        userlist.at(swap).first->setGeometry(ITEM_WIDTH*(3+i)+ITEM_WIDTH-FACE_WIDTH,
                                             ITEM_HEIGHT-FACE_WIDTH,
                                             FACE_WIDTH,
                                             FACE_HEIGHT);
        userlist.at(swap).first->show();
    }
}

void  MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"1111111111111 "<<currentUser;
   if(event->key() == Qt::Key_Left){
       qDebug()<<"left key pressed";
       leftKeyPressed();
   }
   else if(event->key() == Qt::Key_Right){
       qDebug()<<"right key pressed";
       rightKeyPressed();
   }
}
