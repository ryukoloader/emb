#include "Bypasser.h"
#include <iostream>

bool Bypasser::InitNtDll () {

	HMODULE ntdllHandle = GetModuleHandleA ("ntdll.dll"), externalNtDllHandle = reinterpret_cast <HMODULE> (m_memoryUtil.GetModuleBase ("ntdll.dll"));

	if (!ntdllHandle || !externalNtDllHandle) return false;

	m_ntOpenFile = GetProcAddress (ntdllHandle, "NtOpenFile"), m_ldrLoadDll = GetProcAddress (ntdllHandle, "LdrLoadDll");

	if (!m_ntOpenFile || !m_ldrLoadDll) return false;

	m_externalNtOpenFile = reinterpret_cast <FARPROC __stdcall> (reinterpret_cast <DWORD> (externalNtDllHandle) + (reinterpret_cast <DWORD> (m_ntOpenFile) - reinterpret_cast <DWORD> (ntdllHandle))),
	m_externalLdrLoadDll = reinterpret_cast <FARPROC __stdcall> (reinterpret_cast <DWORD> (externalNtDllHandle) + (reinterpret_cast <DWORD> (m_ldrLoadDll) - reinterpret_cast <DWORD> (ntdllHandle)));

	std::cout << "Internal/External NTDLL handles: " << std::hex << "0x" << reinterpret_cast <DWORD> (ntdllHandle) << " / " << "0x" << reinterpret_cast <DWORD> (externalNtDllHandle)  << "." << std::endl;
	std::cout << "Internal/External NtOpenFile: "    << std::hex << "0x" << reinterpret_cast <DWORD> (m_ntOpenFile)  << " / " << "0x" << reinterpret_cast <DWORD> (m_externalNtOpenFile) << "." << std::endl;
	std::cout << "Internal/External LdrLoadDll: "    << std::hex << "0x" << reinterpret_cast <DWORD> (m_ldrLoadDll)  << " / " << "0x" << reinterpret_cast <DWORD> (m_externalLdrLoadDll) << "." << std::endl;

}

bool Bypasser::NtOpenFile () {
	//Premium bypazz.
	return m_memoryUtil.WriteToMemory (reinterpret_cast <DWORD> (m_externalNtOpenFile), m_ntOpenFile, 10);
}

bool Bypasser::LdrLoadDll () {
	//Premium bypazz.
	return m_memoryUtil.WriteToMemory (reinterpret_cast <DWORD> (m_externalLdrLoadDll), m_ldrLoadDll, 10);
}