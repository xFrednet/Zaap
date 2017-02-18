#include "StringUtil.h"

#include <maths/Vec2.h>
#include <maths/Vec3.h>
#include <maths/Vec4.h>
#include <maths/Mat4.h>
#include <maths/Plane3D.h>

#include <graphics/Color.h>
#include <graphics/Material.h>

namespace zaap {
	String StringUtil::getDateString(const time_t& time)
	{
		char buffer[22];
		strftime(buffer, 22, "[%d-%m-%Y %I:%M:%S]", localtime(&time));
		return String(buffer);
	}

	std::vector<String> StringUtil::Split(String baseString, const String& delimiters)
	{
		std::vector<std::string> splitString;

		size_t pos = 0;
		while ((pos = baseString.find(delimiters)) != std::string::npos)
		{
			splitString.push_back(baseString.substr(0, pos));
			baseString.erase(0, pos + delimiters.length());
		}
		splitString.push_back(baseString);
		return splitString;
	}

	bool StringUtil::StartsWith(const String& baseString, const String& str2)
	{
		if (str2.length() > baseString.length() ||
			str2.size() > baseString.size())
			return false;

		return memcmp(baseString.c_str(), str2.c_str(), str2.size()) == 0;
	}

	String StringUtil::Replace(String baseString, const String& oldString, const String& newString)
	{
		if (baseString.empty() || oldString.empty())
			return baseString;

		size_t offset = 0;
		size_t pos;

		//tests if the oldString can be replaced directly
		while ((pos = baseString.find(oldString, offset)) != baseString.npos)
		{
			baseString.replace(pos, oldString.size(), newString);

			offset = pos + newString.size(); // move one more maybe
		}

		return baseString;
	}

}
/* //////////////////////////////////////////////////////////////////////////////// */
// // ToString //
/* //////////////////////////////////////////////////////////////////////////////// */

namespace zaap {

	/* ********************************************************* */
	// * ZA_RESULT *
	/* ********************************************************* */
	template <>
	String ToString<short>(const ZA_RESULT& result)
	{
		return GetZAResultMessage(result);
	}
	template <>
	String ToString<ZA_MULTI_RESULT_>(const ZA_MULTI_RESULT& multiResult)
	{
		return GetZAResultMessages(multiResult);
	}
	/* ********************************************************* */
	// * Maths *
	/* ********************************************************* */
	template <>
	String ToString<Vec2>(const Vec2& vec)
	{
		return "Vec2(X:" + std::to_string(vec.X) + ", Y:" + std::to_string(vec.Y) + ")";
	}
	template <>
	String ToString<Vec3>(const Vec3& vec)
	{
		return "Vec3(X:" + std::to_string(vec.X) + 
			", Y:" + std::to_string(vec.Y) + 
			", Z:" + std::to_string(vec.Z) + ")";
	}

	template <>
	String ToString<Vec4>(const Vec4& vec)
	{
		return "Vec4(X:" + std::to_string(vec.X) +
			", Y:" + std::to_string(vec.Y) +
			", Z:" + std::to_string(vec.Z) +
			", W:" + std::to_string(vec.W) + ")";
	}

	template <>
	String ToString<Mat4>(const Mat4& mat)
	{
		using namespace std;
		return "Mat4(" +
			to_string(mat.m11) + ", " + to_string(mat.m12) + ", " + to_string(mat.m13) + ", " + to_string(mat.m14) + "|" +
			to_string(mat.m21) + ", " + to_string(mat.m22) + ", " + to_string(mat.m23) + ", " + to_string(mat.m24) + "|" +
			to_string(mat.m31) + ", " + to_string(mat.m32) + ", " + to_string(mat.m33) + ", " + to_string(mat.m34) + "|" +
			to_string(mat.m41) + ", " + to_string(mat.m42) + ", " + to_string(mat.m43) + ", " + to_string(mat.m44) + "|)";
	}

	template <>
	String ToString<Plane3D>(const Plane3D& plane)
	{
		return "Plane3D(N: " + plane.N.toString() + ", D: " + std::to_string(plane.D) + ")";
	}

	/* ********************************************************* */
	// * graphics *
	/* ********************************************************* */
	template <>
	String ToString<graphics::Color>(const graphics::Color& color)
	{
		return "Color(R " + std::to_string(color.getIntR()) +
			", G " + std::to_string(color.getIntG()) +
			", B " + std::to_string(color.getIntB()) +
			", A " + std::to_string(color.getIntA()) + ")";
	}

	template <>
	String ToString<graphics::Material>(const graphics::Material& material)
	{
		return "Material(DiffuseReflectivity: " + material.DiffuseReflectivity.toString() +
			", SpectralReflectivity: " + std::to_string(material.SpectralReflectivity) + ")";
	}
}
