#ifndef CUSTOMERLOGINDIALOG_H
#define CUSTOMERLOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Restaurant.h"
#include "Customer.h"

class CustomerLoginDialog : public QDialog
{
    Q_OBJECT

public:
    CustomerLoginDialog(Restaurant *res, QWidget *parent = nullptr);
    ~CustomerLoginDialog() = default;

private slots:
    void onConfirmClicked();

private:
    Restaurant *restaurant;
    QLineEdit *editPhone;
    QPushButton *btnConfirm;
};

#endif // CUSTOMERLOGINDIALOG_H
