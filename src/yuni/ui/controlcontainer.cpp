
# include "controlcontainer.h"


namespace Yuni
{
namespace UI
{


	void IControlContainer::resizeWL(float& newWidth, float& newHeight)
	{
		IControl::resizeWL(newWidth, newHeight);
		// TODO : Resize children to fit the size of the container
	}



} // namespace UI
} // namespace Yuni
