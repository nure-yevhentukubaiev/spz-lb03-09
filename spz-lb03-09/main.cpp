#include <ntddk.h>
VOID SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	KdPrint(("Func: %s\n", __FUNCTION__));
	UNREFERENCED_PARAMETER(DriverObject);
	return;
}
extern "C"
NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	RTL_OSVERSIONINFOW rtlOSVer;
	RtlSecureZeroMemory(&rtlOSVer, sizeof(rtlOSVer));
	NTSTATUS nt = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = SampleUnload;
	
	KdPrint(("Func: %s\n", __FUNCTION__));

	nt = RtlGetVersion(&rtlOSVer);
	KdPrint((
		"Got Windows version: %lu.%lu.%lu\n",
		rtlOSVer.dwMajorVersion,
		rtlOSVer.dwMinorVersion,
		rtlOSVer.dwBuildNumber
	));

	return nt;
}