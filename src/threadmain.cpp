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
#include "threadmain.h"
#include<qdebug.h>
#include "objdevice.h"
#include<qthreadpool.h>
//#include<workerpool.h>
#include<qlist.h>
#include<qdatetime.h>
#include<filehandler.h>
#include<dlusecase.h>
#include<dldevicetemplate.h>
#include<dldevicesubscribedata.h>
#include<dldevicepublishdata.h>
#include<dldevicecoapdata.h>
#include<dldevicehttpdata.h>
#include<qnetworkinterface.h>


#define INETADDR(a, b, c, d)    (d + (c << 8) + (b << 16) + (a << 24))

ThreadMain::ThreadMain()
{

}
bool ThreadMain::CreateDevice(objDevice _objDevice,bool isSave)
{
      FileHandler _FileHandler;
      QString initialPrint ="";
      initialPrint += "\nDevice Name="+ _objDevice.deviceName + "\n";
      initialPrint += "IP="+ _objDevice.sHostName + "\n";
      initialPrint += "Protocol="+_objDevice.protocol + "\n";
      initialPrint += "IsAttackingEntity="+ QString::number(_objDevice.isAttackingEntity) + "\n";
      if(_objDevice.isAttackingEntity)
      {
          initialPrint += "AttackType="+ _objDevice.attackType + "\n";
          initialPrint +="SourceIP="+ _objDevice.sourceIP +"\n";
          initialPrint += "TargetIP="+ _objDevice.targetIP + "\n";
          initialPrint += "TargetPort="+ QString::number(_objDevice.targetPort) + "\n";
          initialPrint += "Messages/sec="+ QString::number(_objDevice.interval) + "\n";
          initialPrint +="Message="+ _objDevice.message +"\n";
      }

      if(_objDevice.protocol == "MQTT")
      {
          initialPrint += "**********MQTT DETAILS START**************\n";
          initialPrint += "Brooker IP="+_objDevice.protocol + "\n";
          if(_objDevice.isAuthenticationRequire)
          {
              initialPrint += "Authentication Require:"+QString::number( _objDevice.isAuthenticationRequire) +"\n";
              initialPrint += "UserName:"+_objDevice.userName +"\n";
              initialPrint += "Password:"+_objDevice.password +"\n";
          }

          initialPrint += "**********MQTT SUBSCRIBE DETAIL**************\n";
          for(int i=0;i<_objDevice.lstSubTopic.count();i++)
          {
              initialPrint += "Subscribe Topic="+_objDevice.lstSubTopic[i].topicName + "\n";
          }
          initialPrint += "**********MQTT PUBLISH DETAIL**************\n";
          for(int i=0;i<_objDevice.lstPubTopic.count();i++)
          {
              initialPrint += "Publish Topic="+_objDevice.lstPubTopic[i].topic + "\n";
              initialPrint += "Publish QoS="+QString::number(_objDevice.lstPubTopic[i].QoS) + "\n";
              initialPrint += "Publish timeprofile="+_objDevice.lstPubTopic[i]._objTimeProfile.name + "\n";
              initialPrint += "Publish dataprofile="+_objDevice.lstPubTopic[i]._objDataProfile.name + "\n";
          }
          initialPrint += "**********MQTT DETAILS END**************\n";
      }
      else if(_objDevice.protocol == "COAP")
      {
          initialPrint += "**********COAP DETAILS START**************\n";

          for(int i=0;i<_objDevice.lstDeviceCoapData.count();i++)
          {
             initialPrint += "Coap URL="+_objDevice.lstDeviceCoapData[i].url + "\n";
             initialPrint += "Coap Command="+_objDevice.lstDeviceCoapData[i].coapCommand + "\n";
             initialPrint += "Coap timeprofile="+_objDevice.lstDeviceCoapData[i].timeprofile + "\n";
             initialPrint += "Coap Dataprofile="+_objDevice.lstDeviceCoapData[i].dataprofile + "\n";
            // initialPrint += "Coap parameters=CreateDevice"+_objDevice.lstDeviceCoapData[i].parameters + "\n";
          }

          initialPrint += "**********COAP DETAILS END**************\n";
      }
      else if(_objDevice.protocol == "HTTP")
      {
          initialPrint += "**********HTTP DETAILS START**************\n";

          for(int i=0;i<_objDevice.lstDeviceHttpData.count();i++)
          {
             initialPrint += "HTTP URL="+_objDevice.lstDeviceHttpData[i].url + "\n";
             initialPrint += "HTTP Command="+_objDevice.lstDeviceHttpData[i].httpCommand + "\n";
             initialPrint += "HTTP timeprofile="+_objDevice.lstDeviceHttpData[i].timeprofile + "\n";
              initialPrint += "HTTP dataprofile="+_objDevice.lstDeviceHttpData[i].dataprofile + "\n";
          //   initialPrint += "HTTP parameters="+_objDevice.lstDeviceHttpData[i].parameters + "\n";
          }

          initialPrint += "**********HTTP DETAILS END**************\n";
      }


//data
      _FileHandler.writeFile(_objDevice.sHostName,initialPrint,false);
      QNetworkInterface interface;
      QList<QNetworkInterface> IpList = interface.allInterfaces();
       QByteArray interfaceName;
       for (int i = 0; i < IpList.size(); i++)
       {
           if(IpList[i].name()!= "lo" )
           {
               interfaceName.append(IpList[i].name());
               //qDebug()<< "Interface " << i << ":" << IpList.at(i).name() << endl;
               break;
           }
       }
//" + interfaceName +"

     //const char* ipval = "sudo -S ifconfig wlp1s0:"+ QString(j).toUtf8() + " " + __objDevice.sHostName.toUtf8() + " up";

       QString command ="sudo -S ifconfig wlp1s0:"+ QString::number(j) + " " + _objDevice.sHostName + " up";
       char* ipval = new char[(command.length() + 1)];
       strcpy(ipval, command.toLatin1().constData());
       qDebug()<<"ipval:"<<ipval;
       system(ipval);
       j++;
      Device *device =  new Device(_objDevice);
      lstWorkers.append(device);
      if(isSave)
        SaveUseCaseDevice(_objDevice);
      lastError = "";
      return true;
}

