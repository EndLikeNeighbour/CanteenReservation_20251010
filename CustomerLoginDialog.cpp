#include "CustomerLoginDialog.h"
#include "CustomerFunctionWidget.h"
#include <QMessageBox>
#include <QFont>
#include <QInputDialog>
#include "CustomerManager.h"

CustomerLoginDialog::CustomerLoginDialog(Restaurant *res, QWidget *parent)
    : QDialog(parent), restaurant(res)
{
    setWindowTitle("顾客登录");
    setFixedSize(350, 200);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 20, 30, 20);

    // 控件
    QFont font("微软雅黑", 10);
    QLabel *labPhone = new QLabel("手机号：", this);
    labPhone->setFont(font);
    editPhone = new QLineEdit(this);
    editPhone->setFont(font);
    editPhone->setPlaceholderText("请输入您的手机号");
    btnConfirm = new QPushButton("确认登录", this);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(25);

    // 布局添加
    layout->addWidget(labPhone);
    layout->addWidget(editPhone);
    layout->addWidget(btnConfirm);

    // 信号槽
    connect(btnConfirm, &QPushButton::clicked, this, &CustomerLoginDialog::onConfirmClicked);
}

void CustomerLoginDialog::onConfirmClicked()
{
    QString phone = editPhone->text().trimmed();
    if (phone.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请输入手机号！");
        return;
    }

    // 查找顾客
    Customer *customer = CustomerManager::getInstance()->findCustomerByPhone(phone.toStdString());
    if (customer)
    {
        // 老顾客
        QMessageBox::information(this, "成功", QString("欢迎回来，%1！").arg(QString::fromStdString(customer->getName())));
        CustomerFunctionWidget *widget = new CustomerFunctionWidget(customer, restaurant);
        widget->show();
        close();
    } else
    {
        // 新顾客
        QString name = QInputDialog::getText(this, "完善信息", "检测到您是第一次光临，请输入姓名：");
        if (name.isEmpty())
        {
            QMessageBox::warning(this, "警告", "姓名不能为空！");
            return;
        }

        // 创建新顾客
        CustomerInfo info = {name.toStdString(), phone.toStdString()};
        customer = new Customer(info);
        CustomerManager::getInstance()->addCustomer(customer);

        QMessageBox::information(this, "成功", QString("注册成功！欢迎您，%1！").arg(name));
        CustomerFunctionWidget *widget = new CustomerFunctionWidget(customer, restaurant);
        widget->show();
        close();
    }
}
