/*
 * sensor_data.c
 *
 * Created: 10/3/2019 4:38:34 PM
 *  Author: Vivek Anchalia - Microchip Technology Inc
 */ 

#include "sensor_data.h"
#include "sio2host.h"

#if defined MISOL_WEATHER_STATION
#define IDENTIFY_TYPE  0x24
uint8_t rawSensorData[17];
//function to receive complete serial data from weather station
bool serialGetSensorData(void)
{
	// variable to store first byte coming from weather station
	uint8_t identifyByte;
	// Sensor Data + CRC + CheckSum
	int i = 1;
	identifyByte = sio2host_getchar();
	if (identifyByte == IDENTIFY_TYPE)
	{
		int rxChar;
		while(i < 17)
		{
			if((-1) != (rxChar = sio2host_getchar_nowait()))
			{
				rawSensorData[i++] = rxChar;
			}
		}
		rawSensorData[0] = identifyByte;
		#if defined (ENABLE_SENSOR_DEBUG)
			printf("\r\n..rawSensorDataReceived..\r\n");
		#endif
		uint8_t sum = 0;
		// checksum check
		// According to MISOL WEATHER STATUION PROTOCOL sum of 16 bytes received = 17th byte
		for (i = 0; i < 16; i++)
		{
			sum = sum + rawSensorData[i];
		}
		if (sum == rawSensorData[16])
		return true;
		else return false;
	}
	else
		return false;

}

uint16_t extractWindDirection(void)
{
	uint16_t wd = 0;
	// WindDirection (deg) is a combination from Nibbles 5th - 7th values
	if (rawSensorData[0] == 0x24)
	{
		wd = (uint16_t) (rawSensorData[2]) + ((uint16_t) ((rawSensorData[3] & 80)) << 1);
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nWind Direction(deg): %d \r\n",wd);
		#endif
	}
	return wd;
}


double extractTemperature(void)
{
	double temperature = 0;
	// Temperature value is a combination from Nibbles 8th, 9th and 10th values
	// Temperature = ((0x0(8th Nibble)00 + 9th Nibble + 10th Nibble) - 400)/10
	if (rawSensorData[0] == 0x24)
	{
		double x1 = (uint16_t) ((rawSensorData[3]) << 8 & 0x0F00);
		double x2 = (uint16_t) rawSensorData[4];
		temperature = (((x1 + x2)- 400)/10);
		#if defined (ENABLE_SENSOR_DEBUG)
			printf("\r\nTemperature: %f C\r\n",temperature);
		#endif
	}
	return temperature;
}

uint8_t extractHumidity(void)
{
	uint8_t hum = 0;
	// Humidity percentage is a raw combination from Nibbles 11th and 12th values
	// Extract 11th and 12th Nibble
	if (rawSensorData[0] == 0x24)
	{
		hum = rawSensorData[5];
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nHumidity (percentage): %d \r\n",hum);
		#endif
	}
	return hum;
}

double extractWindSpeed(void)
{
	double ws = 0;
	// Wind Speed m/s is a combination from Nibbles 13th and 14th values
	// Wind Speed = ((13th Nibble << 4* 0xF0 + 14th Nibble)/8) * 1.12
	if (rawSensorData[0] == 0x24)
	{
		ws = (rawSensorData[6]/8) * 1.12; 
		#if defined (ENABLE_SENSOR_DEBUG)
			printf("\r\nWind Speed(m/s): %f \r\n",ws);
		#endif
	}
	return ws;
}

double extractGustSpeed(void)
{
	double gs = 0;
	// Gust Speed m/s is a combination from Nibbles 15th and 16th values
	// Gust Speed = ((15th Nibble << 4* 0xF0 + 16th Nibble)) * 1.12
	if (rawSensorData[0] == 0x24)
	{
		gs = (rawSensorData[7]) * 1.12;
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nGust Speed(m/s): %f \r\n",gs);
		#endif
	}
	return gs;
}

float extractRainfall(void)
{
	float rf = 0;
	// Rain Fall mm is a combination from Nibbles 17th - 20th values
	// Rain Fall = ((17th Nibble << 4 * 0xF0 + 18th Nibble)) << 8 * 0xFF00 + (19th Nibble << 4 * 0x00F0 + 20th Nibble))
	if (rawSensorData[0] == 0x24)
	{
		rf = (uint16_t) ((rawSensorData[8]) << 8 & 0xFF00) + (uint16_t) rawSensorData[9];
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nRain Fall(mm): %f \r\n",rf);
		#endif
	}
	return rf;
}

uint16_t extractUV(void)
{
	uint16_t uv = 0;
	// UV uW/cm^2 is a combination from Nibbles 21th - 24th values
	// Rain Fall = ((21th Nibble << 4 * 0xF0 + 22th Nibble)) << 8 * 0xFF00 + (23th Nibble << 4 * 0x00F0 + 24th Nibble))
	if (rawSensorData[0] == 0x24)
	{
		uv = (uint16_t) ((rawSensorData[10]) << 8 & 0xFF00) + (uint16_t) rawSensorData[11];
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nuv(uW/cm^2): %d \r\n",uv);
		#endif
	}
	return uv;
}

uint32_t extractLight(void)
{
	int light = 0;
	// light (LUX) is a combination from Nibbles 25th - 30th values
	// light = ((26th Nibble << 4 * 0xF0 + 27th Nibble)) << 8 * 0x00FF00 + (29th Nibble << 4 * 0x0000F0 + 30th Nibble))
	if (rawSensorData[0] == 0x24)
	{
		light = (uint32_t) ((rawSensorData[12]) << 16 & 0xFF0000) + (uint32_t) ((rawSensorData[13] << 8) & 0x00FF00) + (uint32_t) rawSensorData[14];
		#if defined (ENABLE_SENSOR_DEBUG)
		printf("\r\nLight (LUX): %d \r\n",light);
		#endif
	}
	return light;
}
#endif