#include "SensorDriver.h"



int main(int argc, char *argv[])
{
  
    uint8_t SensorNum, Precision;
    float val;
    
    InitDescr fd = SensorInitialization();
    
    uint64_t loop_count = 10;
    uint64_t i;
    
    
    for(i=0;i<loop_count;i++){
      SensorNum = 1; Precision = 3;
      val = SensorRead(fd, SensorNum, Precision);
      printf("The value of Sensor %d is: %f\n",SensorNum, val);
      
      
      SensorNum = 2; Precision = 2;
      val = SensorRead(fd, SensorNum, Precision);
      printf("The value of Sensor %d is: %f\n",SensorNum, val);
      
      
      SensorNum = 3; Precision = 3;
      val = SensorRead(fd, SensorNum, Precision);
      printf("The value of Sensor %d is: %f\n",SensorNum, val);
      
      
      SensorNum = 4; Precision = 1;
      val = SensorRead(fd, SensorNum, Precision);
      printf("The value of Sensor %d is: %f\n",SensorNum, val);
      
      
      delay(fd, 1000); // waits for a second
    }
    
    SensorFinalization(fd);
 
    return 0;
}
