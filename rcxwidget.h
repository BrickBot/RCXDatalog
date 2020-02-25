#ifndef RCXWIDGET_H
#define RCXWIDGET_H

#include <qframe.h>

class QPushButton;
class RCXDatalogWidget;
class RCXLightWidget;
class RCXBatteryWidget;
class RCXBoolSensorWidget;

class RCXWidget : public QFrame
{
  
  Q_OBJECT

 public:
  RCXWidget( QWidget *parent=0, const char *name=0 );

  public slots:
    void Print(void);  

signals:
  void RCXErrorSignal( int );

protected:
  void resizeEvent( QResizeEvent * );
  void timerEvent( QTimerEvent * );
  void mousePressEvent (QMouseEvent *);

private:
  QPushButton *quit;
  QPushButton *upload;
  QPushButton *read_sensor;
  QPushButton *read_battery;
  RCXDatalogWidget *rcx_datalog;
  RCXLightWidget *rcx_sensor;
  RCXBatteryWidget *rcx_battery;
  RCXBoolSensorWidget *led;
};

#endif
