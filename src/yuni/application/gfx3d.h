#ifndef __YUNI_APPLICATION_GFX_3D_H__
# define __YUNI_APPLICATION_GFX_3D_H__

# include "abstract.h"
# include "../gfx/device.h"
# include "../misc/event.h"
# include "../gfx/engine.h"



namespace Yuni
{
namespace Application
{


	/*!
	** \brief 3D Application
	*/
	class Gfx3D : public Application::Abstract, public Event::Receiver
	{
	public:
		/*!
		** \brief Get the global instance of the console application
		*/
		static Gfx3D* Instance() {return dynamic_cast<Gfx3D*>(Abstract::Instance());}

	public:
		//! \name Constructor & Destructor
		//@{
		
		/*!
		** \brief Constructor
		** \param argc The number of arguments
		** \param argv All arguments
		*/
		Gfx3D(int argc, char* argv[]);

		//! Destructor
		virtual ~Gfx3D();
		
		//@}

		//! \name Application title
		//@{
		//! Get the application title
		String title() const {return Gfx::Engine::Instance()->applicationTitle();}
		//! Set the application title
		void title(const String& t) {Gfx::Engine::Instance()->applicationTitle(t);}
		//@}


		//! \name Events
		//@{

		/*!
		** \brief Event: Before the 3D Device is created
		*/
		virtual void onBeforeCreateDevice() {}

		/*!
		** \brief Event: After the 3D Device has been created
		**
		** \param success True if the creation of the 3D device has succeeded
		*/
		virtual void onAfterCreateDevice(const bool /* success */) {}
		//@}

		virtual bool onPreExecute() {return true;}

		void execute();

		virtual void onExecute() {}

	public:
		//! Informations about the 3D device
		Gfx::Device device;

	}; // class Application::Gfx3D



} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_GFX_3D_H__
