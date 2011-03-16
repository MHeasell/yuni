
#include "localforvirtual.h"
#include "../local/adapter/localforrepresentation.h"

namespace Yuni
{
namespace UI
{
namespace Adapter
{

	LocalForVirtual::LocalForVirtual()
	{}


	LocalForVirtual::LocalForVirtual(Private::UI::Local::Adapter::LocalForRepresentation* forRepresentation):
		ForVirtual(forRepresentation)
	{}


	void LocalForVirtual::sendShowWindow(IComponent::ID id) const
	{
		if (pDestination)
			pDestination->receiveShowWindow(id);
	}



} // namespace Adapter
} // namespace UI
} // namespace Yuni
