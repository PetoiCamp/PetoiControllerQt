#include "QtBasics.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include <QtGlobal>


QGraphicsScene* QtBasics::loadImageFromRes(const char *path, int width, int height,
                                           Qt::AspectRatioMode mode) {

    // load image from file
    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap pixels(path);

    // adjust image size
    QPixmap scaled = pixels.scaled(width, height, mode);

    // apply to the image
    scene->addPixmap(scaled);

    return scene;
};


QString QtBasics::loadFile(const QString file) {
    QFile qzFile(file);
    QString context = "";

    if (qzFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&qzFile);

        // load all context from the file
        context = in.readAll();
    }

    qzFile.close();
    return context;
};


void QtBasics::saveFile(const QString file, const QString context) {
    QFile qzFile(file);

    if (qzFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&qzFile);
        out << context;
    }

    qzFile.close();
};


bool QtBasics::exists(const QString path) {
    QFileInfo info(path);
    bool flag = info.exists();
    return flag;
};


bool QtBasics::isFile(const QString path) {
    QFileInfo info(path);
    bool flag1 = info.isFile();
    bool flag2 = exists(path);
    return flag1 && flag2;
};


bool QtBasics::isPath(const QString path) {
    QFileInfo info(path);
    return info.isDir() && exists(path);
};


void QtBasics::mkdir(const QString path) {
    QDir dir;

    if (!exists(path)) {
        dir.mkdir(path);
    }
};


void QtBasics::touch(const QString path) {
    QDir dir(path);

    // if root path is not exist
    auto trunk_path = trunk(path);
    if (!exists(trunk_path)) {
        mkdir(trunk_path);
    }

    // if file not exist, then create a new one
    QFile file(path);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
    }

    // close to create a new file
    file.close();
};


QString QtBasics::trunk(const QString path) {
    QFileInfo fi(path);

    return fi.path();
};
