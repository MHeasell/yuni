#ifndef __YUNI_PRIVATE_UI_ID_H__
# define __YUNI_PRIVATE_UI_ID_H__

# include "../yuni.h"


# define YUNI_UI_INVALID_ID  -9223372036854775807
# define YUNI_UI_MIN_ID      -9223372036854775806
# define YUNI_UI_MAX_ID      +9223372036854775808


namespace Yuni
{
namespace Private
{
namespace UI
{

	/*!
	** \brief Component identifier management
	*/
	class ID
	{
	public:
		typedef sint64  Type;

	public:
		//! Get a new free identifier
		static Type New();

	private:
		ID();
		ID(const ID&);

	};



} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_UI_ID_H__
