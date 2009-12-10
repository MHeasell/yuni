#ifndef __YUNI_AUDIO_SOUND_H__
# define __YUNI_AUDIO_SOUND_H__

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
	class Sound: Policy::ObjectLevelLockable<Sound>
	{
	public:
		//! \name Typedefs
		//@{
		typedef SmartPtr<Sound> Ptr;

		typedef Policy::ObjectLevelLockable<Sound> ThreadingPolicy;
		//@}

	public:
		/*!
		** \brief Empty constructor, use default values.
		*/
		Sound(): pFilePath(""), pFile(NULL)
		{}

	private:
		//! Forbid default copy constructor
		Sound(const Sound&);
		//! Forbid default operator=
		Sound& operator= (const Sound&);

	public:
		//! \name Methods
		//@{
		virtual bool prepare() = 0;
		virtual unsigned int buffer() = 0;
		//@}

		//! \name Accessors
		//@{
		const String& name() const { return pName; }
		void name(const String& name) { pName = name; }

		//! Is the sound ready to play?
		bool ready() const { return NULL != pFile; }
		//@}

	protected:
		//! \name Protected methods
		//@{
		//! Load the file
		bool loadFile();
		//@}

	protected:
		//! String identifier for the sound
		String pName;
		//! File path or URL
		String pFilePath;
		//! A loaded AV file, NULL if not loaded
		AudioFile* pFile;

	}; // Sound

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_H__
