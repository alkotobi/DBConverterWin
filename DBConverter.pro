QT       += core gui sql widgets
PACKAGECONFIG_append_pn-qtbase = "sql-sqlite"
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databases/mnauthor.cpp \
    databases/mnbook.cpp \
    databases/mnbooklist.cpp \
    databases/mncat.cpp \
    databases/mnindex.cpp \
    databases/mnmidtableslink.cpp \
    databases/mnpage.cpp \
    databases/mnsearchbook.cpp \
    databases/mntable.cpp \
    databases/mntachkil.cpp \
    databases/mnwords.cpp \
    imports/mndb.cpp \
    imports/mnimport.cpp \
    imports/mnpathes.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    mnbookshowform.cpp \
    mninit.cpp \
    mnnass.cpp \
    mnquery.cpp \
    mnrecord.cpp \
    mnshowbookwid.cpp \
    mnsql.cpp

HEADERS += \
    MNConst.h \
    databases/mnauthor.h \
    databases/mnbook.h \
    databases/mnbooklist.h \
    databases/mncat.h \
    databases/mnindex.h \
    databases/mnmidtableslink.h \
    databases/mnpage.h \
    databases/mnsearchbook.h \
    databases/mntable.h \
    databases/mntachkil.h \
    databases/mnwords.h \
    imports/mndb.h \
    imports/mnimport.h \
    imports/mnpathes.h \
    log.h \
    mainwindow.h \
    mnbookshowform.h \
    mninit.h \
    mnnass.h \
    mnquery.h \
    mnrecord.h \
    mnshowbookwid.h \
    mnsql.h

FORMS += \
    mainwindow.ui \
    mnbookshowform.ui \
    mnshowbookwid.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
