#ifndef __WORLD__
#define __WORLD__

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "Tracer.h"

class World {

	public:

		ViewPlane vp;
		RGBColor background_color;
		Sphere shere;
		Tracer* tracer_ptr;

	public:

		World(void);

		~World();

		void build(void);

		void render_scene(void) const;

		void open_window(const int hres, const int vres) const;

		void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;


};

#endif