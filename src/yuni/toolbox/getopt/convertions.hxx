#ifndef __YUNI_TOOLBOX_GETOPT_CONVERTIONS_HXX__ 
# define __YUNI_TOOLBOX_GETOPT_CONVERTIONS_HXX__ 


namespace Yuni
{
namespace ToolBox
{
namespace GetOpt
{


	// Specialization for String
	template<>
	class DefaultConverterTo<String>
	{
	public:
		static const String& FromString(const String& s) {return s;}
	};
	
	
	// Specialization for String
	template<>
	class DefaultConverterTo<bool>
	{
	public:
		static bool FromString(const String& s) {return s.toBool();}
	};
	
	
	// Specialization for String
	template<>
	class DefaultConverterTo<sint8>
	{
	public:
		static sint8 FromString(const String& s) {return s.toInt8();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<sint16>
	{
	public:
		static sint16 FromString(const String& s) {return s.toInt16();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<sint32>
	{
	public:
		static sint32 FromString(const String& s) {return s.toInt32();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<sint64>
	{
	public:
		static sint64 FromString(const String& s) {return s.toInt64();}
	};
	

	
	// Specialization for String
	template<>
	class DefaultConverterTo<uint8>
	{
	public:
		static uint8 FromString(const String& s) {return s.toUInt8();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<uint16>
	{
	public:
		static uint16 FromString(const String& s) {return s.toUInt16();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<uint32>
	{
	public:
		static uint32 FromString(const String& s) {return s.toUInt32();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<uint64>
	{
	public:
		static uint64 FromString(const String& s) {return s.toUInt64();}
	};
	

	
	// Specialization for String
	template<>
	class DefaultConverterTo<float>
	{
	public:
		static float FromString(const String& s) {return s.toFloat();}
	};
	
	// Specialization for String
	template<>
	class DefaultConverterTo<double>
	{
	public:
		static double FromString(const String& s) {return s.toDouble();}
	};
	


} // namespace GetOpt
} // namespace ToolBox
} // namespace Yuni


#endif // __YUNI_TOOLBOX_GETOPT_CONVERTIONS_HXX__ 
