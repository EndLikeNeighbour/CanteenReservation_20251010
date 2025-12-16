#include "CustomerFunctionWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QRegularExpressionValidator>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QScrollArea>
#include "MainWindow.h"


CustomerFunctionWidget::CustomerFunctionWidget(Customer *cust, Restaurant *res, QWidget *parent): QWidget(parent), customer(cust), restaurant(res)
{
    setObjectName("CustomerFunctionWidget");
    setWindowTitle(QString("顾客端 - %1").arg(QString::fromStdString(customer->getName())));
    setFixedSize(450, 450);


    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(60, 40, 60, 40);


    // 字体
    QFont btnFont("微软雅黑", 11);

    // 按钮创建
    btnViewMenu = new QPushButton("查看菜单", this);
    btnMakeReservation = new QPushButton("预订餐桌", this);
    btnViewMyReservations = new QPushButton("查看我的预订", this);
    btnCancelReservation = new QPushButton("取消预订", this);
    btnLogout = new QPushButton("退出登录", this);

    // 按钮样式
    QList<QPushButton*> btns = {btnViewMenu, btnMakeReservation, btnViewMyReservations, btnCancelReservation, btnLogout};
    for (auto btn : btns)
    {
        btn->setFont(btnFont);
        btn->setFixedHeight(35);
        layout->addWidget(btn);
    }

    // 信号槽
    connect(btnViewMenu, &QPushButton::clicked, this, &CustomerFunctionWidget::onViewMenuClicked);
    connect(btnMakeReservation, &QPushButton::clicked, this, &CustomerFunctionWidget::onMakeReservationClicked);
    connect(btnViewMyReservations, &QPushButton::clicked, this, &CustomerFunctionWidget::onViewMyReservationsClicked);
    connect(btnCancelReservation, &QPushButton::clicked, this, &CustomerFunctionWidget::onCancelReservationClicked);
    connect(btnLogout, &QPushButton::clicked, this, &CustomerFunctionWidget::onLogoutClicked);
}

void CustomerFunctionWidget::onViewMenuClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("餐厅菜单");
    dialog.setFixedSize(600, 500); // 扩大窗口尺寸

    // 使用表格展示菜单
    QTableWidget *menuTable = new QTableWidget(&dialog);
    menuTable->setColumnCount(3);
    menuTable->setHorizontalHeaderLabels(QStringList() << "菜品名称" << "价格" << "状态");
    menuTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    menuTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    menuTable->setAlternatingRowColors(true);
    menuTable->verticalHeader()->setVisible(false);
    menuTable->setStyleSheet(R"(
        QTableWidget {
            border: 1px solid #f0f0f0;
            border-radius: 8px;
            padding: 5px;
        }
        QHeaderView::section {
            background-color: #f5f9ff;
            color: #333;
            font-weight: bold;
            padding: 8px;
            border: none;
        }
        QTableWidget::item {
            padding: 6px;
        }
        QTableWidget::item:alternate {
            background-color: #fafafa;
            color: #000;
        }
    )");

    // 获取菜品并按分类排序
    std::vector<FoodItem> items = restaurant->getMenu()->getFoodItems();
    std::string currentCategory = "";
    int row = 0;

    for (const auto& item : items)
    {
        // 分类标题行（每个分类只显示一次）
        if (item.category != currentCategory)
        {
            currentCategory = item.category;
            // 添加分类标题行（合并单元格）
            menuTable->insertRow(row);
            QTableWidgetItem *categoryItem = new QTableWidgetItem(QString::fromStdString(currentCategory));
            categoryItem->setBackground(QColor("#e6f0ff")); // 分类行背景色
            categoryItem->setFont(QFont("微软雅黑", 10, QFont::Bold)); // 加粗字体
            menuTable->setItem(row, 0, categoryItem);
            menuTable->setSpan(row, 0, 1, 3); // 合并3列
            row++;
        }

        // 添加菜品行
        menuTable->insertRow(row);
        // 菜品名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(item.foodName));
        nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        menuTable->setItem(row, 0, nameItem);
        // 价格
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString("¥%1").arg(item.foodPrice, 0, 'f', 2));
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        menuTable->setItem(row, 1, priceItem);
        // 状态
        QString status = item.IsAvailable ? "可售" : "售罄";
        QTableWidgetItem *statusItem = new QTableWidgetItem(status);
        statusItem->setTextAlignment(Qt::AlignCenter);
        menuTable->setItem(row, 2, statusItem);

        row++;
    }

    // 添加滚动区域（菜多时可滚动）
    QScrollArea *scrollArea = new QScrollArea(&dialog);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->addWidget(menuTable);
    scrollArea->setWidget(scrollContent);

    // 窗口布局
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->addWidget(scrollArea);
    dialog.exec();
}

