#include "Fisheye.h"
#include "Constants.h"
#include "World.h"
#include <math.h>
#include <iostream>

Fisheye::Fisheye()
:	Camera(),
	psi_max(180.0)
{}

Fisheye::Fisheye(const Fisheye& fs)
:	Camera(fs),
	psi_max(fs.psi_max)
{}

Fisheye& Fisheye::operator= (const Fisheye& fs) {
	if(this == &fs)
		return(*this);

	Camera::operator= (fs);

	psi_max = fs.psi_max;

	return(*this);
}

Fisheye::~Fisheye() {}

Vector3D Fisheye::ray_direction(const Point2D& p, const int hres, const int vres, const float s, float& r) const {

	Point2D pn(2.0 / (s * hres) * p.x, 2.0 / (s * vres) * p.y);
	r = pn.x * pn.x + pn.y * pn.y;

	if(r <= 1.0) {
		r = sqrt(r);
		float psi = r * psi_max * PI_ON_180;
		float sin_psi = sin(psi);
		float cos_psi = cos(psi);
		float sin_alpha = pn.y / r;
		float cos_alpha = pn.x / r;
		Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;
		return(dir);
	}
	else
		return Vector3D(0.0);
}

Fisheye* Fisheye::clone(void) const {
	return (new Fisheye(*this));
}

void Fisheye::render_scene(World& w) {
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
	float r_squared;

	ray.o  = eye;

	for(int r = 0; r < vres; r++)
		for(int c = 0; c < hres; c++) {
			L = black;

			for(int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr -> sample_unit_square();
				pp.x = s * (c - hres / 2.0 + sp.x);
				pp.y = s * (r - vres / 2.0 + sp.y);
				ray.d = ray_direction(pp, hres, vres, s, r_squared);

				if(r_squared <= 1.0)
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