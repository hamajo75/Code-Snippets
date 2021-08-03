#include <stdio.h>
#include <iostream>
#include <string.h>
#include "windows.h"

CRITICAL_SECTION FQueueLock;

typedef struct _HIDD_ATTRIBUTES
{
	u_long Size; // = sizeof (struct _HIDD_ATTRIBUTES)
	u_short VendorID;
	u_short ProductID;
	u_short VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

typedef struct _HIDP_PREPARSED_DATA *PHIDP_PREPARSED_DATA;
typedef USHORT USAGE, *PUSAGE;

typedef struct _HIDP_CAPS {
	USAGE   Usage;
	USAGE   UsagePage;
	USHORT  InputReportByteLength;
	USHORT  OutputReportByteLength;
	USHORT  FeatureReportByteLength;
	USHORT  Reserved[17];
	USHORT  NumberLinkCollectionNodes;
	USHORT  NumberInputButtonCaps;
	USHORT  NumberInputValueCaps;
	USHORT  NumberInputDataIndices;
	USHORT  NumberOutputButtonCaps;
	USHORT  NumberOutputValueCaps;
	USHORT  NumberOutputDataIndices;
	USHORT  NumberFeatureButtonCaps;
	USHORT  NumberFeatureValueCaps;
	USHORT  NumberFeatureDataIndices;
} HIDP_CAPS, *PHIDP_CAPS;

typedef VOID    (__stdcall *pHidD_GetHidGuid)(LPGUID);
typedef BOOLEAN (__stdcall *pHidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef BOOLEAN (__stdcall *pHidD_SetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *pHidD_GetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *pHidD_GetManufacturerString)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *pHidD_GetProductString)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *pHidD_GetSerialNumberString)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *pHidD_SetNumInputBuffers)(HANDLE, ULONG);
typedef BOOLEAN (__stdcall *pHidD_GetPreparsedData) (HANDLE, PHIDP_PREPARSED_DATA *);
typedef BOOLEAN (__stdcall *pHidP_GetCaps) (HANDLE, PHIDP_CAPS);

static HINSTANCE hHID = NULL;

static HANDLE FDeviceHandle = INVALID_HANDLE_VALUE;
static HANDLE FReadDeviceHandle = INVALID_HANDLE_VALUE;

static pHidD_GetHidGuid HidD_GetHidGuid = NULL;
static pHidD_GetAttributes HidD_GetAttributes = NULL;
static pHidD_SetFeature HidD_SetFeature = NULL;
static pHidD_GetFeature HidD_GetFeature = NULL;
static pHidD_GetManufacturerString HidD_GetManufacturerString = NULL;
static pHidD_GetProductString HidD_GetProductString = NULL;
static pHidD_GetSerialNumberString HidD_GetSerialNumberString = NULL;
static pHidD_SetNumInputBuffers HidD_SetNumInputBuffers = NULL;
static pHidD_GetPreparsedData HidD_GetPreparsedData = NULL;
static pHidP_GetCaps HidP_GetCaps = NULL;

#define USB_MAX_OUT_REPORT_SIZE	65
#define USB_MAX_IN_REPORT_SIZE	65

