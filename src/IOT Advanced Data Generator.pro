#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# *                                                                         *
# *  Copyright (C) 2019 IRIL Lab, KICS, UET Lahore <iril@kics.edu.pk>       *
# *                                                                         *
# *  This file is part of IRIL Advanced Data Generator.                     *                                         *
# *                                                                         *
# *  IRIL Advanced Data Generator is free software: you can redistribute    *
# *  it and/or modify it under the terms of the GNU General Public License  *
# *  as published by the Free Software Foundation, version 3 of the License.*
# *                                                                         *
# *                                                                         *
# *  IRIL Advanced Data Generator is distributed in the hope that it will   *
# *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty *
# *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        *
# *  GNU General Public License for more details.                           *
# *                                                                         *
# *  You should have received a copy of the GNU General Public License      *
# *  along with IRIL Advanced Data Generator.                               *
# *  If not, see <http://www.gnu.org/licenses/>.                            *
# *                                                                         *
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T10:33:12
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRIL_IoT_DataGenerator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dal.cpp \
    dldataprofile.cpp \
    dltimeprofile.cpp \
    dltopic.cpp \
    objdataprofile.cpp \
    objtimeprofile.cpp \
    objtopic.cpp \
    viewtopics.cpp \
    viewdataprofile.cpp \
    viewtimeprofile.cpp \
    topics.cpp \
    dataprofile.cpp \
    timeprofile.cpp \
    udpflood.cpp \
    objdevicetemplate.cpp \
    objdevicesubscribedata.cpp \
    objdevicepublishdata.cpp \
    objfrmnewdevicetemplateview.cpp \
    dlfrmnewdevicetemplateview.cpp \
    frmnewdevicetemplateview.cpp \
    dldevicesubscribedata.cpp \
    dldevicepublishdata.cpp \
    dldevicetemplate.cpp \
    frmnewdevicetemplate.cpp \
    objdevicecoapdata.cpp \
    objdevicehttpdata.cpp \
    dldevicehttpdata.cpp \
    dldevicecoapdata.cpp \
    constants.cpp \
    synattack.cpp \
    floodattack.cpp \
    frmnewdevice.cpp \
    coap/coapnetworkaccessmanager.cpp \
    coap/coapobserveresource.cpp \
    coap/coapoption.cpp \
    coap/coappdu.cpp \
    coap/coappdublock.cpp \
    coap/coapreply.cpp \
    coap/coaprequest.cpp \
    coap/coaptarget.cpp \
    coap/corelink.cpp \
    coap/corelinkparser.cpp \
    mqtt/qmqttclient.cpp \
    mqtt/qmqttconnection.cpp \
    mqtt/qmqttcontrolpacket.cpp \
    mqtt/qmqttmessage.cpp \
    mqtt/qmqttsubscription.cpp \
    mqtt/qmqtttopicfilter.cpp \
    mqtt/qmqtttopicname.cpp \
    threadmain.cpp \
    objdevice.cpp \
    objglobal.cpp \
    device.cpp \
    frmkeyvalue.cpp \
    frmloadusecase.cpp \
    frmsaveusecase.cpp \
    frmviewlog.cpp \
    filehandler.cpp \
    objusecase.cpp \
    dlusecase.cpp

HEADERS += \
        mainwindow.h \
    dal.h \
    dldataprofile.h \
    dltimeprofile.h \
    dltopic.h \
    objdataprofile.h \
    objtimeprofile.h \
    objtopic.h \
    viewtopics.h \
    viewdataprofile.h \
    viewtimeprofile.h \
    topics.h \
    dataprofile.h \
    timeprofile.h \
    udpflood.h \
    objdevicesubscribedata.h \
    objdevicetemplate.h \
    objfrmnewdevicetemplateview.h \
    dlfrmnewdevicetemplateview.h \
    objdevicepublishdata.h \
    frmnewdevicetemplateview.h \
    frmnewdevicetemplate.h \
    dldevicesubscribedata.h \
    dldevicepublishdata.h \
    dldevicetemplate.h \
    objdevicecoapdata.h \
    objdevicehttpdata.h \
    dldevicehttpdata.h \
    dldevicecoapdata.h \
    constants.h \
    synattack.h \
    floodattack.h \
    frmnewdevice.h \
    coap/coapnetworkaccessmanager.h \
    coap/coapobserveresource.h \
    coap/coapoption.h \
    coap/coappdu.h \
    coap/coappdublock.h \
    coap/coapreply.h \
    coap/coaprequest.h \
    coap/coaptarget.h \
    coap/corelink.h \
    coap/corelinkparser.h \
    mqtt/qguard_p.h \
    mqtt/qmqttclient.h \
    mqtt/qmqttclient_p.h \
    mqtt/qmqttconnection_p.h \
    mqtt/qmqttcontrolpacket_p.h \
    mqtt/qmqttglobal.h \
    mqtt/qmqttmessage.h \
    mqtt/qmqttsubscription.h \
    mqtt/qmqttsubscription_p.h \
    mqtt/qmqtttopicfilter.h \
    mqtt/qmqtttopicname.h \
    mqtt/qobject_p.h \
    threadmain.h \
    objdevice.h \
    objglobal.h \
    device.h \
    frmkeyvalue.h \
    frmloadusecase.h \
    frmsaveusecase.h \
    frmviewlog.h \
    filehandler.h \
    objusecase.h \
    dlusecase.h

FORMS += \
        mainwindow.ui \
    viewtopics.ui \
    viewdataprofile.ui \
    viewtimeprofile.ui \
    topics.ui \
    dataprofile.ui \
    timeprofile.ui \
    udpflood.ui \
    frmnewdevicetemplateview.ui \
    frmnewdevicetemplate.ui \
    synattack.ui \
    floodattack.ui \
    frmnewdevice.ui \
    dataprofile.ui \
    frmkeyvalue.ui \
    frmloadusecase.ui \
    frmsaveusecase.ui \
    frmviewlog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    coap/coap.pri

SUBDIRS += \
    mqtt/mqtt.pro



INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
