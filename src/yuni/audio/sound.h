#ifndef __YUNI_AUDIO_SOUND_H__
# define __YUNI_AUDIO_SOUND_H__

# include "../yuni.h"
# include "openal.h"
# include "av.h"
# include "../core/smartptr.h"
# include "../core/string.h"

namespace Yuni
{
namespace Audio
{


	/*!
	** \brief A sound is any kind of audio content that can be played by Yuni.
	*/
	class ASound : public Policy::ObjectLevelLockable<ASound>
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<ASound> Ptr;
		//! The Threading Policy
		typedef Policy::ObjectLevelLockable<ASound> ThreadingPolicy;

	public:
		//! \name Constructor
		//@{
		/*!
		** \brief Empty constructor, use default values.
		*/
		ASound();
		//! Destructor
		virtual ~ASound() {}
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
		ASound(const ASound&);
		//! Forbid default operator=
		ASound& operator = (const ASound&);

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
		ThreadingPolicy::Volatile<AudioFile*>::Type pFile;

	}; // class ASound




} // namespace Audio
} // namespace Yuni

# include "sound.hxx"

#endif // __YUNI_AUDIO_SOUND_H__
