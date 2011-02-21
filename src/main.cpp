#include <stdio.h>
#include <gtkmm/main.h>
#include <mainWindow.hpp>

int main(int argc, char **argv) {

	Gtk::Main kit(argc, argv);
	mainWindow window(argc, argv);
	Gtk::Main::run(window);

	return -1;
}
