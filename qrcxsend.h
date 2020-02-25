#ifndef QLMRCX_H_
#define QLMRCX_H_

#include <qwidget.h>
#include "send.h"

class QRCXSend : public QWidget, public RCXSend
{
  Q_OBJECT
    
    protected:
    // overridden virtual function from RCX
  virtual void Send(const char *commandstring);

};


#endif

