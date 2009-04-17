#ifndef __YUNI_TOOLBOX_DYNAMICLIBRARY_FILE_HXX__
# define __YUNI_TOOLBOX_DYNAMICLIBRARY_FILE_HXX__



namespace Yuni
{
namespace DynamicLibrary
{




	inline File::File(const char* filename, const Relocation r,
			const Visibility v)
		:pHandle(NullHandle)
	{
		(void)load(filename, r, v);
	}


	inline File::File(const String& filename, const Relocation r,
			const Visibility v)
		:pHandle(NullHandle)
	{
		(void)load(filename.c_str(), r, v);
	}


	inline File::File()
		:pHandle(NullHandle)
	{}

	inline File::~File()
	{
		if (NullHandle != pHandle)
			wrapperDlClose(pHandle);
	}


	inline bool File::loadFromRawFilename(const String& filename,
		const File::Relocation r,
		const File::Visibility v)
	{
		return loadFromRawFilename(filename.c_str(), r, v);
	}




	inline bool File::hasSymbol(const String& name) const
	{
		return NullHandle != pHandle && NULL != wrapperDlSym(pHandle, name.c_str());
	}


	inline bool File::hasSymbol(const char* name) const
	{
		return (name && NullHandle != pHandle) && NULL != wrapperDlSym(pHandle, name);
	}


	inline Symbol
	File::resolve(const String& name) const
	{
		return NullHandle != pHandle ? wrapperDlSym(pHandle, name.c_str()) : NULL;
	}

	inline Symbol
	File::resolve(const char* name) const
	{
		return (name && NullHandle != pHandle) ? wrapperDlSym(pHandle, name) : NULL;
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

	inline Symbol
	File::operator [] (const char* name) const
	{
		return (name && NullHandle != pHandle) ? wrapperDlSym(pHandle, name) : NULL;
	}

	inline Symbol
	File::operator [] (const String& name) const
	{
		return (NullHandle != pHandle) ? wrapperDlSym(pHandle, name.c_str()) : NULL;
	}




} // namespace DyanmicLibrary
} // namespace Yuni

#endif // __YUNI_TOOLBOX_DYNAMICLIBRARY_FILE_HXX__
