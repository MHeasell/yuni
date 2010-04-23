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
		typedef SmartPtr<Buffer<> > Ptr;
		typedef std::map<String, Ptr> Map;

	public:
		enum // anonymous
		{
			BufferCount = 4,
			BufferSize = BufferSizeT
		}; // enum anonymous

	public:
		Buffer(AudioStream* stream);
		~Buffer();

		bool prepare(unsigned int source);

		bool update(unsigned int source);

	private:
		AudioStream* pStream;

		unsigned int pIDs[BufferCount];

		CustomString<BufferSize, false, false> pData;

	}; // class Buffer



} // namespace Audio
} // namespace Private
} // namespace Yuni


# include "buffer.hxx"


#endif // __YUNI_PRIVATE_AUDIO_BUFFER_H__
