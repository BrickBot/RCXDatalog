#ifndef RCX_BOOLSENSOR_H
#define RCX_BOOLSENSOR_H

#include <qframe.h>
#include "rcxsensor.h"
#include "qlmled.h"

// a sensor that can be either on or off. 

class RCXBoolSensorWidget : public RCXSensorWidget
{
  Q_OBJECT

    public:
  RCXBoolSensorWidget ( int input, QWidget *parent, const char *name );
  RCXBoolSensorWidget ( QWidget *parent, const char *name );
  virtual void ReadSensor(void);

 protected:
  virtual void drawContents(QPainter *p);
  virtual void resizeEvent( QResizeEvent * );
  virtual void Construct(void);
  virtual void Init(void);
    
 private:
  QlmLed *led;
};

#endif
