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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewtopics.h"
#include "viewtimeprofile.h"
#include "viewdataprofile.h"
#include<frmnewdevicetemplateview.h>
#include "udpflood.h"
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <frmnewdevice.h>
#include <frmnewdevicetemplate.h>
#include <frmsaveusecase.h>
#include <ui_frmsaveusecase.h>
#include <frmloadusecase.h>
#include <ui_frmloadusecase.h>
#include "frmviewlog.h"
#include "ui_frmviewlog.h"
#include"dlusecase.h"
#include<pthread.h>
#include<cstdlib>
#include<qnetworkinterface.h>
//#include<QThread>
#include<QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    try {
    ui->setupUi(this);
    QMainWindow::showMaximized();
    this->setWindowTitle(_constants.APPLICATION_NAME);

    //hiding timer detials on main window for later use
    ui->chkTimer->setVisible(false);
    ui->lblTimer->setVisible(false);
    ui->sbAutoRefresh->setVisible(false);
    ui->lblSecTimer->setVisible(false);
    ui->btnStart->setVisible(false);
    ui->btnStop->setVisible(false);
     QStringList titles;
    ui->tableWidget->setColumnCount(8);
    titles<<"ID"<<"Device Name"<<"Protocol"<<"IP Address"<<"Attack Type"<<"Last Activity"<<"View Log"<<"Delete";
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    int colIndex = 0;
    ui->tableWidget->setColumnWidth(colIndex++, 25);
    ui->tableWidget->setColumnWidth(colIndex++, 230);
    ui->tableWidget->setColumnWidth(colIndex++, 130);
    ui->tableWidget->setColumnWidth(colIndex++, 130);
    ui->tableWidget->setColumnWidth(colIndex++, 130);
    ui->tableWidget->setColumnWidth(colIndex++, 300);
    ui->tableWidget->setColumnWidth(colIndex++, 80);
    ui->tableWidget->setColumnWidth(colIndex++, 50);
    ui->tableWidget->setColumnHidden(5,true);
    ui->tableWidget->setColumnHidden(0,true);
    //fillMainTable(threadMain.RefreshUseCase());
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionTopic_triggered()
{
    try {
    ViewTopics _ViewTopics;
    _ViewTopics.setModal(true);
    _ViewTopics.exec();
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_actionData_Profile_triggered()
{
    try {
    ViewDataProfile _ViewDataProfile;
    _ViewDataProfile.setModal(true);
    _ViewDataProfile.exec();
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_actionTime_Profile_triggered()
{
    try{
    ViewTimeProfile _ViewTimeProfile;
    _ViewTimeProfile.setModal(true);
    _ViewTimeProfile.exec();
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_actionDevice_Template_triggered()
{
    try{
    frmNewDeviceTemplateView _frmNewDeviceTemplateView;
    _frmNewDeviceTemplateView.setModal(true);
    _frmNewDeviceTemplateView.exec();
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::fillMainTable(QString _QString){
    //ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    if(_QString == "")
        return;
    QStringList rowsList = _QString.split(";");
    int r,g,b;
    foreach(QString row, rowsList)
    {
        QStringList col = row.split(",");
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowIndex=ui->tableWidget->rowCount()-1;
        int colIndex = 0;
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[0]));
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[0]));//device name
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[1]));//protocol
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[2]));//ip
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[3]));//attack type
        ui->tableWidget->setItem(rowIndex, colIndex++, new QTableWidgetItem(col[4]));//last activity

        QPushButton *view = new QPushButton("",this);
        view->setFixedWidth(80);
        view->setFixedHeight(30);
        QPixmap pixmapView(_constants.PATH_VIEWICON);
        QIcon ViewButtonIcon(pixmapView);
        view->setIcon(ViewButtonIcon);
        view->setIconSize(QSize(30, 20));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,6,view);
        connect(view, &QPushButton::clicked, this, &MainWindow::viewLog);

        QPushButton *del = new QPushButton("",this);
        del->setFixedWidth(50);
        del->setFixedHeight(30);
        QPixmap pixmapDel(_constants.PATH_DELETEICON);
        QIcon DelButtonIcon(pixmapDel);
        del->setIcon(DelButtonIcon);
        del->setIconSize(QSize(30, 20));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,7,del);
        connect(del, &QPushButton::clicked, this, &MainWindow::deleteDevice);
    }
}

