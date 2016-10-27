﻿#include "Vector3.h"

namespace ZaapCLI {

	//Constructors
	Vector3::Vector3()
		: ManagedClass(new zaap::Vec3())
	{
	}
	Vector3::Vector3(zaap::Vec3 *instance)
		: ManagedClass(instance)
	{
	}
	Vector3::Vector3(float x, float y, float z)
		: ManagedClass(new zaap::Vec3(x, y, z))
	{
	}
	Vector3::Vector3(Vector2^ vec2, float z)
		: ManagedClass(new zaap::Vec3(*vec2->getHandle(), z))
	{
	}

	//operations
	void  Vector3::normalize()
	{
		m_Instance->normalize();
	}
	void  Vector3::scale(float scale)
	{
		m_Instance->scale(scale);
	}
	void  Vector3::clamp(float min, float max)
	{
		m_Instance->clamp(min, max);
	}
	Vector3^ Vector3::cross(Vector3^ other)
	{
		return gcnew Vector3(&Cross(*m_Instance, *other->getHandle()));
	}
	float Vector3::dot(Vector3^ other)
	{
		return m_Instance->dot(*other->getHandle());
	}
	float Vector3::getLength()
	{
		return m_Instance->getLength();
	}

	//operators
	bool Vector3::operator==(Vector3^ other) 
	{
		return Equal(*m_Instance, *other->getHandle());
	}
	bool Vector3::operator!=(Vector3^ other)
	{
		return !Equal(*m_Instance, *other->getHandle());
	}

	Vector3^ Vector3::operator+=(Vector3^ other)
	{
		*m_Instance = Add(*m_Instance, *other->getHandle());
		return this;
	}
	Vector3^ Vector3::operator-=(Vector3^ other)
	{
		*m_Instance = Subtract(*m_Instance, *other->getHandle());
		return this;
	}
	Vector3^ Vector3::operator*=(Vector3^ other)
	{
		*m_Instance = Multiply(*m_Instance, *other->getHandle());
		return this;
	}
	Vector3^ Vector3::operator/=(Vector3^ other)
	{
		*m_Instance = Divide(*m_Instance, *other->getHandle());
		return this;
	}

	Vector3^ Vector3::operator*=(float value)
	{
		*m_Instance = Multiply(*m_Instance, value);
		return this;
	}
	Vector3^ Vector3::operator/=(float value)
	{
		*m_Instance = Divide(*m_Instance, value);
		return this;
	}

	Vector3^ Vector3::operator+(Vector3^ left, Vector3^ right) 
	{
		return gcnew Vector3(&Add(*left->getHandle(), *right->getHandle()));
	}
	Vector3^ Vector3::operator-(Vector3^ left, Vector3^ right)
	{
		return gcnew Vector3(&Subtract(*left->getHandle(), *right->getHandle()));
	}
	Vector3^ Vector3::operator*(Vector3^ left, Vector3^ right)
	{
		return gcnew Vector3(&Multiply(*left->getHandle(), *right->getHandle()));
	}
	Vector3^ Vector3::operator/(Vector3^ left, Vector3^ right)
	{
		return gcnew Vector3(&Divide(*left->getHandle(), *right->getHandle()));
	}

	Vector3^ Vector3::operator*(Vector3^ left, float right)
	{
		return gcnew Vector3(&Multiply(*left->getHandle(), right));
	}
	Vector3^ Vector3::operator/(Vector3^ left, float right)
	{
		return gcnew Vector3(&Divide(*left->getHandle(), right));
	}
}
