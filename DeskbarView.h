#ifndef HARDMONY_DBVIEW_H
#define HARDMONY_DBVIEW_H

#include <View.h>
#include <MessageRunner.h>

#include "SensorReader.h"
#include "SensorView.h"

enum {
	HARDMONY_ABOUT	 			= 'HMAb',
	HARDMONY_OPEN_WIN 			= 'HMOW',
	HARDMONY_QUIT				= 'HMQt',
	HARDMONY_SETTINGS			= 'HMSt',
	HARDMONY_UPDATE 			= 'HMUp',
	HARDMONY_CHANGE_INTERFACE	= 'HMCI'
};

class _EXPORT HardmonyDBView : public BView {
	public:
				HardmonyDBView(const char name[]);
				HardmonyDBView(BMessage* message);
		virtual	~HardmonyDBView();

		static	HardmonyDBView*	Instantiate(BMessage* archive);
		virtual	status_t		Archive(BMessage* archive, bool deep = true) const;

		virtual void	AttachedToWindow();
		virtual void	Draw(BRect updateRect);
		virtual void	MessageReceived(BMessage* message);
		virtual void	MouseDown(BPoint where);
				void	Pulse();
				int		UpdateTemp();
	private:
		void	OnAboutRequested();
		void	OnQuitRequested();

		BMessenger*		fMessenger;
		BMessageRunner*	fMessageRunner;
		SensorReader*	sensor;
};

#endif // HARDMONY_DBVIEW_H
