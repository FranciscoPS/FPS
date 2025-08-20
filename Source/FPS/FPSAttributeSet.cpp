// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAttributeSet.h"
#include "FPSBaseCharacter.h"

UFPSAttributeSet::UFPSAttributeSet()
{
}

void UFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	AFPSBaseCharacter* MyCharacter = Cast<AFPSBaseCharacter>(GetOwningActor());
	if(Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, MyCharacter->maxHealth);
	else if(Attribute == GetArmorAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, MyCharacter->maxArmor);
	else if (Attribute == GetBulletsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, MyCharacter->maxBullets);
	else if (Attribute == GetRocketsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, MyCharacter->maxRockets);
}

bool UFPSAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	float AbsMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);
	AFPSBaseCharacter* MyCharacter = Cast<AFPSBaseCharacter>(GetOwningActor());
	if(Data.EvaluatedData.Magnitude > 0)
	{
		if(Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor()+AbsMagnitude >= MyCharacter->maxArmor)
		{
			SetArmor(MyCharacter->maxArmor);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth()+AbsMagnitude >= MyCharacter->maxHealth)
		{
			SetHealth(MyCharacter->maxHealth);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets()+AbsMagnitude >= MyCharacter->maxBullets)
		{
			SetBullets(MyCharacter->maxBullets);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets()+AbsMagnitude >= MyCharacter->maxRockets)
		{
			SetRockets(MyCharacter->maxRockets);
			return false;
		}

	}
	else
	{
	if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsMagnitude > GetArmor())
		Health.SetCurrentValue(Health.GetCurrentValue() -(AbsMagnitude-GetArmor()));	
	}


	return true;
}

void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() < 0)	
		SetHealth(0);
	else if(Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() < 0)
		SetArmor(0);
	else if(Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() < 0)
		SetBullets(0);
	else if(Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() < 0)
		SetRockets(0);
}