void ThreadMain::CreateDevices(objDevice __objDevice)
{
    char ip_buff[16];
    ipstr2dec(__objDevice.sHostName);
    unsigned long max_ips = from + __objDevice.IPCount;
    while ((from < max_ips) && (from < to))
    {
        getNextIP(ip_buff);
        //objDevice _objDevice(__objDevice);
        //_objDevice.sHostName = ip_buff;

        __objDevice.sHostName = ip_buff;

    /*    //const char* ipval = "sudo -S ifconfig wlp1s0:"+ QString(j).toUtf8() + " " + __objDevice.sHostName.toUtf8() + " up";
         QNetworkInterface interface;
         QList<QNetworkInterface> IpList = interface.allInterfaces();
          QByteArray interfaceName;
          for (int i = 0; i < IpList.size(); i++)
          {
              if(IpList[i].name()!= "lo" )
              {
                  interfaceName.append(IpList[i].name());
                  //qDebug()<< "Interface " << i << ":" << IpList.at(i).name() << endl;
                  break;
              }
          }
//" + interfaceName +"

        //const char* ipval = "sudo -S ifconfig wlp1s0:"+ QString(j).toUtf8() + " " + __objDevice.sHostName.toUtf8() + " up";

          QString command ="sudo -S ifconfig wlp1s0:"+ QString::number(j) + " " + __objDevice.sHostName + " up";
          char* ipval = new char[(command.length() + 1)];
          strcpy(ipval, command.toLatin1().constData());
          qDebug()<<"ipval:"<<ipval;
          system(ipval);
          j++;

          */

        CreateDevice(__objDevice,true);
   }
    //qDebug()<<"END Time:"<<QDateTime::currentDateTime()<<"\n";
  //  qDebug()<<"CreateDevice : "<<CreateDevice(__objDevice);
}

