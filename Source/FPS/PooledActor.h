// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledActorAdded, APooledActor*, PoolActor);

UCLASS()
class FPS_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APooledActor();

	FOnPooledActorAdded OnPooledActorAdded;

	void SetActive(bool bIsActive);
	void setLifeSpan(float lifespan);
	void setPoolIndex(int index);

	UFUNCTION(BlueprintCallable, Category = "PooledActor")
	void Deactivate();

	bool isActive();
	int getPoolIndex();

protected:
	bool Active;
	float lifeSpawn = 0;
	int PoolIndex;

	FTimerHandle lifeSpawnTimer;

};
