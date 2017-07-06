QT += charts multimedia

HEADERS += \
    widget.h \
    audioDevice.h

SOURCES += \
    main.cpp\
    widget.cpp \
    audioDevice.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
INSTALLS += target
