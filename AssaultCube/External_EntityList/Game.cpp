#include <windows.h>
#include "Game.h";

DWORD Game::GetProcessID()
{
	return mem::GetPID(L"ac_client.exe");
}

uintptr_t Game::GetModuleBaseAddress(DWORD processID)
{
	return mem::GetModuleBaseAddress(processID, L"ac_client.exe");
}