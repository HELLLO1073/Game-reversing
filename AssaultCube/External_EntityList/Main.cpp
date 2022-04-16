// Finding entity list in cpp externally

#include <Windows.h>
#include <iostream>
#include "memory.h"
#include "Game.h"

// Base addresses
uintptr_t LocalPlayerAddr = 0x187C0C;
uintptr_t EntityListAddr = 0x187C10;
uintptr_t numOfPlayersAddr = 0x187C18;

// Base ptrs
uintptr_t LocalPlayerPTR;
uintptr_t EntityListPTR;
int numOfPlayers;

int main()
{	
	// Getting module base + process id
	DWORD procID = Game::GetProcessID();
	uintptr_t ModuleBaseAddr = Game::GetModuleBaseAddress(procID);

	// Getting the handle to process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

	while (!procID)
	{
		system("cls");
		std::cout << "Waiting for game";
		Sleep(444);
		std::cout << ".";
		Sleep(444);
		std::cout << ".";
		Sleep(444);
		std::cout << ".";
		procID = Game::GetProcessID();
		system("cls");
	}

	if (procID) {
		std::cout << "Found process!" << std::endl;
	}

	if (hProcess)
	{	

		// Entity offsets
		DWORD usernameOffset = 0x205;
		DWORD XCoord{ 0x28 };
		DWORD YCoord{ 0x2C };
		DWORD ZCoord{ 0x30 };
		DWORD health{ 0xEC };

		float myXCoord;
		float myYCoord;
		float myZCoord;
		
		ReadProcessMemory(hProcess, (BYTE*)ModuleBaseAddr + LocalPlayerAddr, &LocalPlayerPTR, sizeof(LocalPlayerAddr), 0);
		while (0.5)
		{
			system("cls");
			ReadProcessMemory(hProcess, (BYTE*)ModuleBaseAddr + EntityListAddr, &EntityListPTR, sizeof(EntityListAddr), 0);
			ReadProcessMemory(hProcess, (BYTE*)ModuleBaseAddr + numOfPlayersAddr, &numOfPlayers, sizeof(numOfPlayersAddr), 0);
			std::cout << "Players in server: " << std::dec << numOfPlayers << std::endl;

			// Probably bad way of reading coords but oh well
			ReadProcessMemory(hProcess, (BYTE*)LocalPlayerPTR + XCoord, &myXCoord, sizeof(myXCoord), 0);
			ReadProcessMemory(hProcess, (BYTE*)LocalPlayerPTR + YCoord, &myYCoord, sizeof(myYCoord), 0);
			ReadProcessMemory(hProcess, (BYTE*)LocalPlayerPTR + ZCoord, &myZCoord, sizeof(myZCoord), 0);

			DWORD currentEntityAdd = 0x0;
			DWORD currentEntity;
			if (numOfPlayers <= 1)
			{
				system("cls");
				std::cout << "No players found!" << std::endl;
				ReadProcessMemory(hProcess, (BYTE*)ModuleBaseAddr + EntityListAddr, &EntityListPTR, sizeof(EntityListAddr), 0);
				ReadProcessMemory(hProcess, (BYTE*)ModuleBaseAddr + numOfPlayersAddr, &numOfPlayers, sizeof(numOfPlayersAddr), 0);
				Sleep(400);
			}

			for (int i = 0; i < numOfPlayers; i++)
			{				
				char curName[16];
				currentEntityAdd += 0x4;


				ReadProcessMemory(hProcess, (BYTE*)EntityListPTR + currentEntityAdd, &currentEntity, sizeof(currentEntity), 0);
				ReadProcessMemory(hProcess, (BYTE*)currentEntity + usernameOffset, &curName, sizeof(curName), 0);

				// Print out all players in server
				std::cout << "Entity[" << i << "] : " << curName << std::endl;

				// Teleport all to me (only for bot matches)
				/*WriteProcessMemory(hProcess, (BYTE*)currentEntity + XCoord, &myXCoord, sizeof(myXCoord), 0);
				WriteProcessMemory(hProcess, (BYTE*)currentEntity + YCoord, &myYCoord, sizeof(myYCoord), 0);
				WriteProcessMemory(hProcess, (BYTE*)currentEntity + ZCoord, &myZCoord, sizeof(myZCoord), 0);*/
				Sleep(1);			
			}	
		}
	}	
	return 0;
}