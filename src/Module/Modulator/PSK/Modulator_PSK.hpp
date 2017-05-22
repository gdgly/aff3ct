#ifndef MODULATOR_PSK_HPP_
#define MODULATOR_PSK_HPP_

#include <complex>
#include <vector>
#include "Tools/Perf/MIPP/mipp.h"
#include "Tools/Math/max.h"

#include "../Modulator.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float, typename Q = R, tools::proto_max<Q> MAX = tools::max_star>
class Modulator_PSK : public Modulator<B,R,Q>
{
private:
	const int bits_per_symbol;
	const int nbr_symbols;
	const bool disable_sig2;
	mipp::vector<std::complex<R>> constellation;

public:
	Modulator_PSK(const int N, const R sigma, const int bits_per_symbol = 2, const bool disable_sig2 = false,
	              const int n_frames = 1, const std::string name = "Modulator_PSK");
	virtual ~Modulator_PSK();

	static int size_mod(const int N, const int bps)
	{
		return Modulator<B,R,Q>::get_buffer_size_after_modulation(N, bps, 0, 1, true);
	}

	static int size_fil(const int N, const int bps)
	{
		return Modulator<B,R,Q>::get_buffer_size_after_filtering(N, bps, 0, 1, true);
	}

protected:
	void   _modulate           (const B *X_N1,                              R *X_N2, const int frame_id);
	void     _filter           (const R *Y_N1,                              R *Y_N2, const int frame_id);
	void _demodulate           (const Q *Y_N1,                              Q *Y_N2, const int frame_id);
	void _demodulate_with_gains(const Q *Y_N1, const R *H_N,                Q *Y_N2, const int frame_id);
	void _demodulate           (const Q *Y_N1,               const Q *Y_N2, Q *Y_N3, const int frame_id);
	void _demodulate_with_gains(const Q *Y_N1, const R *H_N, const Q *Y_N2, Q *Y_N3, const int frame_id);

private:
	inline std::complex<R> bits_to_symbol(const B* bits) const;
};
}
}

#include "Modulator_PSK.hxx"

#endif // MODULATOR_PSK_HPP_
