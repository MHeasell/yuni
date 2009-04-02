#ifndef __YUNI_TOOLBOX_VARIANT_VARIANT_PRIVATE_HXX__
#define __YUNI_TOOLBOX_VARIANT_VARIANT_PRIVATE_HXX__

namespace Yuni
{
namespace Private
{
namespace Variant
{

	/*!
	** \brief Specialisation for Bool to String.
	*/
	template<>
	struct Converter<bool, String>
	{
		// Please use Yuni::String << bool
		static bool Value(const bool& from, String& to)
		{
			to = (from) ? "True" : "False";
			return true;
		}
	};

	/*!
	** \brief Specialization for anything to String.
	*/
	template<typename W>
	struct Converter<W, String>
	{
		static bool Value(const W& from, String& to)
		{
			to << from;
			return true;
		}
	};


	template <typename T>
	T AData::to() const
	{
		DataConverter<T> dc;
		convertUsing(dc);
		return dc.result;
	}

} // namespace Variant
} // namespace Private
} // namespace Yuni

#endif /* !__YUNI_TOOLBOX_VARIANT_VARIANT_PRIVATE_HXX__ */

