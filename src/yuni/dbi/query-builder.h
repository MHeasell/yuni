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

	class PreparedStatement final : private Yuni::NonCopyable<PreparedStatement>
	{
	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		PreparedStatement(::yn_dbi_adapter& adapter, void* handle);
		/*!
		** \brief Move constructor
		*/
		PreparedStatement(PreparedStatement&& other);
		//! Destructor
		~PreparedStatement();
		//@}


		//! \name Bindings
		//@{
		//! Bind a sepcific parameter as a string
		PreparedStatement& bind(uint index, const AnyString& value);
		//! Bind a sepcific parameter as a bool
		PreparedStatement& bind(uint index, bool value);
		//! Bind a sepcific parameter as a sint32
		PreparedStatement& bind(uint index, sint32 value);
		//! Bind a sepcific parameter as a sint64
		PreparedStatement& bind(uint index, sint64 value);
		//! Bind a sepcific parameter as a double
		PreparedStatement& bind(uint index, double value);
		//! Bind a sepcific parameter as a null
		PreparedStatement& bind(uint index, const NullPtr&);

		//! Convenient method for binding the first 1 parameter
		template<class A1>
		PreparedStatement& map(const A1& a1);
		//! Convenient method for binding the first 2 parameters at once
		template<class A1, class A2>
		PreparedStatement& map(const A1& a1, const A2& a2);
		//! Convenient method for binding the first 3 parameters at once
		template<class A1, class A2, class A3>
		PreparedStatement& map(const A1& a1, const A2& a2, const A3& a3);
		//! Convenient method for binding the first 4 parameters at once
		template<class A1, class A2, class A3, class A4>
		PreparedStatement& map(const A1& a1, const A2& a2, const A3& a3, const A4& a4);
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


		//! \name Resultset
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
		DBI::Error moveTo(uint64 rowindex);

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
		// \internal This reference can be null and must never be called if pHandle is null
		::yn_dbi_adapter& pAdapter;
		//! Opaque data for the current query
		void* pHandle;
		//! Row count
		uint64 pRowCount;

	}; // class PreparedStatement





} // namespace DBI
} // namespace Yuni

# include "query-builder.hxx"

#endif // __YUNI_DBI_QUERY_BUILDER_H__
