#include <Alert.h>
#include <Box.h>
#include <Button.h>
#include <CheckBox.h>
#include <Deskbar.h>
#include <Entry.h>
#include <View.h>
#include <Window.h>
#include <Message.h>
#include <Roster.h>
#include <Screen.h>
#include <StringView.h>
#include <stdio.h>
#include <strings.h>

#include "HardmonyApp.h"
#include "DeskbarView.h"
#include "SensorView.h"
#include "SettingsView.h"

const BRect kViewFrame (0, 0, 240, 213);

enum volts_msgs {
	VOLTS_MIN	= 'vol1',
	VOLTS_MAX	= 'vol9'
};

enum temps_msgs {
	TEMPS_MIN	= 'tem1',
	TEMPS_MAX	= 'tem9'
};

enum fans_msgs {
	FAN_MIN	= 'fan1',
	FAN_MAX	= 'fan3'
};

const uint32 kMsgCBV1 = 'CBv1';
const uint32 kMsgCBV2 = 'CBv2';
const uint32 kMsgCBV3 = 'CBv3';
const uint32 kMsgCBV4 = 'CBv4'; 
const uint32 kMsgCBV5 = 'CBv5';
const uint32 kMsgCBV6 = 'CBv6';
const uint32 kMsgCBV7 = 'CBv7';
const uint32 kMsgCBV8 = 'CBv8';
const uint32 kMsgCBV9 = 'CBv9';

const uint32 kMsgCBT1 = 'CBt1';
const uint32 kMsgCBT2 = 'CBt2';
const uint32 kMsgCBT3 = 'CBt3';
const uint32 kMsgCBT4 = 'CBt4';

const uint32 kMsgCBF1 = 'CBf1';
const uint32 kMsgCBF2 = 'CBf2';
const uint32 kMsgCBF3 = 'CBf3';

const uint32 kMsgBtSettings = 'BSet';
const uint32 kMsgCBDeskBar = 'CBDb';


SensorView::SensorView()
	: BView(kViewFrame, "SensorView", B_FOLLOW_ALL, B_WILL_DRAW | B_PULSE_NEEDED)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	fSensor =  new SensorReader();

////////////////////////////////////////////////////////////////////////////////////////
	BRect frame(4, 4, 112, 206);
	fVoltagesBox = new BBox(frame, "fVoltagesBox"); fVoltagesBox->SetLabel("Voltages [V]");

	frame = BRect(8, 14, 62, 32);
	cbV1 = new BCheckBox(frame, "STV1", "VCore", new BMessage(kMsgCBV1));
	fVoltagesBox->AddChild(cbV1);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV2 = new BCheckBox(frame, "STV2", "+2.5", new BMessage(kMsgCBV2));
	fVoltagesBox->AddChild(cbV2);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV3 = new BCheckBox(frame, "STV3", "+3.3", new BMessage(kMsgCBV3));
	fVoltagesBox->AddChild(cbV3);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV4 = new BCheckBox(frame, "STV4", "+5.0", new BMessage(kMsgCBV4));
	fVoltagesBox->AddChild(cbV4);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV5 = new BCheckBox(frame, "STV5", "+12.0", new BMessage(kMsgCBV5));
	fVoltagesBox->AddChild(cbV5);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV6 = new BCheckBox(frame, "STV6", "-12.0", new BMessage(kMsgCBV6));
	fVoltagesBox->AddChild(cbV6);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV7 = new BCheckBox(frame, "STV7", "SB3V", new BMessage(kMsgCBV7));
	fVoltagesBox->AddChild(cbV7);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV8 = new BCheckBox(frame, "STV8", "SB5V", new BMessage(kMsgCBV8));
	fVoltagesBox->AddChild(cbV8);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbV9 = new BCheckBox(frame, "STV9", "Battery", new BMessage(kMsgCBV9));
	fVoltagesBox->AddChild(cbV9);

	frame = BRect(70, 16, 102, 30);

	stV1 = new BStringView(frame, "stV1", "0.000"); fVoltagesBox->AddChild(stV1);
	stV1->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV2 = new BStringView(frame, "stV2", "0.000"); fVoltagesBox->AddChild(stV2);
	stV2->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV3 = new BStringView(frame, "stV3", "0.000"); fVoltagesBox->AddChild(stV3);
	stV3->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV4 = new BStringView(frame, "stV4", "0.000"); fVoltagesBox->AddChild(stV4);
	stV4->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV5 = new BStringView(frame, "stV5", "0.000"); fVoltagesBox->AddChild(stV5);
	stV5->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV6 = new BStringView(frame, "stV6", "0.000"); fVoltagesBox->AddChild(stV6);
	stV6->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV7 = new BStringView(frame, "stV7", "0.000"); fVoltagesBox->AddChild(stV7);
	stV7->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV8 = new BStringView(frame, "stV8", "0.000"); fVoltagesBox->AddChild(stV8);
	stV8->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stV9 = new BStringView(frame, "stV9", "0.000"); fVoltagesBox->AddChild(stV9);
	stV9->SetAlignment(B_ALIGN_RIGHT);

	AddChild(fVoltagesBox);

