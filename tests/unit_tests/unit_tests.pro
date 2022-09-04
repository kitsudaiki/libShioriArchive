include(../../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++17 console

LIBS += -L../../src -lSagiriArchive
INCLUDEPATH += $$PWD


LIBS += -L../../../libKitsunemimiHanamiEndpoints/src -lKitsunemimiHanamiEndpoints
LIBS += -L../../../libKitsunemimiHanamiEndpoints/src/debug -lKitsunemimiHanamiEndpoints
LIBS += -L../../../libKitsunemimiHanamiEndpoints/src/release -lKitsunemimiHanamiEndpoints
INCLUDEPATH += ../../../libKitsunemimiHanamiEndpoints/include

LIBS += -L../../../libKitsunemimiSakuraLang/src -lKitsunemimiSakuraLang
LIBS += -L../../../libKitsunemimiSakuraLang/src/debug -lKitsunemimiSakuraLang
LIBS += -L../../../libKitsunemimiSakuraLang/src/release -lKitsunemimiSakuraLang
INCLUDEPATH += ../../../libKitsunemimiSakuraLang/include

LIBS += -L../../../libKitsunemimiConfig/src -lKitsunemimiConfig
LIBS += -L../../../libKitsunemimiConfig/src/debug -lKitsunemimiConfig
LIBS += -L../../../libKitsunemimiConfig/src/release -lKitsunemimiConfig
INCLUDEPATH += ../../../libKitsunemimiConfig/include

LIBS += -L../../../libKitsunemimiSakuraNetwork/src -lKitsunemimiSakuraNetwork
LIBS += -L../../../libKitsunemimiSakuraNetwork/src/debug -lKitsunemimiSakuraNetwork
LIBS += -L../../../libKitsunemimiSakuraNetwork/src/release -lKitsunemimiSakuraNetwork
INCLUDEPATH += ../../../libKitsunemimiSakuraNetwork/include

LIBS += -L../../../libKitsunemimiSakuraNetwork/src -lKitsunemimiSakuraNetwork
LIBS += -L../../../libKitsunemimiSakuraNetwork/src/debug -lKitsunemimiSakuraNetwork
LIBS += -L../../../libKitsunemimiSakuraNetwork/src/release -lKitsunemimiSakuraNetwork
INCLUDEPATH += ../../../libKitsunemimiSakuraNetwork/include

LIBS += -L../../../libKitsunemimiNetwork/src -lKitsunemimiNetwork
LIBS += -L../../../libKitsunemimiNetwork/src/debug -lKitsunemimiNetwork
LIBS += -L../../../libKitsunemimiNetwork/src/release -lKitsunemimiNetwork
INCLUDEPATH += ../../../libKitsunemimiNetwork/include

LIBS += -L../../../libKitsunemimiJinja2/src -lKitsunemimiJinja2
LIBS += -L../../../libKitsunemimiJinja2/src/debug -lKitsunemimiJinja2
LIBS += -L../../../libKitsunemimiJinja2/src/release -lKitsunemimiJinja2
INCLUDEPATH += ../../../libKitsunemimiJinja2/include

LIBS += -L../../../libKitsunemimiJwt/src -lKitsunemimiJwt
LIBS += -L../../../libKitsunemimiJwt/src/debug -lKitsunemimiJwt
LIBS += -L../../../libKitsunemimiJwt/src/release -lKitsunemimiJwt
INCLUDEPATH += ../../../libKitsunemimiJwt/include

LIBS += -L../../../libKitsunemimiCrypto/src -lKitsunemimiCrypto
LIBS += -L../../../libKitsunemimiCrypto/src/debug -lKitsunemimiCrypto
LIBS += -L../../../libKitsunemimiCrypto/src/release -lKitsunemimiCrypto
INCLUDEPATH += ../../../libKitsunemimiCrypto/include

LIBS += -L../../../libKitsunemimiJson/src -lKitsunemimiJson
LIBS += -L../../../libKitsunemimiJson/src/debug -lKitsunemimiJson
LIBS += -L../../../libKitsunemimiJson/src/release -lKitsunemimiJson
INCLUDEPATH += ../../../libKitsunemimiJson/include

LIBS += -L../../../libKitsunemimiIni/src -lKitsunemimiIni
LIBS += -L../../../libKitsunemimiIni/src/debug -lKitsunemimiIni
LIBS += -L../../../libKitsunemimiIni/src/release -lKitsunemimiIni
INCLUDEPATH += ../../../libKitsunemimiIni/include

LIBS += -L../../../libKitsunemimiHanamiCommon/src -lKitsunemimiHanamiCommon
LIBS += -L../../../libKitsunemimiHanamiCommon/src/debug -lKitsunemimiHanamiCommon
LIBS += -L../../../libKitsunemimiHanamiCommon/src/release -lKitsunemimiHanamiCommon
INCLUDEPATH += ../../../libKitsunemimiHanamiCommon/include

LIBS += -L../../../libKitsunemimiArgs/src -lKitsunemimiArgs
LIBS += -L../../../libKitsunemimiArgs/src/debug -lKitsunemimiArgs
LIBS += -L../../../libKitsunemimiArgs/src/release -lKitsunemimiArgs
INCLUDEPATH += ../../../libKitsunemimiArgs/include

LIBS += -L../../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../../libKitsunemimiCommon/include

LIBS += -L../../../libKitsunemimiHanamiNetwork/src -lKitsunemimiHanamiMessaging
LIBS += -L../../../libKitsunemimiHanamiNetwork/src/debug -lKitsunemimiHanamiMessaging
LIBS += -L../../../libKitsunemimiHanamiNetwork/src/release -lKitsunemimiHanamiMessaging
INCLUDEPATH += ../../../libKitsunemimiHanamiNetwork/include

LIBS += -lssl -lcryptopp -lcrypto

SOURCES += \
    main.cpp  \
    sagiri_messages_test.cpp

HEADERS += \
    sagiri_messages_test.h
