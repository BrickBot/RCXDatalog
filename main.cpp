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

#include <iostream>
#include <qapplication.h>
#include "rcx.h"
#include "rcxcc.h"

int main( int argc, char **argv )
{

    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );
 
    // Try to connect to RCX
    try {
     KRCXWindow *mw=new KRCXWindow();
    }
    catch (RCXError::RCXError &e) {
      
      // unrecoverable RCX error
      cerr << "Unrecoverable error :";
      e.debug_print();
      exit(1);
    }
    
    KRCXWindow *mw=new KRCXWindow();
    mw->setCaption("RCX Datalog 0.01");
    mw->show();
    
   
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}
