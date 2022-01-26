/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/


#pragma once


#include "Core.h"
#include "EngineMinimal.h"
#include "../Blueprint/BluetoothDevice.h"


class IBluetoothOperationsInterface
{ 
public:
	virtual bool IsBluetoothSupported() = 0;
	virtual void ShowAndroidToast(FString toastString) = 0;
	virtual bool IsGeolocationEnabled() = 0;

	virtual bool IsEnabled() = 0;
	virtual bool EnableBluetoothAdapter() = 0;
	virtual bool DisableBluetoothAdapter() = 0;
	virtual TArray<UBluetoothDevice*> GetBondedDevices() = 0;
	virtual bool IsBLESupported() =	0;
	virtual bool IsScanning() = 0;

	virtual bool ScanBLEdevices(int32 scanTimeout, int64 scanReportDelay) = 0;
	virtual bool ScanByCharacteristic(int32 scanTimeout, int64 scanReportDelay, FString characteristicUUID, FString addr) = 0;
	virtual void StopScan() = 0;
	virtual TArray<UBluetoothDevice*> GetDiscoveredDevices() = 0;
	virtual void ClearDiscoveredDevicesList() = 0;

	virtual bool CreateGattServer(FString serviceUUID, int32 maxConnections) = 0;
	virtual void ResumeAdvertisments() = 0;
	virtual void StopAdvertisments() = 0;
	virtual void StopGattServer() = 0;
	virtual bool IsAdvertismentsOn() = 0;
	virtual bool IsGattServerOn() = 0;
	virtual bool SetAutoAdvertisments(bool newValue) = 0;
	virtual TArray<UBluetoothDevice*> GetGattServerDevices() = 0;
	virtual bool IsDeviceConnected(UBluetoothDevice* device) = 0;
	virtual bool SendGattMessage(UBluetoothDevice* device, FString message) = 0;
	virtual void CancelGattDeviceConnection(UBluetoothDevice* device) = 0;

	virtual bool ConnectGatt(UBluetoothDevice* device) = 0;
	virtual void DisconnectGatt() = 0;
	virtual bool IsGattConnected() = 0;
};