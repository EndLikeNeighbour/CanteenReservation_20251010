#include "ManagerFunctionWidget.h"
#include "StaffFunctionWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QApplication>
#include "MainWindow.h"

ManagerFunctionWidget::ManagerFunctionWidget(Manager *mgr, Restaurant *res, QWidget *parent)
    : QWidget(parent), manager(mgr), restaurant(res)
{
    setWindowTitle("经理端");
    setFixedSize(400, 550);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(50, 30, 50, 30);

    // 字体
    QFont btnFont("微软雅黑", 11);

    // 按钮创建
    btnStaffFunction = new QPushButton("员工端所有功能", this);
    btnAddTable = new QPushButton("添加新餐桌", this);
    btnRemoveTable = new QPushButton("移除餐桌", this);
    btnAddFood = new QPushButton("添加菜品到菜单", this);
    btnModifyFood = new QPushButton("修改菜品信息", this);
    btnGenerateReport = new QPushButton("生成预订报表", this);
    btnViewStats = new QPushButton("查看业务统计", this);
    btnLogout = new QPushButton("退出登录", this);

    // 按钮样式
    QList<QPushButton*> btns = {btnStaffFunction, btnAddTable, btnRemoveTable, btnAddFood, btnModifyFood, btnGenerateReport, btnViewStats, btnLogout};
    for (auto btn : btns)
    {
        btn->setFont(btnFont);
        btn->setFixedHeight(35);
        layout->addWidget(btn);
    }

    // 信号槽
    connect(btnStaffFunction, &QPushButton::clicked, this, &ManagerFunctionWidget::onStaffFunctionClicked);
    connect(btnAddTable, &QPushButton::clicked, this, &ManagerFunctionWidget::onAddTableClicked);
    connect(btnRemoveTable, &QPushButton::clicked, this, &ManagerFunctionWidget::onRemoveTableClicked);
    connect(btnAddFood, &QPushButton::clicked, this, &ManagerFunctionWidget::onAddFoodClicked);
    connect(btnModifyFood, &QPushButton::clicked, this, &ManagerFunctionWidget::onModifyFoodClicked);
    connect(btnGenerateReport, &QPushButton::clicked, this, &ManagerFunctionWidget::onGenerateReportClicked);
    connect(btnViewStats, &QPushButton::clicked, this, &ManagerFunctionWidget::onViewStatsClicked);
    connect(btnLogout, &QPushButton::clicked, this, &ManagerFunctionWidget::onLogoutClicked);
}

void ManagerFunctionWidget::onStaffFunctionClicked()
{
    // 隐藏当前经理界面，显示员工功能界面（经理模式）
    hide();
    StaffFunctionWidget *staffWidget = new StaffFunctionWidget(manager, restaurant, nullptr, true);
    staffWidget->show();
}

void ManagerFunctionWidget::onAddTableClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加新餐桌");
    dialog.setFixedSize(380, 300);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 20, 30, 20);

    QFont font("微软雅黑", 10);

    // 餐桌ID
    QLabel *labTableId = new QLabel("新餐桌ID：", &dialog);
    labTableId->setFont(font);
    QLineEdit *editTableId = new QLineEdit(&dialog);
    editTableId->setFont(font);
    editTableId->setValidator(new QIntValidator(1, 999, &dialog));

    // 容量
    QLabel *labCapacity = new QLabel("餐桌容量（人数）：", &dialog);
    labCapacity->setFont(font);
    QLineEdit *editCapacity = new QLineEdit(&dialog);
    editCapacity->setFont(font);
    editCapacity->setValidator(new QIntValidator(1, 20, &dialog));

    // 位置
    QLabel *labLocation = new QLabel("餐桌位置：", &dialog);
    labLocation->setFont(font);
    QLineEdit *editLocation = new QLineEdit(&dialog);
    editLocation->setFont(font);
    editLocation->setPlaceholderText("如：包间B、大厅2");

    // 确认按钮
    QPushButton *btnConfirm = new QPushButton("确认添加", &dialog);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(35);

    // 布局添加
    layout->addWidget(labTableId);
    layout->addWidget(editTableId);
    layout->addWidget(labCapacity);
    layout->addWidget(editCapacity);
    layout->addWidget(labLocation);
    layout->addWidget(editLocation);
    layout->addWidget(btnConfirm);

    // 确认逻辑
    connect(btnConfirm, &QPushButton::clicked, [&]()
    {
        QString tableIdStr = editTableId->text().trimmed();
        QString capacityStr = editCapacity->text().trimmed();
        QString location = editLocation->text().trimmed();

        if (tableIdStr.isEmpty() || capacityStr.isEmpty() || location.isEmpty()) {
            QMessageBox::warning(&dialog, "警告", "所有字段不能为空！");
            return;
        }

        int tableId = tableIdStr.toInt();
        int capacity = capacityStr.toInt();

        manager->addNewTable(tableId, capacity, location.toStdString());
        QMessageBox::information(&dialog, "成功", "该餐桌添加成功！");
        dialog.close();
    });

    dialog.exec();
}