void MainWindow::viewLog(){
    int row = ui->tableWidget->currentRow();
    QString deviceIP = ui->tableWidget->item(row,colIP)->text();
    QString deviceLog = threadMain.ViewDeviceData(deviceIP);

     frmViewLog _frmViewLog;
    _frmViewLog.setModal(true);
    _frmViewLog.ui->txtLog->setText(deviceLog);
    _frmViewLog.exec();

}
void MainWindow::deleteDevice(){
     try{
    int row = ui->tableWidget->currentRow();
    threadMain.DeleteDevice(ui->tableWidget->item(row,colIP)->text());
     on_btnRefresh_clicked();
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}
void MainWindow:: myFunction3() {

    threadMain.CreateDevices(_objDevice);
    on_btnRefresh_clicked();

}
void MainWindow::on_actionNew_Device_triggered()
{
    try{

    if(useCaseName.isEmpty())
    {
        frmSaveUseCase _frmSaveUseCase;
        _frmSaveUseCase.setModal(true);
        if(_frmSaveUseCase.exec() == QDialog::Accepted)
        {
            objUseCase _objUseCase;
            useCaseName = _objUseCase.name;
            useCaseID = _objUseCase._id;
            ui->ucNameLabel->setText(useCaseName);
        }
    }

if(!useCaseName.isEmpty())
{


    frmNewDeviceTemplate myNewDevice(this,"NEWDEVICE");
    myNewDevice.setModal(true);
    if(myNewDevice.exec() == QDialog::Accepted)
    {
        myNewDevice._objDevice.useCaseID = useCaseID;
        //_objDevice= myNewDevice._objDevice;

          threadMain.CreateDevices(myNewDevice._objDevice);
          on_btnRefresh_clicked();


    }
 }
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_actionLoad_triggered()
{
    try{
    frmLoadUseCase _frmLoadUseCase(this, "useCases");
    _frmLoadUseCase.setModal(true);
    if(_frmLoadUseCase.exec() == QDialog::Accepted)
    {
        on_btnClear_clicked();
        if(threadMain.LoadUseCase(_frmLoadUseCase._useCaseId))
        {
            dlUseCase _dlUseCase;
            objUseCase _objUseCase= _dlUseCase.GetUseCaseByID(_frmLoadUseCase._useCaseId);
            useCaseID = _objUseCase._id;
            useCaseName = _objUseCase.name;
            ui->ucNameLabel->setText(useCaseName);
            on_btnRefresh_clicked();
            QMessageBox::information(this, tr(""), tr("Successfully loaded."));

        }
        else
        {
            QMessageBox::information(this, tr(""), tr("Problem occured while loading."));

        }
    }
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_btnClear_clicked()
{
    try{
        if(threadMain.ClearUseCase())
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            ui->ucNameLabel->clear();
            useCaseID  = 0;
            useCaseName= "";
        }
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_btnRefresh_clicked()
{
    try{
    fillMainTable(threadMain.RefreshUseCase());
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
    }

void MainWindow::on_checkBox_clicked()
{
    /*   Uncomment if timer on main screen on
    if(ui->chkTimer->isChecked() && (ui->sbAutoRefresh->value() == 0)){
        QMessageBox::critical(this, tr("Error"), tr("Auto Refresh time must be greater than 0"));
        ui->chkTimer->setChecked(false);
        return;
    }

    if(ui->chkTimer->isChecked()){
        connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(RefreshTimerTick()));
        refreshTimer.start(1000*(ui->sbAutoRefresh->value()));
    }
    else{
        refreshTimer.disconnect();
    }
    */
}

void MainWindow::RefreshTimerTick(){
    //fillMainTable(threadMain.RefreshUseCase());
}

void MainWindow::on_btnStart_clicked()
{
    try{
    threadMain.StartUsecase(ui->tableWidget->rowCount());
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
}

void MainWindow::on_btnStop_clicked()
{
    try{
    threadMain.StopUsecase(ui->tableWidget->rowCount());
    } catch (std::exception &e) {
            msgBox.setText(e.what());
            msgBox.exec();
        } catch (...) {
            msgBox.setText("Problem occured");
            msgBox.exec();
        }
 }

void MainWindow::on_actionNew_triggered()
{
    /*
    frmSaveUseCase _frmSaveUseCase;
    _frmSaveUseCase.setModal(true);
    if(_frmSaveUseCase.exec() == QDialog::Accepted)
    {
        QString _useCaseName = _frmSaveUseCase.ui->txtName->text();
        dlUseCase _dlUseCase;
        objUseCase _objUseCase;
        _objUseCase.name = _useCaseName;
        useCaseID = _dlUseCase.Insert(_objUseCase);
        useCaseName = _useCaseName;
        ui->ucNameLabel->setText(_useCaseName);
    }
    */

}
