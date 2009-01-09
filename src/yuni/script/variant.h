#ifndef __YUNI_SCRIPT_VARIANT_H__
# define __YUNI_SCRIPT_VARIANT_H__

# include "../yuni.h"
# include "../toolbox/string.h"

namespace Yuni
{
namespace Script
{
	/*!
	** \brief Variant class. Can hold basic types of
	** values (int, double, string, ...) that may be
	** used as parameters in scripts function calls.
	**
	** TODO: do a better documentation of the Variant class.
	** TODO: Variant is implemented very naively (better say it that way) just to test,
	** TODO: i'm sure there's far better ways to do that.
	*/
	class Variant
	{

	public:
		//! All the values that can be stored in this kind of Variant
		enum ValueType {
			vtNone = 0,
			vtShort,
			vtInt,
			vtString,
			vtCString,
			vtDouble,
			vtPointer
		};

	private:
		Variant() { pType = vtNone; }


	public:
		//! \name Contructors & Destructor
		//@{
		Variant(const short value) { pStore.vsShort = value; pType = vtShort; }
		Variant(const int value) { pStore.vsInt = value; pType = vtInt; }
		Variant(const String& value) { pStore.vsString = &value; pType = vtString; }
		Variant(const char * value) { pStore.vsCString = value; pType = vtCString; }
		Variant(const double value) { pStore.vsDouble = value; pType = vtDouble; }
		Variant(void * value) { pStore.vsPointer = value; pType = vtPointer; }

		//! Dtor
		~Variant() {}
		//@}

	public:
		//! \name Value manipulation
		//@{
		ValueType type() const { return pType; }

		short asShort() const { return pStore.vsShort; }
		int asInt() const { return pStore.vsInt; }
		const String& asString() const { return *pStore.vsString; }
		const char * asCString() const { return pStore.vsCString; }
		double asDouble() const { return pStore.vsDouble; }
		void * asPointer() const { return pStore.vsPointer; }

		//@}
	
	public:
		//! A null variant that contains nothing for default parameters
		static const Variant Null; 
	
	private:
		ValueType pType;

		union ValueStore
		{
			short vsShort;
			int vsInt;
			const String * vsString;
			const char * vsCString;
			double vsDouble;
			void * vsPointer;
		};

		ValueStore pStore;

	}; // class Variant


} // namespace Script
} // namespace Yuni


#endif /* !__YUNI_SCRIPT_VARIANT_H__ */
