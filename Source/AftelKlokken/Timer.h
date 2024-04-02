// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "Delegates/DelegateCombinations.h"
#include "Components/WidgetComponent.h"
#include "Timer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeChangedEvent);


UCLASS()
class AFTELKLOKKEN_API ATimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// DELEGATES
public:
	UPROPERTY(BlueprintAssignable)
	FOnTimeChangedEvent OnTimeChanged;


// VARIABLES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsCountingDown = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StartTime = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FKey ResetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FKey StartStopKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FKey ToggleVisibilityKey;

private:
	float m_timeLeft;


// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable)
		FText SecondsToTimerText(float time);

	void ResetTimer();

	UFUNCTION(BlueprintCallable)
		float GetTimeLeft() const;

private:
	void SetTimeLeft(float newValue);

	bool IsKeyJustPressed(FKey key);
};
