
#include <iostream>
//#include <unistd.h>
#include <windows.h>
#include <winbase.h>
#include "./av.h"
#include "./openal.h"

// 3 buffers is a good amount (one playing, one ready to play, another being filled)
const unsigned int NUM_BUFFERS = 3;
// 16KB to 32KB is a good size per buffer
const unsigned int BUFFER_SIZE = 32768;

int main(unsigned int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Please provide the file name as argument!" << std::endl;
		return 1;
	}

	if (!initAL())
	{
		std::cerr << "OpenAL initialization failed!" << std::endl;
		return 1;
	}

	// Set the listener at (0,0,0)
	ALfloat listenerPos[3] = {0.0,0.0,0.0};
	ALfloat listenerVel[3] = {0.0,0.0,0.0};
	// Listener is oriented towards Y positive
	ALfloat listenerOri[6] = {0.0,0.0,1.0, 0.0,1.0,0.0};
	setALListener(listenerPos, listenerVel, listenerOri);

	// Set the OpenAL source
	ALfloat sourcePos[3] = { 0.0, 0.0, 0.0};
	ALfloat sourceVel[3] = { 0.0, 0.0, 0.0};
	ALfloat sourceDir[3] = { 0.0, 0.0, 0.0};
	ALuint source = createALSource(sourcePos, sourceVel, sourceDir, 1.0f, 1.0f, false, false);

	void* dataBuffer = malloc(BUFFER_SIZE);

	ALuint* buffers = createALBuffers(NUM_BUFFERS);

	// Open the file
	MyFile* file = openAVFile(argv[1]);
	// Get the audio stream
	MyStream* stream = getAVAudioStream(file, 0);
	if (!stream)
	{
		std::cerr << "Error opening file \"" << argv[1] << "\"" << std::endl;
		return 1;
	}

	int rate;
	int channels;
	int bits;
	if (getAVAudioInfo(stream, &rate, &channels, &bits) != 0)
	{
		closeAVFile(file);
		std::cerr << "Error getting audio info for \"" << argv[1] << "\"" << std::endl;
		return 1;
	}

	// Check the format
	ALenum format = getALFormat(bits, channels);
	if (0 == format)
	{
		closeAVFile(file);
		std::cerr << "Unhandled format (" << channels << " channels, " << bits << " bits) for \"" << argv[1] << "\"" << std::endl;
		return 1;
	}

	alSourceRewind(source);
	alSourcei(source, AL_BUFFER, 0);

	// Loop on all buffers
	for (unsigned int i = 0; i < NUM_BUFFERS; ++i)
	{
		// Make sure we get some data to give to the buffer
		int count = getAVAudioData(stream, dataBuffer, BUFFER_SIZE);
		if (count <= 0)
			break;

		// Buffer the data with OpenAL
		alBufferData(buffers[i], format, dataBuffer, count, rate);
		// Queue the buffer onto the source
		alSourceQueueBuffers(source, 1, &buffers[i]);
	}
	// Start asynchronous playback on the source
	if (!playALSource(source))
	{
		closeAVFile(file);
		std::cerr << "Error starting playback for " << argv[1] << "\"" << std::endl;
		return 1;
	}
	std::cout << "Playing " << argv[1] << " (" << bits << "-bit, " << channels << " channels, " << rate << "hz)" << std::endl;

	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	double step = -0.0001;

	// Start main loop
	while (state == AL_PLAYING)
	{
		// Move the source to and fro
		if (sourcePos[1] < -10.0f)
			step = 0.0001f;
		else if (sourcePos[1] > 10.0f)
			step = -0.0001f;
		sourcePos[1] = (float)(sourcePos[1] + step);
		moveALSource(source, sourcePos, sourceVel, sourceDir);

		// Keep looping while no buffer has finished playing
		ALint processed = 0;
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (processed == 0)
			continue;

		// A buffer has finished playing, unqueue it
		ALuint buf;
		alSourceUnqueueBuffers(source, 1, &buf);
		// Get the next data to feed the buffer
		int count = getAVAudioData(stream, dataBuffer, BUFFER_SIZE);
		if (count <= 0)
			break;

		// Buffer the data with OpenAL and queue the buffer onto the source
		alBufferData(buf, format, dataBuffer, count, rate);
		alSourceQueueBuffers(source, 1, &buf);

		// Update state
		alGetSourcei(source, AL_SOURCE_STATE, &state);
	}

	destroyALSource(source);
	destroyALBuffers(NUM_BUFFERS, buffers);
	free(dataBuffer);
	closeAVFile(file);
	closeAL();
	return 0;
}
