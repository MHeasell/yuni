
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <yuni/core/string.h>
#include <yuni/audio/manager.h>
#include <yuni/core/system/sleep.h>

using namespace Yuni;


class MovingSource : public Application::Console
{
public:
	MovingSource(int argc, char* argv[])
		:Application::Console(argc, argv), pFileName(argv[1])
	{
		pAudio.start();
	}

	virtual ~MovingSource()
	{
		pAudio.stop();
	}

	virtual void onExecute()
	{
		const float LIMIT = 20.0f;

		String sourceName("Source");
		if (!pAudio.addSource(sourceName, false))
		{
			std::cerr << "Source creation failed !" << std::endl;
			return;
		}
		pAudio.loadSound(pFileName);
		pAudio.playSound(sourceName, pFileName);
		Gfx::Point3D<> position;
		bool inverse = false;
		position.y = -LIMIT;
		pAudio.moveSource(sourceName, position);
		for (int i = 0; i < 2000; ++i)
		{
			Yuni::SleepMilliSeconds(100);
			position.y += 1.0f * (inverse ? -1.0f : 1.0f);
			if (!inverse && position.y > LIMIT)
				inverse = true;
			else if (inverse && position.y < -LIMIT)
				inverse = false;
			pAudio.moveSource(sourceName, position);
		}
	}

private:
	String pFileName;
	Audio::Manager pAudio;

}; // class MovingSource




int main(int argc, char* argv[])
{
	if (argc < 2)
		return false;

	/*
	 * Yuni main loop
	 */
	MovingSource app(argc, argv);
	app.onExecute();
	return app.exitCode();
}