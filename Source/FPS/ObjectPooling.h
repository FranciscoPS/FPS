// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "Components/ActorComponent.h"
#include "ObjectPooling.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UObjectPooling : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPooling();

	UFUNCTION(BlueprintCallable, Category = "ObjectPool")
	APooledActor* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	TSubclassOf<APooledActor> PoolClass;

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	int poolSize = 20;

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	float pooledObjectLifeSpawn = 0.0f;

	UFUNCTION()
	void OnPooledObjectDespawn(APooledActor* poolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APooledActor*> SpawnedObjects;
	TArray<int> spawnIndex;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
