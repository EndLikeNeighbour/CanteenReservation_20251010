QT       += core gui widgets
TARGET = RestaurantReservationSystem
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        Customer.cpp \
        CustomerFunctionWidget.cpp \
        CustomerLoginDialog.cpp \
        CustomerManager.cpp \
        Manager.cpp \
        ManagerFunctionWidget.cpp \
        ManagerLoginDialog.cpp \
        Menu.cpp \
        Reservation.cpp \
        Restaurant.cpp \
        Staff.cpp \
        StaffFunctionWidget.cpp \
        StaffLoginDialog.cpp \
        Table.cpp \
        main.cpp \
        MainWindow.cpp \

HEADERS  += \
        Customer.h \
        CustomerFunctionWidget.h \
        CustomerLoginDialog.h \
        CustomerManager.h \
        MainWindow.h \
        Reservation.h \
        Restaurant.h \
        Staff.h \
        StaffLoginDialog.h \
        StaffFunctionWidget.h \
        ManagerLoginDialog.h \
        ManagerFunctionWidget.h \
        Manager.h \
        Menu.h \
        Table.h \
        user.h \

RESOURCES += \
    res.qrc
