#include "Vector4.h"

namespace ZaapCLI {

	//Constructors
	Vector4::Vector4()
		: ManagedClass(new zaap::Vec4())
	{
	}
	Vector4::Vector4(zaap::Vec4 *instance) 
		: ManagedClass(instance)
	{
	}
	Vector4::Vector4(float x, float y, float z, float w)
		: ManagedClass(new zaap::Vec4(x, y, z, w))
	{
	}
	Vector4::Vector4(Vector2^ vec2, float z, float w)
		: ManagedClass(new zaap::Vec4(*vec2->getHandle(), z, w))
	{
	}
	Vector4::Vector4(Vector3^ vec3, float w)
		: ManagedClass(new zaap::Vec4(*vec3->getHandle(), w))
	{
	}

	//operations
	void  Vector4::normalize()
	{
		m_Instance->normalize();
	}
	void  Vector4::scale(float scale)
	{
		m_Instance->scale(scale);
	}
	void  Vector4::clamp(float min, float max)
	{
		m_Instance->clamp(min, max);
	}
	float Vector4::dot(Vector4^ other)
	{
		return zaap::Dot(*m_Instance, *other->getHandle());
	}
	float Vector4::getLength()
	{
		return zaap::Length(*m_Instance);
	}

	//operators
	bool Vector4::operator==(Vector4^ other) 
	{
		return Equal(*m_Instance, *other->getHandle());
	}
	bool Vector4::operator!=(Vector4^ other)
	{
		return !Equal(*m_Instance, *other->getHandle());
	}

	Vector4^ Vector4::operator+=(Vector4^ other) 
	{
		*m_Instance = Add(*m_Instance, *other->getHandle());
		return this;
	}
	Vector4^ Vector4::operator-=(Vector4^ other) 
	{
		*m_Instance = Subtract(*m_Instance, *other->getHandle());
		return this;
	}
	Vector4^ Vector4::operator*=(Vector4^ other)
	{
		*m_Instance = Multiply(*m_Instance, *other->getHandle());
		return this;
	}
	Vector4^ Vector4::operator/=(Vector4^ other)
	{
		*m_Instance = Divide(*m_Instance, *other->getHandle());
		return this;
	}

	Vector4^ Vector4::operator*=(float value)
	{
		*m_Instance = Multiply(*m_Instance, value);
		return this;
	}
	Vector4^ Vector4::operator/=(float value)
	{
		*m_Instance = Divide(*m_Instance, value);
		return this;
	}

	Vector4^ Vector4::operator+(Vector4^ left, Vector4^ right) 
	{
		return gcnew Vector4(&Add(*left->getHandle(), *right->getHandle()));
	}
	Vector4^ Vector4::operator-(Vector4^ left, Vector4^ right) 
	{
		return gcnew Vector4(&Subtract(*left->getHandle(), *right->getHandle()));
	}
	Vector4^ Vector4::operator*(Vector4^ left, Vector4^ right)
	{
		return gcnew Vector4(&Multiply(*left->getHandle(), *right->getHandle()));
	}
	Vector4^ Vector4::operator/(Vector4^ left, Vector4^ right)
	{
		return gcnew Vector4(&Divide(*left->getHandle(), *right->getHandle()));
	}

	Vector4^ Vector4::operator*(Vector4^ left, float right)
	{
		return gcnew Vector4(&Multiply(*left->getHandle(), right));
	}
	Vector4^ Vector4::operator/(Vector4^ left, float right)
	{
		return gcnew Vector4(&Divide(*left->getHandle(), right));
	}

}
