#include "DataPacketHandler.h"
#include <QDebug>

#include <iostream>
#include <memory>

/**
 * constructor
 */
DataPacketHandler::DataPacketHandler() {
    empty();
}

/**
 * empty and zero all buffer and parameters
 */
void DataPacketHandler::empty() {
    // zero parameter
    memset(&param, 0, sizeof(SerialDataPacket));
    lastPos = 0;
}

/**
 * easy element accessing, similar to [] operator
 *
 * @param pos default is -1, which will return the reference to
 * the next empty char-data in buffer
 */
char& DataPacketHandler::at(int pos) {
    char* ptr = (char*) &param;

    if (pos >= 0 && pos < 32) {
        return ptr[pos];
    } else if (pos == -1 && lastPos >= 0 && lastPos < 32) {
        int temp = lastPos++;
        return ptr[temp];
    } else {
        return ptr[0];
    }
}

/**
 * Since Arduino uses Serial.read() to get the incoming data, one
 * char by one char. Should pass the value to the buffer for data
 * assembling.
 *
 * @param sz received char from Serial.read()
 * @param callback callback function, when data assembled, it will be called
 */
void DataPacketHandler::inputChar(char sz, SerialPacketCallback callback) {
    // get the next available reference of char,
    // and assign the updated value to it
    at() = sz;

    // if the last char is \r and the previous is \n, means need to validate the
    // buffer and call the callback function
    if (isValid()) {

        // pass buffer to callback function
        callback(&param);

        // cleanup everything and wait for next turn
        empty();
    }

    // if buffer full of garbage, do cleaning task
    garbageClean();
}

/**
 * When you are going to send data to the remote, use this function to update the buffer.
 * After that, use Serial.println() to send instruction back to the target.
 * @param ins0 general instruction
 * @param ins1 subclass instruction
 * @param error error code
 * @param type data type
 * @param data additional information going to append to buffer
 * @param datalen data length
 * @return converted buffer as char array
 */
char* DataPacketHandler::prepare(byte ins0, byte ins1, byte error, byte type,
              void* data, int datalen) {

    // header
    param.version = VERSION;
    param.dataLen = 8 + datalen;
    param.ins0 = ins0;
    param.ins1 = ins1;
    param.error = error;
    param.type = type;

    // additional information
    if (data != nullptr && datalen <= 24) {
        memcpy(param.rest, data, datalen);
    }

    // tailer
    param.rest[datalen + 0] = '\r';
    param.rest[datalen + 1] = '\n';

    // convert to char array
    return (char*)&param;
}

/**
 * data validation
 */
bool DataPacketHandler::isValid() {

    // check data length
    if (param.dataLen != lastPos) {
        return false;
    }

    // check tailer
    char r = param.rest[param.dataLen - 8]; // datalen + 0
    char n = param.rest[param.dataLen - 7]; // datalen + 1
    if (r != '\r' || n != '\n' ) {
        return false;
    }

    // check header
    if (param.version != VERSION) {
        return false;
    }

    return true;
}


/**
 * garbage cleaning
 */
void DataPacketHandler::garbageClean() {
    if (lastPos > 8) // the minimal instruction
    {
        if (lastPos >= param.dataLen || lastPos == sizeof(SerialDataPacket)) {

            // cleanup everything and wait for next turn
            memset(&param, 0, sizeof(SerialDataPacket));
            lastPos = 0;
        }
    }
}
