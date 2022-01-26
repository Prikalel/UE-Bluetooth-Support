/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/


#include "BluetoothSupportBPLibrary.h"
#include "TaDispatcher.h"

UBluetoothSupportBPLibrary::UBluetoothSupportBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

bool UBluetoothSupportBPLibrary::IsBluetoothSupported()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsBluetoothSupported();
#endif
	return false;
}

void UBluetoothSupportBPLibrary::ShowAndroidToast(FString string)
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->ShowAndroidToast(string);
#endif
}

bool UBluetoothSupportBPLibrary::IsGeolocationEnabled()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsGeolocationEnabled();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::IsBluetoothEnabled()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsEnabled();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::EnableBluetooth()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->EnableBluetoothAdapter();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::DisableBluetooth()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->DisableBluetoothAdapter();
#endif
	return false;
}

TArray<UBluetoothDevice*> UBluetoothSupportBPLibrary::GetBondedDevices()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->GetBondedDevices();
#endif
	return {};
}

bool UBluetoothSupportBPLibrary::IsLowEnergySupported()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsBLESupported();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::IsBluetoothScanning()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsScanning();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::ScanBLEdevices(int32 scanTimeout, int64 scanReportDelay)
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->ScanBLEdevices(scanTimeout, scanReportDelay);
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::ScanByCharacteristic(int32 scanTimeout, int64 scanReportDelay, FString serviceUUID, FString deviceAddress)
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->ScanByCharacteristic(scanTimeout, scanReportDelay, serviceUUID, deviceAddress);
#endif
	return false;
}

void UBluetoothSupportBPLibrary::StopBluetoothScan()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->StopScan();
#endif
}

TArray<UBluetoothDevice*> UBluetoothSupportBPLibrary::GetDiscoveredDevices()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->GetDiscoveredDevices();
#endif
	return {};
}

void UBluetoothSupportBPLibrary::ClearDiscoveredDevicesList()
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->ClearDiscoveredDevicesList();
#endif
}

bool UBluetoothSupportBPLibrary::CreateGattServer(FString serviceUUID, int32 maxConnections) {
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->CreateGattServer(serviceUUID, maxConnections);
#endif
	return false;
}

void UBluetoothSupportBPLibrary::ResumeAdvertisments()
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->ResumeAdvertisments();
#endif
}

void UBluetoothSupportBPLibrary::StopAdvertisments()
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->StopAdvertisments();
#endif
}

void UBluetoothSupportBPLibrary::StopGattServer()
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->StopGattServer();
#endif
}

bool UBluetoothSupportBPLibrary::IsAdvertismentsOn()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsAdvertismentsOn();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::IsGattServerOn()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsGattServerOn();
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::SetAutoAdvertisments(bool toAutoAdvertisments)
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->SetAutoAdvertisments(toAutoAdvertisments);
#endif
	return false;
}

TArray<UBluetoothDevice*> UBluetoothSupportBPLibrary::GetGattServerDevices()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->GetGattServerDevices();
#endif
	return {};
}

bool UBluetoothSupportBPLibrary::IsDeviceConnected(UBluetoothDevice* device)
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsDeviceConnected(device);
#endif
	return false;
}

bool UBluetoothSupportBPLibrary::SendGattMessage(UBluetoothDevice* device, FString message) {
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->SendGattMessage(device, message);
#endif
	return false;
}

void UBluetoothSupportBPLibrary::CancelGattDeviceConnection(UBluetoothDevice* device)
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->CancelGattDeviceConnection(device);
#endif
}

bool UBluetoothSupportBPLibrary::ConnectGatt(UBluetoothDevice* device) {
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->ConnectGatt(device);
#endif
	return false;
}

void UBluetoothSupportBPLibrary::DisconnectGatt()
{
#if PLATFORM_ANDROID
	TaDispatcher::Get().GetAndroidGatewayInterface()->DisconnectGatt();
#endif
}

bool UBluetoothSupportBPLibrary::IsGattConnected()
{
#if PLATFORM_ANDROID
	return TaDispatcher::Get().GetAndroidGatewayInterface()->IsGattConnected();
#endif
	return false;
}