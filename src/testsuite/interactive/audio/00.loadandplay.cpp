
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <yuni/core/string.h>
#include <yuni/audio/queueservice.h>
#include <yuni/core/system/sleep.h>

using namespace Yuni;


class LoadAndPlay : public Application::Console
{
public:
	LoadAndPlay(int argc, char* argv[])
		:Application::Console(argc, argv), audio()
	{
		for (int i = 1; i < argc; ++i)
		{
			pFileNames.push_back(argv[i]);
		}
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
		String::Vector::const_iterator end = pFileNames.end();
		unsigned int i = 0;
		for (String::Vector::const_iterator it = pFileNames.begin(); it != end; ++it)
		{
			String sourceName("Source");
			sourceName << i++;
			if (!audio.addSource(sourceName, false))
			{
				std::cerr << "Source creation failed !" << std::endl;
				return;
			}
			audio.loadSound(*it);
			audio.playSound(sourceName, *it);
		}
		Yuni::Sleep(3);
	}

private:
	String::Vector pFileNames;
	Audio::QueueService audio;

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
