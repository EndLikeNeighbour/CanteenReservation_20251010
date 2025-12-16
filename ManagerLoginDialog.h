#ifndef MANAGERLOGINDIALOG_H
#define MANAGERLOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Restaurant.h"

class ManagerLoginDialog : public QDialog
{
    Q_OBJECT

public:
    ManagerLoginDialog(Restaurant *res, QWidget *parent = nullptr);
    ~ManagerLoginDialog() = default;

private slots:
    void onConfirmClicked();

private:
    Restaurant *restaurant;
    QLineEdit *editManagerId;
    QPushButton *btnConfirm;
};

#endif // MANAGERLOGINDIALOG_H
