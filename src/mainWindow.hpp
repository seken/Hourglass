#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <sigc++/sigc++.h>

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
};
