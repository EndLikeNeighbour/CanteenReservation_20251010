#include "StaffLoginDialog.h"
#include "StaffFunctionWidget.h"
#include <QMessageBox>
#include <QFont>

StaffLoginDialog::StaffLoginDialog(Restaurant *res, QWidget *parent)
    : QDialog(parent), restaurant(res)
{
    setWindowTitle("员工登录");
    setFixedSize(350, 200);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 20, 30, 20);

    // 控件
    QFont font("微软雅黑", 10);
    QLabel *labStaffId = new QLabel("员工工号：", this);
    labStaffId->setFont(font);
    editStaffId = new QLineEdit(this);
    editStaffId->setFont(font);
    editStaffId->setPlaceholderText("请输入员工工号");
    btnConfirm = new QPushButton("确认登录", this);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(35);

    // 布局添加
    layout->addWidget(labStaffId);
    layout->addWidget(editStaffId);
    layout->addWidget(btnConfirm);

    // 信号槽
    connect(btnConfirm, &QPushButton::clicked, this, &StaffLoginDialog::onConfirmClicked);
}

void StaffLoginDialog::onConfirmClicked()
{
    QString staffId = editStaffId->text().trimmed();
    if (staffId.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请输入员工工号！");
        return;
    }

    // 创建员工对象（简化验证：工号非空即通过）
    StaffInfo info = {staffId.toStdString(), "", "Staff", ""};
    Staff *staff = new Staff(info, restaurant);
    if (staff->login(staffId.toStdString()))
    {
        QMessageBox::information(this, "成功", "登录成功！欢迎您，员工！");
        StaffFunctionWidget *widget = new StaffFunctionWidget(staff, restaurant, nullptr, false);
        widget->show();
        close();
    }
    else
    {
        QMessageBox::critical(this, "失败", "登录失败！工号不存在！");
        delete staff;
    }
}
