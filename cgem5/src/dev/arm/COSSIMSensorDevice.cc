/*
 * Copyright (c) 2010 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2005 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Tampouratzis Nikolaos
 *
 */

#include "base/trace.hh"
#include "debug/COSSIMSensorDevice.hh"
#include "dev/arm/amba_device.hh"
#include "dev/arm/COSSIMSensorDevice.hh"
#include "mem/packet.hh"
#include "mem/packet_access.hh"

#include "sim/system.hh"

#include <unistd.h>


using namespace std;


COSSIMSensorDevice::COSSIMSensorDevice(const Params *p)
    : AmbaIntDevice(p, p->pio_size), nodeNumber(p->nodeNum)
{
  
}



Tick
COSSIMSensorDevice::read(PacketPtr pkt)
{
    pkt->makeAtomicResponse();
    assert(pkt->getAddr() >= pioAddr && pkt->getAddr() < pioAddr + pioSize); 
    
    float SensorValue;
    
    switch (nodeNumber) {
      case 0:
	//! Here the user may define the sensors of NodeNum 0 !//
	switch (pkt->getAddr() - pioAddr) {
	    case SENSOR_NUMBER_1:
	      SensorValue = -10.1234; //Application partner should read the sensorValue for Sensor0 from some file
	      SendValue(pkt, PrecisionSensor1, SensorValue);
	      break;
	    case SENSOR_NUMBER_2:
	      SensorValue = 20.1234; //Application partner should read the sensorValue for Sensor1 from some file
	      SendValue(pkt, PrecisionSensor2, SensorValue);
	      break;
	    case SENSOR_NUMBER_3:
	      SensorValue = -30.1234; //Application partner should read the sensorValue for Sensor2 from some file
	      SendValue(pkt, PrecisionSensor3, SensorValue);
	      break;
	    case SENSOR_NUMBER_4:
	      SensorValue = 40.1234; //Application partner should read the sensorValue for Sensor3 from some file
	      SendValue(pkt, PrecisionSensor4, SensorValue);
	      break;
	    //Application partner may add another sensors here for the NodeNum 0
	    default:
	      panic("Device: Unrecognized Sensor Value!\n");
	}
	break;
      
      case 1:
	//! Here the user may define the sensors of NodeNum 1 !//
	switch (pkt->getAddr() - pioAddr) {
	    case SENSOR_NUMBER_1:
	      SensorValue = -100.1234; //Application partner should read the sensorValue for Sensor0 from some file
	      SendValue(pkt, PrecisionSensor1, SensorValue);
	      break;
	    case SENSOR_NUMBER_2:
	      SensorValue = 200.1234; //Application partner should read the sensorValue for Sensor1 from some file
	      SendValue(pkt, PrecisionSensor2, SensorValue);
	      break;
	    case SENSOR_NUMBER_3:
	      SensorValue = -300.1234; //Application partner should read the sensorValue for Sensor2 from some file
	      SendValue(pkt, PrecisionSensor3, SensorValue);
	      break;
	    case SENSOR_NUMBER_4:
	      SensorValue = 400.1234; //Application partner should read the sensorValue for Sensor3 from some file
	      SendValue(pkt, PrecisionSensor4, SensorValue);
	      break;
	    //Application partner may add another sensors here for the NodeNum 1
	    default:
	      panic("Device: Unrecognized Sensor Value!\n");
	}
	break;
      
      /* In this example NodeNum2 not contains any Sensors */
	
      case 3:
	//! Here the user may define the sensors of NodeNum 3 !//
	switch (pkt->getAddr() - pioAddr) {
	    case SENSOR_NUMBER_1:
	      SensorValue = -1000.1234; //Application partner should read the sensorValue for Sensor0 from some file
	      SendValue(pkt, PrecisionSensor1, SensorValue);
	      break;
	    case SENSOR_NUMBER_2:
	      SensorValue = 2000.1234; //Application partner should read the sensorValue for Sensor1 from some file
	      SendValue(pkt, PrecisionSensor2, SensorValue);
	      break;
	    case SENSOR_NUMBER_3:
	      SensorValue = -3000.1234; //Application partner should read the sensorValue for Sensor2 from some file
	      SendValue(pkt, PrecisionSensor3, SensorValue);
	      break;
	    case SENSOR_NUMBER_4:
	      SensorValue = 4000.1234; //Application partner should read the sensorValue for Sensor3 from some file
	      SendValue(pkt, PrecisionSensor4, SensorValue);
	      break;
	    //Application partner may add another sensors here for the NodeNum 3
	    default:
	      panic("Device: Unrecognized Sensor Value!\n");
	}
	break;
      default:
	panic("Device: Node Number does not exist!\n");
    }
    
    
    return pioDelay;
}




Tick
COSSIMSensorDevice::write(PacketPtr pkt)
{
  
    pkt->makeAtomicResponse();    
    switch (pkt->getAddr() - pioAddr) {
	/* Here the application partner should declare the MAX_NUMBER of sensors.              *
         * Example: max(NumberOfSensorsNode0,NumberOfSensorsNode1,NumberOfSensorsNode3, etc..) */
        case SENSOR_NUMBER_1:
	  PrecisionSensor1 = pkt->get<uint8_t>();
	  break;
	case SENSOR_NUMBER_2:
	  PrecisionSensor2 = pkt->get<uint8_t>();
	  break;
	case SENSOR_NUMBER_3:
	  PrecisionSensor3 = pkt->get<uint8_t>();
	  break;
	case SENSOR_NUMBER_4:
	  PrecisionSensor4 = pkt->get<uint8_t>();
	  break;
	//Application partner may add another sensors here
        default:
          panic("Device: Unrecognized Sensor Value!\n");
    }
           
    return pioDelay;
}

void 
COSSIMSensorDevice::SendValue(PacketPtr pkt, uint8_t Precision, float val){
  int32_t tmp_val = (int32_t) (val*pow(10,Precision));
  pkt->set(tmp_val);
}

AddrRangeList
COSSIMSensorDevice::getAddrRanges() const
{
    AddrRangeList ranges;
    ranges.push_back(RangeSize(pioAddr, pioSize));
    return ranges;
}


COSSIMSensorDevice *
COSSIMSensorDeviceParams::create()
{
    return new COSSIMSensorDevice(this);
}
