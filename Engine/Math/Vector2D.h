#ifndef POINT2D_H
#define POINT2D_H
namespace Engine {
	class Vector2D
	{
	public:
		Vector2D(const float iX, const float iY);
		float getX() const;
		void setX(const float iX);
		float getY() const;
		void setY(const float iY);
		Vector2D& operator+=(const Vector2D&);
		Vector2D& operator-=(const Vector2D&);
	private:
		float x, y;
	};
	Vector2D operator+(const Vector2D&, const Vector2D&);
	Vector2D operator-(const Vector2D&, const Vector2D&);
	bool operator==(const Vector2D&, const Vector2D&);
}
#endif // !VECTOR2D_H
