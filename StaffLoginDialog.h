#ifndef STAFFLOGINDIALOG_H
#define STAFFLOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Restaurant.h"

class StaffLoginDialog : public QDialog
{
    Q_OBJECT

public:
    StaffLoginDialog(Restaurant *res, QWidget *parent = nullptr);
    ~StaffLoginDialog() = default;

private slots:
    void onConfirmClicked();

private:
    Restaurant *restaurant;
    QLineEdit *editStaffId;
    QPushButton *btnConfirm;
};

#endif // STAFFLOGINDIALOG_H
