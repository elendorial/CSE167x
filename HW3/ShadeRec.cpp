#include "Constants.h"
#include "ShadeRec.h"


ShadeRec::ShadeRec(World& wr)
: hit_an_object(false),
  material_ptr(NULL),
  hit_point(),
  local_hit_point(),
  normal(),
  ray(),
  depth(0),
  t(0.0),
  dir(),
  w(wr)
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
: hit_an_object(sr.hit_an_object),
  material_ptr(sr.material_ptr),
  hit_point(sr.hit_point),
  local_hit_point(sr.local_hit_point),
  normal(sr.normal),
  ray(sr.ray),
  depth(sr.depth),
  t(sr.t),
  dir(sr.dir),
  w(sr.w)
{}

