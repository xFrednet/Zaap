#pragma once
#include <msclr\marshal_cppstd.h>

#define ZA_CLI_VALUE(type, name, setName) \
property type name {				\
	type get()						\
	{								\
		return m_Instance->name;	\
	}								\
	void set(type setName)			\
	{								\
		m_Instance->name = setName;	\
	}								\
}

#define ZA_CLI_VECTOR4(name, setName, original)		\
property Vector4^ name {							\
	Vector4^ get()									\
	{												\
		return gcnew Vector4(&m_Instance->original);\
	}												\
	void set(Vector4^ setName)						\
	{												\
		m_Instance->original = *setName->getHandle();\
	}												\
}

namespace ZaapCLI
{
	static System::String^ to_CLI_String(std::string stdString)
	{
		return msclr::interop::marshal_as<System::String^>(stdString);
	}

	static std::string to_CPP_String(System::String^ cliString)
	{
		return msclr::interop::marshal_as<std::string>(cliString);
	}

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