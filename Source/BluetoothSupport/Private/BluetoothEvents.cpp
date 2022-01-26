/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/

#include "BluetoothEvents.h"


UBluetoothEvents* UBluetoothEvents::instance = nullptr;

UBluetoothEvents* UBluetoothEvents::GetServerEvents() { 
	if (instance == nullptr) {
		instance = NewObject<UBluetoothEvents>();
	}
	return instance;
}