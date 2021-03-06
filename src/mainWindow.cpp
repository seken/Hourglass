#include <mainWindow.hpp>
#include <glibmm/optioncontext.h>
#include <glibmm/optiongroup.h>
#include <glibmm/optionentry.h>
#include <sigc++/bind.h>
#include <iostream>
#include <time.h>
#include <config.h>

#ifdef JOGGLER
#include "joggler.hpp"
#endif //JOGGLER

mainWindow::mainWindow(int &argc, char **argv) : Gtk::Window(),
		m_fullscreen(false),
		m_time("00:00 am"),
		m_date("Monday, 21 Febuary 2011"),
		m_homeButton("Menu") {
	// Command line parser
	Glib::OptionContext prgOpt;
	prgOpt.set_help_enabled();
	prgOpt.set_ignore_unknown_options(true);
	prgOpt.set_description("A Gtk based alarm clock");

	// Config file (xml)
	std::string configFile = "~/.hourglass/config.xml";

	// Main Options
	Glib::OptionGroup mGrp("", "");

	Glib::OptionEntry fOpt;
	fOpt.set_long_name("fullscreen");
	fOpt.set_short_name('f');
	mGrp.add_entry(fOpt, m_fullscreen);

	Glib::OptionEntry cOpt;
	cOpt.set_long_name("config");
	cOpt.set_short_name('c');
	cOpt.set_arg_description(configFile);
	mGrp.add_entry_filename(cOpt, configFile);

	prgOpt.set_main_group(mGrp);

	prgOpt.parse(argc, argv);

	if (m_fullscreen) {
		fullscreen();
	}

	#ifdef JOGGLER
	m_tasks.push_back(new jogglerTask(&m_config));
	#endif //JOGGLER

	set_border_width(8);

	m_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &mainWindow::on_second), 1000);

	add(m_topBox);

	m_date.set_alignment(1.0, 0.5);
	m_topBox.pack_start(m_date, Gtk::PACK_SHRINK);
	m_topBox.pack_start(m_time);
	m_homeButton.set_size_request(-1, 50);
	m_topBox.pack_start(m_homeButton, Gtk::PACK_SHRINK);

	m_topBox.show_all();
	on_second();
}

mainWindow::~mainWindow() {}

bool mainWindow::on_second() {
	time_t t = time(NULL);

	struct tm *lt = localtime(&t);

	if (lt == NULL) {
		return true;
	}

	char buf[512];
	if (strftime(buf, 511, "%l:%M %P", lt) != 0) {
		std::string markup = "<span font=\"72\">";
		markup+= buf;
		markup+="</span>";
		m_time.set_markup(markup);
	}

	if (strftime(buf, 511, "%A %d %B, %Y", lt) != 0) {
		m_date.set_text(buf);
	}

	std::vector<task*>::iterator iter = m_tasks.begin();
	for (; iter != m_tasks.end(); ++iter) {
		(*iter)->run();
	}

	return true;
}
