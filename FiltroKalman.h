/*
 https://github.com/micuat/ofxUkf

 Naoto Hieda <micuat@gmail.com> 2014
 */

#include "UKF.h"
#include "Vec4.h"

typedef Vec4<double> Vec4f;

typedef Vec4f Vec4f;
typedef Vec4f Vec3f;
typedef Vec4f Vec2f;
typedef Vec4f Vec1f;

template <class T, int D>
class FiltroKalman : public UKF<T> {
	math::matrix<T> x;
public:
	void init(T smoothness = 0.1, T rapidness = 0.1); // smaller is more smooth/rapid
	void update(const Vec4f&);
	Vec4f getEstimation();
	Vec4f getVelocity();

	math::matrix<T> state_function(math::matrix<T>& s);
	math::matrix<T> measurement_function(math::matrix<T>& m);

};

typedef FiltroKalman<double,1> FiltroKalman1D;
typedef FiltroKalman<double,2> FiltroKalman2D;
typedef FiltroKalman<double,3> FiltroKalman3D;
