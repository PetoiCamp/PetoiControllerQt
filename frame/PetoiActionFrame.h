#ifndef PETOIACTIONFRAME_H
#define PETOIACTIONFRAME_H

#include <QString>
#include <QVector>
#include <QTimer>
#include <QObject>
#include <QPair>
#include <QThread>

#include "frame/FrameAction.h"
#include "frame/CJson.h"

//typedef void(*ActionCallback)(const char*);

class PetoiActionFrame: public QThread
{
    Q_OBJECT

private:
    QVector<QPair<int, FrameAction>>    actions;
    JsonHandler             handler;
    int                     cursor;
    int                     count;
//    ActionCallback          callback;
    bool                    running;


public:
//    explicit PetoiActionFrame(QString const &filename, ActionCallback action);
    explicit PetoiActionFrame(QString const &filename);

    ~PetoiActionFrame();

    // to access every servo individual angle
    QPair<int, FrameAction>& operator[](int pos);

    // stop play action
    void stop();

signals:
   void sendSerialCmd(char* serialCmd);

protected:
    void run();
};

#endif // PETOIACTIONFRAME_H
