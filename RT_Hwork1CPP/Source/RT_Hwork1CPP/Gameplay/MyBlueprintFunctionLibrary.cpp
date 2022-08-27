// Fill out your copyright notice in the Description page of Project Settings.


#include "../Gameplay/MyBlueprintFunctionLibrary.h"

static UMaterial* GetMatByMat(int Mat) {
		//实际上没有用上
		//原计划做一个C++的库让大家调用的
		class UMaterial* ColorMaterial;
		switch (Mat) {
		case 0:
			ColorMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/M_Metal_Gold.M_Metal_Gold'")).Get();
			break;
		case 1:
			ColorMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/M_Metal_Chrome.M_Metal_Chrome'")).Get();
			break;
		case 3:
			ColorMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/M_Glass.M_Glass'")).Get();
			break;
		default:
			ColorMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/BasicShapeMaterial.BasicShapeMaterial'")).Get();
			break;
		}

		return ColorMaterial;
		/*if (ColorMaterial) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ColorMaterial->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, MeshCom->GetName());
			}

			MeshCom->SetMaterial(0, ColorMaterial);
		}*/

	
	
}
