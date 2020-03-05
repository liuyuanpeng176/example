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
    QList<QPushButton *> userList;
    QPropertyAnimation *animation;
    QWidget *userView;
    QList<QPushButton *> userList;

    void initView();
    void initUserList(int count);
    void alignedView();


};

#endif // MAINWINDOW_H
