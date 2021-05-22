#include "UiCustomActions.h"
#include "src/Config/GlobalConfig.h"
#include "src/Main/MainWindow.h"
#include "JsonParementer.h"

#include <QStringList>
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QHBoxLayout>


UiCustomActions::UiCustomActions(QObject *parent) :
    QObject(parent)
{
    if (theModel == nullptr) {
        theModel = new QStandardItemModel();
    }

    // try to load records from json file
    actions = JsonParementer::loadCommands();
}

UiCustomActions::~UiCustomActions() {

    if (theModel) { // delete data
        delete  theModel;
    }

//    if (dialog) {
//        delete dialog;
//    }

    // save updated records to json file
    JsonParementer::saveCommands(actions);
}

void UiCustomActions::setupViewTable(QTableView *view) {

    if (view == nullptr) { return;
    } else {
        theView = view;
        theView->setModel(theModel);

        // scroll bar off
        theView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    // setup list table
    updateViewTable();

    // setup dialogs
    if (dialog == nullptr) {
        dialog = new DialogCustomAction;
    }

    // scroll bar off
    theView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    theView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // disable user-editing
    theView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void UiCustomActions::setupControlPanel(
        QPushButton* btnAdd) {

    // connect signals and slots
    connect(btnAdd, SIGNAL(clicked(bool)), this, SLOT(onAddCommand()));
}


void UiCustomActions::updateViewTable() {
    // clear all
    theModel->clear();

    // set columns
    QStringList columnTitles;
    columnTitles << "Id" << "Name" << "Content" << "Options";
    theModel->setHorizontalHeaderLabels(columnTitles);

    // get contents
    int i = 0;
    for (auto iter = actions.begin();
         iter != actions.end(); iter++, i++) {

        // set columns
        theModel->setItem(i, 0, new QStandardItem(QString::number(i)));
        theModel->setItem(i, 1, new QStandardItem(iter->first));
        theModel->setItem(i, 2, new QStandardItem(iter->second));

        // the item's related buttons
        auto sendBtn = createTableviewItemBtn(i, "Send", iter->first, iter->second);
        auto editBtn = createTableviewItemBtn(i, "Edit", iter->first, iter->second);
        auto deltBtn = createTableviewItemBtn(i, "Delete", iter->first, iter->second);

        // add buttons to the table's row
        QWidget* temp = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(temp);
        layout->addWidget(sendBtn);
        layout->addWidget(editBtn);
        layout->addWidget(deltBtn);
        layout->setMargin(0);
        theView->setIndexWidget(theModel->index(i, 3), temp); // may cause mem leaks?

        // connect
        connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendCommand()));
        connect(editBtn, SIGNAL(clicked(bool)), this, SLOT(onModifyCommand()));
        connect(deltBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteCommand()));
    }

    // auto-fit
    theView->resizeColumnsToContents();
}


QPushButton*
UiCustomActions::createTableviewItemBtn(
        int id,
        QString btn,
        QString name,
        QString cmd) {

    // add button to the column
    QPushButton *button = new QPushButton(btn);

    // store some values to button's property
    button->setProperty("cmd", cmd);
    button->setProperty("name", name);
    button->setProperty("id", id);

    // return to caller
    return button;
};


void UiCustomActions::onSendCommand() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString cmd = btn->property("cmd").toString();

    MainWindow::uiSerialHandler.sendCmdViaSerialPort(cmd);
}


void UiCustomActions::onAddCommand() {
    dialog->setDialogValues(::AddItem);
    dialog->show();
}


void UiCustomActions::onDeleteCommand() {

    // get values from the button's property
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int id = btn->property("id").toInt();

    // remove item by id
    actions.removeAt(id);

    // reload the table
    updateViewTable();
}


void UiCustomActions::onModifyCommand() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    int id = btn->property("id").toInt();
    QString cmd = btn->property("cmd").toString();
    QString name = btn->property("name").toString();

    dialog->setDialogValues(::ModifyItem, id, name, cmd);
    dialog->show();
}
