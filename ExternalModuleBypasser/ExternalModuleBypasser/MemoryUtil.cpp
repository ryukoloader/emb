#include "MemoryUtil.h"
#include <TlHelp32.h>
#include <comdef.h>

DWORD MemoryUtil::GetModuleBase (const char* module) {
	
	HANDLE snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPMODULE, GetProcessId (m_applicationHandle));

	if (snapshot == INVALID_HANDLE_VALUE) return 0;

	MODULEENTRY32 module32;
	module32.dwSize = sizeof (MODULEENTRY32);

	Module32First (snapshot, &module32);

	do {
		if (!strcmp (_bstr_t(module32.szModule), module)) break;
	} while (Module32Next (snapshot, &module32));

	CloseHandle (snapshot);

	return (DWORD) module32.modBaseAddr;

}