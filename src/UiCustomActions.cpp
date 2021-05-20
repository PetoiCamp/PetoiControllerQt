#include "UiCustomActions.h"
#include "src/Config/GlobalConfig.h"

#include <QStringList>
#include <QDebug>
#include <QPushButton>


UiCustomActions::UiCustomActions(QObject *parent) :
    QObject(parent),
    handler()
{
    if (theModel == nullptr) {
        theModel = new QStandardItemModel();
    }
}

UiCustomActions::~UiCustomActions() {

    if (theModel) {

        // delete data
        delete  theModel;
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
    petoi::loadJson(handler, FRAMES_FILE);

    // setup list table
    initTableView();
}


void UiCustomActions::setupControlPanel(QPushButton *btnAdd,
                                        QPushButton *btnDel,
                                        QPushButton* btnSave) {
    // connect signals and slots
    connect(btnAdd, SIGNAL(clicked(bool)), this, SLOT(onAddCommand()));
    connect(btnDel, SIGNAL(clicked(bool)), this, SLOT(onDeleteCommand()));
    connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveCommand()));
}


void UiCustomActions::initTableView() {

    // set columns
    QStringList columnTitles;
    columnTitles << "id" << "name" << "command" << "action";
    theModel->setHorizontalHeaderLabels(columnTitles);

    // get contents
    std::vector<std::string> entities =
            handler.get_multi_json_lists("actions");

    for (size_t i = 0; i < entities.size(); i++) {

        // parse json string
        JsonHandler item;
        item.from_json(entities[i]);

        // set name and command
        auto name = item.has_item("name") ? item.get_string("name") : "unknown";
        auto cmd = item.has_item("cmd") ? item.get_string("cmd") : "";

        // add button to the column
        QPushButton *button = new QPushButton("Send");

        // set button's properties
        button->setProperty("id", (int)i);
        button->setProperty("cmd", cmd);

        // click event
        connect(button, SIGNAL(clicked(bool)), this, SLOT(onSendCommand()));

        // set column
        theModel->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        theModel->setItem(i, 1, new QStandardItem(QString(name)));
        theModel->setItem(i, 2, new QStandardItem(QString(cmd)));

        // insert button to last line
        theView->setIndexWidget(theModel->index(i, 3), button);
    }

    // scroll bar off
    theView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    theView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // disable user-editing
    theView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void UiCustomActions::onSendCommand() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString cmd = btn->property("cmd").toString();

    qDebug() << cmd;
}


void UiCustomActions::onAddCommand() {
    qDebug() << "onAddCommand";
}


void UiCustomActions::onDeleteCommand() {
    qDebug() << "onDeleteCommand";
}


void UiCustomActions::onModifyCommand() {
    qDebug() << "onModifyCommand";
}


void UiCustomActions::onSaveCommand() {
    qDebug() << "onSaveCommand";
    petoi::saveJson(handler, FRAMES_FILE);
}
