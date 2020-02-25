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
#include <stdlib.h>
#include <ostream.h>
#include "rcx.h"

bool RCX::AliveP(void) {
  
  Send("10");
  
  // Not necessary anymore: handled by exceptions
  /*  if (error_status!=OK) 
    return false;
  */
  if (len==1 && (recvbuf[0]|0x08)==0xef) 
    return true;
  else
    return false;
}

int RCX::Status(void) {
  
  return error_status;

}

void RCX::PlaySound(int sound) {

  if (sound <0 || sound >5) {

    cerr << "PlaySound(): Invalid sound number\n";
    return;
    
  }

  snprintf(message, MESSAGE_SIZE, "51 %02x",sound);
  Send(message);
}

int RCX::GetDatalogSize(void) {
  
  // Get the datalog size, _excluding_ the datalog size entry itself
  

  // get the first byte of the datalog
  Send("a4 00 00 01 00");
  
  // return the response
  if (len==4) {
    
    if (recvbuf[1]==0xff) {
      
      int reply=recvbuf[2]+256*recvbuf[3]-1;
      
      return reply;

    } else {
      return -1;
    }
  } else
    return -1;
}

void RCX::UploadDatalog(int *array, int startpos, int amount) {

  // upload "amount" datalog entries from "startpos" and put them 
  // in "array"
  
  // prepare message
  snprintf(message, MESSAGE_SIZE, "a4 %02x %02x %02x %02x", 
	   LO(startpos+1), HI(startpos+1), LO(amount), HI(amount));
  
  Send(message);
  
  // get reply and put in array
  for (int i=0;i<amount;i++) {
    
    int index=2+i*3;
    array[i]=recvbuf[index]+256*recvbuf[index+1];
    
  }

} 

void RCX::SetSensorType(int sensor_index, SensorType s) {

  CheckRange(sensor_index, 0,2);
  
  snprintf(message, MESSAGE_SIZE, "32 %02x %02x", sensor_index, s);
  Send(message);

}

void RCX::SetSensorMode(int sensor_index, int slope, int mode) {

  CheckRange(sensor_index, 0 ,2);
  CheckRange(slope, 0, 31);
  CheckRange(mode, 0,7);
  
  unsigned char code = 
    (((unsigned char)mode)&7)<<5 || (((unsigned char)slope)&31);

  snprintf(message, MESSAGE_SIZE, "42 %02x %02x", sensor_index, code);
  Send(message);
}


int RCX::GetSensorValue(int sensor_index) {

  // low level function. Please set the sensor type and
  // mode using SetSensorMode and SetSensorType
  CheckRange(sensor_index, 0, 2);
  
  snprintf(message, MESSAGE_SIZE, "12 09 %02x", sensor_index);
  Send(message);
  
  // Get reply
  int reply=recvbuf[1]+recvbuf[2]*256;
  
  return reply;
  
}

int RCX::GetBatteryPower(void) {
  
  // get the battery power and return the value in millivolts 
  snprintf(message, MESSAGE_SIZE, "30");
  Send(message);
  
  // Get reply
  int reply=recvbuf[1]+recvbuf[2]*256;
  
  return reply;
}

// private

void RCX::CheckRange(int index, int low, int high) {
  
  if (index<low || index>high) {
    cerr << "Sorry, parameter " << index << 
      " out of range [" << low << "-" << high << "]\n";
    exit(1);
  }

}

int RCX::GetValue(int source, int argument) {
  
  CheckRange(source, 0, 15);
  if (source>=5 && source <=7) {
    
    cerr << "RCX::GetValue(): sources 5-7 are invalid!\n";
    exit(1);
  }

}


