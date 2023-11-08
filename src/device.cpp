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
/*
   Copyright 2013 Fabien Pierre-Nicolas.
      - Primarily authored by Fabien Pierre-Nicolas

   This file is part of simple-qt-thread-example, a simple example to demonstrate how to use threads.
   This example is explained on http://fabienpn.wordpress.com/qt-thread-simple-and-stable-with-sources/

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This progra is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "device.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include<objdevice.h>
#include<mqtt/qmqttclient.h>
#include<objglobal.h>
#include<QRandomGenerator>
#include<qregularexpression.h>
#include<objdataprofile.h>
#include<objtimeprofile.h>
#include<qdatetime.h>
#include<filehandler.h>
#include<coap/coapnetworkaccessmanager.h>
#include<qvariant.h>




Device::Device(objDevice __objDevice)
{
    //_working =false;
    //_abort = false;
    _objDevice = __objDevice;
    SetInitialData();
}
Device::Device()
{

}
void Device::SetInitialData()
{
    if(_objDevice.protocol == "MQTT")
    {
        m_client = new QMqttClient();
        m_client->setShostname(_objDevice.sHostName); //device ip
        m_client->setHostname(_objDevice.hostName);  //mqtt brooker
        m_client->setPort(_objDevice.port);          //mqtt booker port
        if(_objDevice.isAuthenticationRequire)
        {
            m_client->setUsername(_objDevice.userName); //arya
            m_client->setPassword(_objDevice.password); //stark
        }
        connect(m_client, &QMqttClient::stateChanged,this, &Device::updateStateChange);
        connect(m_client, &QMqttClient::disconnected, this, &Device::brokerDisconnected);
        connect(m_client, &QMqttClient::messageReceived, this, &Device::MessageReceived);
        m_client->connectToHost();
   }
    else if(_objDevice.protocol == "COAP")
    {
          RunTimer();
         //TimerTick();
    }
    else if(_objDevice.protocol == "HTTP")
    {
        RunTimer();
    }


    if(_objDevice.isAttackingEntity)
    {
        RunAttackTimer(_objDevice.interval);

    }
}


void Device::RunTimer()
{
   timer = new QTimer();
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerTick()));
   timer->start(1000);
   isTimerActive = true;

}

void Device::RunAttackTimer(int interval)
{
   attackTimer = new QTimer();
   connect(attackTimer, SIGNAL(timeout()), this, SLOT(TimerTickAttack()));
   attackTimer->start(1000);
   isAttackTimerActive = true;

}
bool Device::isSendTime(QString lastSentTime,QString timeProfileType,int interval)
{
    bool isSendDataNow = false;

    if(lastSentTime == "")
    {
       isSendDataNow = true;
    }
    else if(timeProfileType.toLower() == "periodic")
    {
        qDebug()<<QDateTime::fromString(lastSentTime).secsTo(QDateTime::currentDateTime()) <<"--"<<interval<<"\n";
       int durationSinceLastSent  = QDateTime::currentDateTime().secsTo(QDateTime::fromString(lastSentTime));
       if(durationSinceLastSent < 0)
           durationSinceLastSent *=-1;
       if(durationSinceLastSent >= interval)
       {
           isSendDataNow = true;
       }
    }
    else  //if(_objDevicePublishData._objTimeProfile.type == "")
    {
       if(interval==0)
           isSendDataNow = true;
       else //if(QDateTime::currentDateTime().secsTo(QDateTime::fromString(lastSentTime)) >= interval)
          {
           int durationSinceLastSent  = QDateTime::currentDateTime().secsTo(QDateTime::fromString(lastSentTime));
           if(durationSinceLastSent < 0)
               durationSinceLastSent *=-1;
           if(durationSinceLastSent >= interval)
           {
               isSendDataNow = true;
           }
         }

    }
   return isSendDataNow;
}

QString Device::GetData(bool isStartText,QString startText,bool isRandom, int from, int to, bool isEndText, QString endText)
{
QString data = "";
if(isStartText)
    data = startText;
if(isRandom)
{
    data = data + QString::number(GenerateRandomNumber(from,to));
}
if(isEndText)
    data = data  + endText;
return  data;
}
int Device::GenerateRandomNumber(int from ,int to)
{
    QRandomGenerator generator;
    generator.seed(rand());
    qint32 rNumber = generator.bounded(from,to);
    return rNumber;
}
void Device::TimerTick( )
{
    // ///////// MQTT Publisher Tick
   if(_objDevice.protocol == "MQTT" && _objDevice.lstPubTopic.length() > 0)
   {
     // foreach(objDevicePublishData _objDevicePublishData,_objDevice.lstPubTopic)
      for(int i=0;i<_objDevice.lstPubTopic.count();i++)
       {
         objDevicePublishData _objDevicePublishData = _objDevice.lstPubTopic[i];
         bool isSendData = isSendTime(_objDevicePublishData._lastSentTime,_objDevicePublishData._objTimeProfile.type,_objDevicePublishData._objTimeProfile.interval);

         if(!isSendData    )
             continue;

         QString data = GetData(_objDevicePublishData._objDataProfile.isStartText,_objDevicePublishData._objDataProfile.startText,_objDevicePublishData._objDataProfile.isRandom,_objDevicePublishData._objDataProfile.randomFrom,_objDevicePublishData._objDataProfile.randomTo,_objDevicePublishData._objDataProfile.isEndText,_objDevicePublishData._objDataProfile.endText);
         QByteArray datagram;
         datagram.append(data);//= data.toStdU16String(); "testing by ghazanfar abbas";
         QMqttTopicName tname;// = new QMqttTopicName();
         tname.setName(_objDevicePublishData.topic);
         if(m_client->publish(tname,datagram,_objDevicePublishData.QoS) == -1)
        {
            WriteInHomeLogs( _objGlobal.msg_ErrorInPublishing + data);
        }
        else
        {
             _objDevice.lstPubTopic[i]._lastSentTime = QDateTime::currentDateTime().toString();
             if(_objDevicePublishData._objTimeProfile.type =="")
                 _objDevicePublishData._objTimeProfile.interval = GenerateRandomNumber(0,_objDevicePublishData._objTimeProfile.randomTo);

              WriteInHomeLogs(_objGlobal.msg_SuccessfulPublished+ data);
        }
      }
   }

   // /////////COAP TICK
   else if(_objDevice.protocol == "COAP")
   {
      //foreach(objDeviceCoapData _objDeviceCoapData,_objDevice.lstDeviceCoapData)
       for(int i=0;i<_objDevice.lstDeviceCoapData.count();i++)
        {
           objDeviceCoapData _objDeviceCoapData = _objDevice.lstDeviceCoapData[i];
           bool isSendData = isSendTime(_objDeviceCoapData._lastSentTime,_objDeviceCoapData._objTimeProfile.type,_objDeviceCoapData._objTimeProfile.interval);

           if(!isSendData    )
               continue;

           QString data = GetData(_objDeviceCoapData._objDataProfile.isStartText,_objDeviceCoapData._objDataProfile.startText,_objDeviceCoapData._objDataProfile.isRandom,_objDeviceCoapData._objDataProfile.randomFrom,_objDeviceCoapData._objDataProfile.randomTo,_objDeviceCoapData._objDataProfile.isEndText,_objDeviceCoapData._objDataProfile.endText);


           CoapNetworkAccessManager *coap = new CoapNetworkAccessManager(this,0,_objDevice.sHostName);
           connect(coap, SIGNAL(replyFinished(CoapReply*)), this, SLOT(onCoapReplyFinished(CoapReply*)));


           //CoapRequest request(QUrl("coap://127.0.0.1/basic"));
            CoapRequest request(QUrl(_objDeviceCoapData.url));



             QByteArray payload;
             payload.append(data);

            if(_objDeviceCoapData.coapCommand == "GET")
            {
                 WriteInHomeLogs(_objGlobal.msg_CoapGetRequest + request.url().toString());
                 coap->get(request);

            }
             else if(_objDeviceCoapData.coapCommand == "POST")
             {
                 coap->post(request,payload);
                 WriteInHomeLogs(_objGlobal.msg_CoapPOSTRequest + request.url().toString());
             }
             if(_objDeviceCoapData.coapCommand == "PUT")
             {
                 coap->put(request,payload);
                 WriteInHomeLogs(_objGlobal.msg_CoapPUTRequest + request.url().toString());

             }
             //coap://coap.me:5683/validate
             if(_objDeviceCoapData.coapCommand == "DELETE")
             {
                 coap->deleteResource(request);
                 WriteInHomeLogs(_objGlobal.msg_CoapDELETERequest + request.url().toString());

             }
                 //coap://vs0.inf.ethz.ch:5683/obs
             //if(_objDeviceCoapData.coapCommand == "OBSERVE")
             //{

               //  connect(coap, SIGNAL(notificationReceived(CoapObserveResource,int,QByteArray)), this, SLOT(onCoapNotificationSignalReceived(CoapObserveResource,int,QByteArray)));
               //  coap->enableResourceNotifications(request);
                //WriteInHomeLogs(_objGlobal.msg_CoapPOSTRequest + request.url().toString());

             //}

              _objDevice.lstDeviceCoapData[i]._lastSentTime = QDateTime::currentDateTime().toString();
              if(_objDevice.lstDeviceCoapData[i]._objTimeProfile.type.toLower() != "periodic")
              {
                  _objDevice.lstDeviceCoapData[i]._objTimeProfile.interval = GenerateRandomNumber(_objDevice.lstDeviceCoapData[i]._objTimeProfile.randomFrom,_objDevice.lstDeviceCoapData[i]._objTimeProfile.randomTo);
                  qDebug()<<"testing interval "<<_objDevice.lstDeviceCoapData[i]._objTimeProfile.interval;
               }
        }
   }
   // /////////HTTP TICK
   else if(_objDevice.protocol == "HTTP")
   {

   }
 }
void Device::TimerTickAttack()
{
        WriteInHomeLogs("Contact admin for attack support: iril@kics.edu.pk");
 }
// //////////COAP SLOTS START
void Device::onCoapReplyFinished(CoapReply *reply)
{
  if (reply->error() != CoapReply::NoError) {
        WriteInHomeLogs(_objGlobal.msg_CoapResponseError + "\n" + reply->errorString());
        return;
        //qWarning() << "Reply finished with error" << reply->errorString();
  }

  QString responseString = "";
  if(reply->messageType() == CoapPdu::MessageType::Acknowledgement)
      responseString += "CoapReply(Acknowledgement)";
  if(reply->messageType() == CoapPdu::MessageType::Reset)
      responseString += "CoapReply(Reset)";
  if(reply->messageType() == CoapPdu::MessageType::Confirmable)
      responseString += "CoapReply(Confirmable)";
  if(reply->messageType() == CoapPdu::MessageType::NonConfirmable)
      responseString += "CoapReply(NonConfirmable)";

  if(reply->statusCode() == CoapPdu::StatusCode::Content)
      responseString += "\n\t\tStatus code: \"2.05 Content\"";

  if(reply->payload().toStdString() != "")
  {
      QString temp =  reply->payload().toStdString().c_str();
      responseString +="\n\t\t"+ temp;
  }
  //QVariant::fromValue(reply->messageType()).toString();;
  WriteInHomeLogs(_objGlobal.msg_CoapResponse + responseString );
  qDebug() << "Reply finished" << reply;
  reply->deleteLater();
}
void Device::onCoapNotificationSignalReceived(CoapObserveResource,int,QByteArray)
{
  WriteInHomeLogs("Coap Notification Signal Received");
}
//
// //////////MQTT SLOTS START
void Device::updateStateChange()
{
    switch (m_client->state()) {
    case 0:
        WriteInHomeLogs(_objGlobal.msg_Disconnected);
        break;
    case 1:
         WriteInHomeLogs(_objGlobal.msg_Connecting);
        break;
    case 2:
         WriteInHomeLogs(_objGlobal.msg_Connected);
         isConnected = true;
        if(_objDevice.isSubscriber)
        {
            foreach (objDeviceSubscribeData _objDeviceSubscribeData,_objDevice.lstSubTopic)
                {
                    QMqttTopicFilter *filter = new QMqttTopicFilter();
                    filter->setFilter(_objDeviceSubscribeData.topicName);
                    auto subscription = m_client->subscribe(*filter);
                    if (!subscription)
                         WriteInHomeLogs(_objGlobal.msg_ErrorInSubscribing + " "+ _objDeviceSubscribeData.topicName);
                    else
                        WriteInHomeLogs(_objGlobal.msg_Subscribed + " "+ _objDeviceSubscribeData.topicName);
                }
        }
        if(_objDevice.lstPubTopic.count()>0)
            RunTimer();
          break;
    }
}

void Device::MessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    WriteInHomeLogs("Message Received: " + message);
}

void Device::brokerDisconnected()
{
     if(m_client->state() == 2){
         WriteInHomeLogs(_objGlobal.msg_Disconnected + _objDevice.sHostName);
     }
}
// //////////MQTT SLOTS END


QString Device::WriteInHomeLogs(QString msg)
{
    //QString finalMsg = _objDevice.sHostName + "  " + msg+ "\n";
    QString fileName = _objDevice.sHostName;

    FileHandler _FileHandler;
    return _FileHandler.writeFile(fileName,msg,true);

    //qDebug()<<finalMsg;
}
void Device::Connected()
{
    mutex.lock();
    isConnected = true;
    mutex.unlock();

}
void Device::Disconnected()
{/*
    mutex.lock();
    isConnected = false;
    mutex.unlock();
*/
}
void Device::SetDevice(objDevice objDevice)
{
    mutex.lock();
    _objDevice = objDevice;
    mutex.unlock();

}
objDevice Device::GetDevice()
{
    return _objDevice;
}



/*
void Device::requestWork()
{

    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();
    emit workRequested();
}
void Device::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
    }
    mutex.unlock();
}*/

void Device::doWork()
{/*
    qDebug()<<"print";
    return;
    while(true){
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();
        if (abort) {
            break;
        }
        QThread::usleep(30);
       }

    mutex.lock();
    _working = false;
    mutex.unlock();
    emit finished(); */
}

