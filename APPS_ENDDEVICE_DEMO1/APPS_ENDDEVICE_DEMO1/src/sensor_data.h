/*
 * sensor_data.h
 *
 * Created: 10/3/2019 4:38:22 PM
 *  Author: Vivek Anchalia - Microchip Technology Inc
 */ 


#ifndef SENSOR_DATA_H_
#define SENSOR_DATA_H_

#include <asf.h>
/*MACRO DEFINITION*/

#define ENABLE_SENSOR_DEBUG
#define MISOL_WEATHER_STATION 
//#define SEND_DUMMY_WEATHER_STATION_DATA


#if defined MISOL_WEATHER_STATION
	#define TOTAL_DATA_LENGTH 17
	extern uint8_t rawSensorData[TOTAL_DATA_LENGTH];
	#define SECURITY_CODE 0x0D
	//function to receive complete serial data from weather station
	bool serialGetSensorData(void);
	uint16_t extractWindDirection(void);
	double extractTemperature(void);
	uint8_t extractHumidity(void);
	double extractWindSpeed(void);
	double extractGustSpeed(void);
	float extractRainfall(void);
	uint16_t extractUV(void);
	uint32_t extractLight(void);
#endif

#endif /* SENSOR_DATA_H_ */