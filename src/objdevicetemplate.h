/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2019 IRIL Lab, KICS, UET Lahore <iril@kics.edu.pk>       *
 *                                                                         *
 *  This file is part of IRIL Advanced Data Generator.                     *                                         *
 *                                                                         *
 *  IRIL Advanced Data Generator is free software: you can redistribute    *
 *  it and/or modify it under the terms of the GNU General Public License  *
 *  as published by the Free Software Foundation, version 3 of the License.*
 *                                                                         *
 *                                                                         *
 *  IRIL Advanced Data Generator is distributed in the hope that it will   *
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty *
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with IRIL Advanced Data Generator.                               *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef OBJDEVICETEMPLATE_H
#define OBJDEVICETEMPLATE_H

#include<QString>

class objDeviceTemplate
{
public:
    objDeviceTemplate();

    int _id;
    int useCaseID;
    QString deviceName;

    QString deviceProtocol;
    QString IPAddress;
    int NumofDevices;

    QString brokerIP;
    bool isRegularPort;
    int portNO;
    bool isAuthenticationRequire;
    QString brokerUserName;
    QString brokerPassword;

    QString coapURL;
    QString httpURL;

    bool isAttackingEntity;
    QString attackType;
    QString sourceIP;
    QString targetIP;
    int targetPort;
    int interval;
    QString message;


   /* QString subscribeTopic;
     // QString deviceType;
    QString publishMessage;
    int publishTimeInterval;


    int publishQoS; */



};
#endif // OBJDEVICETEMPLATE_H
