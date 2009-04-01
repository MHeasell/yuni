#ifndef __YUNI_TOOLBOX_VARIANT_VARIANT_HXX__
#define __YUNI_TOOLBOX_VARIANT_VARIANT_HXX__

namespace Yuni
{

	template <typename T>
	Variant::Variant(const T& rhs) : pData(NULL)
	{ assign(rhs); }

	template <typename T>
	void Variant::assign(const T& rhs)
	{
		// TODO: We need to suppress any const fom the type T
		// because we do not want to write converters
		// for const and non-const base types.

		if (pData)
			delete pData;
		pData = new Private::Variant::Data<T>(rhs);
	}

	template <typename T>
	Variant& Variant::operator = (const T& rhs)
	{ assign(rhs); return *this; }

	template <typename T>
	T Variant::to() const
	{ return (pData) ? pData->to<T>() : T(); }

}

#endif /* !__YUNI_TOOLBOX_VARIANT_VARIANT_HXX__ */
