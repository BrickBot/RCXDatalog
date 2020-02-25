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

#include <ostream.h>
#include <qwidget.h>
#include "rcxerrormessage.h"
#include "qrcxsend.h"

// QRCXSend: catches errors of SEND
// displays an errorbox if connection to RCX is lost.

void QRCXSend::Send(const char *commandstring) {

  while (true) {
    
    try {
      RCXSend::Send(commandstring);
      break;
    }
    catch (RCXError::RCXError& e) {
      
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
