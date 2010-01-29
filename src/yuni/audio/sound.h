#ifndef __YUNI_AUDIO_SOUND_H__
# define __YUNI_AUDIO_SOUND_H__

# include <vector>
# include "../yuni.h"
# include "../private/audio/openal.h"
# include "../private/audio/av.h"
# include "../core/smartptr.h"
# include "../core/string.h"

namespace Yuni
{
namespace Audio
{


	/*!
	** \brief A sound is any kind of audio content that can be played by Yuni.
	*/
	class ISound : public Policy::ObjectLevelLockable<ISound>
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<ISound> Ptr;
		//! Vector of sounds
		typedef std::vector<ISound> Vector;
		//! The Threading Policy
		typedef Policy::ObjectLevelLockable<ISound> ThreadingPolicy;

	public:
		//! \name Constructor
		//@{
		/*!
		** \brief Empty constructor, use default values.
		*/
		ISound();
		//! Destructor
		virtual ~ISound() {}
		//@}

		//! \name Methods
		//@{
		virtual bool prepare() = 0;
		virtual unsigned int buffer() const = 0;
		//@}

		//! \name Accessors
		//@{
		String name() const;
		template<class AnyStringT> void name(const AnyStringT& name);

		//! Is the sound ready to play?
		bool valid() const;
		//@}

		//! \name Operators
		//@{
		bool operator ! () const;
		//@}

	private:
		//! Forbid default copy constructor
		ISound(const ISound&);
		//! Forbid default operator=
		ISound& operator = (const ISound&);

	protected:
		//! \name Protected methods
		//@{
		/*!
		** \brief Load the file
		*/
		bool loadFromFile();
		bool loadFromFileWL();
		//@}

	protected:
		//! String identifier for the sound
		String pName;
		//! File path or URL
		String pFilePath;
		//! A loaded AV file, NULL if not loaded
		ThreadingPolicy::Volatile<Private::Audio::AudioFile*>::Type pFile;

	}; // class ISound




} // namespace Audio
} // namespace Yuni

# include "sound.hxx"

#endif // __YUNI_AUDIO_SOUND_H__
