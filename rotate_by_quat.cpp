#include "rotate_by_quat.h"

#include "quat_conjugate.h"
#include "quat_mult.h"
#include "normalize_quat.h"
#include <cassert>

template <typename Q_type>
IGL_INLINE void igl::rotate_by_quat(
  const Q_type *v,
  const Q_type *q,
  Q_type *out)
{
  // Quaternion form of v, copy data in v, (as a result out can be same pointer
  // as v)
  Q_type quat_v[4] = {v[0],v[1],v[2],0};

  // normalize input 
  Q_type normalized_q[4];
  bool normalized = igl::normalize_quat<Q_type>(q,normalized_q);
  assert(normalized);

  // Conjugate of q
  Q_type q_conj[4];
  igl::quat_conjugate<Q_type>(normalized_q,q_conj);

  // Rotate of vector v by quaternion q is:
  // q*v*conj(q)
  // Compute q*v
  Q_type q_mult_quat_v[4];
  igl::quat_mult<Q_type>(normalized_q,quat_v,q_mult_quat_v);
  // Compute (q*v) * conj(q)
  igl::quat_mult<Q_type>(q_mult_quat_v,q_conj,out);
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
