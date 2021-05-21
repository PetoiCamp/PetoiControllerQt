#include "DialogCustomAction.h"
#include "ui_DialogCustomAction.h"
#include "src/Main/MainWindow.h"

#include <QDebug>


DialogCustomAction::DialogCustomAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomActions)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Apply);

    QObject* acceptBtn = (QObject*)ui->buttonBox->button(QDialogButtonBox::Ok);
    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnPressed()));

    currentStatus = ::AddItem;
}


DialogCustomAction::~DialogCustomAction()
{
    delete ui;
}


void DialogCustomAction::setDialogStatus(DialogCustomStatus changeStatus,
                                          int id,
                                          QString name,
                                          QString cmd) {
    currentStatus = changeStatus;

    // set name and command
    ui->lineEditCommand->setText(cmd);
    ui->lineEditName->setText(name);

    itemId = id;
};


void DialogCustomAction::onOkBtnPressed() {

    lineName = ui->lineEditName->text();
    lineCommand  = ui->lineEditCommand->text();

    std::vector<std::string> entities;

    if (currentStatus == ::AddItem) {

        entities = addNewItem(lineName, lineCommand);

    } else if (currentStatus == ::ModifyItem) {

        entities = modifyItem(itemId, lineName, lineCommand);

    }

    // clear all
//    MainWindow::uiCustomActions.handler.clear();

    // set new json string
//    MainWindow::uiCustomActions.handler.set_multi_json_lists("actions", entities);

    // refresh table
    MainWindow::uiCustomActions.updateViewTable();
}


std::vector<std::string> DialogCustomAction::addNewItem(QString name, QString cmd) {
    // get items from json file
//    std::vector<std::string> entities =
//            MainWindow::uiCustomActions.handler
//                .get_multi_json_lists("actions");

//    JsonHandler item;
//    item.set_string("name", name.toStdString());
//    item.set_string("cmd", cmd.toStdString());

//    entities.push_back(item.to_str());

//    return entities;
    return std::vector<std::string>();
}


std::vector<std::string> DialogCustomAction::modifyItem(int id, QString name, QString cmd) {
    // get items from json file
//    std::vector<std::string> entities =
//            MainWindow::uiCustomActions.handler
//                .get_multi_json_lists("actions");

//    JsonHandler item;
//    item.set_string("name", name.toStdString());
//    item.set_string("cmd", cmd.toStdString());

//    entities[id] = item.to_str();

//    return entities;
    return std::vector<std::string>();
}
