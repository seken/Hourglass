#ifndef __mainWindow_HPP__
#define __mainWindow_HPP__

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <sigc++/sigc++.h>
#include <vector>

#include "config.hpp"
#include "task.hpp"

class mainWindow : public Gtk::Window {
	public:
		mainWindow(int &argc, char **argv);
		~mainWindow();

		bool on_second();

	private:
		bool m_fullscreen;

		Gtk::VBox m_topBox;
		Gtk::Label m_time;
		Gtk::Label m_date;
		Gtk::Button m_homeButton;

		// on_second connection
		sigc::connection m_timer;

		config m_config;

		std::vector<task*> m_tasks;
};

#endif//__mainWindow_HPP__
