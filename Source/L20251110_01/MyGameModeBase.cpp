// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "P38.h"
#include "MyPC.h"

AMyGameModeBase::AMyGameModeBase()
{
	//UE_LOG(LogTemp, Warning, TEXT("안녕하세요. %d %f %s"), 1, 2.f, TEXT("로그에요."));
	DefaultPawnClass = AP38::StaticClass();			//CDO 포인터, 기본 객체, 클래스 이름
	PlayerControllerClass = AMyPC::StaticClass();
}
