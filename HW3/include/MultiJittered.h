#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

#include "Sampler.h"

class MultiJittered: public Sampler {

    public:

        MultiJittered(void);

        MultiJittered(const int num_samples);

        MultiJittered(const int num_samples, const int m);

        MultiJittered(const MultiJittered& rhs);

        MultiJittered& operator= (const MultiJittered& rhs);

        virtual MultiJittered* clone(void) const;

        virtual ~MultiJittered(void);

    private:

        virtual void generate_samples(void);
};

#endif