void ManagerFunctionWidget::onRemoveTableClicked()
{
    bool ok;
    int tableId = QInputDialog::getInt(this, "移除餐桌", "请输入要移除的餐桌ID：", 1, 1, 999, 1, &ok);
    if (!ok) return;

    bool success = manager->removeTable(tableId);
    if (success)
    {
        QMessageBox::information(this, "成功", QString("餐桌%1已移除").arg(tableId));
    }
    else
    {
        QMessageBox::critical(this, "失败", "移除失败！未找到该餐桌ID。");
    }
}

void ManagerFunctionWidget::onAddFoodClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加菜品到菜单");
    dialog.setFixedSize(380, 400);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 20, 30, 20);

    QFont font("微软雅黑", 10);

    // 菜品名称
    QLabel *labName = new QLabel("菜品名称：", &dialog);
    labName->setFont(font);
    QLineEdit *editName = new QLineEdit(&dialog);
    editName->setFont(font);

    // 菜品价格
    QLabel *labPrice = new QLabel("菜品价格（元）：", &dialog);
    labPrice->setFont(font);
    QLineEdit *editPrice = new QLineEdit(&dialog);
    editPrice->setFont(font);
    editPrice->setValidator(new QDoubleValidator(0.01, 999.99, 2, &dialog));

    // 菜品分类
    QLabel *labCategory = new QLabel("菜品分类：", &dialog);
    labCategory->setFont(font);
    QLineEdit *editCategory = new QLineEdit(&dialog);
    editCategory->setFont(font);
    editCategory->setPlaceholderText("如：热菜、甜品、饮品");

    // 是否可售
    QLabel *labAvailable = new QLabel("是否可售（1=是，0=否）：", &dialog);
    labAvailable->setFont(font);
    QLineEdit *editAvailable = new QLineEdit(&dialog);
    editAvailable->setFont(font);
    editAvailable->setValidator(new QIntValidator(0, 1, &dialog));

    // 确认按钮
    QPushButton *btnConfirm = new QPushButton("确认添加", &dialog);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(35);

    // 布局添加
    layout->addWidget(labName);
    layout->addWidget(editName);
    layout->addWidget(labPrice);
    layout->addWidget(editPrice);
    layout->addWidget(labCategory);
    layout->addWidget(editCategory);
    layout->addWidget(labAvailable);
    layout->addWidget(editAvailable);
    layout->addWidget(btnConfirm);

    // 确认逻辑
    connect(btnConfirm, &QPushButton::clicked, [&]()
    {
        QString name = editName->text().trimmed();
        QString priceStr = editPrice->text().trimmed();
        QString category = editCategory->text().trimmed();
        QString availableStr = editAvailable->text().trimmed();

        if (name.isEmpty() || priceStr.isEmpty() || category.isEmpty() || availableStr.isEmpty())
        {
            QMessageBox::warning(&dialog, "警告", "所有字段不能为空！");
            return;
        }

        double price = priceStr.toDouble();
        bool available = (availableStr.toInt() == 1);

        FoodItem item = {name.toStdString(), price, category.toStdString(), available};
        manager->updateMenu(item, true);
        QMessageBox::information(&dialog, "成功", "菜品添加成功！");
        dialog.close();
    });

    dialog.exec();
}

