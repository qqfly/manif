#ifndef _MANIF_MANIF_SE2_H_
#define _MANIF_MANIF_SE2_H_

#include "manif/impl/se2/SE2_base.h"

#include <Eigen/Core>

namespace manif
{

// Forward declare for type traits specialization

template <typename _Scalar> struct SE2;
template <typename _Scalar> struct SE2Tangent;

namespace internal
{

// Traits specialization

template <>
template <typename _Scalar>
struct traits<SE2<_Scalar>>
{
  using Scalar = _Scalar;

  using Manifold = SE2<_Scalar>;
  using Tangent  = SE2Tangent<_Scalar>;

  using Base = SE2Base<SE2<_Scalar>>;

  static constexpr int Dim = ManifoldProperties<Base>::Dim;
  static constexpr int DoF = ManifoldProperties<Base>::DoF;
  static constexpr int N   = ManifoldProperties<Base>::N;

  /// @todo move those to some traits ?

  using DataType = Eigen::Matrix<Scalar, 4, 1>;

  using Jacobian       = Eigen::Matrix<Scalar, DoF, DoF>;
  using Transformation = Eigen::Matrix<Scalar, N, N>;
  using Rotation       = Eigen::Matrix<Scalar, Dim, Dim>;
  using Vector         = Eigen::Matrix<Scalar, DoF, 1>;
};

} /* namespace internal */
} /* namespace manif */

namespace manif
{

////////////////
///          ///
/// Manifold ///
///          ///
////////////////

template <typename _Scalar>
struct SE2 : SE2Base<SE2<_Scalar>>
{
private:

  using Base = SE2Base<SE2<_Scalar>>;
  using Type = SE2<_Scalar>;

public:

  MANIF_COMPLETE_MANIFOLD_TYPEDEF

  SE2()  = default;
  ~SE2() = default;

  SE2(const DataType& d);
  SE2(const Scalar x, const Scalar y, const Scalar theta);
  SE2(const Scalar x, const Scalar y, const Scalar real, const Scalar imag);

  /// Manifold common API

  const DataType* data() const;

  MANIF_INHERIT_MANIFOLD_API

  /// SE2 specific API

  using Base::angle;

protected:

  friend class ManifoldBase<SE2<Scalar>>;
  DataType* data();

  DataType data_;
};

MANIF_EXTRA_MANIFOLD_TYPEDEF(SE2)

template <typename _Scalar>
SE2<_Scalar>::SE2(const DataType& d)
  : data_(d)
{
  //
}

template <typename _Scalar>
SE2<_Scalar>::SE2(const Scalar x, const Scalar y, const Scalar theta)
  : SE2(DataType(x, y, cos(theta), sin(theta)))
{
  using std::cos;
  using std::sin;
}

template <typename _Scalar>
SE2<_Scalar>::SE2(const Scalar x, const Scalar y, const Scalar real, const Scalar imag)
  : SE2(DataType(x, y, real, imag))
{
  //
}

template <typename _Scalar>
typename SE2<_Scalar>::DataType*
SE2<_Scalar>::data()
{
  return &data_;
}

template <typename _Scalar>
const typename SE2<_Scalar>::DataType*
SE2<_Scalar>::data() const
{
  return &data_;
}

} /* namespace manif */

#endif /* _MANIF_MANIF_SE2_H_ */