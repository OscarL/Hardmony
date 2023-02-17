//
//  © 2003-2005 by Oscar Lesta (BiPolar)
//

#ifndef MBPROBE_APP_H
#define MBPROBE_APP_H

#include <Application.h>
#include "MainWindow.h"

#define VERSION "0.3"
#define DBREPLICANT_NAME "HardmonyDBView"

extern const char* HARDMONY_APP_SIGNATURE;

//#define HARDMONY_APP_SIGNATURE "application/x-vnd.OscarL-Hardmony"

class HardmonyApp : public BApplication {
	public :
						HardmonyApp();
		virtual			~HardmonyApp();
				void	ReadyToRun();
};

#endif // MBPROBE_APP_H
