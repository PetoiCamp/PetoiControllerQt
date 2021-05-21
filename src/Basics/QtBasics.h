#ifndef QtBasics_h
#define QtBasics_h

#include <QObject>
#include <QString>
#include <QGraphicsScene>

class QtBasics
{
public:

    // load materials from qt resources
    static QGraphicsScene* loadImageFromRes(const char *path, int width, int height,
                                            Qt::AspectRatioMode=Qt::AspectRatioMode::KeepAspectRatio);

    // load string context from a file
    static QString loadFile(const QString file);

    // save string context to a file
    static void saveFile(const QString file, const QString context);

    // test if file/folder exists
    static bool exists(const QString path);

    // whether path is a file
    static bool isFile(const QString path);

    // whether path is a folder
    static bool isPath(const QString path);

    // mkdir
    static void mkdir(const QString path);

    // touch
    static void touch(const QString path);

    // remove
    static void remove(const QString path);

    // trunk, e.g. /home/user/Desktop/file.txt -> /home/user/Desktop/
    static QString trunk(const QString path);
};

#endif
