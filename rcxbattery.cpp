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
#include <qwt_thermo.h>
#include "rcxbattery.h"

RCXBatteryWidget::RCXBatteryWidget ( QWidget *parent, const char *name )
  : RCXRealSensorWidget( parent, name ) {
  
  Init();

}

void RCXBatteryWidget::Init(void) {

  

  setAlarmValue(7.0); 

  sensor->setValue(0.);
  sensor->setRange(0.,10.);
  
  setLabel("Battery Level [V]");

  ReadSensor();
}

void RCXBatteryWidget::ReadSensor(void) {
  
  // overridden virtual function
  cerr << "Reading Battery Level\n";
  // Read the battery value and set the value in the QwtThermo widget
  sensor->setValue(((double)rcx.GetBatteryPower())/1000.);
  if (sensor->value()<AlarmValue)
    sensor->setFillColor(QColor("red"));
  else
    sensor->setFillColor(QColor("green"));
}

void RCXBatteryWidget::setAlarmValue(double value) {
  
  // set the battery level (in Volts) below which the
  // indicator should be painted red
  
  AlarmValue=value;

}




