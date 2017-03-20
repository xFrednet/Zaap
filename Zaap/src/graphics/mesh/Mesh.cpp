#include "Mesh.h"

#include "MeshManager.h"
#include "util/Loader.h"

namespace zaap { namespace graphics {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_TERRAIN_VERTEX //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_TERRAIN_VERTEX::ZA_TERRAIN_VERTEX(Vec3 position, Vec3 normal, Vec3 texMapColor, Vec2 texCoord)
		: Position(position),
		Normal(normal),
		TexMapColor(texMapColor),
		TexCoord(texCoord)
	{
	}

	ZA_TERRAIN_VERTEX::ZA_TERRAIN_VERTEX()
		: Position(),
		Normal(),
		TexMapColor(),
		TexCoord()
	{
	}

	Mesh Mesh::GetOrLoad(const String& file)
	{
		if (MeshManager::Contains(file))
			return MeshManager::Get(file);

		return zaap::Loader::LoadOBJFile(file);;
	}


	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Mesh //
	/* //////////////////////////////////////////////////////////////////////////////// */
	Mesh::Mesh()
		: Mesh("NULL", nullptr)
	{
	}
	Mesh::Mesh(String name, API::VertexBuffer* vertexBuffer)
		: Mesh(name, vertexBuffer, nullptr, 0)
	{
	}
	Mesh::Mesh(String name, API::VertexBuffer* vertexBuffer, Material const* materials, uint materialCount)
		: m_Name(name),
		m_VertexBuffer(vertexBuffer),
		m_Materials(nullptr),
		m_MaterialCount(0)
	{
		setMaterials(materials, materialCount);

		if (m_Name != "NULL")
			MeshManager::Add(*this);
	}

	Mesh::~Mesh()
	{
		// TODO release the texture and the vertex buffer API::VertexBuffer::Delete();
		/*if (m_Materials)
			delete m_Materials;*/
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Vertex Buffer //
	/* //////////////////////////////////////////////////////////////////////////////// */
	API::VertexBuffer* Mesh::getVertexBuffer() const
	{
		return m_VertexBuffer;
	}
	uint Mesh::getVertexCount() const
	{
		//use getIndexCount because this is equal
		//to the entire vertex count that is drawn.
		return m_VertexBuffer->getIndexCount();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Texture //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void Mesh::setTexture(API::Texture2D* texture)
	{
		m_Texture = texture;
	}
	API::Texture2D* Mesh::getTexture() const
	{
		return m_Texture;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Material //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void Mesh::setMaterials(const Material* &materials, const uint& materialCount)
	{
		if (m_Materials)
			delete m_Materials;

		if (materials)
		{
			m_MaterialCount = materialCount;
			m_Materials = new Material[materialCount];
			memcpy(m_Materials, materials, sizeof(Material) * materialCount);
		} else
		{
			m_MaterialCount = 0;
			m_Materials = nullptr;
		}

	}
	Material* Mesh::getMaterials() const
	{
		return m_Materials;
	}
	uint Mesh::getMaterialCount() const
	{
		return m_MaterialCount;
	}

	String Mesh::getName() const
	{
		return m_Name;
	}

}}