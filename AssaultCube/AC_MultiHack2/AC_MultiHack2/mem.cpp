#include "pch.h"
#include "mem.h"

using namespace mem;

void mem::Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

void mem::Nop(BYTE* dst, unsigned int size) {
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

bool mem::Hook(void* addr, void* ourFunc, unsigned int size) {
	if (size >= 5) {
		DWORD curProtection;
		VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &curProtection);
		memset(addr, 0x90, size);

		DWORD relativeAddress = ((DWORD)ourFunc - (DWORD)addr) - 5;

		*(BYTE*)addr = 0xE9;
		*(DWORD*)((DWORD)addr + 1) = relativeAddress;

		DWORD temp;
		VirtualProtect(addr, size, curProtection, &temp);
		return true;
	}
	else {
		return false;
	}
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++) {

		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}

