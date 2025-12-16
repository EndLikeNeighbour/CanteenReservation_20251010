#ifndef MANAGERFUNCTIONWIDGET_H
#define MANAGERFUNCTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Manager.h"
#include "Restaurant.h"

class ManagerFunctionWidget : public QWidget
{
    Q_OBJECT

public:
    ManagerFunctionWidget(Manager *manager, Restaurant *res, QWidget *parent = nullptr);
    ~ManagerFunctionWidget() = default;

private slots:
    void onStaffFunctionClicked();
    void onAddTableClicked();
    void onRemoveTableClicked();
    void onAddFoodClicked();
    void onModifyFoodClicked();
    void onGenerateReportClicked();
    void onViewStatsClicked();
    void onLogoutClicked();

private:
    Manager *manager;
    Restaurant *restaurant;
    QPushButton *btnStaffFunction;
    QPushButton *btnAddTable;
    QPushButton *btnRemoveTable;
    QPushButton *btnAddFood;
    QPushButton *btnModifyFood;
    QPushButton *btnGenerateReport;
    QPushButton *btnViewStats;
    QPushButton *btnLogout;
};

#endif // MANAGERFUNCTIONWIDGET_H
