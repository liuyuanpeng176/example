#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <QPair>
#include <QPropertyAnimation>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QList<QPair<QPushButton *, QPair<int ,int>>> userlist;
    QPropertyAnimation *animation;
    QWidget *userView;
    int currentUser;
    int leftCount;
    int rightCount;


    void initView();
    void initUserList(int count);
    void setCurrentUser(int count);
    void leftKeyPressed();
    void rightKeyPressed();
    void leftToRight();
    void leftToLeft();
    void rightToRight();
    void rightToLeft();
    void centerToleft();
    void centerToRight();
    void moveAnimation(QPushButton *button,QRect preRect,QRect nextRect);

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
