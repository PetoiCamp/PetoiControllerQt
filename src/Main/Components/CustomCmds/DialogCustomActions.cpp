#include "DialogCustomActions.h"
#include "ui_DialogCustomActions.h"
#include "MainWindow.h"

#include <QDebug>


DialogCustomActions::DialogCustomActions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomActions)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Apply);

    QObject* acceptBtn = (QObject*)ui->buttonBox->button(QDialogButtonBox::Ok);
    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnPressed()));

    currentStatus = ::AddItem;
}


DialogCustomActions::~DialogCustomActions()
{
    delete ui;
}


void DialogCustomActions::setDialogStatus(DialogCustomStatus changeStatus,
                                          int id,
                                          QString name,
                                          QString cmd) {
    currentStatus = changeStatus;

    // set name and command
    ui->lineEditCommand->setText(cmd);
    ui->lineEditName->setText(name);

    itemId = id;
};


void DialogCustomActions::onOkBtnPressed() {

    lineName = ui->lineEditName->text();
    lineCommand  = ui->lineEditCommand->text();

    std::vector<std::string> entities;

    if (currentStatus == ::AddItem) {

        entities = addNewItem(lineName, lineCommand);

    } else if (currentStatus == ::ModifyItem) {

        entities = modifyItem(itemId, lineName, lineCommand);

    }

    // clear all
    MainWindow::uiCustomActions.handler.clear();

    // set new json string
    MainWindow::uiCustomActions.handler.set_multi_json_lists("actions", entities);

    // refresh table
    MainWindow::uiCustomActions.updateViewTable();
}


std::vector<std::string> DialogCustomActions::addNewItem(QString name, QString cmd) {
    // get items from json file
    std::vector<std::string> entities =
            MainWindow::uiCustomActions.handler
                .get_multi_json_lists("actions");

    JsonHandler item;
    item.set_string("name", name.toStdString());
    item.set_string("cmd", cmd.toStdString());

    entities.push_back(item.to_str());

    return entities;
}


std::vector<std::string> DialogCustomActions::modifyItem(int id, QString name, QString cmd) {
    // get items from json file
    std::vector<std::string> entities =
            MainWindow::uiCustomActions.handler
                .get_multi_json_lists("actions");

    JsonHandler item;
    item.set_string("name", name.toStdString());
    item.set_string("cmd", cmd.toStdString());

    entities[id] = item.to_str();

    return entities;
}
