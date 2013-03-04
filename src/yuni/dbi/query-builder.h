#ifndef __YUNI_DBI_QUERY_BUILDER_H__
# define __YUNI_DBI_QUERY_BUILDER_H__

# include "../yuni.h"
# include "../core/string.h"
# include "../core/noncopyable.h"
# include "adapter/entries.h"


namespace Yuni
{
namespace DBI
{

	class QueryBuilder final : private Yuni::NonCopyable<QueryBuilder>
	{
	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		explicit QueryBuilder(::yn_dbi_adapter& adapter, const AnyString& stmt);
		/*!
		** \brief Move constructor
		*/
		QueryBuilder(QueryBuilder&& other);
		//! Destructor
		~QueryBuilder();
		//@}


		//! \name Bindings
		//@{
		//! Bind a sepcific parameter as a string
		QueryBuilder& bind(uint index, const AnyString& value);
		//! Bind a sepcific parameter as a bool
		QueryBuilder& bind(uint index, bool value);
		//! Bind a sepcific parameter as a sint32
		QueryBuilder& bind(uint index, sint32 value);
		//! Bind a sepcific parameter as a sint64
		QueryBuilder& bind(uint index, sint64 value);
		//! Bind a sepcific parameter as a double
		QueryBuilder& bind(uint index, double value);
		//! Bind a sepcific parameter as a null
		QueryBuilder& bind(uint index, const NullPtr&);

		//! Convenient method for binding the first 1 parameter
		template<class A1>
		QueryBuilder& map(const A1& a1);
		//! Convenient method for binding the first 2 parameters at once
		template<class A1, class A2>
		QueryBuilder& map(const A1& a1, const A2& a2);
		//! Convenient method for binding the first 3 parameters at once
		template<class A1, class A2, class A3>
		QueryBuilder& map(const A1& a1, const A2& a2, const A3& a3);
		//! Convenient method for binding the first 4 parameters at once
		template<class A1, class A2, class A3, class A4>
		QueryBuilder& map(const A1& a1, const A2& a2, const A3& a3, const A4& a4);
		//@}


		//! \name Execution
		//@{
		/*!
		** \brief Execute the query but discard the results
		*/
		DBI::Error perform();

		/*!
		** \brief Execute the query
		*/
		DBI::Error execute();
		//@}


		//! \name Row management
		//@{
		/*!
		** \brief Iterate over all rows in the resultset
		*/
		template<class CallbackT> DBI::Error each(const CallbackT& callback);
		/*!
		** \brief Go to the next row
		*/
		DBI::Error next();

		/*!
		** \brief Go to the previous row
		*/
		DBI::Error previous();

		/*!
		** \brief Move the cursor to a specific row index in the result set
		*/
		bool moveTo(uint64 rowindex);

		/*!
		** \brief Get if the result set is empty
		*/
		bool empty() const;

		/*!
		** \brief Get the number of rows in the result set
		*/
		uint64 rowCount() const;
		//@}


	private:
		//! Alias to the current channel
		::yn_dbi_adapter& pAdapter;
		//! Opaque data for the current query
		void* pHandle;
		//! Row count
		uint64 pRowCount;

	}; // class QueryBuilder





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_QUERY_BUILDER_H__
