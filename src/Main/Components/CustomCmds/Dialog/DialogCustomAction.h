#ifndef DIALOGCUSTOMACTION_H
#define DIALOGCUSTOMACTION_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QPair>

namespace Ui {
class DialogCustomActions;
}

enum DialogCustomStatus {
    AddItem,
    ModifyItem,
};

class DialogCustomAction : public QDialog
{
    Q_OBJECT

    DialogCustomStatus currentStatus;
    QString lineName;
    QString lineCommand;
    int     itemId;

public:
    explicit DialogCustomAction(QWidget *parent = nullptr);

    ~DialogCustomAction();

    /**
     * @brief setDialogStatus
     * @param changeStatus
     * @param id
     * @param name
     * @param cmd
     */
    void setDialogValues(DialogCustomStatus changeStatus,
            int id = 0,
            QString name = "",
            QString cmd = "");

    
private:

    void addNewItem(
        QString name, 
        QString cmd);

    void modifyItem(
        int id, 
        QString name, 
        QString cmd);

protected slots:

    void onOkBtnPressed();

private:
    Ui::DialogCustomActions *ui;
};

#endif // DIALOGCUSTOMACTION_H
