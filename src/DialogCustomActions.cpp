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
                                          QString name, QString cmd) {
    currentStatus = changeStatus;

    // set name and command
    ui->lineEditCommand->setText(cmd);
    ui->lineEditName->setText(name);
};


void DialogCustomActions::onOkBtnPressed() {

    // get items from json file
    std::vector<std::string> entities =
            MainWindow::uiCustomActions.handler
                .get_multi_json_lists("actions");

    QString name = ui->lineEditName->text();
    QString cmd  = ui->lineEditCommand->text();

    if (currentStatus == ::AddItem) {
        JsonHandler item;
        item.set_string("name", name.toStdString());
        item.set_string("cmd", cmd.toStdString());

        entities.push_back(item.to_str());
    } else if (currentStatus == ::ModifyItem) {
        for (size_t i = 0; i < entities.size(); i++) {
            JsonHandler item;
            item.from_json(entities[i]);

            QString qname = QString(item.get_string("name"));
            if (qname == name) {
                item.set_string("cmd", cmd.toStdString());
            }

            entities[i] = item.to_str();
            break;
        }
    }

    // clear all
    MainWindow::uiCustomActions.handler.clear();

    // set new json string
    MainWindow::uiCustomActions.handler.set_multi_json_lists("actions", entities);

    for (auto iter = entities.begin(); iter != entities.end(); iter++) {
        qDebug() << QString(iter->c_str());
    }

    qDebug() << MainWindow::uiCustomActions.handler.to_str().c_str();

    // refresh table
//    MainWindow::uiCustomActions.updateViewTable();
}
