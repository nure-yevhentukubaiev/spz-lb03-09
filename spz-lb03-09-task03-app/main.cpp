#include "stdafx.h"

int _tmain(int argc, TCHAR *argv[])
{
	DWORD bErr = 0;
	HANDLE hFile = CreateFile(
		_T("\\\\.\\Simple3Link"), GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING,
		NULL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		bErr = GetLastError();
		_tprintf_s(
			_T("Function CreateFile failed, error: %08lX\n"), bErr
		);
		goto fail;
	} else {
		_tprintf_s(
			_T("Function CreateFile succeded, handle: %p\n"), hFile
		);
	}
	
	if (!CloseHandle(hFile)) {
		bErr = GetLastError();
		_tprintf_s(
			_T("Function CloseHandle failed, error: %08lX\n"), bErr
		);
	} else {
		_tprintf_s(
			_T("Function CloseHandle succeded\n")
		);
	}
	

	fail:
	return bErr;
}