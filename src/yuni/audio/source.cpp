#include "source.h"

namespace Yuni
{
namespace Audio
{

	bool Source::play(const Sound3D& sound)
	{
		OpenAL::playSource(pID);
	}

	bool Source::play(const Music& sound)
	{
		OpenAL::playSource(pID);
	}

} // namespace Audio
} // namespace Yuni
