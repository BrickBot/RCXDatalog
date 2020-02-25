#ifndef RCX_SENSOR_H
#define RCX_SENSOR_H

#include <qframe.h>
#include "rcx.h"

//class QwtThermo;
class QLabel;

class RCXSensorWidget : public QFrame
{
  Q_OBJECT

public:
  RCXSensorWidget( int input,  QWidget *parent=0, const char *name=0 );
  RCXSensorWidget( QWidget *parent=0, const char *name=0 );
  void setLabel(const char *labeltext);

public slots:
  virtual void ReadSensor(void);

signals:
  void RCXErrorSignal( int );

protected:
 void mousePressEvent(QMouseEvent *me);
 virtual void resizeEvent( QResizeEvent * );
 virtual void drawContents( QPainter * );
 virtual void Init(void);
 RCX rcx;
 int Sensor();
 virtual void Construct(void);
 QLabel *label;
 int sensor_index;
 static const int LabelHeight;

private:
  
};

#endif
