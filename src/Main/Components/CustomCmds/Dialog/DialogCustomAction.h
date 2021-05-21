#ifndef DIALOGCUSTOMACTION_H
#define DIALOGCUSTOMACTION_H

#include <QDialog>
#include <QString>

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

    void setDialogStatus(DialogCustomStatus changeStatus,
            int id = 0,
            QString name = "",
            QString cmd = "");

    
    std::vector<std::string> addNewItem(QString name, QString cmd);


    std::vector<std::string> modifyItem(int id, QString name, QString cmd);

protected slots:

    void onOkBtnPressed();

private:
    Ui::DialogCustomActions *ui;
};

#endif // DIALOGCUSTOMACTION_H
