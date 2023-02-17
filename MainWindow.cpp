#include <Alert.h>
#include <Application.h>
#include "MainWindow.h"

MainWindow::MainWindow(void)
	: BWindow(BRect(800-244, 49, 796, 261), "Hardmony",
		B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
		B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK)
{
	fSensorView = new SensorView();
	AddChild(fSensorView);
	SetPulseRate(2000000); // two seconds
}

MainWindow::~MainWindow(void)
{
//	delete fSensorView;
}

void MainWindow::MessageReceived(BMessage *message)
{
	if (! message->IsSystem()) {
		fSensorView->MessageReceived(message);
	}
	else
		switch (message->what) {
			default:
				BWindow::MessageReceived(message);
			break;
		}
}

bool MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
