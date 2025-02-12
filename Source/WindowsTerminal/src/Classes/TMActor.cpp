// Fill out your copyright notice in the Description page of Project Settings.



//
// THIRD_PARTY_INCLUDES_START
// // UE_PUSH_MACRO("check")
// #undef check
// //
// // #include "Windows/PreWindowsApi.h"
// // #include "Windows/AllowWindowsPlatformTypes.h"
// // #include "Windows/AllowWindowsPlatformAtomics.h"
// #include "pch.h"
// //
// #include "Terminal.hpp"
//
#include "TMActor.h"

#include "test.h"
// Sets default values
ATMActor::ATMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMActor::BeginPlay()
{
	Super::BeginPlay();

	test();

	// test2();
	
}

// Called every frame
void ATMActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMActor::Test()
{
	test();

}

void ATMActor::Test1(int32 a, int32 b)
{
	UE_LOG(LogTemp, Log, TEXT("Called static function: %d + %d = %d"), a, b, a+b );
	
}

// #include ""
