#ifndef UICUSTOMACTIONS_H
#define UICUSTOMACTIONS_H

#include <QObject>

#include <QPushButton>
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


    /**
     * @brief setupViewTable
     * @param view
     */
    void setupViewTable(QTableView* view);


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

private:
    JsonHandler handler;

    QTableView*            theView;
    QStandardItemModel*    theModel;
    QItemSelectionModel*   theSelection;

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

private:

    /**
     * @brief initTableView
     */
    void initTableView();
};

#endif // UICUSTOMACTIONS_H
