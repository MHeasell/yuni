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


	inline void AApplication::terminate(const int ex)
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


	inline int AApplication::exitCode() const
	{
		return pExitCode;
	}


	inline AApplication::AApplication(const AApplication&)
		:ThreadingPolicy()
	{}


	inline AApplication& AApplication::operator = (const AApplication&)
	{
		return *this;
	}


	inline void AApplication::execute()
	{
		if (!pTerminated)
			this->onExecute();
	}



} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_AAPPLICATION_HXX__


