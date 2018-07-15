#include "switch.h"

//function to store data in eeprom in given address
bool eepromStore(String data,size_t addr_start,size_t addr_end)
{
	if(data.length() < (addr_end - addr_start)+1)
	{
		//Serial.print("data.length():");Serial.print(data.length());Serial.print('\n');
		for (size_t i = addr_start; i < addr_end; i++)
		{
			EEPROM.put(i, 0); //clearing
			if(i < addr_start+data.length())
				EEPROM.put(i, data[i - addr_start]);//storing data
			else
				EEPROM.put(i, ' ');
		}
		EEPROM.commit();
		return 1;
	}
	return 0;
}

//function to retrieve data in eeprom in given address
String eepromRead(int addr_start,int addr_end)
{
	if((addr_end - addr_start) > 0)
	{
		String data;
		for (int i = addr_start; i < addr_end; ++i)
		{
			data += char(EEPROM.read(i));//fetching data
		}
		return data;
	}
	return "\0";
}
