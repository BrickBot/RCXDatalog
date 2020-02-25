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

#include <qmessagebox.h>
#include "rcxerrormessage.h"

namespace RCXErrorMessage {
  
  int Connection(void) {
    
    return QMessageBox::warning(0, "RCX Datalog", "Could not connect to RCX\n\n"
				   "Possibly it was not turned on, or the\n"
				   "RCX is out of view of the IR tower.\n"
				   "Please correct the problem, and\n"
				   "press \"Try again\" or Quit to exit. \n",
				"Try Again", "Quit", 0,
				0,1);
    
    
  }
}