void CustomerFunctionWidget::onMakeReservationClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("预订餐桌");
    dialog.setFixedSize(400, 400);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 20, 30, 20);

    // 控件
    QFont font("微软雅黑", 10);
    QLabel *labDateTime = new QLabel("预订时间（YYYY-MM-DD HH:MM）：", &dialog);
    labDateTime->setFont(font);
    QLineEdit *editDateTime = new QLineEdit(&dialog);
    editDateTime->setFont(font);
    editDateTime->setPlaceholderText("例如：2025-12-01 18:30");

    QLabel *labPartySize = new QLabel("用餐人数：", &dialog);
    labPartySize->setFont(font);
    QLineEdit *editPartySize = new QLineEdit(&dialog);
    editPartySize->setFont(font);
    editPartySize->setPlaceholderText("请输入正整数");
    editPartySize->setValidator(new QIntValidator(1, 100, &dialog));

    QLabel *labRequest = new QLabel("特殊需求：", &dialog);
    labRequest->setFont(font);
    QLineEdit *editRequest = new QLineEdit(&dialog);
    editRequest->setFont(font);
    editRequest->setPlaceholderText("如：靠窗、不要辣");

    QLabel *labLocation = new QLabel("期望位置（可选）：", &dialog);
    labLocation->setFont(font);
    QLineEdit *editLocation = new QLineEdit(&dialog);
    editRequest->setFont(font);
    editLocation->setPlaceholderText("如：大厅、包间");

    QPushButton *btnConfirm = new QPushButton("确认预订", &dialog);
    btnConfirm->setFont(font);
    btnConfirm->setFixedHeight(35);

    // 布局添加
    layout->addWidget(labDateTime);
    layout->addWidget(editDateTime);
    layout->addWidget(labPartySize);
    layout->addWidget(editPartySize);
    layout->addWidget(labRequest);
    layout->addWidget(editRequest);
    layout->addWidget(labLocation);
    layout->addWidget(editLocation);
    layout->addWidget(btnConfirm);

    // 确认按钮逻辑
    connect(btnConfirm, &QPushButton::clicked, [&]()
            {
                QString dateTime = editDateTime->text().trimmed();
                QString partySizeStr = editPartySize->text().trimmed();
                QString request = editRequest->text().trimmed();
                QString location = editLocation->text().trimmed();

                if (dateTime.isEmpty() || partySizeStr.isEmpty())
                {
                    QMessageBox::warning(&dialog, "警告", "预订时间和用餐人数不能为空！");
                    return;
                }

                int partySize = partySizeStr.toInt();
                std::string resId = customer->makeReservation(restaurant,
                                                              dateTime.toStdString(),
                                                              partySize,
                                                              request.toStdString(),
                                                              location.toStdString());

                if (!resId.empty())
                {
                    QMessageBox::information(&dialog, "成功", QString("预订成功！预订ID：%1").arg(QString::fromStdString(resId)));
                    dialog.close();
                }
                else
                {
                    QMessageBox::critical(&dialog, "失败", "预订失败！没有可用餐桌或输入信息有误。");
                }
            });
    dialog.exec();
}

void CustomerFunctionWidget::onViewMyReservationsClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("我的预订记录");
    dialog.setFixedSize(450, 400);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setFont(QFont("微软雅黑", 10));

    std::vector<Reservation*> reservations = customer->getReservations();
    if (reservations.empty())
    {
        textEdit->setText("您暂无预订记录");
    }
    else
    {
        std::string resText = QString("===== %1 的预订记录 =====\n\n").arg(QString::fromStdString(customer->getName())).toStdString();
        for (const auto& res : reservations)
        {
            resText += "预订ID：" + res->getReservationId() + "\n"
                                                              "时间：" + res->getDateTime() + "\n"
                                              "人数：" + std::to_string(res->getPartySize()) + "\n"
                                                               "状态：" + res->getStatus() + "\n"
                                            "需求：" + res->getCustomerRequest() + "\n\n";
        }
        textEdit->setText(QString::fromStdString(resText));
    }

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(textEdit);
    dialog.exec();
}

void CustomerFunctionWidget::onCancelReservationClicked()
{
    QString resId = QInputDialog::getText(this, "取消预订", "请输入要取消的预订ID：");
    if (resId.isEmpty())
    {
        QMessageBox::warning(this, "警告", "预订ID不能为空！");
        return;
    }

    bool success = customer->cancelReservation(resId.toStdString());
    if (success)
    {
        QMessageBox::information(this, "成功", "预订取消成功！");
    }
    else
    {
        QMessageBox::critical(this, "失败", "取消失败！未找到该预订ID。");
    }
}

void CustomerFunctionWidget::onLogoutClicked()
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
