#include "RawMessage.h"
#include <memory>
#include <iostream>


RawMessage::RawMessage(unsigned char* income, int len) {
    if (income != nullptr && len > 0) {

        // create a chunk of memory to hold the value
        data = new unsigned char[len + 1];
        size = len + 1;

        // copy to data
        memset(data, 0, len + 1);
        memcpy(data, income, len);
    }
}


RawMessage::~RawMessage() {
    if (data != nullptr) {
        delete data;
    }
}


int RawMessage::copy(unsigned char *ptr, int available_size) {

    // to avoid over range
    int min_size = std::min(available_size, size);

    // copy data back to ptr
    if (ptr != nullptr) {
        memcpy(ptr, data, min_size);

        return min_size;
    }

    return -1; // failed
}
