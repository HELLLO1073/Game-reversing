#pragma once

namespace mem {

	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);

	bool Hook(void* addr, void* ourFunc, unsigned int size);

	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
}

