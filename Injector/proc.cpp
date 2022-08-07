

#include "proc.h"
DWORD GetProceId(const wchar_t* ProceName) {
	DWORD procid = 0;
	HANDLE proHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (proHandle != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procentry;
		procentry.dwSize = sizeof(procentry);
		Process32First(proHandle, &procentry);
			do {
				if (!_wcsicmp(procentry.szExeFile, ProceName)) {
					procid = procentry.th32ProcessID;
					break;
				}
			} while (Process32Next(proHandle, &procentry));
		
	}
	CloseHandle(proHandle);
	return procid;
}
uintptr_t FindDMAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offest) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offest.size(); ++i) {
		ReadProcessMemory(hProc, (LPVOID)addr, (LPVOID)&addr, sizeof(addr), NULL);
		addr += offest[i];
	}
	return addr;
}
uintptr_t GetModuleBaseAdress(DWORD procid, const wchar_t* Module) {
	uintptr_t BaseAdress = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procid);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(ModuleEntry);
		Module32First(hSnap, &ModuleEntry);
			do {
				if (!_wcsicmp(ModuleEntry.szModule, Module)) {
					BaseAdress = (uintptr_t)ModuleEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &ModuleEntry));
		
	}
	CloseHandle(hSnap);
	return BaseAdress;
}