#ifndef __INSTANCE__
#define __INSTANCE__

#include "GeometricObject.h"
#include "Matrix.h"

class Instance:public GeometricObject {
	public:

		Instance(void);

		Instance(GeometricObject* obj_ptr);

		Instance(const Instance& instance);

		virtual Instance* clone(void) const;

		virtual ~Instance(void);

		Instance& operator= (const Instance& rhs);

		void set_object(GeometricObject* obj_ptr);

		virtual Material* get_material(void) const;

		virtual void set_material(Material* materialPtr);

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool shadow_hit(const Ray& ray, float& tmin) const;

		void translate(const Vector3D& trans);

		void translate(const double dx, const double dy, const double dz);

		void scale(const Vector3D& s);

		void scale(const double a, const double b, const double c);

		virtual void rotate_x(const double r);

		virtual void rotate_y(const double r);

		virtual void rotate_z(const double r);

		virtual void rotate(const double axis0, const double axis1, const float axis2, double theta);

		void shear(const Matrix& m);

		Matrix inv_matrix;


	private:

		GeometricObject* object_ptr;
		
		static Matrix forward_matrix;

};

#endif