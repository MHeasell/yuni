#ifndef __YUNI_DOCMAKE_JOB_WRITER_H__
# define __YUNI_DOCMAKE_JOB_WRITER_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include <yuni/job/job.h>
# include <yuni/job/queue.h>
# include <vector>
# include "article.h"



class JobWriter : public Yuni::Job::IJob
{
public:
	static void Add(const Yuni::String& input, const Yuni::String& htdocs, const ArticleData& article);

	static void PushAllInQueue();

	static bool ReadTemplateIndex();

public:
	//! \name Constructor & Destructor
	//@{
	/*!
	** \brief Constructor
	*/
	JobWriter(const Yuni::String& input, const Yuni::String& htdocs, const ArticleData& article);
	//! Destructor
	virtual ~JobWriter();
	//@}



private:
	virtual void onExecute();

	void prepareVariables(const Yuni::String& filenameInHtdocs);

private:
	typedef std::map<Yuni::String, Yuni::String>  Variables;

private:
	const Yuni::String& pInput;
	const Yuni::String& pHtdocs;
	ArticleData pArticle;
	Variables pVars;

}; // class CompileJob




#endif // __YUNI_DOCMAKE_JOB_WRITER_H__
