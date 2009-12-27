#ifndef __YUNI_APPLICATION_AAPPLICATION_HXX__
# define __YUNI_APPLICATION_AAPPLICATION_HXX__


namespace Yuni
{
namespace Application
{


	inline AApplication::Ptr AApplication::Instance()
	{
		return pGlobalInstance;
	}


	inline bool AApplication::terminated() const
	{
		return pTerminated;
	}


	inline void AApplication::terminate(const sint8 ex)
	{
		pExitCode = ex;
		pTerminated = true;
	}


	inline const AApplication::PathType& AApplication::exeName() const
	{
		return pExeName;
	}


	inline const AApplication::PathType& AApplication::rootFolder() const
	{
		return pRootFolder;
	}


	inline sint8 AApplication::exitCode() const
	{
		return pExitCode;
	}


	inline AApplication::AApplication(const AApplication&)
		:ThreadingPolicy()
	{}


	AApplication& AApplication::operator = (const AApplication&)
	{
		return *this;
	}





} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_AAPPLICATION_HXX__


