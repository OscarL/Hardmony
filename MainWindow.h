#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <Window.h>
#include "SensorView.h"

class SensorView;

class MainWindow : public BWindow {
public:
			MainWindow();
			~MainWindow();
	void	MessageReceived(BMessage *message);
	bool	QuitRequested();
private:
	SensorView	*fSensorView;
};

#endif
