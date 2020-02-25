#ifndef RCX_REALSENSOR_H
#define RCX_REALSENSOR_H

#include <qframe.h>
#include "rcxsensor.h"


// a sensor that has a "real" reading as opposed to a "boolean" sensor
// that can be either on or off. 

class QwtThermo;

class RCXRealSensorWidget : public RCXSensorWidget
{
  Q_OBJECT

    public:
  RCXRealSensorWidget ( int input, QWidget *parent, const char *name );
  RCXRealSensorWidget ( QWidget *parent, const char *name );
  virtual void ReadSensor(void);

 protected:
  virtual void drawContents(QPainter *p);
  virtual void resizeEvent( QResizeEvent * );
  QwtThermo *sensor; // the readings are displayed using a "thermo" widget
  virtual void Construct(void);

 private:
  
};

#endif
