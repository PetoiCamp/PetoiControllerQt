#ifndef UICUSTOMACTIONS_H
#define UICUSTOMACTIONS_H

#include <QObject>

#include <QTableView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "src/Config/JsonHandler.h"


class UiCustomActions : public QObject
{
    Q_OBJECT
public:
    explicit UiCustomActions(QObject *parent = nullptr);

    ~UiCustomActions();

    void setupWidgets(QTableView* view);

private:
    JsonHandler handler;

    QTableView*            theView;
    QStandardItemModel*    theModel;
    QItemSelectionModel*   theSelection;

protected slots:
    void onSendCmdPressed();

private:
    void initTableView();
};

#endif // UICUSTOMACTIONS_H
