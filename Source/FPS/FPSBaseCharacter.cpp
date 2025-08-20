// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "FPSAttributeSet.h"

// Sets default values
AFPSBaseCharacter::AFPSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UFPSAttributeSet>("AttributeSet");

}

UAbilitySystemComponent* AFPSBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Called when the game starts or when spawned
void AFPSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		if (DefaultAttributeEffect)
		{
			FGameplayEffectContextHandle effectHandle = AbilitySystemComponent->MakeEffectContext();
			effectHandle.AddSourceObject(this);
			FGameplayEffectSpecHandle spectHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, effectHandle);

			if (spectHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*spectHandle.Data.Get());
			}
		}
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& f : defaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(f.GetDefaultObject(), 1, 0));
			}
		}
	}
	
}

// Called every frame
void AFPSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

