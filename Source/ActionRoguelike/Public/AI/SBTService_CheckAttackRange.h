// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	
protected:

	//Editable anywhere in AI
	UPROPERTY(EditAnywhere, Category = "AI")
	//BB key for AttackRange
	FBlackboardKeySelector AttackRangeKey;

	/* Max desired attack range of AI pawn */
	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxAttackRange;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	USBTService_CheckAttackRange();

};
