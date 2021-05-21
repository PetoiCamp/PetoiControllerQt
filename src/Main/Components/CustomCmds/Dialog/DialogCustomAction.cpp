#include "DialogCustomAction.h"
#include "ui_DialogCustomAction.h"
#include "src/Main/MainWindow.h"

#include <QDebug>


DialogCustomAction::DialogCustomAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomActions)
{
    ui->setupUi(this);

    // connect SIGNAL/SLOT
    QObject* acceptBtn = (QObject*)ui->buttonBox->button(QDialogButtonBox::Ok);
    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnPressed()));

    // set default status to add item
    currentStatus = ::AddItem;
}


DialogCustomAction::~DialogCustomAction()
{
    delete ui;

    QObject* acceptBtn = (QObject*)ui->buttonBox->button(QDialogButtonBox::Ok);
    disconnect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnPressed()));

}


void DialogCustomAction::setDialogValues(DialogCustomStatus changeStatus,
                                          int id,
                                          QString name,
                                          QString cmd) {
    currentStatus = changeStatus;
    itemId = id;

    // set name and command
    ui->lineEditCommand->setText(cmd);
    ui->lineEditName->setText(name);
};


void DialogCustomAction::onOkBtnPressed() {

    lineName = ui->lineEditName->text();
    lineCommand  = ui->lineEditCommand->text();

    if (currentStatus == ::AddItem) {

        addNewItem(lineName, lineCommand);

    } else if (currentStatus == ::ModifyItem) {

        modifyItem(itemId, lineName, lineCommand);
    }

    MainWindow::uiCustomActions.updateViewTable();
}


void DialogCustomAction::addNewItem(
        QString name,
        QString cmd) {

    QPair<QString, QString> pair(name, cmd);
    MainWindow::uiCustomActions.actions.push_back(pair);
}


void DialogCustomAction::modifyItem(
        int id,
        QString name,
        QString cmd) {

    MainWindow::uiCustomActions.actions[id].first = name;
    MainWindow::uiCustomActions.actions[id].second = cmd;
}
