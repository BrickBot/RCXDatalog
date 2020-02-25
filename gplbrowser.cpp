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

#include <qtextbrowser.h>
#include <qtoolbar.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include "gplbrowser.h"
#include "home.xpm"
#include "forward.xpm"
#include "back.xpm"

GPLBrowser::GPLBrowser( QWidget *parent, const char *name) 
  : QMainWindow( parent, name) 
{
  setMinimumSize( 400, 285 );
  setCaption("GNU General Public License");
  // Browse GNU Public License
  //buttongrid = new QGrid(4, QGrid::Horizontal, this, "buttons");
  browseButtons = new QToolBar( this, "browse buttons" );
  browseButtons->setLabel( tr( "Buttons" ) );


  license_view = new QTextBrowser(this, "GNU General Public License");
 //  license_view->setGeometry(0,30,width(),height()-30);
//   license_view->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  license_view->mimeSourceFactory()->setFilePath(".");
  license_view->setSource("file:/gpl.html");
  setCentralWidget(license_view);
  
  QPixmap backIcon, forwardIcon, homeIcon;
  backIcon = QPixmap( (const char**)back );
  QToolButton * Back
    = new QToolButton( backIcon, "Back", QString::null,
		       license_view, SLOT(backward()), browseButtons, "back" );
  forwardIcon = QPixmap( (const char**)forward );
  QToolButton * Forward
    = new QToolButton( forwardIcon, "Forward", QString::null,
		       license_view, SLOT(forward()), browseButtons, "forward" );
  homeIcon = QPixmap( (const char**)::home );
  QToolButton * Home
    = new QToolButton( homeIcon, "Home", QString::null,
		       license_view, SLOT(home()), browseButtons, "home" );
  
  QToolButton * Warranty
    = new QToolButton(browseButtons, "warranty");
  Warranty->setText("NO &WARRANTY");
  connect(Warranty, SIGNAL(clicked()), this, SLOT(ScrollToWarranty() ))
;
  QToolButton * Close 
    = new QToolButton(browseButtons, "close");
  Close->setText("&Close");
  connect(Close, SIGNAL(clicked()), this, SLOT(close()));
  
  show();
}

void GPLBrowser::ScrollToWarranty(void) {
  
  // SLOT
  // Scroll TextBrowser to No Warranty section
  license_view->scrollToAnchor ("nowarranty");

}

void GPLBrowser::home(void) {

  license_view->home();

}
