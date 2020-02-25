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

/* An error dialog in case the RCX could not be contacted */

#include <qdialog.h>
#include <qpushbutton.h>
#include "rcxerrordialog.h"

RCXErrorDialog::RCXErrorDialog( QWidget *parent, QString err_mess) : QDialog (parent, err_mess, TRUE) {
  
  // This is a modal Dialog; the user has to answer before continuing
  QPushButton *ok, *close;
  ok = new QPushButton( "OK", this);
  ok->setGeometry  ( 10,10, 100,30 );
  connect( ok, SIGNAL(clicked()), SLOT(accept()) ) ;
  close = new QPushButton( "Exit program", this);
  close->setGeometry ( 110, 10, 200, 30);
  connect( close, SIGNAL(clicked()) , SLOT(reject()) );
    
}
