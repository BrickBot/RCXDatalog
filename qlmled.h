// A "LED" that can be turned on or off

#ifndef QLM_LED_H
#define QLM_LED_H

#include <qwidget.h>

class QlmLed : public QWidget
{
  Q_OBJECT

public:
  QlmLed( QWidget *parent=0, const char *name=0 );
public slots:
 void setState ( bool new_state );
 void ToggleState (void);
protected:
  void paintEvent( QPaintEvent *);
private:
  bool state; // is led turned on or off?
};

#endif
