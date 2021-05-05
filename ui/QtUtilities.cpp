#include "ui/QtUtilities.h"

QGraphicsScene* QtUtilities::loadImageFromRes(const char *path, int width, int height, Qt::AspectRatioMode mode) {
    // load image from file
    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap pixels(path);

    // adjust image size
    QPixmap scaled = pixels.scaled(width, height, mode);

    // apply to the image
    scene->addPixmap(scaled);

    return scene;
};
