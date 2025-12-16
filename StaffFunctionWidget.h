#ifndef STAFFFUNCTIONWIDGET_H
#define STAFFFUNCTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Staff.h"
#include "Restaurant.h"

class StaffFunctionWidget : public QWidget
{
    Q_OBJECT

public:
    // isManagerMode：true=经理调用（退出返回经理界面），false=普通员工（退出返回主窗口）
    StaffFunctionWidget(Staff *staff, Restaurant *res, QWidget *parent = nullptr, bool isManagerMode = false);
    ~StaffFunctionWidget() = default;

private slots:
    void onViewTableStatusClicked();
    void onConfirmReservationClicked();
    void onRejectReservationClicked();
    void onMarkArrivalClicked();
    void onMarkDepartureClicked();
    void onHandleWalkInClicked();
    void onLogoutClicked();

private:
    Staff *staff;
    Restaurant *restaurant;
    bool isManagerMode; // 是否为经理调用模式
    QPushButton *btnViewTableStatus;
    QPushButton *btnConfirmReservation;
    QPushButton *btnRejectReservation;
    QPushButton *btnMarkArrival;
    QPushButton *btnMarkDeparture;
    QPushButton *btnHandleWalkIn;
    QPushButton *btnLogout;
};


#endif // STAFFFUNCTIONWIDGET_H
