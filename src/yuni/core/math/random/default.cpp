
#include "default.h"
#include <time.h>


namespace Yuni
{
namespace Math
{
namespace Random
{


	void Default::reset()
	{
		// Initializing the random generator with a standard seed
		::srand((unsigned int) ::time(NULL));
		// Compute a random number for nothing, to avoid the first generated number
		::rand();
	}


	void Default::reset(const unsigned int seed)
	{
		// Initializing the random generator with the given seed
		::srand(seed);
		// Compute a random number for nothing, to avoid the first generated number
		::rand();
	}



} // namespace Random
} // namespace Math
} // namespace Yuni


