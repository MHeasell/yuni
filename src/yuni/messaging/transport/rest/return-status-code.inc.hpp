
namespace Yuni
{
namespace Messaging
{
namespace Transport
{
namespace REST
{

	namespace // anonymous
	{

		template<uint ErrorIndex>
		struct HttpErrorCode
		{
			static inline const char* Message() { return "HTTP/1.1 500 Error\r\n\r\nInternal error" ; }
			enum {size = 36};
		};


		template<> struct HttpErrorCode<400>
		{
			static inline const char* Message() { return "HTTP/1.1 400 Error\r\n\r\nBad request"; }
			enum {size = 33};
		};

		template<> struct HttpErrorCode<401>
		{
			// If the request already included Authorization credentials, then
			// the 401 response indicates that authorization has been refused
			// for those credentials.
			static inline const char* Message() { return "HTTP/1.1 401 Error\r\n\r\nUnauthorized"; }
			enum {size = 34};
		};

		template<> struct HttpErrorCode<403>
		{
			// The server understood the request, but is refusing to fulfill it.
			static inline const char* Message() { return "HTTP/1.1 403 Error\r\n\r\nForbidden"; }
			enum {size = 31};
		};

		template<> struct HttpErrorCode<404>
		{
			static inline const char* Message() { return "HTTP/1.1 404 Error\r\n\r\nNot found"; }
			enum {size = 31};
		};

	} // anonymous





	template<uint ErrorIndex> static inline void* HTTPErrorCode(struct mg_connection* conn)
	{
		mg_write(conn, HttpErrorCode<ErrorIndex>::Message(), HttpErrorCode<ErrorIndex>::size);
		return (void*)"ok"; // the request has been managed
	}




} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Yuni

