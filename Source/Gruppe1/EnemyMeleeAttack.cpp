// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyMeleeAttack.h"


// Sets default values for this component's properties
UEnemyMeleeAttack::UEnemyMeleeAttack()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEnemyMeleeAttack::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UEnemyMeleeAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

