/**
* !Created By Taha HICHRI
* @project    Bluetooth Support for UNREAL engine.
* @author     Taha HICHRI <hishri.taha@gmail.com>
* @see        https://github.com/hishriTaha
* Copyright (c) 2018 hishri.com
*/

#pragma once	
#include "AndroidGateway.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "../../Public/BluetoothEvents.h"
#include "Async.h"

#define INIT_JAVA_METHOD(name, signature) \
	name##Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
	check(name##Method != NULL); 


FAndroidGateway::FAndroidGateway()
{
	// Java signatures: http://www.rgagnon.com/javadetails/java-0286.html.
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		INIT_JAVA_METHOD(isBluetoothSupported, "()Z");
		INIT_JAVA_METHOD(ShowToast, "(Ljava/lang/String;)V");
		INIT_JAVA_METHOD(isGeolocationEnabled, "()Z");
		
		INIT_JAVA_METHOD(isBluetoothEnabled, "()Z");
		INIT_JAVA_METHOD(enableBluetooth, "()Z");
		INIT_JAVA_METHOD(disableBluetooth, "()Z");
		INIT_JAVA_METHOD(getBluetoothBondedDevices, "()[Ljava/lang/String;");
		INIT_JAVA_METHOD(isBluetoothLowEnergySupported, "()Z");
		INIT_JAVA_METHOD(isScanning, "()Z");

		INIT_JAVA_METHOD(startLEScan, "(IJ)V");
		INIT_JAVA_METHOD(startFilteredScan, "(IJLjava/lang/String;Ljava/lang/String;)V");
		INIT_JAVA_METHOD(stopLEScan, "()V");
		INIT_JAVA_METHOD(getDiscoveredDevices, "()[Ljava/lang/String;");
		INIT_JAVA_METHOD(clearDiscoveredDevices, "()V");

		INIT_JAVA_METHOD(createBLEGattServer, "(Ljava/lang/String;I)Z");
		INIT_JAVA_METHOD(resumeAdvertisments, "()V");
		INIT_JAVA_METHOD(stopAdvertising, "()V");
		INIT_JAVA_METHOD(stopBLEGattServer, "()V");
		INIT_JAVA_METHOD(isAdvertisingRunning, "()Z");
		INIT_JAVA_METHOD(isBleGattServerRunning, "()Z");
		INIT_JAVA_METHOD(setAutoAdvertisments, "(Z)Z");
		INIT_JAVA_METHOD(getBLEServerConnectedDevices, "()[Ljava/lang/String;");
		INIT_JAVA_METHOD(isDeviceBleConnected, "(Ljava/lang/String;)Z");
		INIT_JAVA_METHOD(sendBLEMessage, "(Ljava/lang/String;Ljava/lang/String;)Z");
		INIT_JAVA_METHOD(closeBLEDeviceConnection, "(Ljava/lang/String;)V");

		INIT_JAVA_METHOD(connectGattServer, "(Ljava/lang/String;)Z");
		INIT_JAVA_METHOD(stopBLEGattClient, "()V");
		INIT_JAVA_METHOD(isRunningGattClient, "()Z");
	}
}

bool FAndroidGateway::IsBluetoothSupported()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isBluetoothSupportedMethod);
	}
	return false;
}

void FAndroidGateway::ShowAndroidToast(FString toastString) 
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring jStringMessageParam = Env->NewStringUTF(TCHAR_TO_UTF8(*toastString));
		if (!jStringMessageParam) {
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from toastString"));
		}
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::ShowToastMethod, jStringMessageParam);
		Env->DeleteLocalRef(jStringMessageParam);
	}
}

bool FAndroidGateway::IsGeolocationEnabled()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isGeolocationEnabledMethod);
	}
	return false;
}

bool FAndroidGateway::IsEnabled()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env,
											   FJavaWrapper::GameActivityThis,
											   FAndroidGateway::isBluetoothEnabledMethod);
	}
	return false;
}

bool FAndroidGateway::EnableBluetoothAdapter()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env,
											   FJavaWrapper::GameActivityThis,
											   FAndroidGateway::enableBluetoothMethod);
	}
	return false;
}

