/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/

#pragma once


#include "Interfaces/BluetoothOperationsInterface.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#include "EngineMinimal.h"
#include "Core.h"
#include <string>

#include "../BluetoothSupport.h"


class FAndroidGateway : public IBluetoothOperationsInterface
{
public:
	FAndroidGateway();
	virtual ~FAndroidGateway() {}

	virtual bool IsBluetoothSupported()						override;
	virtual void ShowAndroidToast(FString toastString)		override;
	virtual bool IsGeolocationEnabled()						override;

	virtual bool IsEnabled()								override;
	virtual bool EnableBluetoothAdapter()					override;
	virtual bool DisableBluetoothAdapter()  				override;
	virtual TArray<UBluetoothDevice*> GetBondedDevices() 	override;
	virtual bool IsBLESupported()							override;
	virtual bool IsScanning()								override;

	virtual bool ScanBLEdevices(int32 scanTimeout, int64 scanReportDelay)													override;
	virtual bool ScanByCharacteristic(int32 scanTimeout, int64 scanReportDelay, FString serviceUUID, FString deviceAddress)	override;
	virtual void StopScan()					 					override;
	virtual TArray<UBluetoothDevice*> GetDiscoveredDevices()	override;
	virtual void ClearDiscoveredDevicesList()  					override;

	virtual bool CreateGattServer(FString serviceUUID, int32 maxConnections) 	override; // Blocking.
	virtual void ResumeAdvertisments() 											override;
	virtual void StopAdvertisments() 											override;
	virtual void StopGattServer() 												override;
	virtual bool IsAdvertismentsOn() 											override;
	virtual bool IsGattServerOn() 												override;
	virtual bool SetAutoAdvertisments(bool newValue) 							override;
	virtual TArray<UBluetoothDevice*> GetGattServerDevices() 					override;
	virtual bool IsDeviceConnected(UBluetoothDevice* device) 					override;
	virtual bool SendGattMessage(UBluetoothDevice* device, FString message) 	override; // Blocking.
	virtual void CancelGattDeviceConnection(UBluetoothDevice* device) 			override;

	virtual bool ConnectGatt(UBluetoothDevice* device)		override; // Blocking.
	virtual void DisconnectGatt() 							override;
	virtual bool IsGattConnected()							override;

	// They all must end with 'Method' suffix (see macro in cpp file):

	jmethodID isBluetoothSupportedMethod;
	jmethodID ShowToastMethod;
	jmethodID isGeolocationEnabledMethod;

	jmethodID isBluetoothEnabledMethod;
	jmethodID enableBluetoothMethod;
	jmethodID disableBluetoothMethod;
	jmethodID getBluetoothBondedDevicesMethod;
	jmethodID isBluetoothLowEnergySupportedMethod;
	jmethodID isScanningMethod;

	jmethodID startLEScanMethod;
	jmethodID startFilteredScanMethod;
	jmethodID stopLEScanMethod;
	jmethodID getDiscoveredDevicesMethod;
	jmethodID clearDiscoveredDevicesMethod;

	jmethodID createBLEGattServerMethod;
	jmethodID resumeAdvertismentsMethod;
	jmethodID stopAdvertisingMethod;
	jmethodID stopBLEGattServerMethod;
	jmethodID isAdvertisingRunningMethod;
	jmethodID isBleGattServerRunningMethod;
	jmethodID setAutoAdvertismentsMethod;
	jmethodID getBLEServerConnectedDevicesMethod;
	jmethodID isDeviceBleConnectedMethod;
	jmethodID sendBLEMessageMethod;
	jmethodID closeBLEDeviceConnectionMethod;

	jmethodID connectGattServerMethod;
	jmethodID stopBLEGattClientMethod;
	jmethodID isRunningGattClientMethod;
};