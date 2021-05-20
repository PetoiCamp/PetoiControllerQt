#ifndef DIALOGCUSTOMACTIONS_H
#define DIALOGCUSTOMACTIONS_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogCustomActions;
}

enum DialogCustomStatus {
    AddItem,
    ModifyItem,
};

class DialogCustomActions : public QDialog
{
    Q_OBJECT

    DialogCustomStatus currentStatus;

public:
    explicit DialogCustomActions(QWidget *parent = nullptr);

    ~DialogCustomActions();

    void setDialogStatus(DialogCustomStatus changeStatus,
            QString name = "", QString cmd = "");

private:
    Ui::DialogCustomActions *ui;
};

#endif // DIALOGCUSTOMACTIONS_H
