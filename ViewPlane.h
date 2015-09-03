#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane {

	public:

		int hres;
		int vres;
		float s;
		int num_samples;

		float gamma;
		float inv_gamma;
		bool show_out_of_gamut;


	public:

		ViewPlane();

		ViewPlane(const ViewPlane& vp);

		ViewPlane& operator= (const ViewPlane& rhs);

		~ViewPlane();

		void set_hres(const int h_res);

		void set_vres(const int v_res);

		void set_pixel_size(const float size);

		void set_gamma(const float g);

		void set_gamut_display(const bool show);

		void set_samples(const int n);

};

inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

inline void ViewPlane::set_pixel_size(const float size) {
	s = size;
}

inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}

inline void ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}

inline void ViewPlane::set_samples(const int n) {
	num_samples = n;
}

#endif