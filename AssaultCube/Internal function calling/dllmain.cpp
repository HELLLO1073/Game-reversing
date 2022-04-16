// AssaultCube 1.2.0.2 _cdecl function calling example. (Reversed with Cheat Engine, GHidra, x64Debug)
// Manual map injection
#include "pch.h"

// Function prototype's
typedef void(_cdecl* _ACPrint)(const char* string, ...); // Arguments: (Format, [string1, color_code, string2]) 
_ACPrint ACPrint;

// Main dll thread
DWORD WINAPI MainThread(LPVOID param)
{
	// Module base address
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(0);

	// Get RVA ptr to function
	ACPrint = (_ACPrint)(moduleBase + 0x6B060);

	// Game's console string format
	const char* string_format = "%s:\f%d %s";

	ACPrint(string_format, "AC Internal", 0, "Dll Loaded");

	while (!GetAsyncKeyState(VK_END))
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{			
			// Calling function example
			ACPrint(string_format, "AC Internal", 1, "Success!");
		}
	}
	ACPrint(string_format, "AC Internal", 9, "Dll Unloaded");

	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);		
		break;
	}
	return TRUE;
}