#pragma once

namespace ZaapCLI
{
	template<typename T>
	public ref class ManagedClass {
	protected:
		T* m_Instance;
	public:
		ManagedClass(T* instance)
			: m_Instance(instance)
		{
		}

		virtual ~ManagedClass()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}

		!ManagedClass()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}

		T* getHandle()
		{
			return m_Instance;
		}

	};
}