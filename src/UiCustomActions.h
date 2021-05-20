#ifndef UICUSTOMACTIONS_H
#define UICUSTOMACTIONS_H

#include <QObject>
#include <QDialog>

#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "src/Config/JsonHandler.h"
#include "src/DialogCustomActions.h"


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
     * @brief updateViewTable
     */
    void updateViewTable();


    /**
     * @brief setupControlPanel
     * @param btnAdd
     * @param btnDel
     * @param btnSave
     */
    void setupControlPanel(
            QPushButton* btnAdd, 
            QPushButton* btnDel, 
            QPushButton* btnSave);

    
    QPushButton* addSendBtnToTableview(JsonHandler& json);

    QPushButton* addEditBtnToTableview(JsonHandler& json);

public:
    JsonHandler handler;

private:
    QTableView*             theView;
    QStandardItemModel*     theModel;
    QItemSelectionModel*    theSelection;

private:
    DialogCustomActions*    dialog;

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

    /**
     * @brief onSaveCommand
     */
    void onSaveCommand();
};

#endif // UICUSTOMACTIONS_H
