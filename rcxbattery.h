#ifndef RCX_BATTERY_H
#define RCX_BATTERY_H

#include <qwidget.h>
#include <qframe.h>
#include "rcxrealsensor.h"

class RCXBatteryWidget : public RCXRealSensorWidget
{
  Q_OBJECT
 public:
  RCXBatteryWidget( QWidget *parent=0, const char *name=0 );
  void setAlarmValue(double value); // set the alarm value in volts
  public slots:
  virtual void ReadSensor(void);
 signals:
 protected:
  virtual void Init(void);
 private:
  double AlarmValue;
};

#endif
