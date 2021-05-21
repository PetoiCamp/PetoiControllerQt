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
#include "src/Main/Components/CustomCmds/DialogCustomActions.h"


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

    
    QPushButton* addSendBtnToTableview(int id, JsonHandler& json);

    QPushButton* addEditBtnToTableview(int id, JsonHandler& json);

public:
    QList<QPair<QString, QString>> actions;

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
