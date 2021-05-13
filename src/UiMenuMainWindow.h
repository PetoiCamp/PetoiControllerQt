#ifndef UIMENUMAINWINDOW_H
#define UIMENUMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>


class UiMenuWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit UiMenuWindow(QWidget *parent = nullptr);

    ~UiMenuWindow();

    /**
     * @brief setMainWindowFileMenuItems
     * @param parent
     * @return
     */
    QMenu* setMainWindowFileMenuItems();


private:
    void translateUi(const char *package);


protected slots:

    /**
     * @brief onFileExit
     */
    void onFileExit();

    /**
     * @brief onFileShowChn
     */
    void onFileShowChn();

    /**
     * @brief onFileShowEng
     */
    void onFileShowEng();

private:

    /// File ///
    QMenu *fileMenu;
    QMenu *fileLinguistMenu;

    QAction *chineseTypeAct;
    QAction *englishTypeAct;
    QAction *exitAct;

};

#endif // UIMENUMAINWINDOW_H
