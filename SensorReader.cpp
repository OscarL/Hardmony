#include "SensorReader.h"
#include <string.h>
#include <stdio.h>

enum sensor_access {
	Legacy,				// ie, ISA I/O at 0x290
	SMBus
};

/*
static SensorData known_sensors_info[] = {
	{	{"IT8705F"}, { 0x8705 }, { 0x290 },
		{
			{ "VCore"  , 0.0,   1.744, true}, { "+2.5" , 0.0,   2.500, true},
			{ "+3.3"   , 0.0,   3.300, true}, { "+5"   , 0.0,   5.000, true},
			{ "+12"    , 0.0,  12.000, true}, { "-12.0", 0.0, -12.000, true},
			{ "SB3V"   , 0.0,   3.000, true}, { "SB5V" , 0.0,   5.000, true},
			{ "Battery", 0.0,   3.300, true},

			{ "Motherboard", 0.0, 0.0, true}, {"CPU" , 0.0, 0.0, true},
			{ "Aux1"       , 0.0, 0.0, true}, {"Aux1", 0.0, 0.0, true},

			{ "CPU", 0.0, 0.0, true}, {"Chassis" , 0.0, 0.0, true},
			{ "Aux", 0.0, 0.0, true}
	}	},

	{	{"IT8712F"}, { 0x8712 }, { 0x290 },
		{
			{ "VCore"  , 0.0,   1.744, true}, { "+2.5" , 0.0,   2.500, true},
			{ "+3.3"   , 0.0,   3.300, true}, { "+5"   , 0.0,   5.000, true},
			{ "+12"    , 0.0,  12.000, true}, { "-12.0", 0.0, -12.000, true},
			{ "SB3V"   , 0.0,   3.000, true}, { "SB5V" , 0.0,   5.000, true},
			{ "Battery", 0.0,   3.300, true},

			{ "Motherboard", 0.0, 0.0, true}, { "CPU" , 0.0, 0.0, true},
			{ "Aux1"       , 0.0, 0.0, true}, { "Aux1", 0.0, 0.0, true},

			{ "CPU", 0.0, 0.0, true}, {"Chassis" , 0.0, 0.0, true},
			{ "Aux", 0.0, 0.0, true}
	}	},

 { {"LM87"}, {0,0}, { 0x290 },
   {{"VCore"  , 0.0,   1.744, true}, {"+2.5" , 0.0,   2.500, true},
    {"+3.3"   , 0.0,   3.300, true}, {"+5"   , 0.0,   5.000, true},
    {"+12"    , 0.0,  12.000, true}, {"-12.0", 0.0, -12.000, true},
    {"SB3V"   , 0.0,   3.000, true}, {"SB5V" , 0.0,   5.000, true},
    {"Battery", 0.0,   3.300, true},

    {"Motherboard", 0.0, 0.0, true}, {"CPU" , 0.0, 0.0, true},
    {"Aux1"       , 0.0, 0.0, true}, {"Aux1", 0.0, 0.0, true},

    {"CPU", 0.0, 0.0, true}, {"Chassis" , 0.0, 0.0, true},
    {"Aux", 0.0, 0.0, true}}
 },

 { {"LM80"}, {0,0}, { 0x290 },
   {{"VCore"  , 0.0,   1.744, true}, {"+2.5" , 0.0,   2.500, true},
    {"+3.3"   , 0.0,   3.300, true}, {"+5"   , 0.0,   5.000, true},
    {"+12"    , 0.0,  12.000, true}, {"-12.0", 0.0, -12.000, true},
    {"SB3V"   , 0.0,   3.000, true}, {"SB5V" , 0.0,   5.000, true},
    {"Battery", 0.0,   3.300, true},

    {"Motherboard", 0.0, 0.0, true}, {"CPU" , 0.0, 0.0, true},
    {"Aux1"       , 0.0, 0.0, true}, {"Aux1", 0.0, 0.0, true},

    {"CPU", 0.0, 0.0, true}, {"Chassis" , 0.0, 0.0, true},
    {"Aux", 0.0, 0.0, true}}
 },

 { {"LM78"}, {0,0}, {0x290},
   {{"VCore"  , 0.0,   1.744, true}, {"+2.5" , 0.0,   2.500, true},
    {"+3.3"   , 0.0,   3.300, true}, {"+5"   , 0.0,   5.000, true},
    {"+12"    , 0.0,  12.000, true}, {"-12.0", 0.0, -12.000, true},
    {"SB3V"   , 0.0,   3.000, true}, {"SB5V" , 0.0,   5.000, true},
    {"Battery", 0.0,   3.300, true},

    {"Motherboard", 0.0, 0.0, true}, {"CPU" , 0.0, 0.0, true},
    {"Aux1"       , 0.0, 0.0, true}, {"Aux1", 0.0, 0.0, true},

    {"CPU", 0.0, 0.0, true}, {"Chassis" , 0.0, 0.0, true},
    {"Aux", 0.0, 0.0, true}}
 },

 { {"LM75"}, {0, 0}, {0x290},
   {{""   , 0.0, 0.0, false}, {"", 0.0, 0.0, false},
    {""   , 0.0, 0.0, false}, {"", 0.0, 0.0, false},
    {""   , 0.0, 0.0, false}, {"", 0.0, 0.0, false},
    {""   , 0.0, 0.0, false}, {"", 0.0, 0.0, false},
    {""   , 0.0, 0.0, false},

    {"Motherboard", 0.0, 0.0, true}, {"", 0.0, 0.0, false},
    {""       , 0.0, 0.0, false},    {"", 0.0, 0.0, false},

    {"", 0.0, 0.0, false}, {"" , 0.0, 0.0, false},
    {"", 0.0, 0.0, false}}
 }
};
*/

