#include "DialogCustomActions.h"
#include "ui_DialogCustomActions.h"

DialogCustomActions::DialogCustomActions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomActions)
{
    ui->setupUi(this);
}


DialogCustomActions::~DialogCustomActions()
{
    delete ui;
}


void DialogCustomActions::setDialogStatus(DialogCustomStatus changeStatus,
                                          QString name, QString cmd) {
    currentStatus = changeStatus;

    // set name and command
    ui->lineEditCommand->setText(cmd);
    ui->lineEditName->setText(name);
};
