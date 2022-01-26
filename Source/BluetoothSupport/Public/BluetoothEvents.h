/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Misc/CoreDelegates.h"
#include "Blueprint/BluetoothDevice.h"
#include "BluetoothEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceDelegate, UBluetoothDevice*, Device);

UCLASS(Blueprintable)
class UBluetoothEvents : public UObject
{
	GENERATED_BODY()

private:
	UBluetoothEvents() {}

	static UBluetoothEvents* instance;

public:
	UPROPERTY(BlueprintAssignable, Category = "Bluetooth Support Plugin|GattServer")
	FDeviceDelegate OnNewGattConnection;

	UPROPERTY(BlueprintAssignable, Category = "Bluetooth Support Plugin|GattServer")
	FDeviceDelegate OnGattConnectionClosed;

	static UBluetoothEvents* GetServerEvents();
};