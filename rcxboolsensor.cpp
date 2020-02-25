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
#include <qlabel.h>
//#include <qwt_thermo.h>
#include "rcxboolsensor.h"

RCXBoolSensorWidget::RCXBoolSensorWidget ( int input, QWidget *parent, const char *name )
        : RCXSensorWidget(input, parent, name )
{
  Construct();
  Init();

}


RCXBoolSensorWidget::RCXBoolSensorWidget ( QWidget *parent, const char *name )
        : RCXSensorWidget( parent, name )
{
  Construct();
}


void RCXBoolSensorWidget::Construct(void) {
  
  led=new QlmLed(this, "led");
    
}

void RCXBoolSensorWidget::Init(void) {

  led->setState(false);
  setLabel("Boolean Sensor");
  rcx.SetSensorType(Sensor(), Boolean);
  
}

void RCXBoolSensorWidget::ReadSensor() {
  
  // slot
  
  // Read the sensor and set the value in the QwtThermo widget
  if(rcx.GetSensorValue(sensor_index)) {
    led->setState(true);
  } else {
    led->setState(false);
  }

}

void RCXBoolSensorWidget::drawContents (QPainter *p ) {
  
  led->repaint();
}

void RCXBoolSensorWidget::resizeEvent( QResizeEvent * )
{
  QRect cont=contentsRect();
  
  float square_side;
  if ( (cont.width()-2) < (cont.height()-1-LabelHeight) ) {
    square_side=cont.width()-2;
  } else {
    square_side=cont.height()-1-LabelHeight;
  }
  
  int xpos= (int)(cont.x()+(cont.width()-square_side)/2);
  led->setGeometry(xpos, cont.y()+LabelHeight, square_side, square_side);
  
  label->setGeometry(cont.x(), cont.y(), cont.width()-2, LabelHeight);
  
}
