#pragma once
#include <Windows.h>

namespace mem
{
	uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);
	uintptr_t GetPID(const wchar_t* procName);
}