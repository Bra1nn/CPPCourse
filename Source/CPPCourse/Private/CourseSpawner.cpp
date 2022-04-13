// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseSpawner.h"
#include "Engine/World.h"

// Sets default values
ACourseSpawner::ACourseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACourseSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnCourse3();

		
}

// Called every frame
void ACourseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACourseSpawner::SpawnCourse1()
{
	UWorld* CourseWorld = GetWorld();
	if (CourseWorld)
	{
		for (int32 i=0;i<10;++i)
		{
			FTransform SpawnDefaultTransform = FTransform(FRotator::ZeroRotator,FVector(0.0f,0.0f,200.0f*i));
			ABaseCourseActor* NewSpawnActor = CourseWorld->SpawnActor<ABaseCourseActor>(CourseActor, SpawnDefaultTransform);
			if (NewSpawnActor)
			{
				FSinMovementData Data;
				Data.DynState = FMath::RandBool() ? EDynamicState::Static : EDynamicState::Dynamic;
				NewSpawnActor->setCourseMeshData(Data);
			}
					
		}
	}
}
void ACourseSpawner::SpawnCourse2()
{
	UWorld* CourseWorld = GetWorld();
		for (int32 i=0;i<10;++i)
		{
			FTransform SpawnDefaultTransform = FTransform(FRotator::ZeroRotator,FVector(500.0f,500.0f,100.0f*i));
			ABaseCourseActor* NewSpawnActor = CourseWorld->SpawnActorDeferred<ABaseCourseActor>(CourseActor, SpawnDefaultTransform);
			if (NewSpawnActor)
			{
				FSinMovementData Data;
				Data.Tint = FLinearColor::MakeRandomColor();
				NewSpawnActor->setCourseMeshData(Data);
				NewSpawnActor->FinishSpawning(SpawnDefaultTransform);
			}
		
		}
}
void ACourseSpawner::SpawnCourse3()
{
	UWorld* CourseWorld = GetWorld();
		for (FLoadData ActorFromArr : InitLoadDataArr)
		{
			FTransform SpawnDefaultTransform = FTransform(FRotator::ZeroRotator,FVector(500.0f,500.0f,100.0f));
			ABaseCourseActor* NewSpawnActor = CourseWorld->SpawnActorDeferred<ABaseCourseActor>(ActorFromArr.SpawnClass, ActorFromArr.InitTransform);
			if (NewSpawnActor)
			{
				NewSpawnActor->setCourseMeshData(ActorFromArr.Data);
				NewSpawnActor->FinishSpawning(ActorFromArr.InitTransform);
			}
		
		}
}
