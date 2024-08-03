QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    adminpage.cpp \
    createaccount.cpp \
    databasehandler.cpp \
    deleteuser.cpp \
    frontpage.cpp \
    main.cpp \
    login.cpp \
    profile.cpp \
    task.cpp \
    taskitemwidget.cpp \
    user.cpp \
    validation.cpp

HEADERS += \
    IAdmin.h \
    ITask.h \
    IUser.h \
    admin.h \
    adminpage.h \
    createaccount.h \
    databasehandler.h \
    deleteuser.h \
    frontpage.h \
    login.h \
    profile.h \
    task.h \
    taskitemwidget.h \
    user.h \
    validation.h

FORMS += \
    adminpage.ui \
    createaccount.ui \
    frontpage.ui \
    login.ui \
    profile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    UserInfo.db
