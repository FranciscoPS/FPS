// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledActor.h"

// Sets default values
APooledActor::APooledActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APooledActor::SetActive(bool bIsActive)
{
	Active = bIsActive;
	SetActorHiddenInGame(!bIsActive);
	GetWorldTimerManager().SetTimer(lifeSpawnTimer, this, &APooledActor::Deactivate, lifeSpawn, true);
}

void APooledActor::setLifeSpan(float lifespan)
{
	lifeSpawn = lifespan;
}

void APooledActor::setPoolIndex(int index)
{
	PoolIndex = index;
}

void APooledActor::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledActorAdded.Broadcast(this);
}

bool APooledActor::isActive()
{
	return Active;
}

int APooledActor::getPoolIndex()
{
	return PoolIndex;
}

