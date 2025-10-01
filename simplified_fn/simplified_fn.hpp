#pragma once

namespace smpl {

	int get_execution_time(void (*fn)(int), int threads);
	void sleep_sec(int s);
	void spacer();
	bool is_debugger_present();
	void heartbeat();
	void resize_console(int width, int height);

}