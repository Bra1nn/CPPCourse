// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BaseCourseActor.generated.h"

UENUM(BlueprintType)
enum class EDynamicState:uint8
{
	Static,
	Dynamic
};

USTRUCT(BlueprintType)
struct FSinMovementData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "MeshDynamic")
	EDynamicState DynState = EDynamicState::Static;
	
	UPROPERTY(EditAnywhere, Category = "MeshDynamic")
	float amplitude = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "MeshDynamic")
	float frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "MeshDynamic")
	FLinearColor Tint = FLinearColor::Gray;
	
	UPROPERTY(EditAnywhere, Category = "MeshDynamic")
	float TimerTickInterval = 3.0f;
};

UCLASS()
class CPPCOURSE_API ABaseCourseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCourseActor();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void setCourseMeshData(FSinMovementData& Data) {SinMovementData = Data;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FSinMovementData SinMovementData;

	FTimerHandle Timer;
	int32 MaxTimerCount = 5;
	int32 CurrentTimerCount = 0;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
	FVector initialLocation;
	void TimerFired();
	void printTypes();
	void printStringTypes();
	void printTransform();
	void setColor(const FLinearColor& Tint);
};
