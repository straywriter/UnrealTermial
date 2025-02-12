// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMActor.generated.h"

UCLASS()
class WINDOWSTERMINAL_API ATMActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	static void Test();

	UFUNCTION()
	static void Test1(int32 a , int32 b);

};
