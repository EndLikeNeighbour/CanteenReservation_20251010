#include "ManagerLoginDialog.h"
#include "ManagerFunctionWidget.h"
#include <QMessageBox>
#include <QFont>

ManagerLoginDialog::ManagerLoginDialog(Restaurant *res, QWidget *parent)
    : QDialog(parent), restaurant(res)
{
    setWindowTitle("经理登录");
    setFixedSize(350, 200);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 20, 30, 20);

    // 控件
    QFont font("微软雅黑", 10);
    QLabel *labManagerId = new QLabel("经理工号：", this);
    labManagerId->setFont(font);
    editManagerId = new QLineEdit(this);
    editManagerId->setFont(font);
    editManagerId->setPlaceholderText("请输入经理工号（以M开头）");
    btnConfirm = new QPushButton("确认登录", this);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(25);

    // 布局添加
    layout->addWidget(labManagerId);
    layout->addWidget(editManagerId);
    layout->addWidget(btnConfirm);

    // 信号槽
    connect(btnConfirm, &QPushButton::clicked, this, &ManagerLoginDialog::onConfirmClicked);
}

void ManagerLoginDialog::onConfirmClicked()
{
    QString managerId = editManagerId->text().trimmed();
    if (managerId.isEmpty() || !managerId.startsWith('M'))
    {
        QMessageBox::warning(this, "警告", "请输入有效的经理工号（以M开头）！");
        return;
    }

    // 创建经理对象
    StaffInfo info = {managerId.toStdString(), "", "Manager", ""};
    Manager *manager = new Manager(info, restaurant);
    if (manager->login(managerId.toStdString()) && manager->getPosition() == "Manager")
    {
        QMessageBox::information(this, "成功", "登录成功！欢迎您，经理！");
        ManagerFunctionWidget *widget = new ManagerFunctionWidget(manager, restaurant);
        widget->show();
        close();
    }
    else
    {
        QMessageBox::critical(this, "失败", "登录失败！无经理权限！");
        delete manager;
    }
}
