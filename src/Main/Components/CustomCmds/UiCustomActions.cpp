#include "UiCustomActions.h"
#include "src/Config/GlobalConfig.h"
#include "src/Main/MainWindow.h"

#include <QStringList>
#include <QDebug>
#include <QPushButton>


UiCustomActions::UiCustomActions(QObject *parent) :
    QObject(parent)
{
    if (theModel == nullptr) {
        theModel = new QStandardItemModel();
    }
}

UiCustomActions::~UiCustomActions() {

    if (theModel) { // delete data
        delete  theModel;
    }

    if (dialog) {
        delete dialog;
    }
}

void UiCustomActions::setupViewTable(QTableView *view) {

    if (view == nullptr) { return;
    } else {
        theView = view;
        theView->setModel(theModel);

        // clear all
        theModel->clear();

        // scroll bar off
        theView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    // load json file
//    petoi::loadJson(handler, FRAMES_FILE);

    // setup list table
    updateViewTable();

    // setup dialogs
    if (dialog == nullptr) {
        dialog = new DialogCustomActions;
    }

    // scroll bar off
    theView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    theView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // disable user-editing
    theView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void UiCustomActions::setupControlPanel(
        QPushButton* btnAdd,
        QPushButton* btnDel,
        QPushButton* btnSave) {

    // connect signals and slots
    connect(btnAdd, SIGNAL(clicked(bool)), this, SLOT(onAddCommand()));
    connect(btnDel, SIGNAL(clicked(bool)), this, SLOT(onDeleteCommand()));
    connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveCommand()));
}


void UiCustomActions::updateViewTable() {

    // set columns
    QStringList columnTitles;
    columnTitles << "id" << "name" << "command" << "send" << "edit";
    theModel->setHorizontalHeaderLabels(columnTitles);

    // get contents
//    std::vector<std::string> entities =
//            handler.get_multi_json_lists("actions");

//    for (size_t i = 0; i < entities.size(); i++) {
//        // parse json string
//        JsonHandler item;
//        item.from_json(entities[i]);

//        // set name and command
//        auto name = item.has_item("name") ? item.get_string("name") : "unknown";
//        auto cmd = item.has_item("cmd") ? item.get_string("cmd") : "";

//        // add send button
//        auto sendBtn = addSendBtnToTableview(i, item);

//        // add edit button
//        auto editBtn = addEditBtnToTableview(i, item);

//        // set column
//        theModel->setItem(i, 0, new QStandardItem(QString::number(i)));
//        theModel->setItem(i, 1, new QStandardItem(QString(name)));
//        theModel->setItem(i, 2, new QStandardItem(QString(cmd)));

//        // insert button to last line
//        theView->setIndexWidget(theModel->index(i, 3), sendBtn);
//        theView->setIndexWidget(theModel->index(i, 4), editBtn);
//    }
}


QPushButton* UiCustomActions::addSendBtnToTableview(int id, JsonHandler& item) {
    // set name and command
    auto name = item.has_item("name") ? item.get_string("name") : "unknown";
    auto cmd = item.has_item("cmd") ? item.get_string("cmd") : "";

    // add button to the column
    QPushButton *button = new QPushButton("Send");

    // set button's properties
    button->setProperty("cmd", cmd);
    button->setProperty("name", name);
    button->setProperty("id", id);

    // click event
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onSendCommand()));

    // return
    return button;
};


QPushButton* UiCustomActions::addEditBtnToTableview(int id, JsonHandler& item) {
    // set name and command
    auto name = item.has_item("name") ? item.get_string("name") : "unknown";
    auto cmd = item.has_item("cmd") ? item.get_string("cmd") : "";

    // add button to the column
    QPushButton *button = new QPushButton("Edit");

    // set button's properties
    button->setProperty("cmd", cmd);
    button->setProperty("name", name);
    button->setProperty("id", id);

    // click event
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onModifyCommand()));

    // return
    return button;
};


void UiCustomActions::onSendCommand() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString cmd = btn->property("cmd").toString();

    MainWindow::uiSerialHandler.sendCmdViaSerialPort(cmd);
}


void UiCustomActions::onAddCommand() {
    qDebug() << "onAddCommand";
    //TODO
    dialog->setDialogStatus(::AddItem);
    dialog->show();
}


void UiCustomActions::onDeleteCommand() {
    qDebug() << "onDeleteCommand";
    //TODO
}


void UiCustomActions::onModifyCommand() {
    qDebug() << "onModifyCommand";

    // get values from sender
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString cmd = btn->property("cmd").toString();
    QString name = btn->property("name").toString();
    int id = btn->property("id").toInt();

    dialog->setDialogStatus(::ModifyItem, id, name, cmd);
    dialog->show();
}


void UiCustomActions::onSaveCommand() {
//    qDebug() << "onSaveCommand";
//    petoi::saveJson(handler, FRAMES_FILE);
}
