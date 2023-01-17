#include "common_includes.hh"
#include "hooks/hooks.hh"
#include "events/events.hh"
#include "globals.hh"

void init() {
    while (!dlopen(_("./bin/linux64/serverbrowser_client.so"), RTLD_NOLOAD | RTLD_NOW))
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

	interfaces::init();
	netvars::init();
	hooks::init();
	config::init();
	events::init();
	input::init();
}

int __attribute__((constructor)) entry_point() {
	std::thread(init).detach();
	
    return 0;
}