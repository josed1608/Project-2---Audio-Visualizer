QT += charts multimedia

HEADERS += \
    AudioCircle.h \
    AudioFace.h \
    View.h \
    AudioDevice.h \
    AudioRect.h \
    ChoiceWidget.h \
    AudioChart.h

SOURCES += \
    main.cpp\
    AudioCircle.cpp \
    AudioFace.cpp \
    View.cpp \
    AudioDevice.cpp \
    AudioRect.cpp \
    ChoiceWidget.cpp \
    AudioChart.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
INSTALLS += target

FORMS += \
    ChoiceWidget.ui
