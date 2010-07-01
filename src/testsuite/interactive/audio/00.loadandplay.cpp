
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
			String emitterName("Emitter ");
			emitterName << i++;
			if (!audio.emitter.add(emitterName))
			{
				std::cerr << "Emitter creation failed !" << std::endl;
				return;
			}
			if (!audio.bank.load(*it))
				return;
			audio.emitter.attach(emitterName, *it);
			audio.emitter.play(emitterName);
		}
		sint64 elapsed;
		for (int i = 0; i < 3000; ++i)
		{
			Yuni::SleepMilliSeconds(100);

			sint64 newTime = audio.emitter.elapsedTime("Emitter 0");
			// Only update if different
			if (newTime != elapsed)
			{
				elapsed = newTime;
				std::cout << (elapsed / 60) << ":";
				if (elapsed % 60 < 10)
					std::cout << 0;
				std::cout << (elapsed % 60) << std::endl;
			}
		}
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
