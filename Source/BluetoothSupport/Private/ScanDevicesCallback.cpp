#include "ScanDevicesCallback.h"
#include "BluetoothSupportBPLibrary.h"


void UScanDevicesCallback::Activate()
{
	TaModule->ClearAllDeviceScanSucceedCompleteDelegate_Handle();
	SucceedDelegateHandle = TaModule->AddDeviceScanSucceedCompleteDelegate_Handle(SucceedDelegate);
	// Characteristic is optional, scan without filters if not present.
	if (searchService.IsEmpty() && searchAddress.IsEmpty())
	{
		UBluetoothSupportBPLibrary::ScanBLEdevices(searchTimeout);
	} 
	else {
		UBluetoothSupportBPLibrary::ScanByCharacteristic(searchTimeout, searchService, searchAddress);
	}
	
	// Call scan device start.
}

UScanDevicesCallback* UScanDevicesCallback::ScanNearbyDevices(int32 timeout, const FString& serviceUUID, const FString& deviceAddress)
{
	UScanDevicesCallback* Proxy = NewObject<UScanDevicesCallback>();
	Proxy->searchTimeout = timeout;
	Proxy->searchService = FString(serviceUUID);
	Proxy->searchAddress = FString(deviceAddress);
	return Proxy;
}

void UScanDevicesCallback::OnSucceedComplete(UBluetoothDevice* Device)
{
	OnResultFound.Broadcast(Device);

	// I should clear the trigger somwhere.
	SetReadyToDestroy();
}
