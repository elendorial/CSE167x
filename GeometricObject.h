#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;

#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"


class GeometricObject 
{
	public:

		GeometricObject(void);

		GeometricObject(const GeometricObject& object);

		virtual GeometricObject* clone(void) const = 0;

		virtual ~GeometricObject(void);

		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

		Material* get_material(void) const;

		virtual void set_material(Material* mPtr);

	protected:

		mutable Material* material_ptr;

		GeometricObject& operator= (const GeometricObject& rhs);

};


inline Material* GeometricObject::get_material(void) const {
	return (material_ptr);
}

#endif