QString ThreadMain::GetDevicesInfo()
{
    QString finalOutput = "";
   // mutex.lock();
    {
        QString output = "";
        for(int i=0;i<lstWorkers.count();i++)
        {
            output = output + lstWorkers[i]->_objDevice.sHostName+","+
                     lstWorkers[i]->_objDevice.protocol+","+
                     lstWorkers[i]->m_client->state()+"\n";

        }

        finalOutput = output;
    }
   // mutex.unlock();
return finalOutput;
}


bool ThreadMain::RemoveDevice(QString _IP)
{
   // mutex.lock();
    {
        for(int i=0;i<lstWorkers.count();i++)
        {
            if(lstWorkers[i]->objectName() == _IP)
            {
                //lstWorkers[i]->abort();
                delete lstWorkers[i];
                i--;
                qDebug()<<lstWorkers.count() + " "+ _IP<<"\n";
                break;
            }
        }
    }
   // mutex.unlock();
    return true;
}



// //////////////////////IP Checks\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

bool ThreadMain::isIPinUse(QString _IP)
{
    QString output = "";
   // mutex.lock();
    {
        for(int i=0;i<lstWorkers.count();i++)
        {
            if(lstWorkers[i]->objectName() == _IP)
            {
                lastError = _IP + "IP INUSE" ;
                qDebug()<<_IP<<" INUSE\n";
                break;
            }
        }
    }
   // mutex.unlock();

    if(lastError == "")
        return   false;
    return  true;
}

void ThreadMain::getNextIP(char ip_addr[]){

    unsigned char *ip;
    ip = (unsigned char *)&from;
    if (ip[0] == 0){
        from++;
    }
    else if (ip[0] == 255){
        from += 2;
    }

    ip = (unsigned char *)&from;
    sprintf(ip_addr, "%u.%u.%u.%u", ip[3], ip[2], ip[1], ip[0]);
    from++;
}

void ThreadMain::ipstr2dec(QString ip)
{
    QStringList server_octets = ip.split(".");
    unsigned int s1 = server_octets.at(0).toUInt();
    unsigned int s2 = server_octets.at(1).toUInt();
    unsigned int s3 = server_octets.at(2).toUInt();
    unsigned int s4 = server_octets.at(3).toUInt();
    from = INETADDR(s1,s2,s3,s4);
    to   = INETADDR(255,255,255,254);
}


// //////////////////////DESTRUCTOR\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

ThreadMain::~ThreadMain()
{

}

bool ThreadMain::SaveUseCase(QString ucName){

    dlUseCase _dlUseCase;
    objUseCase _objUseCase;
    _objUseCase.name = ucName;
    int useCaseID =  _dlUseCase.Insert(_objUseCase);

    for(int j=0;j<lstWorkers.count();j++)
    {
        SaveUseCaseDevice(lstWorkers[j]->_objDevice);
    }
    qDebug()<<"Successfully Done";

    return true;

}