void ManagerFunctionWidget::onModifyFoodClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("修改菜品信息");
    dialog.setFixedSize(380, 280);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 20, 30, 20);

    QFont font("微软雅黑", 10);

    // 菜品名称
    QLabel *labName = new QLabel("要修改的菜品名称：", &dialog);
    labName->setFont(font);
    QLineEdit *editName = new QLineEdit(&dialog);
    editName->setFont(font);

    // 新价格
    QLabel *labNewPrice = new QLabel("新价格（元）：", &dialog);
    labNewPrice->setFont(font);
    QLineEdit *editNewPrice = new QLineEdit(&dialog);
    editNewPrice->setFont(font);
    editNewPrice->setValidator(new QDoubleValidator(0.01, 999.99, 2, &dialog));

    // 是否可售
    QLabel *labAvailable = new QLabel("是否可售（1=是，0=否）：", &dialog);
    labAvailable->setFont(font);
    QLineEdit *editAvailable = new QLineEdit(&dialog);
    editAvailable->setFont(font);
    editAvailable->setValidator(new QIntValidator(0, 1, &dialog));

    // 确认按钮
    QPushButton *btnConfirm = new QPushButton("确认修改", &dialog);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(35);

    // 布局添加
    layout->addWidget(labName);
    layout->addWidget(editName);
    layout->addWidget(labNewPrice);
    layout->addWidget(editNewPrice);
    layout->addWidget(labAvailable);
    layout->addWidget(editAvailable);
    layout->addWidget(btnConfirm);

    // 确认逻辑
    connect(btnConfirm, &QPushButton::clicked, [&]()
    {
        QString name = editName->text().trimmed();
        QString newPriceStr = editNewPrice->text().trimmed();
        QString availableStr = editAvailable->text().trimmed();

        if (name.isEmpty() || newPriceStr.isEmpty() || availableStr.isEmpty())
        {
            QMessageBox::warning(&dialog, "警告", "所有字段不能为空！");
            return;
        }

        double newPrice = newPriceStr.toDouble();
        bool newAvailable = (availableStr.toInt() == 1);

        bool success = manager->modifyMenuItem(name.toStdString(), newPrice, newAvailable);
        if (success)
        {
            QMessageBox::information(&dialog, "成功", "菜品修改成功！");
            dialog.close();
        }
        else
        {
            QMessageBox::critical(&dialog, "失败", "修改失败！未找到该菜品。");
        }
    });

    dialog.exec();
}

void ManagerFunctionWidget::onGenerateReportClicked()
{
    QString date = QInputDialog::getText(this, "生成预订报表", "请输入要统计的日期（YYYY-MM-DD）：");
    if (date.isEmpty())
    {
        QMessageBox::warning(this, "警告", "日期不能为空！");
        return;
    }

    // 验证日期格式
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        QMessageBox::warning(this, "警告", "日期格式错误！请输入YYYY-MM-DD格式。");
        return;
    }

    manager->generateReservationReport(date.toStdString());
    QString reportName = QString("ReservationReport_%1.txt").arg(date);
    QMessageBox::information(this, "成功", QString("报表生成成功！报表名称：%1").arg(reportName));
}

void ManagerFunctionWidget::onViewStatsClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("业务统计");
    dialog.setFixedSize(400, 250);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setFont(QFont("微软雅黑", 10));

    // 调用经理的统计方法
    std::vector<Table*> tables = restaurant->getTables();
    std::vector<FoodItem> foods = restaurant->getMenu()->getFoodItems();

    int totalTables = tables.size();
    int occupiedTables = 0;
    for (const auto& table : tables)
    {
        if (!table->isTableAvailable()) occupiedTables++;
    }
    double tableUsageRate = totalTables > 0 ? (occupiedTables * 100.0 / totalTables) : 0;

    double avgPrice = 0.0;
    for (const auto& food : foods)
    {
        avgPrice += food.foodPrice;
    }
    avgPrice = foods.empty() ? 0 : avgPrice / foods.size();

    std::string statsText = "===== 业务统计 =====\n\n";
    statsText += "1. 餐桌使用率：" + QString::number(tableUsageRate, 'f', 1).toStdString() + "%\n"
                                                                                             "   占用餐桌：" + std::to_string(occupiedTables) + "/" + std::to_string(totalTables) + "\n\n"
                                                                                        "2. 菜品统计：\n"
                                                                                        "   总菜品数：" + std::to_string(foods.size()) + "\n"
                                                  "   菜品均价：￥" + QString::number(avgPrice, 'f', 1).toStdString() + "\n";

    textEdit->setText(QString::fromStdString(statsText));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(textEdit);
    dialog.exec();
}

void ManagerFunctionWidget::onLogoutClicked()
{
    QMessageBox::information(this, "提示", "退出登录成功！");
    close();
    // 查找主窗口并显示
    for (QWidget *w : QApplication::topLevelWidgets())
    {
        // 假设主窗口类名为MainWindow
        if (MainWindow *mainWin = qobject_cast<MainWindow*>(w))
        {
            mainWin->show();  // 显示主窗口
            return;
        }
    }
}
