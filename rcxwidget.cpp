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
#include <qframe.h>
#include <qpushbutton.h>
#include <qscrollbar.h>
#include <qlcdnumber.h>
#include <qfont.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include "rcxdatalog.h"
#include "rcxlight.h"
#include "rcxbattery.h"
#include "rcxwidget.h"
#include "rcxboolsensor.h"

RCXWidget::RCXWidget( QWidget *parent, const char *name )
        : QFrame( parent, name )
{
  
  setMinimumSize( 400, 285 );

  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth( 2 );

  rcx_datalog = new RCXDatalogWidget( this, "rcx_log");
  rcx_datalog->setGeometry( 10, 10, width()-20, height()-85);

  // relay error signal from rcx_datalog to the outside world
  connect( rcx_datalog, SIGNAL(RCXErrorSignal(int) ), 
     SIGNAL( RCXErrorSignal(int) ));
  
  rcx_battery = new RCXBatteryWidget( this, "battery");
  rcx_battery->setLabel("Battery Level [V]");
  rcx_battery->setFixedSize( 150, 70);
  rcx_battery->move( 
		    rcx_datalog->x()+rcx_datalog->width()
		    -150, rcx_datalog->y()+rcx_datalog->height());

  upload = new QPushButton( "Upload datalog", this, "upload" );
  upload->setFont( QFont( "Times", 18, QFont::Bold ) );
  // upload->setFixedSize( 150, 30 );
  upload->setFixedSize( rcx_datalog->width()-rcx_battery->width(), 30);
  upload->move(rcx_datalog->x(), rcx_datalog->y()+rcx_datalog->height());
  connect( upload, SIGNAL(clicked()), rcx_datalog, SLOT(UpLoad() ));

  read_battery = new QPushButton("Refresh Battery Level", this, "batt_refr");
  read_battery->setFont( QFont( "Times", 18, QFont::Bold ) );
  read_battery->setFixedSize( rcx_datalog->width()-rcx_battery->width(), 30);
  read_battery->move(upload->x(), upload->y()+upload->height());
  connect ( read_battery, SIGNAL(clicked()), rcx_battery, SLOT(ReadSensor()) );
  
  

  // I have turned off the light sensors and boolean sensors
  // First, I will have to add the possibility to tell the program
  // which type of sensor is connected to which input port

  /*
    rcx_sensor = new RCXLightWidget ( 2, this, "sensor");
    rcx_sensor->setGeometry(170, 10, 150, 70 );
  
    // relay error signal from rcxsensor to the outside world
    connect( rcx_sensor , SIGNAL(RCXErrorSignal(int) ), 
    SIGNAL( RCXErrorSignal(int) ));
  */

  /*
    led=new RCXBoolSensorWidget(0, this, "led");
    
    led->setGeometry ( 500, 10, 150, 70);
    
    // relay error signal from rcx_battery to the outside world
    connect( rcx_battery, SIGNAL(RCXErrorSignal(int) ), 
    SIGNAL( RCXErrorSignal(int) ));
  */

  
  // read sensor twice a second
  // Turned off, since we don't have the light and touch sensors right now
  //startTimer( 500 );
  
}

void RCXWidget::resizeEvent( QResizeEvent * )
{
    rcx_datalog->setGeometry( 10, 10, width()-20, height()-85);
    rcx_battery->move( 
		      rcx_datalog->x()+rcx_datalog->width()
		      -150, rcx_datalog->y()+rcx_datalog->height());
    upload->setFixedSize( rcx_datalog->width()-rcx_battery->width(), 30);
    upload->move(rcx_datalog->x(), rcx_datalog->y()+rcx_datalog->height());
    read_battery->setFixedSize( rcx_datalog->width()-rcx_battery->width(), 30);
    read_battery->move(upload->x(), upload->y()+upload->height());

    cerr << "[" << width() << "," << height() << '\n';
}

void RCXWidget::mousePressEvent (QMouseEvent *me) {
  cerr << "MousePressEvent from RCXWidget\n";
}

void RCXWidget::timerEvent( QTimerEvent *) 
{
  led->ReadSensor();
  rcx_sensor->ReadSensor();
}

void RCXWidget::Print(void) {

  // Start up a dialog to ask the user for the printer
  QPrinter printer;
  QPrintDialog SpecifyPrinter( &printer);
  
  // if the user has specified a printer, print
  // else do not print
  if (QPrintDialog::getPrinterSetup( &printer )) {
    
    rcx_datalog->Print( printer );
    
  }
  
}
