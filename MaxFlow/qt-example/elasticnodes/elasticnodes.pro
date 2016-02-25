QT += widgets

HEADERS += \
        edge.h \
        node.h \
        graphwidget.h \
    mainwindow.h \
    vnetwork.h

SOURCES += \
        edge.cpp \
        main.cpp \
        node.cpp \
        graphwidget.cpp \
    mainwindow.cpp \
    vnetwork.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target
