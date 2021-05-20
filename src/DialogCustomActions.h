#ifndef DIALOGCUSTOMACTIONS_H
#define DIALOGCUSTOMACTIONS_H

#include <QDialog>

namespace Ui {
class DialogCustomActions;
}

class DialogCustomActions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCustomActions(QWidget *parent = nullptr);
    ~DialogCustomActions();

private:
    Ui::DialogCustomActions *ui;
};

#endif // DIALOGCUSTOMACTIONS_H
