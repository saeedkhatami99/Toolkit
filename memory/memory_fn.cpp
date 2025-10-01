#include "memory_fn.hpp"
#include "../simplified_fn/simplified_fn.hpp"
#include <cstdint>



HANDLE memory::attach(const char* process_name, DWORD access_rights) {

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE process_handle = NULL;

	if (snapshot)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		wchar_t w_to_c[256];

		// Convert process name to wide string for comparison
		if (Process32First(snapshot, &pe))
		{
			do
			{
				// Use strcmp for ANSI comparison
				if (!strcmp(pe.szExeFile, process_name))
				{
					process_handle = OpenProcess(access_rights, false, pe.th32ProcessID);
				}
			} while (Process32Next(snapshot, &pe));
		}
		CloseHandle(snapshot);
	}

	// sort of a check, testing
	printf("process_handle(%s): %p\n", process_name, process_handle);

	if (process_handle) 
	{ 
		return process_handle;
	}
	else 
	{ 
		return 0;
	}

}

bool memory::detach(HANDLE h) {

	return CloseHandle(h);

}

std::vector<unsigned int> memory::get_pid_list(std::string_view process_name)
{
	std::vector<unsigned int> process_list;
	HANDLE handle_to_pid = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);
	do
	{
		if (!strcmp(entry.szExeFile, process_name.data()))
		{
			process_list.push_back(entry.th32ProcessID);
			CloseHandle(handle_to_pid);
		}

	} while (Process32Next(handle_to_pid, &entry));

	return process_list;
}


template<typename t>
inline t memory::read_memory(uintptr_t address, process Process)
{
	t buffer;
	ReadProcessMemory(Process.process_handle, (LPCVOID)address, &buffer, sizeof(t), NULL);
	return buffer;
}

template<typename t>
void memory::write_memory(uintptr_t address, t buffer, HANDLE process)
{
	WriteProcessMemory(process, (LPVOID)address, &buffer, sizeof(t), NULL);
}

bool memory::memcmp(const BYTE* data, const BYTE* mask, const char* mask_str) {
	for (; *mask_str; ++mask_str, ++data, ++mask) {
		if (*mask_str == 'x' && *data != *mask) {
			return false;
		}
	}
	return (*mask_str == '\0');
}

uintptr_t memory::find_signature(uintptr_t start, size_t size, const char* sig, const char* mask, process Process)
{
	std::vector<BYTE> data(size);
	SIZE_T read_bytes;

	ReadProcessMemory(Process.process_handle, (LPVOID)start, data.data(), size, &read_bytes);

	for (size_t i = 0; i < size; i++)
	{
		if (memory::memcmp(data.data() + i, (const BYTE*)sig, mask)) {
			return start + i;
		}
	}
	return 0;
}

void memory::inject_shell( char shellcode[], const char* process_name) {

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE process_handle = NULL;
	process info;

	if (snapshot)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &pe))
		{
			do
			{
				if (!strcmp(pe.szExeFile, process_name))
				{
					std::cout << "[+] pe.szExeFile: " << pe.szExeFile << " -- FOUND " << std::endl;
					process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, pe.th32ProcessID);
				}
				
			} while (Process32Next(snapshot, &pe));
		}
		CloseHandle(snapshot);
	}
	if (!process_handle) {
		std::cout << "Invalid process_handle" << std::endl;
		return;
	}
	uintptr_t ptr_alloc;
	ptr_alloc = reinterpret_cast<uintptr_t>(VirtualAllocEx(process_handle, 0, strlen(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

	if (ptr_alloc == 0) {
		std::cout << "Error while injecting shellcode. Couldn't retrieve the base address." << std::endl;
		smpl::sleep_sec(10);
		return;
	}

	DWORD lpd_shit = 0x50002;
	memory::write_memory(ptr_alloc, shellcode, process_handle);
	std::cout << "Successfully injected shellcode into the selected process." << std::endl;
	CreateRemoteThread(process_handle, 0, 100, (LPTHREAD_START_ROUTINE)ptr_alloc, 0, 0, &lpd_shit);

	memory::detach(process_handle);

}
