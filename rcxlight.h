#ifndef RCX_LIGHT_H
#define RCX_LIGHT_H

#include "rcxrealsensor.h"

class RCXLightWidget : public RCXRealSensorWidget
{
 public:
  RCXLightWidget( int input,  QWidget *parent=0, const char *name=0 );
 protected:
  virtual void Init(void);
};

#endif
