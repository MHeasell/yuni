#ifndef __YUNI_PRIVATE_AUDIO_AV_H__
# define __YUNI_PRIVATE_AUDIO_AV_H__

# include "../../yuni.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	/*!
	** \brief This is a wrapper around the AV* libs from ffmpeg.
	*/
	class AV
	{
	public:
		//! Initialize ffmpeg
		static bool Init();

	}; // class AV




} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_AV_H__
