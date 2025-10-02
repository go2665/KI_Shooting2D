#pragma once
#include "Singleton.h"

class Factory : public Singleton<Factory>
{
	friend class Singleton<Factory>;

public:
private:
	Factory() = default;
	virtual ~Factory() = default;
};