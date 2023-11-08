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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<constants.h>
#include<threadmain.h>
#include<objdevice.h>
#include<QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    QMessageBox msgBox;
    Constants  _constants;
    ThreadMain threadMain;
    QTimer refreshTimer;
    objDevice _objDevice;
    QString useCaseName = "";
    int useCaseID = -1;
    int colIP = 3;
void myFunction3();

private slots:
    void on_actionTopic_triggered();

    void on_actionData_Profile_triggered();

    void on_actionTime_Profile_triggered();

    void on_actionDevice_Template_triggered();

    void fillMainTable(QString _QString);

    void viewLog();
    void deleteDevice();


//void on_actionUDP_Flood_triggered();

    void on_actionNew_Device_triggered();

    //void on_actionSave_triggered();

   // void on_actionSave_As_triggered();

    void on_actionLoad_triggered();

    void on_btnClear_clicked();

    void on_btnRefresh_clicked();

    //void on_checkBox_stateChanged(int arg1);
    void RefreshTimerTick();

    void on_checkBox_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    enum Colum
    {
        ID,
        IP,
        PROTOCOL,
        STATUS,
        VIEW,
        DELETE
    };
};

#endif // MAINWINDOW_H
