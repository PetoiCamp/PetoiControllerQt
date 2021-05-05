#ifndef QTUTILITIES_H
#define QTUTILITIES_H

#include <QObject>
#include <QGraphicsScene>

class QtUtilities
{
public:

    // load materials from qt resources
    static QGraphicsScene* loadImageFromRes(const char *path, int width, int height, Qt::AspectRatioMode=Qt::AspectRatioMode::KeepAspectRatio);

};

#endif // QTUTILITIES_H
