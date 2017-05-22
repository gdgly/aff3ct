#include "Module/Interleaver/Random_column/Interleaver_random_column.hpp"
#include "Module/Interleaver/Row_column/Interleaver_row_column.hpp"
#include "Module/Interleaver/LTE/Interleaver_LTE.hpp"
#include "Module/Interleaver/CCSDS/Interleaver_CCSDS.hpp"
#include "Module/Interleaver/NO/Interleaver_NO.hpp"
#include "Module/Interleaver/Golden/Interleaver_golden.hpp"
#include "Module/Interleaver/Random/Interleaver_random.hpp"
#include "Module/Interleaver/User/Interleaver_user.hpp"

#include "Factory_interleaver.hpp"

using namespace aff3ct::module;
using namespace aff3ct::tools;

template <typename T>
Interleaver<T>* Factory_interleaver<T>
::build(const parameters &params, const int &size, const int seed)
{
	Interleaver<T> *interleaver = nullptr;

	// build the interleaver
	if (params.interleaver.type == "LTE")
		interleaver = new Interleaver_LTE<T>(size, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "CCSDS")
		interleaver = new Interleaver_CCSDS<T>(size, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "RANDOM")
		interleaver = new Interleaver_random<T>(size, seed, params.interleaver.uniform, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "RAND_COL")
		interleaver = new Interleaver_random_column<T>(size, params.interleaver.n_cols, seed, params.interleaver.uniform, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "ROW_COL")
		interleaver = new Interleaver_row_column<T>(size, params.interleaver.n_cols, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "GOLDEN")
		interleaver = new Interleaver_golden<T>(size, seed, params.interleaver.uniform, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "USER")
		interleaver = new Interleaver_user<T>(size, params.interleaver.path, params.simulation.inter_frame_level);
	else if (params.interleaver.type == "NO")
		interleaver = new Interleaver_NO<T>(size, params.simulation.inter_frame_level);

	return interleaver;
}

// ==================================================================================== explicit template instantiation 
template struct aff3ct::tools::Factory_interleaver<short>;
template struct aff3ct::tools::Factory_interleaver<int>;
template struct aff3ct::tools::Factory_interleaver<long long>;
// ==================================================================================== explicit template instantiation
