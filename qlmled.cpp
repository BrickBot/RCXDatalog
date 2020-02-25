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
#include "qlmled.h"
#include <qpainter.h>

QlmLed::QlmLed(QWidget *parent, const char *name )
  : QWidget( parent, name ) {

  state=false; // turned off initially
  repaint();
}

void QlmLed::setState (bool new_state) {

  if (state!=new_state) {
    state=new_state;
    repaint();
  }
}

void QlmLed::ToggleState(void) {
  if (state)
    setState(false);
  else
    setState(true);
}
void QlmLed::paintEvent( QPaintEvent * )
{
    QPainter p;
    //QBrush   brush( black );

    QPen     pen( black,2   );

    p.begin( this );
    //p.setBrush( brush );
    p.setPen( pen );
    
    // draw the outer circle in the widget
    p.drawEllipse( rect() );

    // if state==true, also draw a filled inner circle
    if (state) {
      
      QBrush brush( SolidPattern  );
      p.setBrush( brush );
      int WidthOfSpaceBetweenCircles=width()/10;
      int HeightOfSpaceBetweenCircles=height()/10;
      
      p.drawEllipse( WidthOfSpaceBetweenCircles,
		     HeightOfSpaceBetweenCircles,
		     width()-2*WidthOfSpaceBetweenCircles,
		     height()-2*HeightOfSpaceBetweenCircles);

    }
    
    p.end();
}