bool FAndroidGateway::DisableBluetoothAdapter()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env,
											   FJavaWrapper::GameActivityThis,
											   FAndroidGateway::disableBluetoothMethod);
	}
	return false;
}

TArray<UBluetoothDevice*> FAndroidGateway::GetBondedDevices()
{
	TArray<UBluetoothDevice*> BondedDevices;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jobjectArray BluetoothDevicesStrArr = (jobjectArray)Env->CallObjectMethod(FJavaWrapper::GameActivityThis, 
																				  FAndroidGateway::getBluetoothBondedDevicesMethod);
		int BluetoothDevicesStrArrSize = Env->GetArrayLength(BluetoothDevicesStrArr);

		// Splitting Devices info and creating a new Device object.
		for (int i = 0; i < BluetoothDevicesStrArrSize; ++i)
		{
			jstring string = (jstring)Env->GetObjectArrayElement(BluetoothDevicesStrArr, i);
			
			const char* mayarray = Env->GetStringUTFChars(string, 0);

			UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
			Ubd->InitDevice(UTF8_TO_TCHAR(mayarray), false);

			BondedDevices.Add(Ubd);

			Env->ReleaseStringUTFChars(string, mayarray);
			Env->DeleteLocalRef(string);
		}
	}
	return BondedDevices;
}

bool FAndroidGateway::IsBLESupported()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isBluetoothLowEnergySupportedMethod);
	}
	return false;
}

bool FAndroidGateway::IsScanning()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isScanningMethod);
	}
	return false;
}

bool FAndroidGateway::ScanBLEdevices(int32 scanTimeout, int64 scanReportDelay)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::startLEScanMethod, 
									 (jint)scanTimeout, (jlong)scanReportDelay);
		return true;
	}
	return false;
}

bool FAndroidGateway::ScanByCharacteristic(int32 scanTimeout, int64 scanReportDelay, FString serviceUUID, FString deviceAddr)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring jStringUUIDParam = Env->NewStringUTF(TCHAR_TO_UTF8(*serviceUUID));
		jstring jStringAddrParam = Env->NewStringUTF(TCHAR_TO_UTF8(*deviceAddr));

		if (!jStringUUIDParam || !jStringAddrParam)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from uuid or address string"));
		}

		FJavaWrapper::CallVoidMethod(Env, 
									 FJavaWrapper::GameActivityThis, 
									 FAndroidGateway::startFilteredScanMethod, 
									 (jint)scanTimeout, 
									 (jlong)scanReportDelay,
									 jStringUUIDParam, 
									 jStringAddrParam);
		
		Env->DeleteLocalRef(jStringUUIDParam);
		Env->DeleteLocalRef(jStringAddrParam);
		return true;
	}
	return false;
}

void FAndroidGateway::StopScan()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::stopLEScanMethod);
	}
}

TArray<UBluetoothDevice*> FAndroidGateway::GetDiscoveredDevices()
{
	TArray<UBluetoothDevice*> DiscoveredDevices;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jobjectArray BluetoothDevicesStrArr = (jobjectArray)Env->CallObjectMethod(FJavaWrapper::GameActivityThis, 
																				  FAndroidGateway::getDiscoveredDevicesMethod);
		int BluetoothDevicesStrArrSize = Env->GetArrayLength(BluetoothDevicesStrArr);

		// Splitting Devices info and creating a new Device object.
		for (int i = 0; i < BluetoothDevicesStrArrSize; ++i)
		{
			jstring string = (jstring)Env->GetObjectArrayElement(BluetoothDevicesStrArr, i);
			
			const char* mayarray = Env->GetStringUTFChars(string, 0);

			UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
			Ubd->InitDevice(UTF8_TO_TCHAR(mayarray), true);

			DiscoveredDevices.Add(Ubd);

			Env->ReleaseStringUTFChars(string, mayarray);
			Env->DeleteLocalRef(string);
		}
	}
	return DiscoveredDevices;
}

void FAndroidGateway::ClearDiscoveredDevicesList()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::clearDiscoveredDevicesMethod);
	}
}

