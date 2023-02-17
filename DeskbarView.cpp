#include <Alert.h>
#include <Deskbar.h>
#include <Roster.h>
#include <View.h>
#include <Window.h>
#include <Menu.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <TextView.h>
#include <stdio.h>

#include "DeskbarView.h"
#include "HardmonyApp.h"
#include "SensorReader.h"
#include "SettingsView.h"

const rgb_color COLOR_FOREGROUND = { 0, 0, 0 };

////////////////////////////////////////////////////////////////////////////////

extern "C" _EXPORT BView* instantiate_deskbar_item()
{
	return new HardmonyDBView("HardmonyDBView");
}

////////////////////////////////////////////////////////////////////////////////

HardmonyDBView::HardmonyDBView(const char name[])
	:	BView(BRect(0, 0, 15, 15), name, B_FOLLOW_ALL_SIDES,
				B_WILL_DRAW | B_PULSE_NEEDED), fMessenger(NULL),
				fMessageRunner(NULL)
{
	SetFont(be_bold_font);
	float width = StringWidth("140°") + 2;
	ResizeTo(width, 15);
	SetViewColor(B_TRANSPARENT_COLOR);
	sensor = new SensorReader();
}


HardmonyDBView::HardmonyDBView(BMessage* message)
	:	BView(message), fMessenger(NULL), fMessageRunner(NULL)
{
	sensor = new SensorReader();
}


HardmonyDBView::~HardmonyDBView()
{
	if (fMessenger != NULL && fMessenger->IsValid()) {
		fMessenger->SendMessage(MSG_QUIT);
	}
	if (fMessageRunner != NULL)
		delete fMessageRunner;
	if (sensor != NULL)
		delete sensor;
}


HardmonyDBView*
HardmonyDBView::Instantiate(BMessage* message)
{
	if (validate_instantiation(message, "HardmonyDBView"))
		return new HardmonyDBView(message);
	return NULL;
}


status_t
HardmonyDBView::Archive(BMessage* archive, bool deep) const
{
	BView::Archive(archive, deep);
	archive->AddString("add_on", "application/x-vnd.OscarL-Hardmony");
	archive->AddString("class", "HardmonyDBView");
	return B_OK;
}


void
HardmonyDBView::AttachedToWindow()
{
	fMessageRunner = new BMessageRunner(BMessenger(this), new BMessage(HARDMONY_UPDATE), 250000/*fUpdateInterval*/);
	SetViewColor(Parent()->ViewColor());
	UpdateTemp();
}


void
HardmonyDBView::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case HARDMONY_UPDATE:
			UpdateTemp();
			Draw(Bounds());
		break;
		case HARDMONY_QUIT: {
			BDeskbar deskbar;
			deskbar.RemoveItem(Name());
		}
		break;
		case HARDMONY_SETTINGS:
			if (fMessenger == NULL || !fMessenger->IsValid()) {
				BDeskbar deskbar;
				BRect frame(deskbar.Frame());
				BWindow *window = new BWindow(BRect(frame.right - 280 -8, frame.bottom+10,
										frame.right-14, frame.bottom + 200),
										"Settings", B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
										B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK);
				BView *view = new HardmonySettingsView("Settings");
				view->Pulse();
				window->AddChild(view);
				window->SetPulseRate(1000000LL);
				window->Show();
				fMessenger = new BMessenger(view);
			}
		break;
		case B_ABOUT_REQUESTED:
			OnAboutRequested();
		break;
		case B_QUIT_REQUESTED:
			OnQuitRequested();
		break;
		default:
			BView::MessageReceived(message);
		break;
	}
}


void
HardmonyDBView::Draw(BRect updateRect)
{
	char string[5];
	sprintf(string, "%3d°", UpdateTemp());

	font_height height;         // center the text horizontally
	GetFontHeight(&height);     // and vertically in the Deskbar
	BRect rect = Bounds();
	float width = StringWidth(string);
	float x = 1 + (rect.Width() - width)/2;
	float y = height.ascent + (rect.Height() - (height.ascent + height.descent))/2;
	SetHighColor(Parent()->ViewColor());
	FillRect(updateRect);
	SetLowColor(Parent()->ViewColor());
	SetHighColor(COLOR_FOREGROUND);
	SetDrawingMode(B_OP_OVER);
	DrawString(string, BPoint(x, y));
}


void
HardmonyDBView::Pulse()
{
/*
	char string[5];
	sprintf(string, "%3d°", UpdateTemp());

	font_height height;         // center the text horizontally
	GetFontHeight(&height);     // and vertically in the Deskbar
	BRect rect = Bounds();
	float width = StringWidth(string);
	float x = 1 + (rect.Width() - width)/2;
	float y = height.ascent + (rect.Height() - (height.ascent + height.descent))/2;
	FillRect(updateRect);
	DrawString(string, BPoint(x, y));
*/
}


int
HardmonyDBView::UpdateTemp()
{
	sensor->Update();
	return (int) sensor->Temps[2];
}


void
HardmonyDBView::MouseDown(BPoint where)
{
	int32 buttons, clicks;

	if (Window()->CurrentMessage()->FindInt32("buttons", &buttons) != B_OK ||
		Window()->CurrentMessage()->FindInt32("clicks", &clicks) != B_OK)
		return;

	if (buttons == B_SECONDARY_MOUSE_BUTTON) {
		BPopUpMenu *popUpMenu = new BPopUpMenu("HardmonyMenu");

		popUpMenu->AddItem(new BMenuItem("Open", new BMessage(HARDMONY_OPEN_WIN)));
		popUpMenu->AddItem(new BMenuItem("Settings...", new BMessage(HARDMONY_SETTINGS)));
		popUpMenu->AddSeparatorItem();
		popUpMenu->AddItem(new BMenuItem("About...", new BMessage(B_ABOUT_REQUESTED)));
		popUpMenu->AddSeparatorItem();
		popUpMenu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED)));
		popUpMenu->SetTargetForItems(this);

		popUpMenu->Go(ConvertToScreen(BPoint(0, 0)), true, false, false);
		delete popUpMenu;
	}
	else if (buttons == B_PRIMARY_MOUSE_BUTTON) {
		be_roster->Launch(HARDMONY_APP_SIGNATURE);
	}
}


void
HardmonyDBView::OnAboutRequested()
{
	(new BAlert(NULL, "Hardmony " VERSION "\n"
		"Hardware Monitoring Made Easy.\n"
		"by Oscar Lesta\n\n" "Hi Mom!.\n", "Duh!"))->Go(NULL);
}


void
HardmonyDBView::OnQuitRequested()
{
	BDeskbar deskbar;
	deskbar.RemoveItem(Name());
}
