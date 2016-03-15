config += debug

SOURCES += main.cpp \
           maindialog.cpp

HEADERS += maindialog.h

FORMS += maindialog.ui

#shared memory log
SOURCES += ../sharedmemorylog/sharedmemorylog.cpp

HEADERS += ../sharedmemorylog/sharedmemorylog.h