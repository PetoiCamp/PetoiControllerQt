#ifndef RAWMESSAGE_H
#define RAWMESSAGE_H


class RawMessage
{
public:
    unsigned char*  data;
    int             size;

public:
    RawMessage(unsigned char* income, int size);

    ~RawMessage();

    /**
     * @brief get_back get value back from raw
     * @param ptr
     * @param available_size
     * @return
     */
    int copy(unsigned char* dst, int available_size);
};

#endif // RAWMESSAGE_H
