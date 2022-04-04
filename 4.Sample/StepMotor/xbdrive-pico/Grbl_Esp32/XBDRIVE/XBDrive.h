#ifndef __XBDRIVE_H_
#define __XBDRIVE_H_

#include <XBDRIVE/global.h>
#include <src/Grbl.h>

class XBDrive
{
private:

public:
    XBDrive(void);
    ~XBDrive(void);
    void setup();
    void loop();
};

extern XBDrive xbdrive;

#endif
