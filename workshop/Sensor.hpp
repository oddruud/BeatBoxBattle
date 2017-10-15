#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_


#define DEBUG 1

#define CHANNEL_MAX 16

#define ASSERT(x) sensorAssert(x, #x, __FILE__, __LINE__)

class Sensor {
	public:
	
	Sensor(int pinIn, int channelIn);
	Sensor(int pinIn, int channelIn, int toneIn);

  virtual void init(void) = 0;
  virtual int measureValue(void) = 0;
  void setTone(int value);
  void MIDImessage(int cmd, int data1, int data2);
  void sensorAssert(int check, char* assertString, char* filename, int lineNumber);
	int pin;
	int channel;
	int tone;
  
  long lastTimeValueChanged;
  int lastValue;
};

#endif // _SENSOR_HPP_
