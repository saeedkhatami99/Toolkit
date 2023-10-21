#include "memory_fn.hpp"

bool memory::attach(const char* process_name, DWORD access_rights) {

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE process_handle = NULL;

	if (snapshot)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		wchar_t text_wchar[30];

		
		char w_to_c[256];
		sprintf_s(w_to_c, "%ws", pe.szExeFile);

		if (Process32First(snapshot, &pe))
		{
			do
			{
				if (!strcmp(w_to_c, process_name)) 
				{
					process_handle = OpenProcess(access_rights, false, pe.th32ProcessID);
				}
			} while (Process32Next(snapshot, &pe));
		}
		CloseHandle(snapshot);
	}

	
	printf("process_handle(%s): 0x%x\n", process_name, (DWORD)process_handle);

	if (process_handle) 
	{ 
		return true; 
	}
	else 
	{ 
		return false; 
	}

}

bool memory::detach(HANDLE h) {

	return CloseHandle(h);

}

template<typename t>
inline t memory::read_memory(DWORD address)
{
	t buffer;
	ReadProcessMemory(this->process_handle, (LPCVOID)address, &buffer, sizeof(t), NULL);
	return buffer;
}

template<typename t>
void memory::write_memory(DWORD address, t buffer)
{
	WriteProcessMemory(this->process_handle, (LPVOID)address, &buffer, sizeof(t), NULL);
}