static USHORT     InputReportByteLength;
static USHORT     OutputReportByteLength;
static TCHAR      devicepath[MAX_PATH];
static HANDLE     FStopEvent = NULL;
static HANDLE     FInputThread = NULL;
static OVERLAPPED ol;
//---------------------------------------------------------------------------
bool Error_SetErr(int error_no)
{

}
//---------------------------------------------------------------------------
bool USB_Open(device_info_t selected_device)
{
	int i;
	void *data;
	bool err = false;
	PHIDP_PREPARSED_DATA	PreparsedData;
	HIDP_CAPS Capabilities;

   USB_Close();

	if (strlen(selected_device.serno) != ILCD_SERIAL_NUM_LEN)
		return Error_SetErr(USB_ERR_SERIAL_NUM_LEN);

	if (FDeviceHandle != INVALID_HANDLE_VALUE)
		return Error_SetErr(USB_ERR_ALREADY_OPEN);

	if (usb_find_devices(&selected_device, true) != 1)
		return Error_SetErr(USB_ERR_DEVICE_NOT_FOUND);

	FDeviceHandle = CreateFile(devicepath,
							GENERIC_READ | GENERIC_WRITE,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							0,
							NULL);

	if (FDeviceHandle == INVALID_HANDLE_VALUE)
		return Error_SetErr(USB_ERR_WR_CREATE_FILE);

	if (HidD_GetPreparsedData(FDeviceHandle, &PreparsedData))
		err = (HidP_GetCaps(PreparsedData, &Capabilities) != HIDP_STATUS_SUCCESS);
	else
		err = true;

	if (!err)
		err = !HidD_SetNumInputBuffers(FDeviceHandle, USB_NUM_BUFFERS);

	if (err)
	{
		CloseHandle(FDeviceHandle);
		FDeviceHandle = INVALID_HANDLE_VALUE;
		return Error_SetErr(USB_ERR_WR_CREATE_FILE);
	}

	InputReportByteLength = Capabilities.InputReportByteLength;
	OutputReportByteLength = Capabilities.OutputReportByteLength;

	if (InputReportByteLength > USB_MAX_IN_REPORT_SIZE ||
		OutputReportByteLength > USB_MAX_OUT_REPORT_SIZE)
	{
		CloseHandle(FDeviceHandle);
		FDeviceHandle = INVALID_HANDLE_VALUE;
		return Error_SetErr(USB_ERR_WR_CREATE_FILE);
	}

	if ((FInputThread = usb_CreateInputThread())== NULL)
	{
		USB_Close();
		return false;
	}

	ResumeThread(FInputThread);
	usb_ClearTXBuffer();
	return true;
}
//---------------------------------------------------------------------------
bool USB_Close(void)
{
	if (FDeviceHandle == INVALID_HANDLE_VALUE)
		return true;

	if (FStopEvent)
		SetEvent(FStopEvent);

	if (FInputThread)
	{
		CloseHandle(FInputThread);
		DeleteCriticalSection(&FQueueLock);
		FInputThread = NULL;
	}

	CloseHandle(FDeviceHandle);
	FDeviceHandle = INVALID_HANDLE_VALUE;

	if (FStopEvent)
	{
		CloseHandle(FStopEvent);
		FStopEvent = NULL;
	}

	usb_UnLoadDLL();
	return true;
}
//---------------------------------------------------------------------------
static void usb_UnLoadDLL(void)
{
	if (hHID)
		FreeLibrary(hHID);

	hHID = NULL;

	HidD_GetHidGuid            = NULL;
	HidD_GetAttributes         = NULL;
	HidD_SetFeature            = NULL;
	HidD_GetFeature            = NULL;
	HidD_GetManufacturerString = NULL;
	HidD_GetProductString      = NULL;
	HidD_GetSerialNumberString = NULL;
	HidD_SetNumInputBuffers    = NULL;
	HidD_GetPreparsedData      = NULL;
	HidP_GetCaps               = NULL;
}
//---------------------------------------------------------------------------
static bool usb_LoadDLL(void)
{
	if (hHID)
		return true;	// Already loaded

	hHID = LoadLibrary(TEXT("HID.DLL"));

	if (!hHID)
		return false;

	HidD_GetHidGuid = (pHidD_GetHidGuid)
		GetProcAddress(hHID, "HidD_GetHidGuid");
	HidD_GetAttributes = (pHidD_GetAttributes)
		GetProcAddress(hHID, "HidD_GetAttributes");
	HidD_SetFeature = (pHidD_SetFeature)
		GetProcAddress(hHID, "HidD_SetFeature");
	HidD_GetFeature = (pHidD_GetFeature)
		GetProcAddress(hHID, "HidD_GetFeature");
	HidD_GetManufacturerString = (pHidD_GetManufacturerString)
		GetProcAddress(hHID, "HidD_GetManufacturerString");
	HidD_GetProductString = (pHidD_GetProductString)
		GetProcAddress(hHID, "HidD_GetProductString");
	HidD_GetSerialNumberString = (pHidD_GetSerialNumberString)
		GetProcAddress(hHID, "HidD_GetSerialNumberString");
	HidD_SetNumInputBuffers = (pHidD_SetNumInputBuffers)
		GetProcAddress(hHID, "HidD_SetNumInputBuffers");
	HidD_GetPreparsedData = (pHidD_GetPreparsedData)
		GetProcAddress(hHID, "HidD_GetPreparsedData");
	HidP_GetCaps = (pHidP_GetCaps)
		GetProcAddress(hHID, "HidP_GetCaps");

	if (!HidD_GetHidGuid || !HidD_GetAttributes || !HidD_SetFeature ||
		!HidD_GetFeature ||!HidD_GetManufacturerString ||
		!HidD_GetProductString || !HidD_GetSerialNumberString ||
		!HidD_SetNumInputBuffers || !HidD_GetPreparsedData || !HidP_GetCaps)
	{		
		usb_UnLoadDLL();
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
unsigned __stdcall usb_ReadThreadProc(void *arg)
{

}
//-------------------------------------------------------------------------------
HANDLE usb_CreateInputThread()
{
	unsigned dwThreadID;
	HANDLE hThread;
	SECURITY_ATTRIBUTES sa =
	{
		sizeof(SECURITY_ATTRIBUTES),
		0,
		true
	};

	hThread = (HANDLE)_beginthreadex(&sa,
							4096,
							usb_ReadThreadProc,
							(void *)0,
							CREATE_SUSPENDED,
							&dwThreadID);

	InitializeCriticalSection(&FQueueLock);	

	return hThread;
}	

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	
	static HANDLE inputThread = NULL;
	static HANDLE FStopEvent = NULL;

	inputThread = usb_CreateInputThread();

	int input;
	std::cout << "Output\n";
	std::cin >> input;
	
}




