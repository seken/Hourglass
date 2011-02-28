#include <gtkmm/main.h>
#include "alarmWindow.hpp"

int main(int argc, char **argv) {
	Gtk::Main kit(argc, argv);
	alarmWindow window(argc, argv);
	Gtk::Main::run(window);

	return -1;
}
