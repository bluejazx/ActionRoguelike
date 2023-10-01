// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Checks distance between AIPawn and TargetActor
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	//Ensure BlackBoard is set
	if (ensure(BlackBoardComp))
	{
		//Gets TargetActor
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		//Check for null
		if (TargetActor)
		{
			//Gets AIController
			AAIController* MyController = OwnerComp.GetAIOwner();
			//Check for null
			if (ensure(MyController))
			{
				//Gets AIController
				APawn* AIPawn = MyController->GetPawn();
				//Check for null
				if (ensure(AIPawn))
				{
					//Get distance from TartgetActor
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					//Check if within range
					bool bWithinRange = DistanceTo < 2000.f;

					bool bHasLOS = false;
					//Check for LineOfSight if within range
					if (bWithinRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}
					

					//Set key in BB
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
				}
			}
		}
	}
}
