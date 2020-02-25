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

#include <stdio.h>
#include <ostream.h>
#include <qframe.h>
#include <qlabel.h>
#include "rcxsensor.h"

const int RCXSensorWidget::LabelHeight=20;

RCXSensorWidget::RCXSensorWidget ( int input, QWidget *parent, const char *name )
        : QFrame( parent, name )
{
  sensor_index = input;
  
  setFrameStyle(QFrame::Panel | QFrame::Raised);
  setLineWidth( 2 );

  Construct();
     
  // relay error signal from rcx to the outside world
  connect( &rcx, SIGNAL(RCXErrorSignal(int) ), SIGNAL( RCXErrorSignal(int) ));
  
}


RCXSensorWidget::RCXSensorWidget ( QWidget *parent, const char *name )
        : QFrame( parent, name )
{
  sensor_index = -1;
  
  setFrameStyle(QFrame::Panel | QFrame::Raised);
  setLineWidth( 2 );

  this->Construct();

  // relay error signal from rcx to the outside world
  connect( &rcx, SIGNAL(RCXErrorSignal(int) ), SIGNAL( RCXErrorSignal(int) ));

}

void RCXSensorWidget::Construct(void) {

  label=new QLabel(this, "label");
  label->setAlignment( AlignCenter );
  setLabel("Sensor");
  
}


void RCXSensorWidget::Init(void) {

  // the appropriate sensor settings should be correctly set
  // in the derived classes. here, a raw sensor value
  // is assumed for testing purposes. 

  rcx.SetSensorMode(sensor_index, 0, 0);
  rcx.SetSensorType(sensor_index, Raw);
  
}

void RCXSensorWidget::ReadSensor() {
  
  // slot
  
  // Read the sensor and set the value in the QwtThermo widget
  
}

void RCXSensorWidget::resizeEvent( QResizeEvent * )
{
  QRect cont=contentsRect();
  
  label->setGeometry(cont.x(), cont.y(), cont.width()-2, LabelHeight);
  
}

void RCXSensorWidget::mousePressEvent(QMouseEvent *me) {
  
  cerr <<  "MousePressEvent from Sensor\n";
  
}

void RCXSensorWidget::drawContents (QPainter *p ) {
  
  if (label) {
    label->repaint();
  }
}

int RCXSensorWidget::Sensor()
{
  return sensor_index;  
}

void RCXSensorWidget::setLabel(const char *labeltext) {

  label->setText(labeltext);
  cerr << labeltext << "\n";
  repaint();
}
