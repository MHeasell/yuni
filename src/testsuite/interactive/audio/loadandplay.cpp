
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <yuni/core/string.h>
#include <yuni/audio/manager.h>
#include <yuni/core/system/sleep.h>

using namespace Yuni;


class LoadAndPlay : public Application::Console
{
public:
	LoadAndPlay(int argc, char* argv[])
		:Application::Console(argc, argv)
	{
		for (int i = 1; i < argc; ++i)
			pFileNames.push_back(argv[i]);
	}

	virtual ~LoadAndPlay()
	{
	}

	virtual void onExecute()
	{
		Audio::Manager& audio = Audio::Manager::Instance();
		audio.start();
		audio.addSource("Source1", false);
		for (String::Vector::const_iterator it = pFileNames.begin();
			it != pFileNames.end(); ++it)
		{
			std::cout << "Loading file: \"" << (*it) << "\"" << std::endl;
			audio.loadSound(*it);
			audio.playSound("Source1", *it);
		}
		Yuni::Sleep(15);
		audio.stop();
	}

private:
	String::Vector pFileNames;

}; // class LoadAndPlay




int main(int argc, char* argv[])
{
	/*
	 * Yuni main loop
	 */
	LoadAndPlay app(argc, argv);
	app.onExecute();
	return app.exitCode();
}
