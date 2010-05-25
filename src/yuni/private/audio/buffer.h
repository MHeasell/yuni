#ifndef __YUNI_PRIVATE_AUDIO_BUFFER_H__
# define __YUNI_PRIVATE_AUDIO_BUFFER_H__

# include <map>
# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/smartptr.h"
# include "../../core/customstring.h"
# include "av.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	template<unsigned int BufferSizeT = 65536>
	class Buffer
	{
	public:
		//! Pointer type
		typedef SmartPtr<Buffer<> > Ptr;
		//! Map from a string to a Buffer::Ptr
		typedef std::map<String, Ptr> Map;

	public:
		enum // anonymous
		{
			MaxBufferCount = 4,
			BufferSize = BufferSizeT
		}; // enum anonymous

	public:
		//! Constructor
		Buffer(AudioStream* stream);
		~Buffer();

		bool prepareDispatched(unsigned int source);

		bool destroyDispatched();

		bool updateDispatched(unsigned int source);

		void stream(AudioStream* stream) { pStream = stream; }

		bool valid() { return NULL != pStream; }

	private:
		//! The audio stream contains the link to the file and the data
		AudioStream* pStream;

		//! Actual number of buffers
		unsigned int pBufferCount;

		//! Identifiers of the OpenAL buffers used
		unsigned int pIDs[MaxBufferCount];

		//! Buffer for storing raw data
		CustomString<BufferSize, false, false> pData;

	}; // class Buffer



} // namespace Audio
} // namespace Private
} // namespace Yuni


# include "buffer.hxx"


#endif // __YUNI_PRIVATE_AUDIO_BUFFER_H__
