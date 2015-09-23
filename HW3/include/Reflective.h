#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"

class Reflective:public Phong {
	public:

		Reflective(void);

		Reflective(const Reflective& rm);

		Reflective& operator= (const Reflective& rhs);

		virtual Reflective* clone(void) const;

		virtual ~Reflective();

		virtual RGBColor shade(ShadeRec& sr);
};

#endif