bool ThreadMain::SaveUseCaseDevice(objDevice _objDevice)
{

    //objDevice _objDevice = lstWorkers[j]->_objDevice;
    objDeviceTemplate _objDeviceTemplate;
    _objDeviceTemplate.deviceName = _objDevice.deviceName;
    _objDeviceTemplate.useCaseID = _objDevice.useCaseID;    //====
    //general tab information
    _objDeviceTemplate.deviceProtocol =_objDevice.protocol;
    _objDeviceTemplate.IPAddress =     _objDevice.sHostName;


    _objDeviceTemplate.isAttackingEntity = _objDevice.isAttackingEntity;
   if(_objDevice.isAttackingEntity)
   {
       _objDeviceTemplate.attackType = _objDevice.attackType;
       _objDeviceTemplate.sourceIP = _objDevice.sourceIP;
       _objDeviceTemplate.targetIP = _objDevice.targetIP;
       _objDeviceTemplate.targetPort = _objDevice.targetPort;
       _objDeviceTemplate.interval = _objDevice.interval;
       _objDeviceTemplate.message = _objDevice.message;

   }

//mqtt basic setting
_objDeviceTemplate.brokerIP = _objDevice.hostName;
if(_objDevice.portType == "REGULAR")
 {
   _objDeviceTemplate.isRegularPort = true;
   _objDeviceTemplate.portNO= _objDevice.port;
  }
  else
   {
    _objDeviceTemplate.isRegularPort = false;
    _objDeviceTemplate.portNO = _objDevice.port;
   }

   if(_objDevice.isAuthenticationRequire)
   {
       _objDeviceTemplate.isAuthenticationRequire = true;
       _objDeviceTemplate.brokerUserName = _objDevice.userName;
       _objDeviceTemplate.brokerPassword = _objDevice.password;
   }
   else
       _objDeviceTemplate.isAuthenticationRequire = false;

//coap basic setting
if(_objDevice.protocol=="COAP")
_objDeviceTemplate.coapURL = _objDevice.hostName;

//http basic setting
if(_objDevice.protocol=="HTTP")
_objDeviceTemplate.httpURL = _objDevice.hostName;

int  templateID = 0;

//saving parent table "device template"
dlDeviceTemplate *_dlDeviceTemplate = new dlDeviceTemplate();
templateID =  _dlDeviceTemplate->InsertForUseCase(_objDeviceTemplate);


if(templateID>0)
{
  //saving mqtt subscribe details
    dlDeviceSubscribeData _dlDeviceSubscribeData;
 // _dlDeviceSubscribeData.DelSubscribeData(templateID);

  for(int i=0;i<_objDevice.lstSubTopic.count();i++)
  {
      _objDevice.isSubscriber = true;
      objDeviceSubscribeData _objDeviceSubscribeData;
      _objDeviceSubscribeData.topicID = _objDevice.lstSubTopic[i].topicID;
      _objDeviceSubscribeData.deviceTemplateID = templateID;
      _dlDeviceSubscribeData.InsertForUseCase(_objDeviceSubscribeData);
  }

  //save mqtt publish details
     dlDevicePublishData _dlDevicePublishData;
//  _dlDevicePublishData.DelPublishData(templateID);
  for(int j=0; j<_objDevice.lstPubTopic.count();j++)
  {
     // titles2<<"TopicID"<<"DataProfileID"<<"TimeProfileID"<<"Topic"<<"QoS"<<"Data Profile"<<"Time Profile"<<" ";
       _objDevice.isPublisher = true;
       objDevicePublishData _objDevicePublishData;
      _objDevicePublishData.deviceTemplateID = templateID;
      _objDevicePublishData.topicID = _objDevice.lstPubTopic[j].topicID;
      _objDevicePublishData.dataProfileID = _objDevice.lstPubTopic[j].dataProfileID;
      _objDevicePublishData.timeProfileID = _objDevice.lstPubTopic[j].timeProfileID;

      _objDevicePublishData.topic = _objDevice.lstPubTopic[j].topic;
      _objDevicePublishData.QoS = _objDevice.lstPubTopic[j].QoS;
      _dlDevicePublishData.InsertForUseCase(_objDevicePublishData);


  }

  //save coap detials
  dlDeviceCoapData _dlDeviceCoapData;
 // _dlDeviceCoapData.DelCoapData(templateID);
 //titles3<<"URL"<<"Command"<<"parameters"<<"TimeProfileID"<<"Time Profile"<<"";
  for(int j=0; j<_objDevice.lstDeviceCoapData.count();j++)
  {
      objDeviceCoapData _objDeviceCoapData;
      _objDeviceCoapData.deviceTemplateID = templateID;
      _objDeviceCoapData.url = _objDevice.lstDeviceCoapData[j].url;
      _objDeviceCoapData.coapCommand = _objDevice.lstDeviceCoapData[j].coapCommand;
      //_objDeviceCoapData.parameters = _objDevice.lstDeviceCoapData[j].parameters;
      //_objDeviceCoapData.parametersWithID = _objDevice.lstDeviceCoapData[j].parametersWithID;
       _objDeviceCoapData.coapTimeProfileID = _objDevice.lstDeviceCoapData[j]._objTimeProfile._id;
       _objDeviceCoapData.timeprofile = _objDevice.lstDeviceCoapData[j].timeprofile;
       _objDeviceCoapData.coapDataProfileID = _objDevice.lstDeviceCoapData[j]._objDataProfile._id;
       _objDeviceCoapData.dataprofile = _objDevice.lstDeviceCoapData[j].dataprofile;
       dlDeviceCoapData _dlDeviceCoapData;
      _dlDeviceCoapData.InsertForUseCase(_objDeviceCoapData);
  }

  //save http details
  dlDeviceHttpData _dlDeviceHttpData;
  //_dlDeviceHttpData.DelHttpData(templateID);

  for(int j=0; j<_objDevice.lstDeviceHttpData.count();j++)
  {
      objDeviceHttpData _objDeviceHttpData;
      _objDeviceHttpData.deviceTemplateID = templateID;
      _objDeviceHttpData.url = _objDevice.lstDeviceHttpData[j].url;
     _objDeviceHttpData.httpCommand = _objDevice.lstDeviceHttpData[j].httpCommand;
    // _objDeviceHttpData.parameters = _objDevice.lstDeviceHttpData[j].parameters;
    // _objDeviceHttpData.parametersWithID = _objDevice.lstDeviceHttpData[j].parametersWithID;
     _objDeviceHttpData.httpTimeProfileID = _objDevice.lstDeviceHttpData[j]._objTimeProfile._id;
     _objDeviceHttpData.timeprofile = _objDevice.lstDeviceHttpData[j].timeprofile;
     _objDeviceHttpData.httpDataProfileID = _objDevice.lstDeviceHttpData[j]._objDataProfile._id;
     _objDeviceHttpData.dataprofile = _objDevice.lstDeviceHttpData[j].dataprofile;
     dlDeviceHttpData _dlDeviceHttpData;
     _dlDeviceHttpData.InsertForUseCase(_objDeviceHttpData);
  }
  return  true;

    qDebug()<<"Successfully inserted";

}
else {
    return false;

  qDebug()<<"Error while inserting";


}

}

