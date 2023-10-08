#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASItemChest::ASItemChest()
{
	//Creates BaseMesh as RootComp
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	//Creates LidMesh
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	//Attaches LidMesh to BaseMesh
	LidMesh->SetupAttachment(BaseMesh);

	//Sets target pitch to a value
	TargetPitch = 110;
}


void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	//Animates lid 
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}