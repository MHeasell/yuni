#include <set>
#include "id.h"
#include "../thread/mutex.h"

namespace Yuni
{
namespace Private
{
namespace UI
{

	namespace // Anonymous
	{

		ID::Type NextID = YUNI_UI_MIN_ID;

		std::set<ID::Type> UsedIDs;

		Yuni::Mutex IDMutex;

	} // namespace Anonymous


	ID::Type ID::New()
	{
		unsigned int count = 0;
		IDMutex.lock();
		do
		{
			++NextID;
			if (YUNI_UI_INVALID_ID == NextID)
			{
				if (2 == ++count)
					throw "All UI IDs are taken !";
				continue;
			}
			if (UsedIDs.end() == UsedIDs.find(NextID))
				break;
		}
		while (true);
		UsedIDs.insert(NextID);
		IDMutex.unlock();
		return NextID;
	}



} // namespace UI
} // namespace Private
} // namespace Yuni
