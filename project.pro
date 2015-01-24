TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/IO/inputreader.cpp \
    src/Core/application.cpp \
    src/Adapter/satadapter.cpp \
    src/Model/filemodel.cpp \
    src/Model/satfilemodel.cpp \
    src/Utils/stringutil.cpp \
    src/Model/Node/abstractnode.cpp \
    src/Model/Node/variablenode.cpp \
    src/Model/Node/Operation/abstractoperationnode.cpp \
    src/Model/Node/Operation/andoperationnode.cpp \
    src/Model/Node/Operation/oroperationnode.cpp \
    src/Model/Node/Operation/notoperationnode.cpp \
    src/Model/Node/Operation/xoroperationnode.cpp \
    src/Model/Node/Operation/equivalenceoperationnode.cpp \
    src/Translator/sattocnftranslator.cpp \
    src/Factory/nodefactory.cpp \
    src/Adapter/cnfadapter.cpp \
    src/Model/cnffilemodel.cpp \
    src/Utils/translationutil.cpp \
    src/Model/Node/truenode.cpp \
    src/Model/Node/falsenode.cpp \
    src/Utils/datetimeutil.cpp \
    src/IO/inputfilereader.cpp \
    src/IO/outputfilewriter.cpp \
    src/Model/Collection/chain.cpp \
    src/Model/Collection/chainelement.cpp \
    src/Model/Collection/chainiterator.cpp \
    src/Exception/expressionequalstrueexception.cpp \
    src/Exception/expressionequalsfalseexception.cpp

HEADERS += \
    src/IO/inputreader.h \
    src/Core/application.h \
    src/Adapter/satadapter.h \
    src/Model/filemodel.h \
    src/Model/satfilemodel.h \
    src/Utils/stringutil.h \
    src/Model/Node/abstractnode.h \
    src/Model/Node/variablenode.h \
    src/Model/Node/Operation/abstractoperationnode.h \
    src/Model/Node/Operation/andoperationnode.h \
    src/Model/Node/Operation/oroperationnode.h \
    src/Model/Node/Operation/notoperationnode.h \
    src/Model/Node/Operation/xoroperationnode.h \
    src/Model/Node/Operation/equivalenceoperationnode.h \
    src/Translator/sattocnftranslator.h \
    src/Factory/nodefactory.h \
    src/Adapter/cnfadapter.h \
    src/Model/cnffilemodel.h \
    src/Utils/translationutil.h \
    src/Model/Node/truenode.h \
    src/Model/Node/falsenode.h \
    src/Utils/datetimeutil.h \
    src/IO/inputfilereader.h \
    src/IO/outputfilewriter.h \
    src/Model/Collection/chain.h \
    src/Model/Collection/chainelement.h \
    src/Model/Collection/chainiterator.h \
    src/Exception/expressionequalstrueexception.h \
    src/Exception/expressionequalsfalseexception.h

