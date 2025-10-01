#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <vector>

class process {
public:
	HANDLE snapshot;
	HANDLE process_handle;
};

namespace memory {

	// These functions are in here for intermediate programmers, mostly people that are into game-hacking.
	// In future there will be some pattern scanning functions and possibly implementation of a communicating
	// with a driver to do some WPM/RPM through kernel.

	HANDLE attach(const char* process_name, DWORD access_rights);
	bool detach(HANDLE h);
	std::vector<unsigned int> get_pid_list(std::string_view process_name);

	template <typename t>
	t read_memory(uintptr_t address, process Process);

	template <typename t>
	void write_memory(uintptr_t address, t value, HANDLE process);

	void inject_shell(char shellcode[], const char* process_name);

	bool memcmp(const BYTE* data, const BYTE* mask, const char* mask_str);
	uintptr_t find_signature(uintptr_t start, size_t size, const char* sig, const char* mask, process Process);

	// Placeholder for future driver communication (not implemented)
	// void read_via_driver(uintptr_t address, void* buffer, size_t size);
	// void write_via_driver(uintptr_t address, void* buffer, size_t size);

}
