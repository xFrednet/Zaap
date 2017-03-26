#include "Rectangle.h"

namespace zaap { namespace gui {
	Rectangle::Rectangle(int x, int y, uint width, uint height)
		: X(x), Y(y),
		Width(width), Height(height)
	{
	}
	Rectangle::Rectangle(Point position, uint width, uint height)
		: Rectangle(position.X, position.Y, width, height)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	int Rectangle::getSize() const
	{
		return Width * Height;
	}

	bool Rectangle::intersects(const Rectangle& other) const
	{
		return ((X + (int)Width) > other.X) && (X < (other.X + (int)other.Width)) &&
			((Y + (int)Height) > other.Y) && (Y < (other.Y + (int)other.Height));
	}
	bool Rectangle::contains(const Point& point) const
	{
		return contains(point.X, point.Y);
	}
	bool Rectangle::contains(const int& x, const int& y) const
	{
		return (x > X && x < (X + (int)Width)) && 
			(y > Y && y < (Y + (int)Height));
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Setters and Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * size *
	/* ********************************************************* */
	void Rectangle::setWidth(const float& width)
	{
		if (width < 0)
			Width = 0;
		else
			Width = (uint)floor(width + 0.5f);
	}
	void Rectangle::setHeight(const float& height)
	{
		if (height < 0)
			Height = 0;
		else
			Height = (uint)floor(height + 0.5f);
	}
	void Rectangle::setDimension(const float& width, const float& height)
	{
		setWidth(width);
		setHeight(height);
	}

	/* ********************************************************* */
	// * calculated values *
	/* ********************************************************* */
	int Rectangle::getMinX() const
	{
		return X;
	}
	int Rectangle::getMinY() const
	{
		return Y;
	}

	int Rectangle::getMaxX() const
	{
		return X + Width;
	}
	int Rectangle::getMaxY() const
	{
		return Y + Height;
	}

	int Rectangle::getCenterX() const
	{
		return X + Width / 2;
	}
	int Rectangle::getCenterY() const
	{
		return Y + Height / 2;
	}
	Point Rectangle::getCenter() const
	{
		return Point(getCenterX(), getCenterY());
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool Rectangle::operator==(const Rectangle& other) const
	{
		return Equal(*this, other);
	}

	bool Rectangle::operator!=(const Rectangle& other) const
	{
		return !Equal(*this, other);
	}

	bool Equal(const Rectangle& a, const Rectangle& b)
	{
		return memcmp(&a, &b, sizeof(Rectangle)) ==  0;
	}
}}
