#ifndef __SHADE_REC__
#define __SHADE_REC__

#include <vector>

class Material;
class World;


#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"


class ShadeRec 
{
	public:

		bool hit_an_object;
		Material* material_ptr;
		Point3D hit_point;
		Point3D local_hit_point;
		Normal normal;
		Ray ray;
		int depth;
		float t;
		Vector3D dir;
		World& w;
		RGBColor color;

		ShadeRec(World& wr);

		ShadeRec(const ShadeRec& sr);

};

#endif