#ifndef __YUNI_CORE_DYNAMICLIBRARY_FILE_HXX__
# define __YUNI_CORE_DYNAMICLIBRARY_FILE_HXX__

namespace Yuni
{
namespace DynamicLibrary
{




	template<class StringT>
	inline bool File::hasSymbol(const StringT& name) const
	{
		const char* const query = Traits::CString<StringT>::Perform(name);
		return NullHandle != pHandle && NULL != wrapperDlSym(pHandle, query);
	}


	template<class StringT>
	inline Symbol File::resolve(const StringT& name) const
	{
		const char* const query = Traits::CString<StringT>::Perform(name);
		return NullHandle != pHandle ? wrapperDlSym(pHandle, query) : NULL;
	}


	inline bool File::loaded() const
	{
		return (pHandle != NullHandle);
	}


	inline const String& File::filename() const
	{
		return pFilename;
	}


	inline File::Handle File::handle() const
	{
		return pHandle;
	}


	template<class StringT>
	inline Symbol File::operator [] (const StringT& name) const
	{
		return resolve(name);
	}





} // namespace DyanmicLibrary
} // namespace Yuni

#endif // __YUNI_CORE_DYNAMICLIBRARY_FILE_HXX__
