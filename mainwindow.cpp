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
    initUserList(10);
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

    setCurrentUser(9);
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

void MainWindow::leftKeyPressed()
{
    if(currentUser <= 0)
       return;

    rightToRight();
    centerToRight();
    leftToRight();
    currentUser-- ;
}

void MainWindow::rightKeyPressed()
{
    if(currentUser >= userlist.count() - 1)
        return ;

   leftToLeft();
   centerToleft();
   rightToLeft();
   currentUser++;
}

void MainWindow::centerToleft()
{
    if(currentUser >= userlist.count() - 1)
        return ;

    QPushButton *button = userlist.at(currentUser);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);

    moveAnimation(button,rec1,rec2);
}

void MainWindow::centerToRight()
{
    qDebug()<<"centerToRight currentuser = "<<currentUser;
    if(currentUser <= 0)
        return ;

    QPushButton *button = userlist.at(currentUser);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH*3+ITEM_WIDTH-FACE_WIDTH,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);

    moveAnimation(button,rec1,rec2);
}

void MainWindow::leftToLeft()
{
    int left = currentUser;

    if(left <= 0){
        return ;
    }

    QPushButton *button = userlist.at(currentUser-1);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(0,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);

    moveAnimation(button,rec1,rec2);

    if(left >= 2){
        QPushButton *button2 = userlist.at(currentUser-2);
        button2->hide();
    }

}

void MainWindow::leftToRight()
{
    int left = currentUser;

    if(left <= 0)
        return ;

    QPushButton *button = userlist.at(currentUser-1);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
    moveAnimation(button,rec1,rec2);

    if(left >= 2){
        QPushButton *button2 = userlist.at(currentUser - 2);
        rec1 = button2->geometry();
        rec2 = QRect(ITEM_WIDTH,ITEM_HEIGHT-FACE_WIDTH,FACE_WIDTH,FACE_WIDTH);

        moveAnimation(button2,rec1,rec2);
    }

    if(left >= 3){
        QPushButton *button3 = userlist.at(currentUser - 3);
        button3->setGeometry(0,ITEM_HEIGHT-FACE_WIDTH,FACE_WIDTH,FACE_WIDTH);
        button3->show();
    }
}

void MainWindow::rightToLeft()
{
    int right = userlist.count() - currentUser - 1;

    if(right <= 0)
        return ;

    QPushButton *button = userlist.at(currentUser + 1);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
    moveAnimation(button,rec1,rec2);

    if(right >= 2){
        QPushButton *button2 = userlist.at(currentUser + 2);
        rec1 = button2->geometry();
        rec2 = QRect(ITEM_WIDTH*3+ITEM_WIDTH-FACE_WIDTH,
                     ITEM_HEIGHT-FACE_WIDTH,
                     FACE_WIDTH,
                     FACE_WIDTH);
        moveAnimation(button2,rec1,rec2);
    }

    if(right >= 3){
        QPushButton *button3 = userlist.at(currentUser + 3);
        button3->setGeometry(ITEM_WIDTH*4+ITEM_WIDTH-FACE_WIDTH,ITEM_HEIGHT-FACE_WIDTH,FACE_WIDTH,FACE_WIDTH);
        button3->show();
    }
}

void MainWindow::rightToRight()
{
    int right = userlist.count() - currentUser - 1;
    if(right <= 0)
        return ;

    QPushButton *button = userlist.at(currentUser + 1);
    QRect rec1 = button->geometry();
    QRect rec2 = QRect(ITEM_WIDTH*4+ITEM_WIDTH-FACE_WIDTH,
                       ITEM_HEIGHT-FACE_WIDTH,
                       FACE_WIDTH,
                       FACE_HEIGHT);

    moveAnimation(button,rec1,rec2);

    if(right >= 2){
        QPushButton *button = userlist.at(currentUser + 2);
        button->hide();
    }
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
        userlist.at(i)->hide();

    userlist.at(user) -> setGeometry(ITEM_WIDTH*2,0,ITEM_WIDTH,ITEM_HEIGHT);
    userlist.at(user)->show();

    for(int i = user + 1; i < userlist.count() && i - user < 3; ++i)
    {
        userlist.at(i)->setGeometry(ITEM_WIDTH*(2+i-user)+ITEM_WIDTH-FACE_WIDTH,
                                    ITEM_HEIGHT-FACE_WIDTH,
                                    FACE_WIDTH,
                                    FACE_HEIGHT);
        userlist.at(i)->show();
    }

    for(int i = user - 1;i >= 0 && user - i < 3; i--)
    {
        userlist.at(i)->setGeometry(ITEM_WIDTH*(2+i-user),
                                    ITEM_HEIGHT-FACE_WIDTH,
                                    FACE_WIDTH,
                                    FACE_HEIGHT);
        userlist.at(i)->show();
    }
}

void  MainWindow::keyPressEvent(QKeyEvent *event)
{
   if(event->key() == Qt::Key_Left){
       qDebug()<<"left key pressed";
       leftKeyPressed();
   }
   else if(event->key() == Qt::Key_Right){
       qDebug()<<"right key pressed";
       rightKeyPressed();
   }
}
