#include "MainWindow.h"
#include "CustomerLoginDialog.h"
#include "StaffLoginDialog.h"
#include "ManagerLoginDialog.h"
#include <QMessageBox>
#include <QFont>
#include "CustomerManager.h"
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    restaurant = new Restaurant("天津宴", "天津市南开区卫津路94号");

    // 窗口设置
    setWindowTitle("【天津宴】餐厅预订系统");
    setFixedSize(500, 400);

    // 中心部件和布局
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(80, 60, 80, 60);


    // 字体设置
    QFont btnFont("微软雅黑", 12);

    // 按钮创建
    btnCustomerLogin = new QPushButton("顾客登录", this);
    btnStaffLogin = new QPushButton("员工登录", this);
    btnManagerLogin = new QPushButton("经理登录", this);
    btnExitSystem = new QPushButton("退出系统", this);

    //添加图标
    btnCustomerLogin->setIcon(QIcon(":/icons/icon_customer.png"));
    btnStaffLogin->setIcon(QIcon(":/icons/icon_staff.png"));
    btnManagerLogin->setIcon(QIcon(":/icons/icon_manager.png"));
    btnExitSystem->setIcon(QIcon(":/icons/icon_exit.png"));

    // 按钮样式和布局
    QList<QPushButton*> btns = {btnCustomerLogin, btnStaffLogin, btnManagerLogin, btnExitSystem};
    for (auto btn : btns)
    {
        btn->setFont(btnFont);
        btn->setFixedHeight(35);
        btn->setIconSize(QSize(20,20));
        mainLayout->addWidget(btn);
    }


    // 信号槽连接
    connect(btnCustomerLogin, &QPushButton::clicked, this, &MainWindow::onCustomerLoginClicked);
    connect(btnStaffLogin, &QPushButton::clicked, this, &MainWindow::onStaffLoginClicked);
    connect(btnManagerLogin, &QPushButton::clicked, this, &MainWindow::onManagerLoginClicked);
    connect(btnExitSystem, &QPushButton::clicked, this, &MainWindow::onExitSystemClicked);
}



MainWindow::~MainWindow()
{
    delete restaurant;
    CustomerManager::getInstance()->cleanup();
}

void MainWindow::onCustomerLoginClicked()
{
    CustomerLoginDialog dialog(restaurant, this);
    dialog.exec();
}

void MainWindow::onStaffLoginClicked()
{
    StaffLoginDialog dialog(restaurant, this);
    dialog.exec();
}

void MainWindow::onManagerLoginClicked()
{
    ManagerLoginDialog dialog(restaurant, this);
    dialog.exec();
}

void MainWindow::onExitSystemClicked()
{
    QMessageBox::information(this, "提示", "感谢使用，再见！");
    close();
}
