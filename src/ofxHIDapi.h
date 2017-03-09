//
//  ofxHIDapi.h
//
//  magicLab 2017
//  http://www.magiclab.nyc
//  Created by enrico<naus3a>viola on 3/9/17.
//
//

#pragma once
#include "ofMain.h"
#include "hidapi.h"


class ofxHIDapi{
public:
    ofxHIDapi();
    ~ofxHIDapi();
    void setReadBufferSize(int nBytes);
    bool connect(unsigned short vendor_id, unsigned short product_id, const wchar_t * serial_number=NULL);
    void setNonBlocking(bool b);
    int read();
    void sendFeatureReport(const unsigned char * data, size_t length);
    void close();
    inline hid_device * getHandle(){return devHandle;}
    inline unsigned char * getReadBuffer(){return readBuffer;}
protected:
    void cleanReadBuffer();

    hid_device * devHandle;
    unsigned char * readBuffer;
};
