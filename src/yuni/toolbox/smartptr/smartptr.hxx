#ifndef __YUNI_TOOLBOX_SMARTPTR_SMARTPTR_HXX__
# define __YUNI_TOOLBOX_SMARTPTR_SMARTPTR_HXX__


namespace Yuni
{

	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline T* SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ExtractPointer(const SmartPtr& p)
	{
		return storagePointer(p);
	}




	// Default constructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr()
	{
		// Checking if a null value is allowed, or not
		CheckingPolicy::onDefault(storagePointer(*this));
	}


	// Explicit
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ExplicitStoredType ptr)
		:StoragePolicy(ptr)
	{
		// Check if the checking policy allows the given value
		CheckingPolicy::onInit(storagePointer(*this));
	}


	// Implicit
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ImplicitStoredType ptr)
		:StoragePolicy(ptr)
	{
		// Check if the checking policy allows the given value
		CheckingPolicy::onInit(storagePointer(*this));
	}


	// Copy constructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::CopyType& rhs)
		:StoragePolicy(rhs), OwnershipPolicy(rhs), CheckingPolicy(rhs), ConversionPolicy(rhs), TrackingPolicy(rhs)
	{
		// Cloning the stored data
		storageReference(*this) = OwnershipPolicy::clone(storageReference(rhs));
	}


	// Copy constructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs)
		:StoragePolicy(rhs), OwnershipPolicy(rhs), CheckingPolicy(rhs), ConversionPolicy(rhs), TrackingPolicy(rhs)
	{
		// Cloning the stored data
		storageReference(*this) = OwnershipPolicy::clone(storageReference(rhs));
	}


	// Copy constructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs)
		:StoragePolicy(rhs), OwnershipPolicy(rhs), CheckingPolicy(rhs), ConversionPolicy(rhs), TrackingPolicy(rhs)
	{
		// Cloning the stored data
		storageReference(*this) = OwnershipPolicy::clone(storageReference(rhs));
	}



	// Move constructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::SmartPtr(Static::MoveConstructor<SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP> > rhs)
		:StoragePolicy(rhs), OwnershipPolicy(rhs), CheckingPolicy(rhs), ConversionPolicy(rhs), TrackingPolicy(rhs)
	{}


	// Destructor
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::~SmartPtr()
	{
		// Shall we destroy the data ?
		if (OwnershipPolicy::release(storagePointer(*static_cast<StoragePolicy*>(this))))
		{
			// Really destroy the data
			StoragePolicy::destroy();
		}
	}


	// Operator =
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>& 
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator = (typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::CopyType& rhs)
	{
		SmartPtr tmp(rhs);
		tmp.swap(*this);
		return *this;
	}


	// Operator =
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>& 
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator = (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs)
	{
		SmartPtr tmp(rhs);
		tmp.swap(*this);
		return *this;
	}


	// Operator =
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>& 
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator = (SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs)
	{
		SmartPtr tmp(rhs);
		tmp.swap(*this);
		return *this;
	}


	// Operator =
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void 
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::swap(SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>& rhs)
	{
		OwnershipPolicy::swapPointer(rhs);
		ConversionPolicy::swapPointer(rhs);
		CheckingPolicy::swapPointer(rhs);
		StoragePolicy::swapPointer(rhs);
	}


	// Operator ->
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ConstPointerType
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator -> () const
	{
		CheckingPolicy::onDereference(storageReference(*this));
		return StoragePolicy::operator -> ();
	}


	// Operator ->
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::PointerType
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator -> ()
	{
		CheckingPolicy::onDereference(storageReference(*this));
		return StoragePolicy::operator -> ();
	}


	// Operator ->
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ConstReferenceType
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator * () const
	{
		CheckingPolicy::onDereference(storageReference(*this));
		return StoragePolicy::operator * ();
	}


	// Operator ->
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline typename SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::ReferenceType
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator * ()
	{
		CheckingPolicy::onDereference(storageReference(*this));
		return StoragePolicy::operator * ();
	}


	// Operator ->
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator ! () const
	{
		return storagePointer(*this) == NULL;
	}


	// Operator ==
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator == (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) == storagePointer(rhs));
	}



	// Operator !=
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator != (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) != storagePointer(rhs));
	}


	// Operator <
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator < (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) < storagePointer(rhs));
	}


	// Operator >
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator > (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) > storagePointer(rhs));
	}


	// Operator <=
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator <= (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) <= storagePointer(rhs));
	}


	// Operator >=
	template<typename T, template <class> class OwspP, template <class> class ChckP,
		template <class> class TrckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	template<typename T1, template <class> class OwspP1, template <class> class ChckP1,
		template <class> class TrckP1, class ConvP1,
		template <class> class StorP1, template <class> class ConsP1>
	inline bool
	SmartPtr<T,OwspP,ChckP,TrckP,ConvP,StorP,ConsP>::operator >= (const SmartPtr<T1,OwspP1,ChckP1,TrckP1,ConvP1,StorP1,ConsP1>& rhs) const
	{
		return (storagePointer(*this) >= storagePointer(rhs));
	}






} // namespace Yuni

#endif // __YUNI_TOOLBOX_SMARTPTR_SMARTPTR_HXX__
