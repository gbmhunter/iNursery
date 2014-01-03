//!
//! @file 				Peltier.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created			2013/12/29
//! @last-modified 	2013/12/29
//! @brief 				Driver for the peltier unit.
//! @details
//!						See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#include <Arduino.h>
#include "Peltier.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace PeltierNs
{
	Peltier::Peltier(uint8_t coolPin, uint8_t heatPin)
	{
		this->coolPin = coolPin;
		this->heatPin = heatPin;
		
		digitalWrite(this->coolPin, LOW);
		digitalWrite(this->heatPin, LOW);
		
		// Set pins to outputs
		pinMode(this->coolPin, OUTPUT);
		pinMode(this->heatPin, OUTPUT);
		
		digitalWrite(this->coolPin, LOW);
		digitalWrite(this->heatPin, LOW);
	}

	void Peltier::Cool(uint8_t pwmValue)
	{
		analogWrite(this->heatPin, 0.0);
		analogWrite(this->coolPin, pwmValue);
	}
	
	void Peltier::Heat(uint8_t pwmValue)
	{
		analogWrite(this->coolPin, 0.0);
		analogWrite(this->heatPin, pwmValue);
	}
	
	void Peltier::Off()
	{
		// Turn both cooling and heating off
		analogWrite(this->coolPin, 0.0);
		analogWrite(this->heatPin, 0.0);
	}
}


