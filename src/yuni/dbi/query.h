#ifndef __YUNI_DBI_QUERY_H__
# define __YUNI_DBI_QUERY_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include "cursor.h"


namespace Yuni
{
namespace DBI
{


	class Query final
	{
	public:
		/*!
		** \brief Default constructor
		*/
		explicit Query(const AnyString& stmt);

		/*!
		** \brief Bind a parameter
		*/
		Query& parameter(uint index, const AnyString& value);

		/*!
		** \brief Bind a variable (named parameter)
		*/
		Query& variable(const AnyString& name, const AnyString& value);

		/*!
		** \brief Execute the query but discard the results
		*/
		bool perform();


		/*!
		** \brief Execute the query
		*/
		Cursor execute();

		/*!
		** \brief Execute the query and walk through the result set
		*/
		template<class CallbackCursorT> bool each(const CallbackCursorT& callback);


	private:
		//! Statement
		AnyString pStmt;

	}; // class Query




} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_QUERY_H__
