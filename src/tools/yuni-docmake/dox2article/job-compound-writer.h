#ifndef __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_JOB_COMPOUND_WRITER_H__
# define __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_JOB_COMPOUND_WRITER_H__

# include <yuni/yuni.h>
# include "job.h"
# include "compound.h"


namespace Yuni
{
namespace Edalene
{
namespace Dox2Article
{
namespace Job
{



	class CompoundWriter : public Yuni::Edalene::Dox2Article::Job::IJob
	{
	public:
		/*!
		** \brief Explorer all known symbols
		*/
		static void Dispatch();

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		explicit CompoundWriter(Compound::Ptr& compound);
		//! Destructor
		virtual ~CompoundWriter();
		//@}

	protected:
		virtual void onExecute();

	private:
		void buildClass();
		void buildNamespace();

	private:
		Compound::Ptr pCompound;

	}; // class CompoundWriter








} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

#endif // __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_JOB_COMPOUND_WRITER_H__
