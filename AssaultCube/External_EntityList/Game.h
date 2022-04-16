#pragma once
#include <windows.h>
#include "memory.h"

class Game {
public:
	// Process ID
	const wchar_t* Module_name = L"ac_client.exe";
	
	
	static DWORD GetProcessID();
	static uintptr_t GetModuleBaseAddress(DWORD processID);
};


