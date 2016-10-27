#include "Vector2.h"

namespace ZaapCLI {

	Vector2::Vector2(zaap::Vec2* instance)
		: ManagedClass(instance)
	{
		
	}

	Vector2::Vector2()
		: ManagedClass(new zaap::Vec2())
	{
	}
	Vector2::Vector2(float x, float y)
		: ManagedClass(new zaap::Vec2(x, y))
	{
	}

	//operations
	void  Vector2::normalize()
	{
		m_Instance->normalize();
	}
	void  Vector2::scale(float scale)
	{
		m_Instance->scale(scale);
	}
	void  Vector2::clamp(float min, float max)
	{
		m_Instance->clamp(min, max);
	}
	float Vector2::dot(Vector2^ v)
	{
		return m_Instance->dot(*v->getHandle());
	}
	float Vector2::getLength()
	{
		return m_Instance->getLength();
	}

	//operators 
	bool Vector2::operator==(Vector2^ other) 
	{
		return zaap::Equal(*m_Instance, *other->getHandle());
	}
	bool Vector2::operator!=(Vector2^ other)
	{
		return !zaap::Equal(*m_Instance, *other->getHandle());
	}

	Vector2^ Vector2::operator+=(Vector2^ other) 
	{
		*m_Instance = zaap::Add(*m_Instance, *other->getHandle());
		return this;
	}
	Vector2^ Vector2::operator-=(Vector2^ other) 
	{
		*m_Instance = zaap::Subtract(*m_Instance, *other->getHandle());
		return this;
	}
	Vector2^ Vector2::operator*=(Vector2^ other) 
	{
		*m_Instance = zaap::Multiply(*m_Instance, *other->getHandle());
		return this;
	}
	Vector2^ Vector2::operator/=(Vector2^ other)
	{
		*m_Instance = zaap::Divide(*m_Instance, *other->getHandle());
		return this;
	}

	Vector2^ Vector2::operator*=(float value)
	{
		*m_Instance = Multiply(*m_Instance, value);
		return this;
	}
	Vector2^ Vector2::operator/=(float value)
	{
		*m_Instance = Divide(*m_Instance, value);
		return this;
	}

	Vector2^ Vector2::operator+(Vector2^ left, Vector2^ right)
	{
		return gcnew Vector2(&zaap::Add(*left->getHandle(), *right->getHandle()));
	}
	Vector2^ Vector2::operator-(Vector2^ left, Vector2^ right)
	{
		return gcnew Vector2(&zaap::Subtract(*left->getHandle(), *right->getHandle()));
	}
	Vector2^ Vector2::operator*(Vector2^ left, Vector2^ right) 
	{
		return gcnew Vector2(&zaap::Multiply(*left->getHandle(), *right->getHandle()));
	}
	Vector2^ Vector2::operator/(Vector2^ left, Vector2^ right) 
	{
		return gcnew Vector2(&zaap::Divide(*left->getHandle(), *right->getHandle()));
	}

	Vector2^ Vector2::operator*(Vector2^ left, float right)
	{
		return gcnew Vector2(&Multiply(*left->getHandle(), right));
	}
	Vector2^ Vector2::operator/(Vector2^ left, float right)
	{
		return gcnew Vector2(&Divide(*left->getHandle(), right));
	}
}