////////////////////////////////////////////////////////////////////////////////////////
	frame = BRect(116, 4, 236, 104);
	fTemperaturesBox = new BBox(frame, "fTemperaturesBox"); fTemperaturesBox->SetLabel("Temperatures [°C]");

	frame = BRect(8, 14, 90, 32);
	cbTemp1 = new BCheckBox(frame, "STTemp1", "Motherboard", new BMessage(kMsgCBT1));
	fTemperaturesBox->AddChild(cbTemp1);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbTemp2 = new BCheckBox(frame, "STTemp2", "CPU", new BMessage(kMsgCBT2));
	fTemperaturesBox->AddChild(cbTemp2);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbTemp3 = new BCheckBox(frame, "STTemp3", "Aux1", new BMessage(kMsgCBT3));
	fTemperaturesBox->AddChild(cbTemp3);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbTemp4 = new BCheckBox(frame, "STTemp4", "Aux2", new BMessage(kMsgCBT4));
	fTemperaturesBox->AddChild(cbTemp4);

	frame = BRect(94, 16, 114, 30);
	stTemp1 = new BStringView(frame, "stTemp1", "000"); fTemperaturesBox->AddChild(stTemp1);
	stTemp1->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stTemp2 = new BStringView(frame, "stTemp2", "000"); fTemperaturesBox->AddChild(stTemp2);
	stTemp2->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stTemp3 = new BStringView(frame, "stTemp3", "000"); fTemperaturesBox->AddChild(stTemp3);
	stTemp3->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stTemp4 = new BStringView(frame, "stTemp4", "000"); fTemperaturesBox->AddChild(stTemp4);
	stTemp4->SetAlignment(B_ALIGN_RIGHT);

	AddChild(fTemperaturesBox);

////////////////////////////////////////////////////////////////////////////////////////
	frame = BRect(116, 108, 236, 186);
	fFanSpeedsBox = new BBox(frame, "bFanSpeeds");
	fFanSpeedsBox->SetLabel("Fan Speeds [RPM]");

	frame = BRect(8, 14, 70, 32);
	cbFan1 = new BCheckBox(frame, "STFan1", "CPU", new BMessage(kMsgCBF1));
	fFanSpeedsBox->AddChild(cbFan1);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbFan2 = new BCheckBox(frame, "STFan2", "Chassis", new BMessage(kMsgCBF2));
	fFanSpeedsBox->AddChild(cbFan2);
	frame.top = frame.bottom + 2; frame.bottom = frame.top + 18;
	cbFan3 = new BCheckBox(frame, "STFan3", "Aux", new BMessage(kMsgCBF3));
	fFanSpeedsBox->AddChild(cbFan3);

	frame = BRect(90, 16, 114, 30);
	stFan1 = new BStringView(frame, "stFan1", "0000");
	fFanSpeedsBox->AddChild(stFan1);
	stFan1->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stFan2 = new BStringView(frame, "stFan2", "0000");
	fFanSpeedsBox->AddChild(stFan2);
	stFan2->SetAlignment(B_ALIGN_RIGHT);
	frame.top = frame.bottom + 6; frame.bottom = frame.top + 14;
	stFan3 = new BStringView(frame, "stFan3", "0000");
	fFanSpeedsBox->AddChild(stFan3);
	stFan3->SetAlignment(B_ALIGN_RIGHT);

	AddChild(fFanSpeedsBox);

////////////////////////////////////////////////////////////////////////////////////////
	frame = BRect(116, 188, 176, 206);
	btSettings = new BButton(frame, "btSettings", "Settings", new BMessage(kMsgBtSettings));
	btSettings->ResizeTo(60, 18);
	AddChild(btSettings);
	frame.left = frame.right + 2; frame.right = frame.left + 60;
	cbDeskbar = new BCheckBox(frame, "cbDeskbar", "Deskbar", new BMessage(kMsgCBDeskBar));
	AddChild(cbDeskbar);

	if (AlreadyInDeskbar())
		cbDeskbar->SetValue(B_CONTROL_ON);

////////////////////////////////////////////////////////////////////////////////////////
}


