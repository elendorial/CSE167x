#ifndef __MATHS__
#define __MATHS__
#include <cstdlib>

inline double max(double x0, double x1);

inline double max(double x0, double x1)
{
	return ((x0 > x1) ? x0 : x1);
}

inline float rand_float(void);

inline float rand_float(void) {
	return ((float)rand() / (float)RAND_MAX);
}

inline int rand_int(void);

inline int rand_int(void) {
	return (rand());
}

inline float rand_float(int l, float h);

inline float rand_float(int l, float h) {
	return (rand_float() * (h - l) + l);
}	

inline int rand_int(int l, int h);   

inline int
rand_int(int l, int h) {
	return ((int) (rand_float(0, h - l + 1) + l));
}

#endif