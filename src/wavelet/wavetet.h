#include <boost/math/quadrature/wavelet_transforms.hpp>

namespace boost::math::quadrature {

    template<class F, typename Real, int p>
    class wavelet
    {
    public:
        wavelet(F f, int grid_refinements = -1, Real tol = 100*std::numeric_limits<Real>::epsilon(),
                                     int max_refinements = 12) {}

        wavelet(F f, boost::math::daubechies_wavelet<Real, p> wavelet, Real tol = 100*std::numeric_limits<Real>::epsilon(),
                                     int max_refinements = 12);

        auto operator()(Real s, Real t)->decltype(std::declval<F>()(std::declval<Real>())) const;

    };
}