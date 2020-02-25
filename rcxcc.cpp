/* rcxsens: See the state of the Lego Mindstorms RCX's sensors */
/* Copyright (C) 2000, 2001 Roeland Merks */
/* Email: roel@science.uva.nl */

/*  This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA. */

#include "rcxcc.h"
#include "rcxwidget.h"
#include "rcx.h"
//#include "rcxerrordialog.h"
#include "rcxerrormessage.h"
#include "gplbrowser.h"
#include <qapplication.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qaccel.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qtextbrowser.h>
#include <qmessagebox.h>
#include <qmime.h>
#include <iostream>

KRCXWindow::KRCXWindow()
    : QMainWindow( 0, "KRCX: inspired by RCXCC" )
{

  setGeometry(100, 100, 500, 400);
  
  // Try to start up an RCX widget (and to contact the RCX)
  rcxwidget = 0;
  
  connectRCX();
  
  QPopupMenu * file = new QPopupMenu();
  menuBar()->insertItem( "&File", file);
  file->insertItem( "&Print Datalog", rcxwidget, SLOT(Print()), CTRL+Key_P);
  file->insertItem( "&Quit", qApp, SLOT(quit()), CTRL+Key_Q );
  
  // right justify help menu:
  menuBar()->insertSeparator();
  QPopupMenu * help = new QPopupMenu();
  help->insertItem("RCXDatalog &License", this, SLOT(ShowGPLLicense()));
  help->insertItem("NO &WARRANTY", this, SLOT(ShowNoWarranty() ) );
  menuBar()->insertItem("&Help", help);
  
  statusBar()->message( "Ready", 2000 );

  license_view = 0;
  setCentralWidget(rcxwidget);

}

void KRCXWindow::connectRCX(void) {

  while (true) {
    try {
      rcxwidget = new RCXWidget( this, "rcx");
      break;
    } catch (RCXError::RCXError &e) {
    
      // connection error
      
      switch (RCXErrorMessage::Connection()) {
	
      case 0: // Try Again
	
	continue;

      case 1: // Quit
	
	cerr << "Exiting...\n";
	throw;
	
	break;

      }
      
    }
  }
}

/*! Destroys the object and frees any allocated resources.

*/

KRCXWindow::~KRCXWindow()
{
  
}

void KRCXWindow::ShowErrorInStatusBar(int error) {
  
//   // Show the error with error number "error" in the status bar
//   if (error == QlmRcx::OK) {
//     statusBar()->message("Connected to RCX");
//     return; 
//   }
  
//   if (error== QlmRcx::BadLink) {
//     statusBar()->message("Bad link to RCX");
//   }

//   if (error == QlmRcx::BadResponse) {
//     statusBar()->message("Bad response from RCX");
//   }

//   if (error == QlmRcx::NoResponse) {
//     statusBar()->message("No response from RCX");
//   }

//   if (error == QlmRcx::ResponseTooLarge) {
//     statusBar()->message("Response from RCX too large. Please send bug report");
//   }
         
  
}

void KRCXWindow::ShowGPLLicense(void) {
  
  // Browse GNU Public License
  if (!license_view)
    license_view = new GPLBrowser();

  license_view->home();
  license_view->show();
  license_view->raise();
}

void KRCXWindow::ShowNoWarranty(void) {

  if (!license_view)
    license_view = new GPLBrowser();
  
  license_view->ScrollToWarranty();
  license_view->show();
  license_view->raise();
}
