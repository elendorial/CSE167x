#include "Hammersley.h"
#include "Maths.h"

Hammersley::Hammersley(void)
:	Sampler()
{}

Hammersley::Hammersley(const int num)
:	Sampler(num) {
	generate_samples();
}

Hammersley::Hammersley(const Hammersley& h)
:	Sampler(h) {
	generate_samples();
}

Hammersley& Hammersley::operator= (const Hammersley& rhs) {
	if(this == &rhs)
		return(*this);

	Sampler::operator= (rhs);

	return(*this);
}

Hammersley* Hammersley::clone(void) const {
	return(new Hammersley(*this));
}

Hammersley::~Hammersley(void) {}

double Hammersley::phi(int j ) {
	double x = 0.0;
	double f = 0.5;

	while(j) {
		x += f * (double) (j % 2);
		j /= 2;
		f *= 0.5;
	}

	return(x);
}

void Hammersley::generate_samples(void) {
	for(int p = 0; p < num_sets; p++)
		for(int j = 0; j < num_samples; j++) {
			Point2D pv((float) j / (float) num_samples, phi(j));
			samples.push_back(pv);
		}
}