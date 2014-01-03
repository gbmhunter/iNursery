//!
//! @file 				TempSensor.hpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created			2013/12/29
//! @last-modified 	2013/12/29
//! @brief 				Driver for the temperature sensor.
//! @details
//!						See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace TempSensorNs
{
	
	class Ema
	{
		public:
		 double alpha;
		 double oldValue;
		 
		 Ema(double alpha)
		 {
			  this->alpha = alpha;
			  oldValue = 0;
		 }

		 double Average(double value)
		 {
			  if (oldValue == 0)
			  {
					oldValue = value;
					return value;
			  }
			  double newValue = oldValue + alpha * (value - oldValue);
			  oldValue = newValue;
			  return newValue;
		 }
	};

	class TempSensor
	{
		public:
		
			double offsetVoltage;
			double voltageRisePerDegree;
			uint8_t analogPin;
			
			TempSensor(uint8_t analogPin, double alpha);
			
			double ReadTemp();
			
		protected:
			Ema* ema;
			// none
	};
}

#endif	// #ifndef TEMP_SENSOR_H


