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
#include <qwt_plot.h>
#include <qwidget.h>
#include <qprogressdialog.h>
#include <qwt_clrfltr.h>
#include <qpen.h>
#include "rcxdatalog.h"

RCXDatalogWidget::RCXDatalogWidget ( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
  Init();
  
  // relay error signal from rcx to the outside world
  connect( &rcx, SIGNAL(RCXErrorSignal(int) ), SIGNAL( RCXErrorSignal(int) ));

}

void RCXDatalogWidget::Init(void) {
  
  datalog = new QwtPlot("RCX Datalog", this, "rcxplot");
  datalog->move(0,0);
  plot = datalog->insertCurve("Datalog");
  datalog->setCurvePen(plot, QPen(black,2));
}

void RCXDatalogWidget::UpLoad(void) {

  rcx.PlaySound(Blip);
    
  // get datalog size
  int datalog_size=rcx.GetDatalogSize();
  
  // allocate enough memory for this datalog
  int *data=new int[datalog_size];
  
  // upload datalog in chunks of ten bytes
  const int ch_size=10;
  
  int n_chunks=datalog_size/ch_size;
  int size_last_ch=datalog_size-n_chunks*ch_size;
  
  char progress_message[100];
  snprintf(progress_message, 99, "Receiving %d datalog entries",datalog_size);
  QProgressDialog progress( progress_message, "Stop" , datalog_size, this, "progress", TRUE);
  
  progress.setCaption("One moment, please...\n");
  
  int completed=0;
  for (int i=0;i<n_chunks;i++) {
    progress.setProgress( completed );
    if (progress.wasCancelled()) 
      break;
    rcx.UploadDatalog(&data[i*ch_size], i*ch_size, ch_size);
    completed+=ch_size;
  }
  
  // last chunk
  rcx.UploadDatalog(&data[n_chunks*ch_size], n_chunks*ch_size, size_last_ch);
  progress.setProgress( datalog_size );
  completed+=size_last_ch;

  // plot the data
  double *x=new double[completed];
  double *y=new double[completed];
  
  for (int i=0;i<completed;i++) {
    
    x[i]=(double)i;
    y[i]=(double)data[i];
    
  }
  
  datalog->setCurveData(plot, x, y, completed);
  
  datalog->replot();
  
  rcx.PlaySound(FastUpward);
  
  delete[] data;
  delete[] x;
  delete[] y;

}

void RCXDatalogWidget::resizeEvent( QResizeEvent * )
{
  datalog->resize( width(), height() );
}

void RCXDatalogWidget::Print( QPrinter &pr )
{
  // print the plot using printer pr
  
  datalog->print(pr);

}
