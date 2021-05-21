#ifndef UICUSTOMACTIONS_H
#define UICUSTOMACTIONS_H

#include <QObject>
#include <QDialog>

#include <QPair>
#include <QList>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "src/Json/JsonHandler.h"
#include "Dialog/DialogCustomAction.h"


class UiCustomActions : public QObject
{
    Q_OBJECT
public:

    explicit UiCustomActions(QObject *parent = nullptr);


    ~UiCustomActions();


    /**
     * @brief setupViewTable
     * @param view
     */
    void setupViewTable(QTableView* view);


    /**
     * @brief setupControlPanel
     * @param btnAdd
     */
    void setupControlPanel(QPushButton* btnAdd);


    /**
     * @brief updateViewTable
     */
    void updateViewTable();

private:
    QPushButton*
    createTableviewItemBtn(
        int id = 0,
        QString name = "",
        QString cmd = "");

public:
    QList<QPair<QString, QString>> actions;

private:
    QTableView*             theView;
    QStandardItemModel*     theModel;
    QItemSelectionModel*    theSelection;

private:
    DialogCustomAction*     dialog;

protected slots:

    /**
     * @brief onSendCommand
     */
    void onSendCommand();

    /**
     * @brief onAddCommand
     */
    void onAddCommand();

    /**
     * @brief onDeleteCommand
     */
    void onDeleteCommand();

    /**
     * @brief onModifyCommand
     */
    void onModifyCommand();
};

#endif // UICUSTOMACTIONS_H
