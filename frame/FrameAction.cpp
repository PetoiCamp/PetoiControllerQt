#include "frame/FrameAction.h"
#include <stdio.h>

FrameAction::FrameAction() {
    for (int i = 0; i < 19; i++) {
        command[i] = 0;
    }

    command[0] = 'i';
    command[17] = '~';
    command[18] = '\0';
};

FrameAction::FrameAction(std::vector<int> frames)
{
    command[0] = 'i';
    command[17] = '~';
    command[18] = '\0';

    int pos = 0;
    for (auto iter = frames.begin(); iter != frames.end(); iter++) {
        at(pos) = *iter;
        pos++;
    }
};

char& FrameAction::operator[](int pos) {
    if (pos > 15) {
        return command[16];
    }

    return command[pos + 1];
};

char& FrameAction::at(int pos) {
    if (pos > 15) {
        return command[16];
    }

    return command[pos + 1];
};

int FrameAction::len() const {
    return 16;
};

bool FrameAction::updateActions(std::vector<int> frames) {

    int pos = 0;
    for (auto iter = frames.begin(); iter != frames.end(); iter++) {
        at(pos) = *iter;
        pos++;
    }

    return true;
};

const char* FrameAction::serialCmd(){
    debug();
    return command;
};

void FrameAction::debug() {

    printf("frame: ");
    for (int i = 0; i < len(); i++) {
        printf("%d ", at(i));
    }
    printf("\n");
}
