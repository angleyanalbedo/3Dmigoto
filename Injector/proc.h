#pragma once
/*
* ���д�Զ�̽��̵õ�����handle
*/


#include<Windows.h>
#include<TlHelp32.h>

#include<vector>
DWORD GetProceId(const wchar_t* ProceName);
uintptr_t FindDMAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offest);
uintptr_t GetModuleBaseAdress(DWORD procid, const wchar_t* Module);


