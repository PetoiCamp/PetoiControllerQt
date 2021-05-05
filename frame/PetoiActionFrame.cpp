#include "frame/PetoiActionFrame.h"
#include <iostream>
#include <QtCore>

PetoiActionFrame::PetoiActionFrame(QString const &filename) :
   handler(filename)
{
    std::vector<std::string> frames = handler.get_multi_json_lists("frames");
    count = handler.get_int("count");
//    callback = doAction;
    running = true;

    for (auto iter = frames.begin(); iter != frames.end(); iter++) {
        JsonHandler json(iter->c_str());
        int delay = json.get_int("delay");
        std::vector<int> pos = json.get_int_list("act");

        FrameAction action(pos);

        QPair<int, FrameAction> pair(delay, action);
        actions.push_back(pair);
    }
}


PetoiActionFrame::~PetoiActionFrame() {

};


// to access every servo individual angle
QPair<int, FrameAction>& PetoiActionFrame::operator[](int pos)
{
    return actions[pos];
};


// stop play action
void PetoiActionFrame::stop() {
    running = false;
};

void PetoiActionFrame::run() {

    for (auto iter = actions.begin(); iter != actions.end(); iter++) {
        int delay = iter->first;
        FrameAction *ptr = &(iter->second);

        // sleep for milliseconds
        if (delay > 0) msleep(delay);

        // do action
        emit sendSerialCmd((char*)ptr->serialCmd());

        if (!running) break;
    }
}
