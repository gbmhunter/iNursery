//!
//! @file 				TempSensor.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created			2013/12/29
//! @last-modified 	2013/12/29
//! @brief 				Driver for the temperature sensor.
//! @details
//!						See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#include <Arduino.h>
#include "TempSensor.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace TempSensorNs
{
	
	TempSensor::TempSensor(uint8_t analogPin, double alpha)
	{
		this->analogPin = analogPin;
		this->ema = new Ema(0.5);
	}

	double TempSensor::ReadTemp()
	{
		double adcVal = (double)analogRead(analogPin);
		double voltage = (adcVal/1024)*5.0;
		double temp = (voltage - 0.5)/0.01;
		return ema->Average(temp);
		//return temp;
	}
}


