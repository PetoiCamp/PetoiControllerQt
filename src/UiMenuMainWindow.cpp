#include "UiMenuMainWindow.h"
#include "MainWindow.h"
#include <QMenuBar>
#include <QTranslator>
#include <QDebug>


UiMenuWindow::UiMenuWindow(QWidget *parent) : QWidget(parent)
{

}


UiMenuWindow::~UiMenuWindow() {

}


void UiMenuWindow::onFileExit() {
    exit(0);
};


void UiMenuWindow::onFileShowChn() {
    translateUi(":/Chinese.qm");
};


void UiMenuWindow::translateUi(const char *package) {
    static QTranslator* translator;
    if (translator != NULL)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = NULL;
    }
    translator = new QTranslator;

    if (translator->load(package))
    {
        qApp->installTranslator(translator);
    }

    qDebug() << "language package file path: " << package;
    ui->retranslateUi(this);
}


void UiMenuWindow::onFileShowEng() {

};


QMenu* UiMenuWindow::setMainWindowFileMenuItems() {

    fileMenu = new QMenu(tr("&File"), this);
    fileLinguistMenu = new QMenu(tr("&Language"), this);

    chineseTypeAct = new QAction(tr("&Chinese"),this);   chineseTypeAct->setShortcut(tr("Ctrl+["));
    englishTypeAct = new QAction(tr("&English"), this);  englishTypeAct->setShortcut(tr("Ctrl+]"));

    fileLinguistMenu->addAction(chineseTypeAct);
    fileLinguistMenu->addAction(englishTypeAct);

    exitAct = new QAction(tr("&Exit"), this); exitAct->setShortcut(tr("Ctrl+Q"));

    fileMenu->addMenu(fileLinguistMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    return fileMenu;
}
