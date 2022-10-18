#include <ntddk.h>

VOID
OnDrvUnload(
	_In_ PDRIVER_OBJECT DriverObject
);

VOID
OnDrvUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Func: %s\n", __FUNCTION__));
	return;
}

extern "C"
NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT pDriverObject,
	_In_ PUNICODE_STRING puniszRegistryPath
)
{
	NTSTATUS nt = STATUS_SUCCESS;
	PDEVICE_OBJECT pDeviceObject = NULL;
	UNICODE_STRING uniszDevice;
	RtlInitUnicodeString(&uniszDevice, L"\\Devices\\Simple2");

	UNREFERENCED_PARAMETER(puniszRegistryPath);
	
	KdPrint(("Func: %s\n", __FUNCTION__));

	nt = IoCreateDevice(
		pDriverObject,
		0, &uniszDevice, 50000, 0, FALSE, &pDeviceObject
	);
	if (nt != STATUS_SUCCESS) {
		goto fail;
	}

	pDriverObject->DriverUnload = OnDrvUnload;

	fail:
	return nt;
}