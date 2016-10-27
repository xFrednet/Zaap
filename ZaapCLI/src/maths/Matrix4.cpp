#include "Matrix4.h"

namespace ZaapCLI {

	//constructors
	Matrix4::Matrix4()
		: ManagedClass(new zaap::Mat4())
	{
	}
	Matrix4::Matrix4(float diagonal)
		: ManagedClass(new zaap::Mat4(diagonal))
	{
	}
	Matrix4::Matrix4(zaap::Mat4 *mat)
		: ManagedClass(mat)
	{
	}
	Matrix4::Matrix4(float mat[16])
		: ManagedClass(new zaap::Mat4(mat))
	{
	}
	Matrix4::Matrix4(Vector4^ row1, Vector4^ row2, Vector4^ row3, Vector4^ row4)
		: ManagedClass(new zaap::Mat4(*row1->getHandle(), 
			*row2->getHandle(), 
			*row3->getHandle(), 
			*row4->getHandle()))
	{
	}

	//operations
	void Matrix4::identify()
	{
		m_Instance->identify();
	}
	void Matrix4::identify(float value)
	{
		m_Instance->identify(value);
	}

	void Matrix4::translate(Vector3^ vec)
	{
		m_Instance->translate(*vec->getHandle());
	}
	void Matrix4::translate(float x, float y, float z)
	{
		m_Instance->translate(x, y, z);
	}

	void Matrix4::rotate(float angle, Vector3^ axis)
	{
		m_Instance->rotate(angle, *axis->getHandle());
	}
	void Matrix4::rotate(float angle, float x, float y, float z)
	{
		m_Instance->rotate(angle, x, y, z);
	}

	void Matrix4::scale(Vector3^ scale)
	{
		m_Instance->scale(*scale->getHandle());
	}
	void Matrix4::scale(float x, float y, float z)
	{
		m_Instance->scale(x, y, z);
	}

	// operators
	bool Matrix4::operator==(Matrix4^ other)
	{
		return Equal(*m_Instance, *other->getHandle());
	}
	bool Matrix4::operator!=(Matrix4^ other)
	{
		return !Equal(*m_Instance, *other->getHandle());
	}

	Matrix4^ Matrix4::operator+=(Matrix4^ other)
	{
		*m_Instance = Add(*m_Instance, *other->getHandle());
		return this;
	}
	Matrix4^ Matrix4::operator-=(Matrix4^ other)
	{
		*m_Instance = Subtract(*m_Instance, *other->getHandle());
		return this;
	}
	Matrix4^ Matrix4::operator*=(Matrix4^ other)
	{
		*m_Instance = Multiply(*m_Instance, *other->getHandle());
		return this;
	}

	Matrix4^ Matrix4::operator*=(float value)
	{
		*m_Instance = Multiply(*m_Instance, value);
		return this;
	}
	Matrix4^ Matrix4::operator/=(float value)
	{
		*m_Instance = Divide(*m_Instance, value);
		return this;
	}

	Matrix4^ Matrix4::operator+(Matrix4^ left, Matrix4^ right) 
	{
		return gcnew Matrix4(&Add(*left->getHandle(), *right->getHandle()));
	}
	Matrix4^ Matrix4::operator-(Matrix4^ left, Matrix4^ right)
	{
		return gcnew Matrix4(&Subtract(*left->getHandle(), *right->getHandle()));
	}
	Matrix4^ Matrix4::operator*(Matrix4^ left, Matrix4^ right)
	{
		return gcnew Matrix4(&Multiply(*left->getHandle(), *right->getHandle()));
	}

	Vector4^ Matrix4::operator*(Matrix4^ left, Vector4^ right)
	{
		return gcnew Vector4(&Multiply(*left->getHandle(), *right->getHandle()));
	}
	Matrix4^ Matrix4::operator*(Matrix4^ left, float value)
	{
		return gcnew Matrix4(&Multiply(*left->getHandle(), value));
	}
	Matrix4^ Matrix4::operator/(Matrix4^ left, float value)
	{
		return gcnew Matrix4(&Divide(*left->getHandle(), value));
	}

}
