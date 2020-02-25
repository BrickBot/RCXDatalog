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
#include <qwt_thermo.h>
#include "rcxrealsensor.h"

RCXRealSensorWidget::RCXRealSensorWidget ( int input, QWidget *parent, const char *name )
        : RCXSensorWidget(input, parent, name )
{
  Construct();
}


RCXRealSensorWidget::RCXRealSensorWidget ( QWidget *parent, const char *name )
        : RCXSensorWidget( parent, name )
{
  Construct();
}

void RCXRealSensorWidget::Construct(void) {

  sensor = new QwtThermo(this, "sensor_reading");
  sensor->setOrientation(QwtThermo::Horizontal, QwtThermo::Bottom);
  
}

void RCXRealSensorWidget::ReadSensor() {
  
  // slot
  
  // Read the sensor and set the value in the QwtThermo widget
  sensor->setValue((double)rcx.GetSensorValue(sensor_index));

}

void RCXRealSensorWidget::drawContents (QPainter *p ) {
  
  
  sensor->repaint();
  if (label) {
    label->repaint();
  }
}

void RCXRealSensorWidget::resizeEvent( QResizeEvent * )
{
  QRect cont=contentsRect();
  
  sensor->setGeometry(cont.x(), cont.y()+LabelHeight, cont.width()-2, (cont.height()-1)-LabelHeight);
  
  label->setGeometry(cont.x(), cont.y(), cont.width()-2, LabelHeight);
  
}
