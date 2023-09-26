// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:

	//Allows for this to be viewed and change in the editor
	UPROPERTY(EditAnywhere)
	//Variable for target pitch once Chest is fully opened
	float TargetPitch;
	
	//Implements the ISGameplayInterface into SItemChest
	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	//VisibleAnywhere makes visible in editor and BlueprintReadOnly makes it readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//Physical component for the bottom of the chest
	UStaticMeshComponent* BaseMesh;

	//VisibleAnywhere makes visible in editor and BlueprintReadOnly makes it readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//Physical component for the lid of the chest
	UStaticMeshComponent* LidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ASItemChest();

};
