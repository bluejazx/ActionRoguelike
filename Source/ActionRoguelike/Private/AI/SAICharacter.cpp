// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	//Creates PawnSensingComp
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	//Gets and sets AI controller 
	AAIController* AIC = Cast<AAIController>(GetController());
	//check for null
	if (AIC)
	{
		//Gets and sets Blackboard
		UBlackboardComponent* BBcomp = AIC->GetBlackboardComponent();

		//Sets the seen Actor TargetActor
		BBcomp->SetValueAsObject("TargetActor", Pawn);

		//Debug string where TargetActor was seen
		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}




