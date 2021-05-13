//
//  DataPacket.h
//  Serial App
//
//  Created by Orlando Chen on 2021/4/29.
//

#ifndef DataPacket_h
#define DataPacket_h

#ifndef byte
#define byte unsigned char
#endif

#define REST_MAX_SIZE    24  // only 24 bytes reserved to user

struct SerialDataPacket {
    byte version;   // packet version & header
    byte dataLen;   // data length
    byte ins0;      // instruction 0
    byte ins1;      // instruction 1
    byte error;     // error code
    byte type;      // data type
    char rest[REST_MAX_SIZE + 2];  // body data and \r\n
}; // totally 32 byte

// callback
typedef void(*SerialPacketCallback)(SerialDataPacket*);

#endif /* DataPacket_h */
