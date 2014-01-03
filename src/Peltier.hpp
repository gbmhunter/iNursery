//!
//! @file 				Peltier.hpp
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

#ifndef PELTIER_H
#define PELTIER_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace PeltierNs
{
	class Peltier
	{
		public:
			
			uint8_t coolPin;
			uint8_t heatPin;
			
			Peltier(uint8_t coolPin, uint8_t heatPin);
			void Cool(uint8_t pwmValue);
			void Heat(uint8_t pwmValue);
			void Off();
			
		protected:
			// none
	};
}

#endif	// #ifndef TEMP_SENSOR_H


