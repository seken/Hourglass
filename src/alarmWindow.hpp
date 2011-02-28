#ifndef __alarmWindow_HPP__
#define __alarmWindow_HPP__

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <sigc++/sigc++.h>
#include <vector>

#include "config.hpp"

class alarmWindow : public Gtk::Window {
	public:
		alarmWindow(int &argc, char **argv);
		~alarmWindow();

		bool on_second();

	private:
		Gtk::VBox m_topBox;
		Gtk::Label m_time;
		Gtk::Button m_snooze;
		Gtk::Button m_quit;
};

#endif //__alarmWindow_HPP__
