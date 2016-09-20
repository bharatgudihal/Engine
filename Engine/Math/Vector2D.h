#ifndef POINT2D_H
#define POINT2D_H
namespace Engine {
	class Vector2D
	{
	public:
		Vector2D(float iX, float iY) :x(iX), y(iY) {};
		float getX() const { return x; }
		void setX(float iX) { x = iX; }
		float getY() const { return y; }
		void setY(float iY) { y = iY; }
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