bool ThreadMain::LoadUseCase(int UseCaseID){


    dlDeviceTemplate _dlDeviceTemplate;
    QList<objDevice> lstObjDevice = _dlDeviceTemplate.GetDeviceListForUseCase(UseCaseID);
    foreach(objDevice _objDevice,lstObjDevice)
        CreateDevice(_objDevice,false);


    return true;
}
bool ThreadMain::StartUsecase(int rowCount)
{
    return true;
}
bool ThreadMain::StopUsecase(int rowCount)
{
    return true;
}

QString ThreadMain::RefreshUseCase(){

    QString finalOutput = "";
   // mutex.lock();
    {
        QString output = "";
        for(int i=0;i<lstWorkers.count();i++)
        {
            output = output + lstWorkers[i]->_objDevice.deviceName+","+
                     lstWorkers[i]->_objDevice.protocol+","+
                     lstWorkers[i]->_objDevice.sHostName+","+
                     lstWorkers[i]->_objDevice.attackType+","+
                     lstWorkers[i]->_objDevice.lastActivity;

            if((i+1)!= lstWorkers.count())
                output += ";";
        }

        finalOutput = output;
    }
    //mutex.unlock();
return finalOutput;
}

bool ThreadMain::ClearUseCase(){


    for(int i=0;i<lstWorkers.count();i++)
    {
        if(lstWorkers[i]->_objDevice.protocol == "MQTT")
        {
            lstWorkers[i]->m_client->disconnectFromHost();
            delete lstWorkers[i]->m_client;
        }
    if (lstWorkers[i]->isTimerActive)
    {
           lstWorkers[i]->timer->stop();
            delete lstWorkers[i]->timer;
    }
    if (lstWorkers[i]->isAttackTimerActive)
    {
           lstWorkers[i]->attackTimer->stop();
           delete lstWorkers[i]->attackTimer;
    }
    }

    lstWorkers.clear();
    return true;

}
bool ThreadMain::DeleteUseCase(int useCaseID)
{


    dlDeviceTemplate _dlDeviceTemplate;
    QList<objDevice> lstObjDevice = _dlDeviceTemplate.GetDeviceListForUseCase(useCaseID);
    for(int i=0;i<lstObjDevice.count();i++)
    {
        int deviceTemplateID= lstObjDevice[i].templateID;
        dlDeviceSubscribeData _dlDeviceSubscribeData;
        _dlDeviceSubscribeData.DelSubscribeDataForUseCase(deviceTemplateID);
        dlDevicePublishData _dlDevicePublishData;
        _dlDevicePublishData.DelPublishDataForUseCase(deviceTemplateID);
        dlDeviceCoapData _dlDeviceCoapData;
        _dlDeviceCoapData.DelCoapDataForUseCase(deviceTemplateID);
        dlDeviceHttpData _dlDeviceHttpData;
        _dlDeviceHttpData.DelHttpDataForUseCase(deviceTemplateID);
        _dlDeviceTemplate.DelDeviceTemplateDataForUseCase(deviceTemplateID);
    }
    dlUseCase _dlUseCase;
    _dlUseCase.DelUseCase(useCaseID);
}


