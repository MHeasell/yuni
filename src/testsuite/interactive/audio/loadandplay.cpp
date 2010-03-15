
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
		:Application::Console(argc, argv), audio(Audio::Manager::Instance())
	{
		for (int i = 1; i < argc; ++i)
			pFileNames.push_back(argv[i]);
		if (!pFileNames.empty())
			audio.start();
	}

	virtual ~LoadAndPlay()
	{
		if (!pFileNames.empty())
			audio.stop();
	}

	virtual void onExecute()
	{
		audio.addSource("Source1", false);
		for (String::Vector::const_iterator it = pFileNames.begin();
			it != pFileNames.end(); ++it)
		{
			std::cout << "Loading file: \"" << (*it) << "\"" << std::endl;
			audio.loadSound(*it);
			audio.playSound("Source1", *it);
		}
		Yuni::Sleep(10);
	}

private:
	String::Vector pFileNames;
	Audio::Manager& audio;

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
