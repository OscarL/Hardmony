#ifndef HARDMONY_SETTINGS_VIEW_H
#define HARDMONY_SETTINGS_VIEW_H

#include <View.h>
#include <Message.h>

enum {
	MSG_QUIT				= 100000,
	MSG_CHANGE_INTERFACE	= 100001
};


class HardmonySettingsView : public BView
{
	public:
					HardmonySettingsView(const char name[]);
		virtual		~HardmonySettingsView();

			void	AttachedToWindow();
			void	MessageReceived(BMessage* msg);
};

#endif // HARDMONY_SETTINGS_VIEW_H
