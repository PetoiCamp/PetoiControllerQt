#ifndef FRAMEACTION_H
#define FRAMEACTION_H

#include <vector>

class FrameAction {
private:
    char command[19];  // l a[16] ~ \0

public:
    FrameAction();

    FrameAction(std::vector<int> frames);

    // to access every servo individual angle
    char& operator[](int pos);

    // to access every servo individual angle
    char& at(int pos);

    // the number of servos
    int len() const;

    // update servos angles
    bool updateActions(std::vector<int> frames);

    // convert to serial command
    const char* serialCmd();

    // for debug only
    void debug();
};

#endif // FRAMEACTION_H
