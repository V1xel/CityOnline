#pragma once

class COAssertionChecker
{
public:
	template <typename T>
	static T* CheckReferenceNotNull(T* Object, FString message)
	{
		if(Object)
		{
			return Object;
		}

		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, *message);
		return {};
	}
};
