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
#ifndef VIEWDATAPROFILE_H
#define VIEWDATAPROFILE_H
#include<constants.h>
#include <QDialog>
#include<qmessagebox.h>
namespace Ui {
class ViewDataProfile;
}

class ViewDataProfile : public QDialog
{
    Q_OBJECT
QMessageBox msgBox;
public:
    explicit ViewDataProfile(QWidget *parent = nullptr);
    ~ViewDataProfile();
    Constants  _constants;

private slots:
    void on_btnNewDataProfile_clicked();
    void deleteRow();
    void editRow();
    void bindData();

private:
    Ui::ViewDataProfile *ui;
    enum Colum
    {
        ID,
        DATA_PROFILE_LIST
    };
};

#endif // VIEWDATAPROFILE_H
