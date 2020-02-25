#ifndef RCX_DATALOG_H
#define RCX_DATALOG_H

#include <qwidget.h>
#include "rcx.h"

class QwtPlot;

class RCXDatalogWidget : public QWidget 
{
  Q_OBJECT

public:
  RCXDatalogWidget( QWidget *parent=0, const char *name=0 );
  void Print(QPrinter &pr);

public slots:
 void UpLoad(void);
 
signals:
  void RCXErrorSignal( int );

protected:
  void resizeEvent( QResizeEvent * );

private:
  QwtPlot *datalog;
  void Init(void);
  RCX rcx;
  long plot;
};

#endif
