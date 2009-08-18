#ifndef __YUNI_GFX_API_H__
# define __YUNI_GFX_API_H__

namespace Yuni
{
namespace Gfx
{
namespace Api
{
	/*!
	** \brief Interface defining the minimum a graphics API should offer
	**
	** This is mainly a way to define a common interface to OpenGL and DirectX
	*/
	class IGfxAPI
	{
	protected:
		IGfxAPI() {}
		virtual ~IGfxAPI() {}
	private:
		IGfxAPI(const IGfxAPI&);

	public:
		virtual bool initialize() = 0;
		virtual void release() = 0;
		virtual void resize(unsigned int width, unsigned int height) = 0;
	};

} // Api
} // Gfx
} // Yuni

#endif // __YUNI_GFX_API_H__
