#include "pch.h"
#include "MyComponent.h"

#include "MyObject.h"

MyComponent::MyComponent(MyObject* _Owner)
	: m_pOwner(_Owner)
{
}

MyComponent::~MyComponent()
{
}
