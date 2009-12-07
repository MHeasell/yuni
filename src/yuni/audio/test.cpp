
#include <yuni/yuni.h>
#include <yuni/core/logs.h>
#include <yuni/audio/queueservice.h>
#include <yuni/audio/music.h>
#include <yuni/audio/sound.h>
#include <yuni/audio/units.h>
#include <yuni/audio/unit/instrument/flute.h>
#include <yuni/audio/unit/bandpassfilter/low.h>
#include <yuni/audio/unit/distorsion.h>
#include <yuni/audio/ambiance/fading.h>


using namespace Yuni;


// Logging
Logs::Logger<> logs;


// Callbacks

static void onStartPlayback(Audio::QueueService& queue, Audio::ISource& source)
{
	logs.debug() << "[audio]  . Starting " << source.uri();
}

static void onStopPlayback(Audio::QueueService& queue, Audio::ISource& source)
{
	logs.debug() << "[audio]  . Stopping " << source.uri();
}


static void startThePlaylist(Audio::Playlist& playlist)
{
	logs.info() << "[audio] Playlist: Start";
	playlist.shuffle();
}


static void endOfThePlaylist(Audio::Playlist& playlist)
{
	// Play the music again !
	logs.info() << "[audio] Playlist: End";
	playlist.play();
}






int main()
{
	logs.checkpoint() << "Yuni Sample: Basic Audio usage with OpenAL";
	# ifdef YUNI_OS_32
	logs.info() << " :: Built for 32-bit architecture";
	# endif
	# ifdef YUNI_OS_64
	logs.info() << " :: Built for 64-bit architecture";
	# endif
	// Empty line
	logs.info();


	// Retrieve the list of all audio devices
	Audio::Device::List devices;
	devices.update();
	if (devices.empty())
	{
		logs.fatal() << "No audio device found. Aborting.";
		return 1;
	}

	for (Audio::Device::List::const_iterator i = devices.begin(); i != devices.end(); ++i)
		logs.info() << "[audio] Detected device: " << *i;

	// The Audio
	Audio::QueueService::Ptr queue = new Audio::QueueService();
	// Selecting the audio device
	queue->switchToDevice(devices.begin());
	if (!queue->valid())
	{
		logs.fatal() << "The Audio Queue service is not ready.";
		return 0;
	}

	// Volumes
	queue->masterVolume(90. /* % */);
	queue->defaultMusicVolume(60.);  // 60% from 90%
	queue->defaultSoundVolume(100.); // 100.% from 90%
	// Events
	if (Logs::Verbosity::Debug::enabled)
	{
		// Only in Debug mode, for performance reasons
		// Event<void (Audio::QueueService&, Audio::ISource&)> event;
		queue->onStartPlayback.connect(&onStartPlayback);
		queue->onStopPlayback.connect(&onStartPlayback);
	}
	// Starting the thread, preparing the queues...
	logs.info() << "[audio] Starting the Queue Service";
	queue->start();

	// Music
	Audio::Music::Ptr ambiance = new Audio::Music();
	// attaching the playback
	queue->attachPlayback(ambiance);
	ambiance->loadFromFile("/somewhere/audio.ogg");
	// ambiance->play();

	// Playlist
	logs.info() << "[audio] Loading music";
	Audio::Playlist::Ptr playlist = new Audio::Playlist();
	queue->attachPlayback(playlist);
	*playlist += ambiance;
	*playlist += new Audio::Music("/somewhere/audio2.ogg");
	*playlist += new Audio::Music("/somewhere/audio3.ogg");
	// Event<void (Audio::Playlist&)> event;
	playlist->onStartPlaylist.connect(&startThePlaylist);
	playlist->onEndPlaylist.connect(&endOfThePlaylist);
	playlist->play();


	logs.info() << "[audio] Loading 'explosion'";
	Audio::Sound::Ptr explosion = new Audio::Sound(queue);
	explosion->loadFromFile("file:///path/to/explosion.mp3");
	explosion->prepare();
	explosion->name("/yuni/explosion");
	// TF1 mode !
	explosion->volume(120. /*%*/);

	logs.info() << "[audio] Loading 'engine', with units (sound effects)";
	Audio::Sound::Ptr engine = new Audio::Sound(queue, "/path/to/engine.mp3");
	engine->unitChain += new Audio::Unit::Instrument::Flute();
	engine->unitChain += new Audio::Unit::BandpassFilter::LowPass();
	engine->unitChain += new Audio::Unit::Distorsion();
	engine->prepare();

	logs.info();
	logs.checkpoint() << "Entering into the main loop";
	int i = 20;
	while (--i)
	{
		// 1 second
		Sleep(1);

		// 3D position
		explosion->move(1., 2.3, 4.3);
		explosion->orientation(2., 3., 4.);
		explosion->speed(7.2);
		explosion->play();
		// A direct method would be :
		// explosion->play(1., 2.3, 4.3, 2., 3., 4., 7.2);

		// Another way to do it : (ran from a script for example)
		// queue->play("/yuni/explosion");
		// queue->play("/yuni/explosion", 1., 2.3, 4.3, 2., 3., 4., 7.2);
	}

	logs.info();
	logs.checkpoint() << "Gracefully exiting...";
	Audio::AmbianceEffect::Fading::Ptr fading = new Audio::AmbianceEffect::Fading(queue);
	fading->speed(5 /*%*/, 50 /*ms*/); // -5% everay 50ms
	// The fading is actually executed in the main loop of the queue
	fading->start();
	// Wait for the end of the process
	fading->wait();

	// Stopping the Audio Queue Service
	logs.info() << "[audio] Stopping the Queue Service";
	queue->stop();
	logs.info() << "Done.";

	return 0;
}
