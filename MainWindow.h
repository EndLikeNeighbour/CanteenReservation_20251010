#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "Restaurant.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCustomerLoginClicked();
    void onStaffLoginClicked();
    void onManagerLoginClicked();
    void onExitSystemClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QPushButton *btnCustomerLogin;
    QPushButton *btnStaffLogin;
    QPushButton *btnManagerLogin;
    QPushButton *btnExitSystem;
    Restaurant *restaurant; // 全局餐厅实例
};

#endif // MAINWINDOW_H
