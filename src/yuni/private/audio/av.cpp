#include <cstdlib>
#include <memory.h>

#include "av.h"
# if (YUNI_OS_GCC_VERSION >= 40102)
#	pragma GCC diagnostic ignored "-Wconversion"
# endif

extern "C"
{
# include "libavutil/pixdesc.h"
# include "libavcodec/avcodec.h"
# include "libavformat/avformat.h"
}

namespace Yuni
{
namespace Private
{
namespace Audio
{


	bool AV::Init()
	{
		av_register_all();
		# ifdef NDEBUG
		// Silence warning output from the lib
		av_log_set_level(AV_LOG_ERROR);
		# else // NDEBUG
		// Only write output when encountering unrecoverable errors
		av_log_set_level(AV_LOG_FATAL);
		# endif // NDEBUG
		return true;
	}



} // namespace Audio
} // namespace Private
} // namespace Yuni
