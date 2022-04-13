// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCourseActor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(CourseLOG,All,All)
// Sets default values
ABaseCourseActor::ABaseCourseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");    //объявляем статик меш компонент
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseCourseActor::BeginPlay()
{
	Super::BeginPlay();

	initialLocation = GetActorLocation();
	setColor(SinMovementData.Tint);
	
	GetWorldTimerManager().SetTimer(Timer,this,&ABaseCourseActor::TimerFired,SinMovementData.TimerTickInterval,true);
}
void ABaseCourseActor::printStringTypes()
{
	FString Name = "Artem Mayangin";
	UE_LOG(CourseLOG,Display, TEXT("Name: %s"), *Name)

	int WeaponsNum = 4;
	float Health = 34.45425f;
	bool IsDead	= false;

	FString WeaponNumStr = "WeaponsNum " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead " + FString(IsDead? "true" : "false");

	FString Stat = FString::Printf(TEXT("\n***All stat***\n %s\n%s\n%s"),*WeaponNumStr,*HealthStr,*IsDeadStr);
	
	UE_LOG(CourseLOG, Warning, TEXT("Name: %s"), *GetName());
	UE_LOG(CourseLOG,Warning, TEXT("Stat: %s"), *Stat);
	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,Name,true,FVector2D(1.5f,1.5f));

}


// Called every frame
void ABaseCourseActor::Tick(float DeltaTime)
{
	switch (SinMovementData.DynState)
	{
	case EDynamicState::Static: break;
	case EDynamicState::Dynamic:
		{
			FVector CurrentLocation = GetActorLocation();
			float time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = initialLocation.Z + SinMovementData.amplitude * FMath::Sin(SinMovementData.frequency*time);
			SetActorLocation(CurrentLocation);	
		}
		break;
	default: ;
	}

	
}

void ABaseCourseActor::TimerFired()
{
	if (++CurrentTimerCount<=MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		setColor(NewColor);
		UE_LOG(LogTemp, Warning, TEXT("Color: %s,\n Count %d"), *NewColor.ToString(), CurrentTimerCount);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Timer);
		UE_LOG(LogTemp, Warning, TEXT("Timer has stoped"));
	}
}

void ABaseCourseActor::printTypes()
{
	UE_LOG(LogTemp, Display, TEXT("Hello Unreal Engine"));
	UE_LOG(LogTemp, Warning, TEXT("Hello Unreal Engine"));
	UE_LOG(LogTemp, Error, TEXT("Hello Unreal Engine"));

	int WeaponsNum = 4;
	int KillsNum = 7;
	float Health = 34.45425f;
	bool IsDead	= false;
	bool HasWeapon = true;
	
	UE_LOG(LogTemp, Display, TEXT("WeaponsNum: %d, KillNum: %i"), WeaponsNum,KillsNum);
	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Display, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTemp, Display, TEXT("HasWeapon: %d"), static_cast<int>(IsDead));
}
void ABaseCourseActor::printTransform()
{
	FTransform DefaultTransfrom = GetActorTransform();
	FVector DefaultLocation = DefaultTransfrom.GetLocation();
	FRotator DefaultRotation = DefaultTransfrom.Rotator();
	FVector DefaultScale = DefaultTransfrom.GetScale3D();

	UE_LOG(CourseLOG,Warning, TEXT("Location: %s"), *DefaultLocation.ToString())
	UE_LOG(CourseLOG,Warning, TEXT("Rotation: %s"), *DefaultRotation.ToString())
	UE_LOG(CourseLOG,Warning, TEXT("Scale: %s"), *DefaultScale.ToString())
	UE_LOG(CourseLOG,Warning, TEXT("Transform: %s"), *DefaultTransfrom.ToHumanReadableString())
}

void ABaseCourseActor::setColor(const FLinearColor& Tint)
{
	UMaterialInstanceDynamic*DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Tint",Tint);
	}
}

