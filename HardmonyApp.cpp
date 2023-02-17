//
//  © 2003-2005 by Oscar Lesta (BiPolar)
//

#include <Alert.h>
#include <Deskbar.h>
#include <Entry.h>
#include <Roster.h>
#include "HardmonyApp.h"

const char* HARDMONY_APP_SIGNATURE = "application/x-vnd.OscarL.Hardmony";

HardmonyApp::HardmonyApp()
	: BApplication(HARDMONY_APP_SIGNATURE)
{
	MainWindow *fMainWindow = new MainWindow();
	fMainWindow->Show();
}


HardmonyApp::~HardmonyApp()
{

}


void HardmonyApp::ReadyToRun()
{

}


int main()
{
	HardmonyApp Application;
	Application.Run();
	return B_OK;
}
