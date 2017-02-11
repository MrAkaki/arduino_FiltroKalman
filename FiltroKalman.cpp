
#include "FiltroKalman.h"

using namespace math;

template <class T, int D>
void FiltroKalman<T, D>::init(T smoothness, T rapidness) {
	UKF<T>::n = D * 2;
	UKF<T>::m = D;

	math::matrix<T> In(UKF<T>::n, UKF<T>::n); // nxn Identity Matrix
	for( int i = 0; i < UKF<T>::n; i++ ) {
		In(i, i) = 1;
	}
	math::matrix<T> Im(UKF<T>::m, UKF<T>::m); // mxm Identity Matrix
	for( int i = 0; i < UKF<T>::m; i++ ) {
		Im(i, i) = 1;
	}

	const T q = smoothness; //std of process. "smoothness". lower the value, smoother the curve
	const T r = rapidness; //std of measurement. "tracking". lower the value, faster the track
	UKF<T>::P = In; // state covariance
	UKF<T>::Q = (q * q) * In; // covariance of process	(size must be nxn)
	UKF<T>::R = (r * r) * Im; // covariance of measurement (size must be mxm)

	x = math::matrix<T>(UKF<T>::n, 1);
}

template <class T, int D>
void FiltroKalman<T, D>::update(const Vec4f& p) {
	math::matrix<T> z(D, 1);
	// copy p to z
	for( int i = 0; i < D; i++ ) {
		z(i, 0) = p[i];
	}
	UKF<T>::ukf(x, z);
}

template <class T, int D>
Vec4f FiltroKalman<T, D>::getEstimation()
{
	math::matrix<T> w = measurement_function(x);
	Vec4f p(0, 0, 0, 0);
	// copy w to p
	for( int i = 0; i < D; i++ ) {
		p[i] = w(i, 0);
	}
	return p;
}

template <class T, int D>
Vec4f FiltroKalman<T, D>::getVelocity()
{
	math::matrix<T> w = measurement_function(x);
	Vec4f v(0, 0, 0, 0);
	// copy w to v
	for( int i = 0; i < D; i++ ) {
		v[i] = w(i + D, 0);
	}
	return v;
}

template <class T, int D>
matrix<T> FiltroKalman<T, D>::state_function(matrix<T>& s)
{
	matrix<T> state(UKF<T>::n, 1);
	// position
	for( int i = 0; i < D; i++ ) {
		state(i, 0) = s(i, 0) + s(i + D, 0);
	}
	// velocity
	for( int i = 0; i < D; i++ ) {
		state(i + D, 0) = s(i + D, 0);
	}
	return state;
}

template <class T, int D>
matrix<T> FiltroKalman<T, D>::measurement_function(matrix<T>& m)
{
	matrix<T> measurement(D, 1);
	measurement = m;
	return measurement;
}


template class FiltroKalman<double, 1>;
template class FiltroKalman<double, 2>;
template class FiltroKalman<double, 3>;
