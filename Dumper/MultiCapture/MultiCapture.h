#pragma once
#include <unordered_set>
#include "Unreal/Enums.h"

namespace MultiCapture
{
	/* Set to store indexes of rooted classes */
	static inline std::unordered_set<int32> RootedClasses;

	/* 
	Iterates the current GObjects array, saves all UClass slots
	via FUObjectItem::RootSet and accumulates them in an internal set keyed by
	object-array index
	*/
	void Capture();

	/* Generates the SDK by calling calls Generator::InitInternal() */
	void Generate();
}