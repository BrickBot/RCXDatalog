#ifndef KRCXWINDOW_H
#define KRCXWINDOW_H

#include <qmainwindow.h>

class GPLBrowser;
class RCXWidget;

class KRCXWindow: public QMainWindow
{
  Q_OBJECT

public:
  KRCXWindow();
  ~KRCXWindow();
  void connectRCX(void);
private slots:
    void ShowErrorInStatusBar( int );
 void ShowGPLLicense(void);
 void ShowNoWarranty(void);
 
private:
 RCXWidget *rcxwidget;
 GPLBrowser *license_view;
};


#endif
