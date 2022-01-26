/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/

#pragma once

#include "Misc/CoreDelegates.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BluetoothEvents.h"
#include "BluetoothSupportBPLibrary.generated.h"

UCLASS()
class UBluetoothSupportBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static FORCEINLINE UBluetoothEvents* getGattServerEvents() { 
		return UBluetoothEvents::GetServerEvents();
	}

	// COMMON:

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|Adapter")
	static bool IsBluetoothSupported();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Additional")
	static void ShowAndroidToast(FString toastString);

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|Additional")
	static bool IsGeolocationEnabled();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|Adapter")
	static bool IsBluetoothEnabled();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Adapter")
	static bool EnableBluetooth();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Adapter")
	static bool DisableBluetooth();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Adapter")
	static TArray<UBluetoothDevice*> GetBondedDevices();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|Adapter")
	static bool IsLowEnergySupported();

	// SCANNING:

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|Scanning")
	static bool IsBluetoothScanning();

	/** These functions are for c++ only: */
	static bool ScanBLEdevices(int32 scanTimeout, int64 scanReportDelay);
	static bool ScanByCharacteristic(int32 scanTimeout, int64 scanReportDelay, FString serviceUUID, FString deviceAddress);

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Scanning")
	static void StopBluetoothScan();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Scanning")
	static TArray<UBluetoothDevice*> GetDiscoveredDevices();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|Scanning")
	static void ClearDiscoveredDevicesList();
	
	// GATT SERVER:

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static bool CreateGattServer(FString serviceUUID, int32 maxConnections); // Blocking.

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static void ResumeAdvertisments();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static void StopAdvertisments();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static void StopGattServer();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|GattServer")
	static bool IsAdvertismentsOn();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|GattServer")
	static bool IsGattServerOn();

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static bool SetAutoAdvertisments(bool newValue);

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static TArray<UBluetoothDevice*> GetGattServerDevices();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|GattServer")
	static bool IsDeviceConnected(UBluetoothDevice* device);

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static bool SendGattMessage(UBluetoothDevice* device, FString message); // Blocking.

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattServer")
	static void CancelGattDeviceConnection(UBluetoothDevice* device);

	// GATT CLIENT:

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattClient")
	static bool ConnectGatt(UBluetoothDevice* device); // Blocking.

	UFUNCTION(BlueprintCallable, Category = "Bluetooth Support Plugin|GattClient")
	static void DisconnectGatt();

	UFUNCTION(BlueprintPure, Category = "Bluetooth Support Plugin|GattClient")
	static bool IsGattConnected();
};