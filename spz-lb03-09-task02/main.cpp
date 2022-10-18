#include <ntddk.h>
VOID SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Func: %s\n", __FUNCTION__));
	return;
}
extern "C"
NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	NTSTATUS nt = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = SampleUnload;

	KdPrint(("Func: %s\n", __FUNCTION__));

	return nt;
}