SensorView::~SensorView()
{
	delete fSensor;
//	delete fMessenger;
}


void
SensorView::AttachedToWindow()
{
	Pulse();
}


void
SensorView::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
		case kMsgCBV1:
		case kMsgCBV2:
		case kMsgCBV3:
		case kMsgCBV4:
		case kMsgCBV5:
		case kMsgCBV6:
		case kMsgCBV7:
		case kMsgCBV8:
		case kMsgCBV9:
		case kMsgCBT1:
		case kMsgCBT2:
		case kMsgCBT3:
		case kMsgCBT4:
		case kMsgCBF1:
		case kMsgCBF2:
		case kMsgCBF3:
			CheckBoxChanged(msg->what);
		break;
		case kMsgBtSettings:
			SettingsWindowRequested();
		break;
		case kMsgCBDeskBar:
			LiveInDeskbarChanged();
		break;
		default:
			BView::MessageReceived(msg);
		break;
	}
}


void
SensorView::CheckBoxChanged(uint32 id)
{

}


void
SensorView::SettingsWindowRequested(void)
{
//	if (fMessenger != NULL || fMessenger->IsValid())
//		return;

	BDeskbar deskbar;
	BRect frame(deskbar.Frame());
	BWindow *window = new BWindow(BRect(frame.right - 280 -8, frame.bottom+10,
						frame.right-14, frame.bottom + 200),
						"Settings", B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
						B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK);
	BView *view = new HardmonySettingsView("Settings");
	window->AddChild(view);
	window->Show();
//	fMessenger = new BMessenger(view);
}


void
SensorView::LiveInDeskbarChanged(void)
{
	if (!LoadInDeskbar()) {
		BAlert* alert = new BAlert(NULL, "Doesnt work :(", "OK");
		alert->Go(NULL);
	}
}


void
SensorView::Pulse()
{
	char text[15];

	if (!fSensor->Update())	// Too early to update values? leave now...
		return;

	if (!Window()->Lock())
		return;

/*
	for (uint i = 0; i < MAX_VOLTAGES; i++)
		sprintf(text, "%2.3f", sensor[i].volt); fItem[i]->Label->SetText(text);

	for (uint i = 0; i < MAX_TEMPS; i++)
		sprintf(text, "%2.3f", sensor[i].temp); fItem[i]->Label->SetText(text);

	for (uint i = 0; i < MAX_FANS; i++)
		sprintf(text, "%2.3f", sensor[i].fan); fItem[i]->Label->SetText(text);
*/
	// Voltages
	sprintf(text, "%2.3f", fSensor->Voltages[0]); stV1->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[1]); stV2->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[2]); stV3->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[3]); stV4->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[4]); stV5->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[5]); stV6->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[6]); stV7->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[7]); stV8->SetText(text);
	sprintf(text, "%2.3f", fSensor->Voltages[8]); stV9->SetText(text);
	// Temperatures
	sprintf(text, "%1.0f", fSensor->Temps[0]); stTemp1->SetText(text);
	sprintf(text, "%1.0f", fSensor->Temps[1]); stTemp2->SetText(text);
	sprintf(text, "%1.0f", fSensor->Temps[2]); stTemp3->SetText(text);
	sprintf(text, "%1.0f", fSensor->Temps[3]); stTemp4->SetText(text);
	// Fans
	sprintf(text, "%1.0f", fSensor->Fans[0]); stFan1->SetText(text);
	sprintf(text, "%1.0f", fSensor->Fans[1]); stFan2->SetText(text);
	sprintf(text, "%1.0f", fSensor->Fans[2]); stFan3->SetText(text);

	Window()->Unlock();
}


bool
SensorView::LoadInDeskbar()
{
	BDeskbar deskbar;
	entry_ref entry;

	if (!deskbar.HasItem("HardmonyDBView"))	{
		if (be_roster->FindApp(HARDMONY_APP_SIGNATURE, &entry) != B_OK) {
			BAlert *alert = new BAlert("Error",
//				"be_roster->FindApp(" HARDMONY_APP_SIGNATURE ") failed!",
				"be_roster->FindApp(HARDMONY_APP_SIGNATURE) failed!",
				"What the Heck?!", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT);
			alert->Go();
		}

		if (deskbar.AddItem(&entry) != B_OK) {
			BAlert *alert = new BAlert("Error",
				"Can't install Hardmony in the Deskbar!",
				"Oscar can't code!", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT);
			alert->Go();
		}
	}

	return true;
}


bool
SensorView::AlreadyInDeskbar()
{
	BDeskbar deskbar;
	if (deskbar.HasItem("HardmonyDBView"))
		return true;

	return false;
}