bool FAndroidGateway::CreateGattServer(FString serviceUUID, int32 maxConnections)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring jStringUUIDParam = Env->NewStringUTF(TCHAR_TO_UTF8(*serviceUUID));

		if (!jStringUUIDParam)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from uuid string when creating a GattServer"));
		}

		bool bRes = FJavaWrapper::CallBooleanMethod(Env, 
													FJavaWrapper::GameActivityThis, 
													FAndroidGateway::createBLEGattServerMethod, 
													jStringUUIDParam, 
													(jint)maxConnections);
		
		Env->DeleteLocalRef(jStringUUIDParam);
		return bRes;
	}
	return false;
}

void FAndroidGateway::ResumeAdvertisments()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::resumeAdvertismentsMethod);
	}
}

void FAndroidGateway::StopAdvertisments()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::stopAdvertisingMethod);
	}
}

void FAndroidGateway::StopGattServer()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::stopBLEGattServerMethod);
	}
}

bool FAndroidGateway::IsAdvertismentsOn()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isAdvertisingRunningMethod);
	}
	return false;
}

bool FAndroidGateway::IsGattServerOn()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isBleGattServerRunningMethod);
	}
	return false;
}

bool FAndroidGateway::SetAutoAdvertisments(bool toAutoAdvertisments)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, 
											   FAndroidGateway::setAutoAdvertismentsMethod, (jboolean)toAutoAdvertisments);
	}
	return false;
}

TArray<UBluetoothDevice*> FAndroidGateway::GetGattServerDevices()
{
	TArray<UBluetoothDevice*> GattServerDevices;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jobjectArray BluetoothDevicesStrArr = (jobjectArray)Env->CallObjectMethod(FJavaWrapper::GameActivityThis, 
																				  FAndroidGateway::getBLEServerConnectedDevicesMethod);
		int BluetoothDevicesStrArrSize = Env->GetArrayLength(BluetoothDevicesStrArr);

		for (int i = 0; i < BluetoothDevicesStrArrSize; ++i)
		{
			jstring string = (jstring)Env->GetObjectArrayElement(BluetoothDevicesStrArr, i);
			
			const char* mayarray = Env->GetStringUTFChars(string, 0);

			UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
			Ubd->InitDevice(UTF8_TO_TCHAR(mayarray), false);

			GattServerDevices.Add(Ubd);

			Env->ReleaseStringUTFChars(string, mayarray);
			Env->DeleteLocalRef(string);
		}
	}
	return GattServerDevices;
}

bool FAndroidGateway::IsDeviceConnected(UBluetoothDevice* device) 
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env && device)
	{
		FString deviceRepresentation = device->StringifyShort();
		jstring jStringRepresentation = Env->NewStringUTF(TCHAR_TO_UTF8(*deviceRepresentation));
		if (!jStringRepresentation) {
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from device representation"));
		}
		bool bResult = (bool)FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isDeviceBleConnectedMethod, jStringRepresentation);
		Env->DeleteLocalRef(jStringRepresentation);
		return bResult;
	}
	return false;
}

bool FAndroidGateway::SendGattMessage(UBluetoothDevice* device, FString message)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env && device)
	{
		FString deviceRepresentation = device->StringifyShort();
		jstring jStringRepresentation = Env->NewStringUTF(TCHAR_TO_UTF8(*deviceRepresentation));
		jstring jStringMessage = Env->NewStringUTF(TCHAR_TO_UTF8(*message));

		if (!jStringRepresentation || !jStringMessage)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from device representation or from message"));
		}

		bool bResult = (bool)FJavaWrapper::CallBooleanMethod(Env, 
															 FJavaWrapper::GameActivityThis, 
															 FAndroidGateway::sendBLEMessageMethod, 
															 jStringRepresentation, 
															 jStringMessage);
		
		Env->DeleteLocalRef(jStringRepresentation);
		Env->DeleteLocalRef(jStringMessage);
		return bResult;
	}
	return false;
}

void FAndroidGateway::CancelGattDeviceConnection(UBluetoothDevice* device) 
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env && device)
	{
		FString deviceRepresentation = device->StringifyShort();
		jstring jStringRepresentation = Env->NewStringUTF(TCHAR_TO_UTF8(*deviceRepresentation));
		if (!jStringRepresentation) {
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from device representation"));
		}
		FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::closeBLEDeviceConnectionMethod, jStringRepresentation);
		Env->DeleteLocalRef(jStringRepresentation);
	}
}

