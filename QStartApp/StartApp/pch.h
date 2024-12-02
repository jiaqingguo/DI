#pragma once

#include <winsock2.h>
#include <WS2tcpip.h>	
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <tchar.h>
#include <atlstr.h>
#include <thread>
#include <Lm.h>
#include "tlhelp32.h"

//Ìí¼Ó¶¯Ì¬¿âµÄlib
#pragma comment(lib, "ws2_32.lib")

#define getExePath(X)\
        wchar_t exePath[MAX_PATH];\
        GetModuleFileNameW(nullptr, exePath, MAX_PATH);\
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;\
        std::string exePathStr = converter.to_bytes(exePath);\
        std::string exeDirPath = exePathStr.substr(0, exePathStr.find_last_of("\\"));\
        std::string X = exeDirPath;

#define STRING_TO_TCHAR(_in,_out) \
		std::wstring wstr(_in.begin(), _in.end());\
		TCHAR* _out = (_TCHAR*)(&wstr[0]);


#define CREATE_STARTUPINFO(_si,_pi) \
		STARTUPINFO _si;\
		memset(&_si, 0, sizeof(STARTUPINFO));\
		_si.cb = sizeof(STARTUPINFO);\
		_si.dwFlags = STARTF_USESHOWWINDOW;\
		_si.wShowWindow = SW_SHOW;\
		PROCESS_INFORMATION _pi;\

#define CLOSE_HANDLE(_pi) \
		CloseHandle(_pi.hProcess);\
		CloseHandle(_pi.hThread);

#define MY_PIPE_BUFFER_SIZE 1024
