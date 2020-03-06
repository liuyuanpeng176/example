#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <QPropertyAnimation>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QList<QPushButton *>userlist;
    QPropertyAnimation *animation;
    QWidget *userView;


    void initView();
    void initUserList(int count);
    void setCurrentUser(int count);


};

#endif // MAINWINDOW_H
