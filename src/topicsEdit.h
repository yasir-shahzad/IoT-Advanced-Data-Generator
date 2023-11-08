#ifndef TOPICS_H
#define TOPICS_H

#include <QDialog>

namespace Ui {
class TopicsEdit;
}

class TopicsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TopicsEdit(QWidget *parent = nullptr);
    ~TopicsEdit();

private slots:
    void on_btnAdd_clicked();

    void on_btnCancel_clicked();

    void on_btnSave_clicked();

private:
    Ui::TopicsEdit *ui;

    QStringList topicList;
};

#endif // TOPICS_H
