#ifndef __TRACER__
#define __TRACER__

#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer {

	public:

		Tracer(void);

		Tracer(World* _world_ptr);

		virtual ~Tracer(void);

		virtual RGBColor trace_ray(const Ray& ray) const;

		virtual RGBColor trace_ray(const Ray ray, const int depth) const;

		//virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;

	protected:

		World* world_ptr;

};

#endif