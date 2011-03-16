
#include "localforrepresentation.h"
#include "../../adapter/localforvirtual.h"

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace Adapter
{

	LocalForRepresentation::LocalForRepresentation()
	{}


	LocalForRepresentation::LocalForRepresentation(Yuni::UI::Adapter::LocalForVirtual* forVirtual):
		ForRepresentation(forVirtual)
	{}


	void LocalForRepresentation::receiveShowWindow(Yuni::UI::IComponent::ID id) const
	{
		// TODO : get the window, ask it to show
	}


} // namespace Adapter
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
