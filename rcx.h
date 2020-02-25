#ifndef _RCX_H_

#include "qrcxsend.h"

#define _RCX_H_
#define MESSAGE_SIZE 256

enum SoundType { Blip, BleepBleep, Downward, Upward, Buzz, FastUpward };
enum SensorType { Raw, Boolean, Temperature, Light, Rotation };

class RCX : public QRCXSend {

 public:
  //RCX();
  void PlaySound(int sound);
  int GetDatalogSize(void);
  void UploadDatalog(int *array, int startpos, int amount);
  bool AliveP(void);
  void SetSensorType(int sensor_index, SensorType s);
  void SetSensorMode(int sensor_index, int slope, int mode);
  int GetSensorValue(int sensor_index);
  int GetBatteryPower(void);
  int Status();

 private:
  char message[MESSAGE_SIZE];
  int GetValue(int source, int argument);
  void CheckRange(int index, int low, int high);
};


#define HI(number) (number)/256
#define LO(number) (number)%256

#endif

