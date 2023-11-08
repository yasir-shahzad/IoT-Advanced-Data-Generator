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
#include "topics.h"
#include "dataprofile.h"
#include "timeprofile.h"
#include <QApplication>
#include "viewtopics.h"
#include "viewdataprofile.h"
#include "viewtimeprofile.h"
#include "qdir.h"
#include<frmnewdevice.h>
#include<frmkeyvalue.h>
#include<qstring.h>
static QString PATH_EDITICON;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir dir(".");
    PATH_EDITICON= dir.absolutePath()+"/edit-icon.png";




    //frmnewDevice w;
    //FrmKeyValue w;
    MainWindow w;
    //Topics w;
    //DataProfile w;
    //TimeProfile w;
    //ViewTopics w;
    //ViewDataProfile w;
    //ViewTimeProfile w;
    w.show();

    return a.exec();
}



//QString PATH_DELETEICON = dir.absolutePath()+"/delete-icon.png";
//QString PATH_VIEWICON = dir.absolutePath()+"/view-icon.png";
