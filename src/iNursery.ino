
#include <LiquidCrystal.h>
#include <PID_v1.h>

#include "TempSensor.hpp"
#include "Peltier.hpp"

#define BUTTON_ADC_PIN           A0  // A0 is the button ADC input
#define LCD_BACKLIGHT_PIN         3  // D3 controls LCD backlight
// ADC readings expected for the 5 buttons on the ADC input
#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            145  // up
#define DOWN_10BIT_ADC          329  // down
#define LEFT_10BIT_ADC          505  // left
#define SELECT_10BIT_ADC        741  // right
#define BUTTONHYSTERESIS         10  // hysteresis for valid button sensing window

LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );
TempSensorNs::TempSensor tempSensor(1, 0.001);
PeltierNs::Peltier peltier(10, 11);

double setTemp = 28.0;
double actTemp = 0.0;
double pidOutput = 0;
//Define Variables we'll be connecting to

typedef enum{
	OFF,
	ONE,
	TWO,
	THREE
} ledState_t;

ledState_t ledState;

typedef enum{
	TEMP,
	LIGHTS,
	DRIVE_STATE
} screenState_t;

screenState_t screenState = TEMP;

typedef enum{
	DRIVE_OFF,
	COOLING,
	HEATING
} driveState_t;

driveState_t driveState = DRIVE_OFF;

//Specify the links and initial tuning parameters
PID myPid(&actTemp, &pidOutput, &setTemp, 80.0, 0.0, 0.0, DIRECT);

//LcdMenu::Menu mainMenu;

void PrintMainScreen();

void setup()
{

  /* add setup code here */

	lcd.begin(16, 2);
	lcd.print(" iNursery v1.0  ");
	delay(2000);

	lcd.setCursor(0,0);	
	lcd.print("                ");
	lcd.setCursor(0,0);	
	lcd.print("MERRY XMAS 2013 ");
	lcd.setCursor(0,1);	
	lcd.print("     RUTHIE     ");
	
	delay(2000);
	lcd.setCursor(0,0);	
	lcd.print("                ");
	lcd.setCursor(0,1);	
	lcd.print("                ");
	lcd.setCursor(0,0);	
	lcd.print("    LOVE GEO    ");
	
	delay(2000);
	lcd.setCursor(0,0);	
	lcd.print("                ");
	lcd.setCursor(0,1);	
	lcd.print("                ");
	lcd.setCursor(0,0);	
	lcd.print(" iNursery v1.0  ");
	
	pinMode(2, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	
	// Turn PID on
	myPid.SetMode(AUTOMATIC);
	myPid.SetOutputLimits(-255.0, 255.0);
}

void loop()
{
	// Delay for good push-button response
	delay(200);
	PrintMainScreen();
	//tempSensor.ReadTemp();
	//mainMenu.Display();
}

void PrintMainScreen()
{
	static uint32_t screenCount = 0;

	double lcdButtonAdcInput = (double)analogRead(0);
	actTemp = tempSensor.ReadTemp();
	
	// Check set-point buttons
	if((lcdButtonAdcInput > UP_10BIT_ADC - BUTTONHYSTERESIS) && (lcdButtonAdcInput < UP_10BIT_ADC + BUTTONHYSTERESIS))
	{
		screenState = TEMP;
		screenCount = 0;
		lcd.setCursor(0,1);
		lcd.print("                ");
		setTemp = setTemp + 1.0;
	}
	
	if((lcdButtonAdcInput > DOWN_10BIT_ADC - BUTTONHYSTERESIS) && (lcdButtonAdcInput < DOWN_10BIT_ADC + BUTTONHYSTERESIS))
	{
		screenState = TEMP;
		screenCount = 0;
		lcd.setCursor(0,1);
		lcd.print("                ");
		setTemp = setTemp - 1.0;
	}
	
	// Check LED button
	if((lcdButtonAdcInput > SELECT_10BIT_ADC - BUTTONHYSTERESIS) && (lcdButtonAdcInput < SELECT_10BIT_ADC  + BUTTONHYSTERESIS))
	{
		screenState = LIGHTS;
		screenCount = 0;
		lcd.setCursor(0,1);
		lcd.print("                ");
	
		switch(ledState)
		{
			case OFF:
				ledState = THREE;
				digitalWrite(2, HIGH);
				digitalWrite(12, HIGH);
				digitalWrite(13, HIGH);
				break;
			case ONE:
				ledState = OFF;
				digitalWrite(2, LOW);
				digitalWrite(12, LOW);
				digitalWrite(13, LOW);
				break;
			case TWO:
				ledState = ONE;
				digitalWrite(2, HIGH);
				digitalWrite(12, LOW);
				digitalWrite(13, LOW);
				break;
				
			case THREE:
				ledState = TWO;
				digitalWrite(2, HIGH);
				digitalWrite(12, HIGH);
				digitalWrite(13, LOW);
				break;
		}
	}
	
	
	// Run PID
	myPid.Compute();
	if(pidOutput > 0.0)
	{
		driveState = HEATING;
		peltier.Heat((uint8_t)pidOutput);
	}
	else if(pidOutput < 0.0)
	{
		driveState = COOLING;
		peltier.Cool(uint8_t(pidOutput*-1.0));
	}
	else
	{
		driveState = DRIVE_OFF;
		peltier.Off();
	}
	
	
	// Set LCD to start of second row
	//lcd.setCursor(0,0);
	
	if(screenCount >= 10)
	{
		screenCount = 0;
		switch(screenState)
		{
			case TEMP:
				screenState = LIGHTS;
				lcd.setCursor(0,1);
				lcd.print("                ");
				break;
				
			case LIGHTS:
				screenState = DRIVE_STATE;
				lcd.setCursor(0,1);
				lcd.print("                ");
				break;
				
			case DRIVE_STATE:
				screenState = TEMP;
				lcd.setCursor(0,1);
				lcd.print("                ");
				break;
		}
	}
	
	switch(screenState)
	{
		case TEMP:
			lcd.setCursor(0,1);
			lcd.print("ST=");
			lcd.print((int32_t)setTemp);
			lcd.print((char)223);
			lcd.print("C AT=");
			lcd.print((int32_t)actTemp);
			lcd.print((char)223);
			lcd.print("C");
			break;
		case LIGHTS:
			lcd.setCursor(0,1);
			lcd.print("  Lights: ");
			switch(ledState)
			{
				case OFF:
					lcd.print("0/3");
					break;
				case ONE:
					lcd.print("1/3");
					break;
				case TWO:
					lcd.print("2/3");
					break;
				case THREE:
					lcd.print("3/3");
					break;
			}
			break;
		case DRIVE_STATE:
			lcd.setCursor(0,1);
			switch(driveState)
			{
				case DRIVE_OFF:
					lcd.print("   Power Off    ");
					break;
				case COOLING:
					lcd.print("  Cooling ");
					lcd.print(uint8_t(((pidOutput*-1.0)/255.0)*100));
					lcd.print("%");
					break;
				case HEATING:
					lcd.print("  Heating ");
					lcd.print(uint8_t((pidOutput/255.0)*100));
					lcd.print("%");
					break;
			}

	}
	
	
	// Increment the screen counter
	screenCount++;
}