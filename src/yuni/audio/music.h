#ifndef __YUNI_AUDIO_MUSIC_H__
# define __YUNI_AUDIO_MUSIC_H__

# include "../yuni.h"
# include "sound.h"


namespace Yuni
{
namespace Audio
{

	/*!
	** \brief A music is a sound meant to be played as ambience
	*/
	class Music: public ASound
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<Music>  Ptr;
		//! The Threading Policy
		typedef ASound::ThreadingPolicy  ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Music() {}
		//! Destructor
		virtual ~Music() {}
		//@}

	public:
		//! \name Methods
		//@{
		virtual bool prepare();
		virtual unsigned int buffer() const;
		//@}

	private:
		Music(const Music&);
		Music& operator= (const Music&);

	}; // Music

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MUSIC_H__
