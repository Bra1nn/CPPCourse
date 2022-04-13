// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCourseActor.h"
#include "GameFramework/Actor.h"
#include "CourseSpawner.generated.h"


USTRUCT(BlueprintType)
struct FLoadData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Load settings")
	TSubclassOf<ABaseCourseActor> SpawnClass;

	UPROPERTY(EditAnywhere, Category = "Load settings")
	FSinMovementData Data;
	
	UPROPERTY(EditAnywhere, Category = "Load settings")
	FTransform InitTransform;
};


UCLASS()
class CPPCOURSE_API ACourseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACourseSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseCourseActor> CourseActor;

	UPROPERTY(EditAnywhere)
	UClass* Class;

	UPROPERTY(EditAnywhere)
	ABaseCourseActor* CourseObject;
	
	UPROPERTY(EditAnywhere)
	TArray<FLoadData> InitLoadDataArr;
	
	void SpawnCourse1();
	void SpawnCourse2();
	void SpawnCourse3();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
