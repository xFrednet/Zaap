#include "Model.h"

#include "maths/MathHelper.h"

namespace zaap { namespace graphics {
	
	Model::Model(TexturedMesh& tMesh, math::Vec3& position, math::Vec3& rotation, float scale)
		: m_TMesh(tMesh),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{}
	Model::Model()
		: m_Scale(1.0f)
	{
	}

	//
	// Position
	//
	void Model::setPosition(math::Vec3& position)
	{
		m_Position = position;
	}
	void Model::addToPosition(math::Vec3& position)
	{
		m_Position += position;
	}
	math::Vec3 Model::getPosition() const
	{
		return m_Position;
	}
	
	//
	// Rotation
	//
	void Model::setRotation(math::Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void Model::addToRotation(math::Vec3& rotation)
	{
		m_Rotation += rotation;
	}
	math::Vec3 Model::getRotation() const
	{
		return m_Rotation;
	}

	//
	// Scale
	//
	void Model::setScale(float scale)
	{
		m_Scale = scale;
	}
	void Model::addToScale(float scale)
	{
		m_Scale += scale;
	}
	float Model::getScale() const
	{
		return m_Scale;
	}
	
	//
	// Getters
	//
	TexturedMesh* Model::getTexturedMesh()
	{
		return &m_TMesh;
	}
	void Model::getTransformationMatrix(math::Mat4 &result) const
	{
		result = math::CreateTransformationMatrix(m_Position, m_Rotation, m_Scale);
	}

}}