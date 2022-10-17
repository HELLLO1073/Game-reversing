#include "pch.h"
#include <math.h>
#include "Vec.h"

class TMath {
public:
	float PI = 3.14159265358979323846f;

	float magnitude(Vec3 vec) { 
		return (float)(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
	}

	float getDistance(Vec3 src, Vec3 dst) {
		return magnitude((Vec3)(src - dst));
	}

	Vec2 CalculateAngle(Vec3 src, Vec3 dst) {
		Vec2 ViewAngles{0,0};
		ViewAngles.x = (-(float)atan2(dst.x - src.x, dst.y - src.y)) / PI * 180.0f + 180.0f;
		ViewAngles.y = (atan2(dst.z - src.z, getDistance(src, dst))) * 180.0f / PI;
		return ViewAngles;
	}
};