SensorReader::SensorReader(void)
{
	fSensorDevice = new BFile();
/*
	for (uint i = 0; i < 9; i++)
		fVoltages[i] = 0;

	for (uint i = 0; i < 3; i++)
		fTemperatures[i] = 0;

	for (uint i = 0; i < 2; i++)
		fFans[i] = 0;
*/

	Voltages[0] = 0.0;
	Voltages[1] = 0.0;
	Voltages[2] = 0.0;
	Voltages[3] = 0.0;
	Voltages[4] = 0.0;
	Voltages[5] = 0.0;
	Voltages[6] = 0.0;
	Voltages[7] = 0.0;
	Voltages[8] = 0.0;

	Temps[0] = 0.0;
	Temps[1] = 0.0;
	Temps[2] = 0.0;
	Temps[3] = 0.0;

	Fans[0] = 0.0;
	Fans[1] = 0.0;
	Fans[2] = 0.0;
}


SensorReader::~SensorReader()
{
	delete fSensorDevice;
}


status_t
SensorReader::InitCheck()
{
	return fSensorDevice->InitCheck();
}


bool
SensorReader::Update()
{
	char buffer[512];
	char* buf = buffer;
	ssize_t bytesRead;

	fSensorDevice->SetTo("/dev/sensor/it87", B_READ_ONLY);

	if (fSensorDevice->InitCheck() != B_OK) {
		printf("fSensorDevice->InitCheck() failed.\n");
		fSensorDevice->Unset();
		return false;
	}

	bytesRead = fSensorDevice->Read(buf, 512);
	if (bytesRead < B_OK) {
		printf("Read returned %s\n", strerror(bytesRead));
		fSensorDevice->Unset();
		return false;
	}

//	printf("read %d bytes\n", bytesRead);

	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[0]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[1]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[2]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[3]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[4]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[5]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[6]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[7]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f V", &Voltages[8]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f °C", &Temps[0]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f °C", &Temps[1]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f °C", &Temps[2]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f RPM", &Fans[0]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f RPM", &Fans[1]);
	buf = strchr(buf, ':') + 1; sscanf(buf, "%f RPM", &Fans[2]);

	fSensorDevice->Unset();

	return true;
}
