#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <Box.h>
#include <View.h>
#include <CheckBox.h>
#include <StringView.h>
#include "SensorReader.h"

struct sensed_item {
	BCheckBox*		ItemName;	// [] ItemName		Value;
	BStringView*	Value;
};

class SensorView : public BView {
	public:
						SensorView();
		virtual			~SensorView();

		virtual void	AttachedToWindow();
		virtual void	MessageReceived(BMessage* msg);
		virtual	void	Pulse();

				bool	AlreadyInDeskbar();
				bool	LoadInDeskbar();

	private:
				void	CheckBoxChanged(uint32);
				void	LiveInDeskbarChanged();
				void	SettingsWindowRequested();

				void	Init();
				void	Uninit();

		BHandler*		fHandler;
		BMessage*		fChangeMessage;
		BMessenger*		fMessenger;

		SensorReader*	fSensor;

		BBox*	fVoltagesBox;
		BBox*	fTemperaturesBox;
		BBox*	fFanSpeedsBox;

		// sensed_item fVoltages[9];
		// sensed_item fTemperatures[3];
		// sensed_item fFANs[3];

		BStringView*	stV1;
		BStringView*	stV2;
		BStringView*	stV3;
		BStringView*	stV4;
		BStringView*	stV5;
		BStringView*	stV6;
		BStringView*	stV7;
		BStringView*	stV8;
		BStringView*	stV9;
		BStringView*	stTemp1;
		BStringView*	stTemp2;
		BStringView*	stTemp3;
		BStringView*	stTemp4;
		BStringView*	stFan1;
		BStringView*	stFan2;
		BStringView*	stFan3;

		BCheckBox*	cbV1;
		BCheckBox*	cbV2;
		BCheckBox*	cbV3;
		BCheckBox*	cbV4;
		BCheckBox*	cbV5;
		BCheckBox*	cbV6;
		BCheckBox*	cbV7;
		BCheckBox*	cbV8;
		BCheckBox*	cbV9;
		BCheckBox*	cbTemp1;
		BCheckBox*	cbTemp2;
		BCheckBox*	cbTemp3;
		BCheckBox*	cbTemp4;
		BCheckBox*	cbFan1;
		BCheckBox*	cbFan2;
		BCheckBox*	cbFan3;

		BButton*	btSettings;
		BCheckBox*	cbDeskbar;
};

#endif // SENSORVIEW_H
