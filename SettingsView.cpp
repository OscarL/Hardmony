#include <Box.h>
#include <StringView.h>
#include <Window.h>

#include "SettingsView.h"

HardmonySettingsView::HardmonySettingsView(const char name[])
	: BView(BRect(0, 0, 279, 199), name, B_FOLLOW_ALL_SIDES, 0)
{
	BRect r(Window()->Bounds());
//	BBox* box = new BBox(BRect(4, 4, 264, 190), "SettingsBox");
	BBox* box = new BBox(r, "SettingsBox");
	box->SetLabel("Settings");
	box->AddChild(new BStringView(BRect(10, 20, 180, 32), "Text1", "Here you'll find some options..."));
	box->AddChild(new BStringView(BRect(10, 40, 180, 52), "Text2", "in the next version :-)"));
	AddChild(box);
}


HardmonySettingsView::~HardmonySettingsView()
{

}


void
HardmonySettingsView::AttachedToWindow()
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	BView::AttachedToWindow();
}


void
HardmonySettingsView::MessageReceived(BMessage* msg)
{
	if (msg->what == MSG_QUIT)
		Window()->Quit();
	else
		BView::MessageReceived(msg);
}
