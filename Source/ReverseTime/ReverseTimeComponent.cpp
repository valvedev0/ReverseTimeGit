// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseTimeComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "ReverseTimeCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "FramePackage.h"





// Sets default values for this component's properties
UReverseTimeComponent::UReverseTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
		
	bReversingTime = false; // Set to true to reverse time
}


// Called when the game starts
void UReverseTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	AReverseTimeCharacter* RevTimeCharacter  = Cast<AReverseTimeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RevTimeCharacter->ReverseTimeDelegate.AddDynamic(this, &UReverseTimeComponent::SetReversingTime);

}


// Called every frame
void UReverseTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if (!bReversingTime) // store data
	{
		AActor* Owner = GetOwner();
		TArray<UActorComponent*> Components = Owner->GetComponentsByClass(UStaticMeshComponent::StaticClass());

		if (Components.Num() > 0) {

			UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Components[0]);
			if (SMC) {

				FFramePackage Package (Owner->GetActorLocation(), Owner->GetActorRotation(), SMC->GetPhysicsAngularVelocity(),
					SMC->GetPhysicsLinearVelocity(), DeltaTime);

				if (RecordedTime > 15.0f) {
					StoredFrames.AddTail(Package);
					RecordedTime += Package.DeltaTime;
					bOutOfData = false;
				}
				else {
					while (RecordedTime >= 15.0f) {
						auto Head = StoredFrames.GetHead();
						float HeadDT = Head->GetValue().DeltaTime;
						StoredFrames.RemoveNode(Head);
						RecordedTime -= HeadDT;
					}

					StoredFrames.AddTail(Package);
					RecordedTime += Package.DeltaTime;
					bOutOfData = false;
				}
			}
		}
	}
	else if (!bOutOfData) // reversing time
	{
		auto Tail = StoredFrames.GetTail(); // Get the last frame package
		if (Tail)
		{
			AActor* Owner = GetOwner();
			Owner->SetActorLocation( Tail->GetValue().Location);
			Owner->SetActorRotation( Tail->GetValue().Rotation);

			TArray<UActorComponent*> Components = Owner->GetComponentsByClass(UStaticMeshComponent::StaticClass());

			if (Components.Num() > 0) {

				UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Components[0]);
				if (SMC) {
					SMC -> SetPhysicsLinearVelocity(Tail->GetValue().LinearVelocity);
					SMC -> SetPhysicsAngularVelocity(Tail->GetValue().AngularVelocity);
				}
			}

			auto Head = StoredFrames.GetHead();
			if (Head == Tail)
			{
				RecordedTime  = 0.0f;
				bOutOfData = true;
			}
				
			else { RecordedTime -= Tail->GetValue().DeltaTime; }
			StoredFrames.RemoveNode(Tail);
			
		}

	}
		


}

void UReverseTimeComponent::SetReversingTime(bool InReversingTime) 
{
	bReversingTime = InReversingTime;

	if (InReversingTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reversing Time"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Reversing Time"));
	}

}

