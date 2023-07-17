#include <MathUtil.hpp>

//
template<typename T>
inline T MathUtil::lerp(T x, T y, double t) {
	return x + (y - x) * t;
}