bool FAndroidGateway::ConnectGatt(UBluetoothDevice* device)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env && device)
	{
		FString deviceRepresentation = device->StringifyShort();
		jstring jStringRepresentation = Env->NewStringUTF(TCHAR_TO_UTF8(*deviceRepresentation));
		if (!jStringRepresentation)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Could Not generate jstring from device representation"));
		}

		bool bResult = (bool)FJavaWrapper::CallBooleanMethod(Env, 
															 FJavaWrapper::GameActivityThis, 
															 FAndroidGateway::connectGattServerMethod, 
															 jStringRepresentation);
		
		Env->DeleteLocalRef(jStringRepresentation);
		return bResult;
	}
	return false;
}

void FAndroidGateway::DisconnectGatt()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::stopBLEGattClientMethod);
	}
}

bool FAndroidGateway::IsGattConnected()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FAndroidGateway::isRunningGattClientMethod);
	}
	return false;
}

/** See native java functions implementation (where we use this macro)...
 */
#define CALL_BLSUPPORTMODULE_METHOD(FunctionAndArguments) \
	FBluetoothSupportModule * Module = FModuleManager::Get().LoadModulePtr<FBluetoothSupportModule>("BluetoothSupport"); \
	if (Module != nullptr) \
	{ \
		Module->FunctionAndArguments; \
		Module = NULL; \
	}


static FCriticalSection ReceiversLock;

extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_cppOnScanResult(JNIEnv * jni, jclass clazz, jstring deviceString)
	{
		ReceiversLock.Lock();
		const char* charArray = jni->GetStringUTFChars(deviceString, 0);

		UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
		Ubd->InitDevice(FString(UTF8_TO_TCHAR(charArray)), true);

		CALL_BLSUPPORTMODULE_METHOD(TriggerDeviceScanSucceedCompleteDelegates(Ubd));

		jni->ReleaseStringUTFChars(deviceString, charArray);
		ReceiversLock.Unlock();
	}

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_cppOnScanFinish(JNIEnv * jni, jclass clazz)
	{
		ReceiversLock.Lock();
		CALL_BLSUPPORTMODULE_METHOD(TriggerDeviceScanFinishDelegates());
		ReceiversLock.Unlock();
	}

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_printDebugUEMessage(JNIEnv * jni, jclass clazz, jstring message)
	{
		ReceiversLock.Lock();
		const char* charArray = jni->GetStringUTFChars(message, 0);

		FString debug_Message = FString(UTF8_TO_TCHAR(charArray));

		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, debug_Message);  
		}

		jni->ReleaseStringUTFChars(message, charArray);
		ReceiversLock.Unlock();
	}

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_cppOnClientMessage(JNIEnv * jni, jclass clazz, jstring deviceString, jstring message)
	{
		// TODO
	}

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_cppOnNewConnection(JNIEnv * jni, jclass clazz, jstring deviceString)
	{
		ReceiversLock.Lock();
		const char* charArray = jni->GetStringUTFChars(deviceString, 0);

		UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
		Ubd->InitDevice(FString(UTF8_TO_TCHAR(charArray)), false);

		UBluetoothEvents::GetServerEvents()->OnNewGattConnection.Broadcast(Ubd);

		jni->ReleaseStringUTFChars(deviceString, charArray);
		ReceiversLock.Unlock();
	}

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_cppOnConnectionClosed(JNIEnv * jni, jclass clazz, jstring deviceString)
	{
		ReceiversLock.Lock();
		const char* charArray = jni->GetStringUTFChars(deviceString, 0);

		UBluetoothDevice* Ubd = NewObject<UBluetoothDevice>();
		Ubd->InitDevice(FString(UTF8_TO_TCHAR(charArray)), false);

		UBluetoothEvents::GetServerEvents()->OnGattConnectionClosed.Broadcast(Ubd);

		jni->ReleaseStringUTFChars(deviceString, charArray);
		ReceiversLock.Unlock();
	}
}