#ifndef DIALOGCUSTOMACTIONS_H
#define DIALOGCUSTOMACTIONS_H

#include <QDialog>

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

    void setDialogStatus(DialogCustomStatus changeStatus);


private:
    Ui::DialogCustomActions *ui;
};

#endif // DIALOGCUSTOMACTIONS_H
