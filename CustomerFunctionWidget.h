#ifndef CUSTOMERFUNCTIONWIDGET_H
#define CUSTOMERFUNCTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Customer.h"
#include "Restaurant.h"

class CustomerFunctionWidget : public QWidget
{
    Q_OBJECT

public:
    CustomerFunctionWidget(Customer *cust, Restaurant *res, QWidget *parent = nullptr);
    ~CustomerFunctionWidget() = default;

private slots:
    void onViewMenuClicked();
    void onMakeReservationClicked();
    void onViewMyReservationsClicked();
    void onCancelReservationClicked();
    void onLogoutClicked();

private:
    Customer *customer;
    Restaurant *restaurant;
    QPushButton *btnViewMenu;
    QPushButton *btnMakeReservation;
    QPushButton *btnViewMyReservations;
    QPushButton *btnCancelReservation;
    QPushButton *btnLogout;
};

#endif // CUSTOMERFUNCTIONWIDGET_H
