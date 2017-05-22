#ifndef CHANNELS_ADDITIVE_USER_HPP_
#define CHANNELS_ADDITIVE_USER_HPP_

#include <vector>
#include "Tools/Perf/MIPP/mipp.h"

#include "../../Channel.hpp"

namespace aff3ct
{
namespace module
{
template <typename R = float>
class Channel_additive_user : public Channel<R>
{
private:
	mipp::vector<mipp::vector<R>> noise;
	int noise_counter;

public:
	Channel_additive_user(const int N, const std::string filename, const int n_frames = 1,
	                      const std::string name = "Channel_additive_user");
	virtual ~Channel_additive_user();

protected:
	void _add_noise(const R *X_N, R *Y_N, const int frame_id);
};
}
}

#endif /* CHANNELS_ADDITIVE_USER_HPP_ */
