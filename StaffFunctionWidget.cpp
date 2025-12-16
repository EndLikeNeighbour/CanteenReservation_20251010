#include "StaffFunctionWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFont>
#include <QIntValidator>
#include <QApplication>
#include "MainWindow.h"
#include "ManagerFunctionWidget.h"  // 添加这行，放在其他#include下方

StaffFunctionWidget::StaffFunctionWidget(Staff *s, Restaurant *res, QWidget *parent, bool isManagerMode)
    : QWidget(parent), staff(s), restaurant(res), isManagerMode(isManagerMode)
{
    QString title = isManagerMode ? "员工功能（经理模式）" : "员工端";
    setWindowTitle(title);
    setFixedSize(400, 500);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(50, 30, 50, 30);

    // 字体
    QFont btnFont("微软雅黑", 11);

    // 按钮创建
    btnViewTableStatus = new QPushButton("查看所有餐桌状态", this);
    btnConfirmReservation = new QPushButton("确认预订", this);
    btnRejectReservation = new QPushButton("拒绝预订", this);
    btnMarkArrival = new QPushButton("标记顾客到店", this);
    btnMarkDeparture = new QPushButton("标记顾客离开", this);
    btnHandleWalkIn = new QPushButton("处理临时到店顾客", this);
    btnLogout = new QPushButton(isManagerMode ? "返回经理界面" : "退出登录", this);

    // 按钮样式
    QList<QPushButton*> btns = {btnViewTableStatus, btnConfirmReservation, btnRejectReservation, btnMarkArrival, btnMarkDeparture, btnHandleWalkIn, btnLogout};
    for (auto btn : btns)
    {
        btn->setFont(btnFont);
        btn->setFixedHeight(35);
        layout->addWidget(btn);
    }

    // 信号槽
    connect(btnViewTableStatus, &QPushButton::clicked, this, &StaffFunctionWidget::onViewTableStatusClicked);
    connect(btnConfirmReservation, &QPushButton::clicked, this, &StaffFunctionWidget::onConfirmReservationClicked);
    connect(btnRejectReservation, &QPushButton::clicked, this, &StaffFunctionWidget::onRejectReservationClicked);
    connect(btnMarkArrival, &QPushButton::clicked, this, &StaffFunctionWidget::onMarkArrivalClicked);
    connect(btnMarkDeparture, &QPushButton::clicked, this, &StaffFunctionWidget::onMarkDepartureClicked);
    connect(btnHandleWalkIn, &QPushButton::clicked, this, &StaffFunctionWidget::onHandleWalkInClicked);
    connect(btnLogout, &QPushButton::clicked, this, &StaffFunctionWidget::onLogoutClicked);
}

void StaffFunctionWidget::onViewTableStatusClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("所有餐桌状态");
    dialog.setFixedSize(450, 400);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setFont(QFont("微软雅黑", 10));

    // 构建餐桌状态文本
    std::vector<Table*> tables = restaurant->getTables();
    std::string statusText = "===== " + restaurant->getName() + " 餐桌状态 =====\n\n";
    for (const auto& table : tables)
    {
        statusText += "餐桌ID：" + std::to_string(table->getTableId()) + "\n"
                                                                         "容量：" + std::to_string(table->getCapacity()) + "人\n"
                                                               "位置：" + table->getLocation() + "\n"
                                               "状态：" + (table->isTableAvailable() ? "【空闲】" : "【占用/已预订】") + "\n\n";
    }

    textEdit->setText(QString::fromStdString(statusText));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(textEdit);
    dialog.exec();
}

void StaffFunctionWidget::onConfirmReservationClicked()
{

    QString resId = QInputDialog::getText(this, "确认预订", "请输入要确认的预订ID：");
    if (resId.isEmpty())
    {
        QMessageBox::warning(this, "警告", "预订ID不能为空！");
        return;
    }

    bool success = staff->confirmReservation(resId.toStdString());
    if (success)
    {
        QMessageBox::information(this, "成功", "预订确认成功！");
    }
    else
    {
        QMessageBox::critical(this, "失败", "确认失败！未找到该预订ID。");
    }
}

void StaffFunctionWidget::onRejectReservationClicked()
{
    QString resId = QInputDialog::getText(this, "拒绝预订", "请输入要拒绝的预订ID：");
    if (resId.isEmpty())
    {
        QMessageBox::warning(this, "警告", "预订ID不能为空！");
        return;
    }

    bool success = staff->rejectReservation(resId.toStdString());
    if (success)
    {
        QMessageBox::information(this, "成功", "预订拒绝成功！");
    }
    else
    {
        QMessageBox::critical(this, "失败", "拒绝失败！未找到该预订ID。");
    }
}

void StaffFunctionWidget::onMarkArrivalClicked()
{
    bool ok;
    int tableId = QInputDialog::getInt(this, "标记到店", "请输入餐桌ID：", 1, 1, 999, 1, &ok);
    if (!ok) return;

    bool success = staff->markCustomerArrival(tableId);
    if (success)
    {
        QMessageBox::information(this, "成功", QString("顾客已到店，餐桌%1标记为占用").arg(tableId));
    }
    else
    {
        QMessageBox::warning(this, "失败", "该餐桌当前空闲，无需标记到店或餐桌ID不存在！");
    }
}

void StaffFunctionWidget::onMarkDepartureClicked()
{
    bool ok;
    int tableId = QInputDialog::getInt(this, "标记离开", "请输入餐桌ID：", 1, 1, 999, 1, &ok);
    if (!ok) return;

    bool success = staff->markCustomerDeparture(tableId);
    if (success)
    {
        QMessageBox::information(this, "成功", QString("顾客已离开，餐桌%1恢复可用").arg(tableId));
    }
    else
    {
        QMessageBox::warning(this, "失败", "该餐桌已空闲或餐桌ID不存在！");
    }
}

void StaffFunctionWidget::onHandleWalkInClicked()
{
    bool ok;
    int partySize = QInputDialog::getInt(this, "临时顾客", "请输入顾客人数：", 1, 1, 100, 1, &ok);
    if (!ok) return;

    Table *table = staff->handleWalkInCustomer(partySize);
    if (table)
    {
        QMessageBox::information(this, "成功", QString("已安排餐桌ID：%1").arg(table->getTableId()));
    }
    else
    {
        QMessageBox::critical(this, "失败", "无可用餐桌，无法安排临时顾客！");
    }
}

void StaffFunctionWidget::onLogoutClicked()
{
    if (isManagerMode)
    {
        // 经理模式：遍历所有窗口找到经理界面并显示
        close();  // 关闭员工界面
        // 遍历所有顶层窗口，找到经理界面
        for (QWidget *w : QApplication::topLevelWidgets())
        {
            if (qobject_cast<ManagerFunctionWidget*>(w))
            {  // 找到经理界面
                w->show();  // 显示经理界面
                break;
            }
        }
    }
    else
    {
        // 普通员工模式逻辑不变...
        QMessageBox::information(this, "提示", "退出登录成功！");
        close();
        for (QWidget *w : QApplication::topLevelWidgets())
        {
            if (MainWindow *mainWin = qobject_cast<MainWindow*>(w))
            {
                mainWin->show();
                return;
            }
        }
    }
}
