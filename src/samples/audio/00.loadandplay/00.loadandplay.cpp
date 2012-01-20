
#include <vector>
#include <yuni/yuni.h>
#include <yuni/core/string.h>
#include <yuni/core/system/suspend.h>
#include <yuni/audio/queueservice.h>

using namespace Yuni;


class LoadAndPlay
{
public:
	LoadAndPlay(int argc, char* argv[])
	{
		for (int i = 1; i < argc; ++i)
		{
			pFilenames.push_back(argv[i]);
		}
		if (!pFilenames.empty())
			audio.start();
	}

	~LoadAndPlay()
	{
		if (!pFilenames.empty())
			audio.stop();
	}

	void onExecute()
	{
		if (!audio.running())
			return;

		String emitterName;

		uint i = 0;
		const String::Vector::const_iterator end = pFilenames.end();
		for (String::Vector::const_iterator it = pFilenames.begin(); it != end; ++it)
		{
			// Load sound file
			if (!audio.bank.load(*it))
				return;

			// Create emitter
			emitterName.clear() << "Emitter " << i++;
			if (!audio.emitter.add(emitterName))
			{
				std::cerr << "Emitter creation failed !" << std::endl;
				return;
			}

			// Attach the emitter to the buffer
			audio.emitter.attach(emitterName, *it);
			// Start playback on the emitter
			audio.emitter.play(emitterName);

			Yuni::SuspendMilliSeconds(1000);
			// Get stream duration
			unsigned int duration = audio.bank.duration(*it);
			std::cout << "Sound duration: ";
			writeTime(duration);
			std::cout << std::endl;

		}
		sint64 elapsed = 0;
		for (unsigned int i = 0; i < 3000; ++i)
		{
			Yuni::SuspendMilliSeconds(100);

			// Get elapsed playback time
			sint64 newTime = audio.emitter.elapsedTime("Emitter 0");
			// Only update if different
			if (newTime != elapsed)
			{
				elapsed = newTime;
				std::cout << "Elapsed time: ";
				writeTime(elapsed);
				std::cout << std::endl;
			}
		}
	}

private:

	template<typename T>
	void writeTime(T timeInSeconds)
	{
		std::cout << (timeInSeconds / 60) << ":";
		if (timeInSeconds % 60 < 10)
			std::cout << 0;
		std::cout << (timeInSeconds % 60);
	}


private:
	String::Vector pFilenames;
	Audio::QueueService audio;

}; // class LoadAndPlay




int main(int argc, char* argv[])
{

	LoadAndPlay app(argc, argv);
	app.onExecute();
	return 0;
}

