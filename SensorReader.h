#ifndef	SENSOREADER_H
#define	SENSOREADER_H

#include <storage/File.h>

struct SensorValue {
	char* 	Name;
	float	Value;
	float	NominalValue;
	bool	Enabled;
};


struct SensorData {
	char*	Name;
	uint8	Model[2];
	uint	Address;
//	bool	Enabled;
	SensorValue	Values[16]; //9+4+3
};


class SensorReader {
	public:
							SensorReader();
		virtual 			~SensorReader();
				status_t	InitCheck();
				bool		Update();

		float Voltages[9];
		float Temps[4];
		float Fans[3];

	private:
		BFile*	fSensorDevice;
};

#endif // SENSOREADER_H
