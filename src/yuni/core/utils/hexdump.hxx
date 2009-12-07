#ifndef __YUNI_CORE_UTILS_HEXDUMP_HXX__
# define __YUNI_CORE_UTILS_HEXDUMP_HXX__

namespace Yuni
{
namespace Core
{
namespace Utils
{

	template <typename U>
	void Hexdump::dump(U& stream) const
	{
		Yuni::String line;
		unsigned int printed;
		unsigned int remains = pSize;

		for (printed = 0; printed <	pSize; printed += 0x10)
		{
			remains = pSize - printed;

			// Print the line's address
			line.appendFormat("%08.8p: ", (pBuffer + printed));

			// Print the next 16 bytes (or less) in hex.
			dumpHexadecimal(line, pBuffer + printed, remains > 0x10 ? 0x10 : remains);

			line.append('|');
			// Print the next 16 bytes (or less) in printable chars.
			dumpPrintable(line, pBuffer + printed, remains > 0x10 ? 0x10 : remains);
			line.append("|\n");

			// Put the line in the stream
			stream << line;
			line.clear();
		}
	}

} // namespace Utils
} // namespace Core
} // namespace Yuni


#endif // __YUNI_CORE_UTILS_HEXDUMP_HXX__

