#include "Spherical.h"
#include "World.h"
#include "Constants.h"
#include <math.h>
#include <iostream>

Spherical::Spherical()
:	Camera(),
	l_max(180),
	psi_max(90)
{}

Spherical::Spherical(const Spherical& sph)
:	Camera(sph),
	l_max(sph.l_max),
	psi_max(sph.psi_max)
{}

Spherical& Spherical::operator= (const Spherical& sph) {
	if(this == &sph)
		return(*this);

	Camera::operator=(sph);

	l_max = sph.l_max;
	psi_max = sph.psi_max;

	return(*this);
}

Spherical::~Spherical() {}

Spherical* Spherical::clone(void) const {
	return (new Spherical(*this));
}

Vector3D Spherical::ray_direction(const Point2D& pp, const int hres, const int vres, const float s) const{

	Point2D pn( 2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);

	float lambda = pn.x * l_max * PI_ON_180;
	float psi = pn.y * psi_max * PI_ON_180;

	float phi = PI - lambda;
	float theta = 0.5 * PI - psi;

	float sin_phi = sin(phi);
	float cos_psi = cos(phi);
	float sin_theta = sin(theta);
	float cos_theta = cos(theta);

	Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_psi * w;

	return(dir);

}

void Spherical::render_scene(World& w) {

	RGBColor L;
	ViewPlane vp(w.vp);
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(vp.hres, vp.vres, 24);
	RGBQUAD color;
	int hres = vp.hres;
	int vres = vp.vres;
	float s = vp.s;
	Ray ray;
	int depth = 0;
	Point2D sp;
	Point2D pp;

	ray.o  = eye;

	for(int r = 0; r < vres; r++)
		for(int c = 0; c < hres; c++) {
			L = black;

			for(int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr -> sample_unit_square();
				pp.x = s * (c - hres / 2.0 + sp.x);
				pp.y = s * (r - vres / 2.0 + sp.y);
				ray.d = ray_direction(pp, hres, vres, s);
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