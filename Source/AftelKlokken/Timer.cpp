// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"

// Sets default values
ATimer::ATimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the (root) component
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	RootComponent = Widget;
}

// Called when the game starts or when spawned
void ATimer::BeginPlay()
{
	Super::BeginPlay();

	ResetTimer();
}

// Called every frame
void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsCountingDown && _timeLeft > 0)
	{
		SetTimeLeft(FMath::Clamp(_timeLeft - DeltaTime, 0, StartTime));
	}

	if (IsKeyJustPressed(ResetKey))
	{
		ResetTimer();
	}

	if (IsKeyJustPressed(StartStopKey))
	{
		IsCountingDown = !IsCountingDown;
	}
}

FText ATimer::SecondsToTimerText(float time)
{
	int minutes = FMath::Floor(time) / 60;
	int seconds = (int)(FMath::Floor(time)) % 60;
	int centiSeconds = (time - FMath::Floor(time)) * 100;

	FString text = FString::Printf(TEXT("%02d:%02d:%02d"), minutes, seconds, centiSeconds);
	return FText::FromString(text);
}

void ATimer::ResetTimer()
{
	SetTimeLeft(StartTime);
}

float  ATimer::GetTimeLeft() const 
{ 
	return _timeLeft; 
}

void  ATimer::SetTimeLeft(float newValue)
{
	if (_timeLeft != newValue)
	{
		_timeLeft = newValue;
		OnTimeChanged.Broadcast();
	}
}


bool ATimer::IsKeyJustPressed(FKey key)
{
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		return controller->WasInputKeyJustPressed(key);
	}
	return false;
}

