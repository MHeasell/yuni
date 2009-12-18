
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <yuni/core/string.h>
#include <yuni/audio/sound.h>


using namespace Yuni;
using namespace Yuni::Audio;


class LoadAndPlay : public Application::Console
{
public:
	LoadAndPlay(int argc, char* argv[])
		:Application::Console(argc, argv)
	{
		for (int i = 1; i <= argc; ++i)
			pFileNames.push_back(argv[i]);
	}

	~LoadAndPlay()
	{
	}

	virtual void onExecute()
	{
		for (std::vector<String>::const_iterator it = pFileNames.begin();
			 it != pFileNames.end(); ++it)
		{
			std::cout << "Loading file: \"" << (*it) << "\"" << std::endl;
		}
	}

private:
	std::vector<String> pFileNames;

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
