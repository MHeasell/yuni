#include "hexdump.h"

namespace Yuni
{
namespace Core
{
namespace Utils
{

	String Hexdump::dump() const
	{
		String s;
		dump(s);
		return s;
	}

	/*
	std::ostream& operator<<(std::ostream& os, const Hexdump& mp)
	{
		mp.dump(os);
		return os;
	}
	*/

	void Hexdump::dumpHexadecimal(String& line, const char* buffer, unsigned int size) const
	{
		for (unsigned int printed = 0; printed < size; ++printed)
		{
			line.appendFormat("%02x", (unsigned int)(*(unsigned int8_t *)(buffer + printed)));
			if (0 != printed % 2)
				line.append(' ');
		}
	}

	void Hexdump::dumpPrintable(String& line, const char* buffer, unsigned int size) const
	{
		for (unsigned int printed = 0; printed < size; ++printed)
		{
			char c = (*(unsigned int8_t *)(buffer + printed));
			if (c < 0x20 || c > 0x7E) // c is not printable ASCII, replace it by a dot '.'
				c = '.';
			line.append(c);
		}
	}

	Hexdump& Hexdump::operator=(const Hexdump& rhs)
	{
		if (this != &rhs)
		{
			this->pBuffer = rhs.pBuffer;
			this->pSize = rhs.pSize;
		}
		return *this;
	}


} // namespace Utils
} // namespace Core
} // namespace Yuni

std::ostream& operator<<(std::ostream& outStream, const Yuni::Core::Utils::Hexdump& hexDumper)
{
	hexDumper.dump(outStream);
	return outStream;
}


