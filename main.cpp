#include "MainWindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ========== 全局样式表：背景全白 + 文字颜色区分 ==========
    QString globalStyle = R"(
        QMainWindow, QWidget, QDialog {
            background-color: #FFFFFF !important;
        }

        QSpinBox, QSpinBox::edit {
        color: #333333 !important;
        background-color: #FFFFFF !important;
        border: 1px solid #cccccc;
        border-radius: 6px;
        padding: 6px;
        min-height: 30px;
        }
        QSpinBox:focus {
        border-color: #4a90e2;
        outline: none;
        }

        QSpinBox::up-button, QSpinBox::down-button {
        width: 0px !important;
        height: 0px !important;
        border: none !important;
        background: transparent !important;
        }

        QSpinBox::up-arrow {
        width: 0px !important;
        height: 0px !important;
        }

        QLineEdit {
            color: #333333 !important;
            background-color: #FFFFFF !important;
            border: 1px solid #cccccc;
            border-radius: 6px;
            padding: 6px;
        }
        QLineEdit:focus {
            border-color: #4a90e2;
            outline: none;
        }

        QTableWidget {
            color: #000000 !important;
            background-color: #FFFFFF !important;
            border-radius: 8px;
        }
        QTableWidget::item:selected {
            color: #000000 !important;
            background-color: #e6f0ff;
        }
        QHeaderView::section {
            color: #000000 !important;
            background-color: #d9e8ff;
            border: none;
            padding: 6px;
        }


        QLabel {
            color: #000000 !important;
            background-color: #FFFFFF !important;
            font-size: 13px;
        }


        QDateEdit, QTimeEdit, QComboBox, QTextEdit {
            color: #000000 !important;
            background-color: #FFFFFF !important;
            border: 1px solid #cccccc;
            border-radius: 6px;
            padding: 6px;
        }


        QPushButton {
            background-color: #4a90e2 !important;
            color: #FFFFFF !important;
            border: none;
            border-radius: 6px;
            padding: 6px 15px;
            text-align: center;
            min-height: 35px;
            min-width: 150px;
        }
        QPushButton:hover {
            background-color: #5b9dee !important;
        }
        QPushButton:pressed {
            background-color: #3a80d2 !important;
        }


        QPushButton::icon {
            margin: 0 !important;
            alignment: center !important;
        }

    )";

    // 应用全局样式（覆盖所有窗口/控件）
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyleSheet(globalStyle);

    // 启动主窗口
    MainWindow w;
    w.setWindowTitle("【天津宴】餐厅预订系统");
    w.show();

    return a.exec();
}
