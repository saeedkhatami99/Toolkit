#include<iostream>
#include<chrono>
#include <Windows.h>
#include "simplified_fn.hpp"

int smpl::get_execution_time(void (*fn)(int), int threads) {

#ifdef _DEBUG 
	auto start_time = std::chrono::high_resolution_clock::now();
	fn(threads);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto int_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::chrono::duration<long, std::micro> int_usec = int_ms;

	return int_usec.count();
#endif
	return 1;
	
}

void smpl::sleep_sec(int s) {

	int conversion_to_s = s * 1000;
	Sleep(conversion_to_s);

}

void smpl::spacer() {

	std::cout << "==============================================================\n";
	// Looks cleaner overall
}
// simple
bool smpl::is_debugger_present() {
	return IsDebuggerPresent();
}

void smpl::heartbeat() {
	while (true) {
		if (IsDebuggerPresent()) {
			// Anti-debug action: terminate or alert
			MessageBoxA(0, "Debugger detected during heartbeat!", "Security Alert", MB_OK | MB_ICONERROR);
			exit(1);
		}
		Sleep(5000); // Check every 5 seconds
	}
}

void smpl::resize_console(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT console_rect;
	GetWindowRect(console, &console_rect);
	MoveWindow(console, console_rect.left, console_rect.top, width, height, TRUE);
}
