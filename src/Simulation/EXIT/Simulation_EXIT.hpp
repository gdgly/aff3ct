#ifndef SIMULATION_EXIT_HPP_
#define SIMULATION_EXIT_HPP_

#include <vector>

#include "Tools/Perf/MIPP/mipp.h"
#include "Tools/params.h"

#include "Module/Source/Source.hpp"
#include "Module/Encoder/Encoder.hpp"
#include "Module/Modulator/Modulator.hpp"
#include "Module/Channel/Channel.hpp"
#include "Module/Decoder/SISO.hpp"

#include "Tools/Display/Terminal/EXIT/Terminal_EXIT.hpp"

#include "../Simulation.hpp"

template <typename B, typename R, typename Q>
class Simulation_EXIT : public Simulation
{
protected:
	const parameters &params; // simulation parameters

	// channel gains
	mipp::vector<R> H_N;

	// data vectors
	mipp::vector<B> B_K, B_N, X_K1, X_N1;
	mipp::vector<R> X_K2, X_N2;
	mipp::vector<R> Y_N, Y_K;
	mipp::vector<R> La_K1;
	mipp::vector<R> Lch_N1;
	mipp::vector<R> La_K2;
	mipp::vector<R> Lch_N2;
	mipp::vector<R> Le_K;
	mipp::vector<R> sys, par;
	mipp::vector<B> B_buff;
	mipp::vector<R> Le_buff, La_buff;

	// EXIT simu parameters
	const int n_trials;
	int cur_trial;
	double I_A, I_E;

	// code specifications
	float sig_a;
	float code_rate;
	float sigma;
	float snr;

	// communication chain
	Source<B>          *source;
	Encoder<B>         *encoder;
	Modulator<B,R,R>   *modulator;
	Modulator<B,R,R>   *modulator_a;
	Channel<R>         *channel;
	Channel<R>         *channel_a;
	SISO<R>            *siso;
	Terminal_EXIT<B,R> *terminal;

	// time points and durations
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> t_snr;

public:
	Simulation_EXIT(const parameters& params);
	virtual ~Simulation_EXIT();
	
	void launch();

private:
	void build_communication_chain();
	void simulation_loop          ();

	static double measure_mutual_info_avg  (const mipp::vector<R>& llrs, const mipp::vector<B>& bits             );
	static double measure_mutual_info_histo(const mipp::vector<R>& llrs, const mipp::vector<B>& bits, const int N);

protected:
	virtual void extract_sys_par(const mipp::vector<R> &Lch_N, 
	                             const mipp::vector<R> &La_K, 
	                                   mipp::vector<R> &sys, 
	                                   mipp::vector<R> &par) = 0;

	virtual void                release_objects  ();
	virtual void                launch_precompute();
	virtual void                snr_precompute   ();

	virtual Source<B>*          build_source     (              );
	virtual Encoder<B>*         build_encoder    (              );
	virtual Modulator<B,R,R>*   build_modulator  (              );
	virtual Modulator<B,R,R>*   build_modulator_a(              );
	virtual Channel<R>*         build_channel    (const int size);
	virtual Channel<R>*         build_channel_a  (const int size);
	virtual SISO<R>*            build_siso       (              ) = 0;
	        Terminal_EXIT<B,R>* build_terminal   (              );
};

#endif /* SIMULATION_EXIT_HPP_ */
