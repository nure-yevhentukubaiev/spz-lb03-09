#include <ntddk.h>

VOID
OnDrvUnload(
	_In_ PDRIVER_OBJECT DriverObject
);

NTSTATUS
OnCreate(
	PDEVICE_OBJECT pDeviceObject,
	PIRP pIrp
);

NTSTATUS
OnClose(
	PDEVICE_OBJECT pDeviceObject,
	PIRP pIrp
);

NTSTATUS
OnCreate(
	PDEVICE_OBJECT pDeviceObject,
	PIRP pIrp
)
{
	UNREFERENCED_PARAMETER(pDeviceObject);
	KdPrint(("Func: %s\n", __FUNCTION__));

	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return pIrp->IoStatus.Status;
}

NTSTATUS
OnClose(
	PDEVICE_OBJECT pDeviceObject,
	PIRP pIrp
)
{
	UNREFERENCED_PARAMETER(pDeviceObject);
	KdPrint(("Func: %s\n", __FUNCTION__));

	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	
	return pIrp->IoStatus.Status;
}

VOID
OnDrvUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Func: %s\n", __FUNCTION__));

	IoDeleteDevice(DriverObject->DeviceObject);

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
	RtlInitUnicodeString(&uniszDevice, L"\\Device\\Simple2");

	UNREFERENCED_PARAMETER(puniszRegistryPath);
	
	KdPrint(("Func: %s\n", __FUNCTION__));

	nt = IoCreateDevice(
		pDriverObject,
		0, &uniszDevice, 50000, 0, FALSE, &pDeviceObject
	);
	if (!NT_SUCCESS(nt)) {
		goto fail;
	}

	pDriverObject->DriverUnload = OnDrvUnload;
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;

	fail:
	KdPrint(("Func: %s returns %lX\n", __FUNCTION__, nt));
	return nt;
}