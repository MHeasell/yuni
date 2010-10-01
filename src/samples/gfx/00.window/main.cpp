
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/device.h>


using namespace Yuni;


class SampleApp : public Application::Gfx3D
{
public:
	SampleApp(int argc, char* argv[])
		: Application::Gfx3D(argc, argv)
	{
		Gfx::Engine* engine = Gfx::Engine::Instance();
		Gfx::Device::Ptr dev = new Gfx::Device();
		dev->type(Gfx::Device::Cairo);
		engine->applicationTitle("Sample application");
		engine->reset(dev);
	}
};

int main(int argc, char* argv[])
{
	SampleApp app(argc, argv);
	app.execute();
	return app.exitCode();
}
