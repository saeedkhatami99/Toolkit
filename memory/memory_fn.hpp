#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

namespace memory {

	bool attach(const char* process_name, DWORD access_rights);
	bool detach(HANDLE h);

	template <typename t>
	t read_memory(DWORD address);

	template <typename t>
	void write_memory(DWORD address, t value);

}