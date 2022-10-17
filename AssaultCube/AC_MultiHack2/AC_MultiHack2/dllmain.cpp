#include "pch.h"
#include <math.h>
#include "Vec.h"
#include "Player.h"
#include "mem.h"
#include "Mathy.h"

#define M_PI (float)3.14159265358979323846f

TMath Math;

int playercount = 0;
bool GodmodeToggle, AmmoToggle, GrenadeToggle = false;
bool TriggerToggle, AimbotToggle = false;

using namespace std;

void UpdateMenu() {
	system("cls");

	cout << "~~~Main~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "[NUM_7] Godmode     | " << boolalpha << GodmodeToggle << "\n";
	cout << "[NUM_8] Ammo mod    | " << boolalpha << AmmoToggle << "\n";
	cout << "[NUM_9] Grenade mod | " << boolalpha << GrenadeToggle << "\n";
	cout << "~~~Combat~~~~~~~~~~~~~~~~~~~\n";
	cout << "[NUM_4] Triggerbot  | " << boolalpha << TriggerToggle << "\n";
	cout << "[NUM_5] Aimbot      | " << boolalpha << AimbotToggle << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Player count: " << playercount << "\n";
	cout << endl;
}

// Hooking the looking at entity function
DWORD ori_call_addr = 0x004607C0;
playerent* targetEnt_value = 0;
DWORD jmpBackAddy = 0x0;

__declspec(naked) void targetEntHook() {
	__asm {
		call ori_call_addr
		pushad

		mov targetEnt_value, eax	
		popad

		jmp[jmpBackAddy]
	}
}

playerent* localPlayer;
EntList* entityList;

playerent* GetClosestEnemy() {
	float MaxDistance = 100000.0f;
	playerent* closest = nullptr;

	for (int i = 0; i < (playercount); i++) {
		playerent* ourTarget = entityList->ents[i];
		if (ourTarget != NULL && localPlayer != NULL) {
			if (ourTarget->Health <= 1000 && ourTarget->Health > 0 && ourTarget->TeamId != localPlayer->TeamId) {
				float distanceToPlayer = Math.getDistance(localPlayer->BodyCoords, ourTarget->BodyCoords);

				if (distanceToPlayer <= MaxDistance) {
					MaxDistance = distanceToPlayer;
					closest = ourTarget;
				}
			}
		}
	}

	return closest;
}

void MainThread(HMODULE hModule) {

	// Allocate console
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);

	// Get module base
	uintptr_t moduleBaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");
	uintptr_t game_base = (moduleBaseAddr + 0x10F000);

	// Locate pointers
	localPlayer = *(playerent**)(game_base + 0x4F4);
	entityList = *(EntList**)(game_base + 0x4F8);
	int* playerCountPtr = (int*)(game_base + 0x500);

	UpdateMenu();

	// target ent hook
	unsigned int hookLength = 5;
	DWORD hookAddr = 0x40AD9D;
	jmpBackAddy = hookAddr + hookLength;
	mem::Hook((void*)hookAddr, (void*)targetEntHook, hookLength);	

	// Main loop
	while (!GetAsyncKeyState(VK_END)) {
		if (localPlayer) {

			playercount = *playerCountPtr;

			if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
				GodmodeToggle = !GodmodeToggle;
				UpdateMenu();
				Sleep(5);
			}

			if (GetAsyncKeyState(VK_NUMPAD8) & 1) {
				AmmoToggle = !AmmoToggle;
				UpdateMenu();
				Sleep(5);
			}

			if (GetAsyncKeyState(VK_NUMPAD9) & 1) {
				GrenadeToggle = !GrenadeToggle;
				UpdateMenu();
				Sleep(5);
			}

			if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
				TriggerToggle = !TriggerToggle;
				UpdateMenu();
				Sleep(5);
			}

			if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
				AimbotToggle = !AimbotToggle;
				UpdateMenu();			
				Sleep(5);
			}

			if (GodmodeToggle) 
				localPlayer->Health = 1000;
			
			if (GrenadeToggle)
				localPlayer->GrenadeCount = 10;

			if (AmmoToggle)
				localPlayer->WeaponPtr->ClipPtr->ClipValue = 1000;

			if (TriggerToggle) {
				INPUT input = { 0 };
				if (targetEnt_value != 0) {
					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &input, sizeof(INPUT));

					Sleep(3);

					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &input, sizeof(INPUT));					
				}
			}

			if (AimbotToggle && GetAsyncKeyState(VK_LCONTROL)) { // Aimbot keybind = left control
				playerent* ourtarget = GetClosestEnemy();
				if (ourtarget != nullptr) {
					localPlayer->ViewAngles = Math.CalculateAngle(localPlayer->BodyCoords, ourtarget->BodyCoords); // Didn't find the head coords just yet.
				}
			}


		}
		Sleep(0.5);
	}

	// Exit program and detach
	FreeConsole();
	fclose(file);
	FreeLibraryAndExitThread(hModule, 0);
}


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, (HMODULE)hInstance, NULL, 0);
	}
}