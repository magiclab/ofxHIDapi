//
//  ofxHIDapi.cpp
//
//  magicLab 2017
//  http://www.magiclab.nyc
//  Created by enrico<naus3a>viola on 3/9/17.
//
//

#include "ofxHIDapi.h"

ofxHIDapi::ofxHIDapi(){
    devHandle = NULL;
    readBuffer = NULL;
}

ofxHIDapi::~ofxHIDapi(){
    close();
    hid_exit();
    cleanReadBuffer();
}

void ofxHIDapi::cleanReadBuffer(){
    if(readBuffer!=NULL){
        delete [] readBuffer;
        readBuffer = NULL;
    }
}

void ofxHIDapi::setReadBufferSize(int nBytes){
    cleanReadBuffer();
    readBuffer = new unsigned char[nBytes];
    cout<<"HID device read buffer: "<<nBytes<<" bytes"<<endl;
}

bool ofxHIDapi::connect(unsigned short vendor_id, unsigned short product_id, const wchar_t * serial_number){
    if(readBuffer==NULL){
        setReadBufferSize(10);
    }
    hid_init();
    devHandle = hid_open(vendor_id, product_id, serial_number);
    if(devHandle==NULL){
        ofLogError("ofxHIDapi::connect","cannot connect to device");
        return false;
    }else{
        wchar_t wstr[6];
        hid_get_manufacturer_string(devHandle, wstr, 6);
        cout<<"HID device connected. Manufacturer string: "<<wstr<<endl;
        return true;
    }
}

void ofxHIDapi::setNonBlocking(bool b){
    if(devHandle!=NULL){
        hid_set_nonblocking(devHandle, b?1:0);
    }else{
        ofLogError("ofxHIDapi::setNonBlocking","no connected device");
    }
}

void ofxHIDapi::close(){
    if(devHandle!=NULL){
        hid_close(devHandle);
    }
}

int ofxHIDapi::read(){
    int nBytes = hid_read(devHandle, readBuffer, sizeof(readBuffer));
    return nBytes;
}

void ofxHIDapi::sendFeatureReport(const unsigned char *data, size_t length){
    hid_send_feature_report(devHandle, data, length);
}
