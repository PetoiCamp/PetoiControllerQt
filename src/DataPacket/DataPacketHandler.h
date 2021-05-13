//
//  SerialInputHandler.hpp
//  Serial App
//
//  Created by Orlando Chen on 2021/4/29.
//

#ifndef DataPacketHandler_h
#define DataPacketHandler_h

#include "Definitions.h"
#include "DataPacket.h"

class DataPacketHandler {
    SerialDataPacket param;
    char lastPos;

public:
    /**
     * constructor
     */
    DataPacketHandler();
    
    /**
     * empty and zero all buffer and parameters
     */
    void empty();

    /**
     * easy element accessing, similar to [] operator
     *
     * @param pos default is -1, which will return the reference to
     * the next empty char-data in buffer
     */
    char& at(int pos=-1);

    /**
     * Since Arduino uses Serial.read() to get the incoming data, one
     * char by one char. Should pass the value to the buffer for data
     * assembling.
     *
     * @param sz received char from Serial.read()
     * @param callback callback function, when data assembled, it will be called
     */
    void inputChar(char sz, SerialPacketCallback callback);
    
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
    char* prepare(byte ins0, byte ins1, byte error, byte type,
                  void* data = nullptr, int datalen = 0);


    /**
     * data validation
     */
    bool isValid();


    /**
     * garbage cleaning
     */
    void garbageClean();
};

#endif /* SerialInputHandler_h */
