#ifndef DIALOG_2_H
#define DIALOG_2_H
#include "dialog.h"
#include <QDialog>

namespace Ui {
class Dialog_2;
}

class Dialog_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_2(QWidget *parent = nullptr);
    ~Dialog_2();

public:
    Ui::Dialog_2 *ui;
public slots:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Dialog *newDialog;
};

#endif // DIALOG_2_H
