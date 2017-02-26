#pragma once

#pragma warning( disable : 4114)

#include <Common.h>

//forward declarations
namespace zaap
{
	struct Vec2;
	struct Vec3;
	struct Vec4;
	struct Mat4;
	struct Plane3D;

	namespace graphics
	{
		struct Color;
		struct Material;
	}

	namespace gui
	{
		struct Point;
		struct Rectangle;
	}

	struct UUID;
}

namespace zaap {
	

	class ZAAP_API StringUtil
	{
	public:
		static String getDateString(const time_t& time = time(0));

		// <Function>
		//      Split
		//
		// <Description>
		//      This splits the string at the delimiters.
		//
		// <Note>
		//      The vector has a minimal length of 1 because the baseString
		//      is added if the string wasn't split.
		//
		// <Input>
		//      baseString:
		//          The String that is split at the specified delimiters.
		//      delimiters:
		//          The char sequence where the baseString is split.
		//
		// <Return>
		//      A vector that stores the split strings.
		//
		static std::vector<String> Split(String baseString, const String& delimiters);

		// <Function>
		//      StartsWith
		//
		// <Description>
		//      This Method tests if the baseString starts with the same
		//      like str2.
		//
		// <Note>
		//      This also returns false if str2 is longer than the baseString.
		//
		// <Input>
		//      baseString:
		//          The string where the start is test.
		//      str2:
		//          The sting that is compared to the start of the baseString.
		//
		// <Return>
		//      The test result.
		//
		static bool StartsWith(const String& baseString, const String& str2);

		// <Function>
		//		Replace
		//
		// <Description>
		//		This replaces the first-String in the base-String with the
		//		second-String. The new String is returned as a result.
		//
		// <Input>
		//		baseString::
		//			The base String where the oldString should be replaced
		//			with the newString.;;
		//		oldString::
		//			The String that should be replaced in the baseString.;;
		//		newString::
		//			The String that replaced the oldString in the baseString;;
		//
		static String Replace(String baseString, const String& oldString, const String& newString);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // ToString //
		/* //////////////////////////////////////////////////////////////////////////////// */

		template<typename T>
		static String ToString(const T& t);
		
		/* ********************************************************* */
		// * ZA_RESULT *
		/* ********************************************************* */
		template<>
		static String ToString<ZA_MULTI_RESULT>(const ZA_MULTI_RESULT& multiResult);

		/* ********************************************************* */
		// * Maths *
		/* ********************************************************* */
		template<>
		static String ToString<Vec2>(const Vec2& vec);
		template<>
		static String ToString<Vec3>(const Vec3& vec);
		template<>
		static String ToString<Vec4>(const Vec4& vec);
		template<>
		static String ToString<Mat4>(const Mat4& mat4);
		template<>
		static String ToString<Plane3D>(const Plane3D& plane);

		/* ********************************************************* */
		// * graphics *
		/* ********************************************************* */
		template<>
		static String ToString<graphics::Color>(const graphics::Color& color);
		template<>
		static String ToString<graphics::Material>(const graphics::Material& material);

		/* ********************************************************* */
		// * GUI *
		/* ********************************************************* */
		template<>
		static String ToString<gui::Point>(const gui::Point& point);
		template<>
		static String ToString<gui::Rectangle>(const gui::Rectangle& rectangle);

		/* ********************************************************* */
		// * other *
		/* ********************************************************* */
		template<>
		static String ToString<UUID>(const UUID& uuid);
	};

	template <typename T>
	String StringUtil::ToString(const T& t)
	{
		return std::to_string(t);
	}
}
