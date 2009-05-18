
#include "uri.private.h"


namespace Yuni
{
namespace Private
{
namespace Uri
{


	Informations::Informations()
		:port(0), isValid(false)
	{}


	Informations::Informations(const Informations& rhs)
		:scheme(rhs.scheme), user(rhs.user), password(rhs.password), server(rhs.server),
		port(rhs.port), path(rhs.path), query(rhs.query), fragment(rhs.fragment),
		isValid(rhs.isValid)
	{}


	Informations::~Informations()
	{}



	void Informations::clear()
	{
		scheme.clear();
		server.clear();
		user.clear();
		password.clear();
		port = 0;
		path.clear();
		query.clear();
		fragment.clear();
		isValid = false;
	}


	void Informations::assign(const Informations& rhs)
	{
		scheme   = rhs.scheme;
		server   = rhs.server;
		user     = rhs.user;
		port     = rhs.port;
		path     = rhs.path;
		query    = rhs.query;
		fragment = rhs.fragment;
		isValid  = rhs.isValid;
	}




	String Informations::toString() const
	{
		if (isValid)
		{
			String s;
			if (!scheme.empty())
				s << scheme << ":";
			if (!server.empty())
			{
				if (!scheme.empty())
					s << "//";
				if (!user.empty())
				{
					s << user;
					if (!password.empty())
						s << ":" << password;
					s << "@";
				}
				s << server;
				if (port > 0)
					s << ":" << port;
			}
			else
			{
				if (!scheme.empty() && "file" == scheme)
					s << "//";
			}
			s << path;
			if (!query.empty())
				s << "?" << query;
			if (!fragment.empty())
				s << "#" << fragment;
			return s;
		}
		return String();
	}




	bool Informations::isEqualsTo(const Informations& rhs) const
	{
		return isValid && rhs.isValid && scheme == rhs.scheme
			&& path == rhs.path && server == rhs.server && port == rhs.port
			&& query == rhs.query && fragment == rhs.fragment
			&& user == rhs.user && password == rhs.password;
	}




} // namespace Uri
} // namespace Private
} // namespace Yuni

