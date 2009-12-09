#include "source.h"

namespace Yuni
{
namespace Audio
{

	bool Source::play(const Sound3D& sound)
	{
		return OpenAL::playSource(pID);
	}

	bool Source::play(const Music& sound)
	{
		return OpenAL::playSource(pID);
	}

} // namespace Audio
} // namespace Yuni
