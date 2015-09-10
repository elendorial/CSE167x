#include "ThinLens.h"
#include "World.h"
#include "Sampler.h"
#include <iostream>

ThinLens::ThinLens(void)
:	Camera(),
	lens_radius(1.0),
	d(40.0),
	f(74.0),
	zoom(1.0),
	sampler_ptr(NULL)
{}

ThinLens::ThinLens(const ThinLens& c)
:	Camera(c),
	lens_radius(c.lens_radius),
	d(c.d),
	f(c.f),
	zoom(c.zoom),
	sampler_ptr(c.sampler_ptr)
{}

Camera* ThinLens::clone(void) const {
	return (new ThinLens(*this));
}

ThinLens& ThinLens::operator= (const ThinLens& rhs) {
	if( this == &rhs)
		return(*this);

	Camera::operator=(rhs);

	lens_radius = rhs.lens_radius;
	d = rhs.d;
	f = rhs.f;
	zoom = rhs.zoom;
	sampler_ptr = rhs.sampler_ptr;

	return(*this);
}

ThinLens::~ThinLens(void) {}

Vector3D ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {
	Point2D p;
	p.x = pixel_point.x * (f / d);
	p.y = pixel_point.y * (f / d);

	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();

	return(dir);

}

void ThinLens::set_sampler(Sampler* sp) {
	if(sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	sampler_ptr = sp;
	sampler_ptr -> map_samples_to_unit_disk();

}

void ThinLens::render_scene(World& w) {
	RGBColor L;
	Ray ray;
	ViewPlane vp(w.vp);
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(vp.hres, vp.vres, 24);
	RGBQUAD color;
	int depth = 0;

	Point2D sp;
	Point2D pp;
	Point2D dp;
	Point2D lp;

	vp.s /= zoom;

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0 ; c < vp.hres; c++) {
			L = black;

			for(int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr -> sample_unit_square();
				pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
				pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);

				dp = sampler_ptr -> sample_unit_disk();
				lp = dp * lens_radius;

				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);
				L += w.tracer_ptr -> trace_ray(ray);
			}

			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
			color.rgbRed = (int)(L.r*255);
			color.rgbGreen = (int)(L.g*255);
			color.rgbBlue = (int)(L.b*255);
			FreeImage_SetPixelColor(bitmap, c, r, &color);
		}
	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		std::cout << "Image Successfully Saved!" << std::endl;

	FreeImage_DeInitialise();

}