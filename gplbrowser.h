#ifndef GPLBROWSER_H
#define GPLBROWSER_H

#include <qmainwindow.h>

class QTextBrowser;
class QToolBar;

class GPLBrowser : public QMainWindow {
  
  Q_OBJECT

    public:
  GPLBrowser(QWidget *parent=0, const char *name=0);

  public slots:
    void ScrollToWarranty(void);
  void home(void);

 private:
  QTextBrowser *license_view;
  QToolBar *browseButtons;
  

};

#endif
