#include "Jittered.h"

Jittered::Jittered(void)
:	Sampler()
{}

Jittered::Jittered(const int num_samples)
:	Sampler(num_samples) {
	generate_samples();
}

Jittered::Jittered(const int num_samples, const int m)
:	Sampler(num_samples, m) {
	generate_samples();
}

Jittered::Jittered(const Jittered& js)
:	Sampler(js) {
	generate_samples();
}

Jittered& Jittered::operator= (const Jittered& rhs) {
	if(this == &rhs)
		return(*this);

	Sampler::operator= (rhs);

	return(*this);
}

Jittered* Jittered::clone(void) const {
	return (new Jittered(*this));
}

Jittered::~Jittered(void) {}

void Jittered::generate_samples(void) {
	int n = (int) sqrt((float)num_samples);

	for(int p = 0; p < num_sets; p++)
		for(int j = 0; j < n; j ++)
			for(int k = 0; k < n; k ++) {
				Point2D sp((k + rand_float()) / n, (j + rand_float()) / n);
				samples.push_back(sp);
			}
}