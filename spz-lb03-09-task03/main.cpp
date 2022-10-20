#include <ntddk.h>

static PCWSTR pszSymbolicLinkName = L"\\DosDevices\\Simple3Link";

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

	KdPrint(("Func: %s returns %lX\n", __FUNCTION__, pIrp->IoStatus.Status));
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

	KdPrint(("Func: %s returns %lX\n", __FUNCTION__, pIrp->IoStatus.Status));
	return pIrp->IoStatus.Status;
}

VOID
OnDrvUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{
	NTSTATUS nt;
	UNICODE_STRING uniszSymbolicLink;

	KdPrint(("Func: %s\n", __FUNCTION__));
	
	RtlInitUnicodeString(&uniszSymbolicLink, pszSymbolicLinkName);
	nt = IoDeleteSymbolicLink(&uniszSymbolicLink);
	KdPrint(("Func: %s: %s returns %lX\n", __FUNCTION__, "IoDeleteSymbolicLink", nt));
	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("Func: %s returns\n", __FUNCTION__));
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
	UNICODE_STRING uniszSymbolicLink;
	RtlInitUnicodeString(&uniszDevice, L"\\Device\\Simple3");
	RtlInitUnicodeString(&uniszSymbolicLink, pszSymbolicLinkName);


	UNREFERENCED_PARAMETER(puniszRegistryPath);

	KdPrint(("Func: %s\n", __FUNCTION__));

	nt = IoCreateDevice(
		pDriverObject,
		0, &uniszDevice, 50000, 0, FALSE, &pDeviceObject
	);
	KdPrint(("Func: %s: %s returns %lX\n", __FUNCTION__, "IoCreateDevice", nt));
	if (!NT_SUCCESS(nt)) {
		goto fail;
	}

	nt = IoCreateSymbolicLink(
		&uniszSymbolicLink, &uniszDevice
	);
	KdPrint(("Func: %s: %s returns %lX\n", __FUNCTION__, "IoCreateSymbolicLink", nt));
	if (!NT_SUCCESS(nt)) {
		IoDeleteDevice(pDriverObject->DeviceObject);
		goto fail;
	}

	pDriverObject->DriverUnload = OnDrvUnload;
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;

fail:
	KdPrint(("Func: %s returns %lX\n", __FUNCTION__, nt));
	return nt;
}