bool ThreadMain::DeleteDevice(QString IP){

    objDevice _objDevice;
    int i=0;
    bool isDelete = false;

    for(;i<lstWorkers.count();i++)
    {
        if(lstWorkers[i]->_objDevice.sHostName == IP)
             _objDevice = lstWorkers[i]->_objDevice;

            dlDeviceSubscribeData _dlDeviceSubscribeData;
            _dlDeviceSubscribeData.DelSubscribeDataForUseCase(_objDevice.templateID);
            dlDevicePublishData _dlDevicePublishData;
            _dlDevicePublishData.DelPublishDataForUseCase(_objDevice.templateID);
            dlDeviceCoapData _dlDeviceCoapData;
            _dlDeviceCoapData.DelCoapDataForUseCase(_objDevice.templateID);
            dlDeviceHttpData _dlDeviceHttpData;
            _dlDeviceHttpData.DelHttpDataForUseCase(_objDevice.templateID);
            dlDeviceTemplate _dlDeviceTemplate;
            _dlDeviceTemplate.DelDeviceTemplateDataForUseCase(_objDevice.templateID);
            if(lstWorkers[i]->_objDevice.protocol == "MQTT")
            {
                lstWorkers[i]->m_client->disconnectFromHost();
                delete lstWorkers[i]->m_client;
            }
           //
            if (lstWorkers[i]->isTimerActive)
            {
                   lstWorkers[i]->timer->stop();
                    delete lstWorkers[i]->timer;
            }
            if (lstWorkers[i]->isAttackTimerActive)
            {
                   lstWorkers[i]->attackTimer->stop();
                   delete lstWorkers[i]->attackTimer;
            }
            lstWorkers.removeAt(i);
            isDelete = true;
            break;
    }

    //if(isDelete)
       //lstWorkers.removeAt(i);



    qDebug() << IP;
}

QString ThreadMain::ViewDeviceData(QString IP){

    FileHandler _FileHandler;
   return  _FileHandler.readFile(IP);


}



