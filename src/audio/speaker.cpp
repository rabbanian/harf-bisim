#include "speaker.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

using namespace audio;

Speaker::Speaker(audio::Device& dev) : device_(dev)
{
  /* Make a OpenAL Listener */
  ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
  alListener3f(AL_POSITION, 0, 0, 1.0f);
  CheckForError();
  alListener3f(AL_VELOCITY, 0, 0, 0);
  CheckForError();
  alListenerfv(AL_ORIENTATION, listenerOri);
  CheckForError();

  /* Make a OpenAL Source */
  alGenSources((ALuint)1, &source_);
  CheckForError();
  alSourcef(source_, AL_PITCH, 1);
  CheckForError();
  alSourcef(source_, AL_GAIN, 1);
  CheckForError();
  alSource3f(source_, AL_POSITION, 0, 0, 0);
  CheckForError();
  alSource3f(source_, AL_VELOCITY, 0, 0, 0);
  CheckForError();
  alSourcei(source_, AL_LOOPING, AL_FALSE);
  CheckForError();
}

void Speaker::CheckForError()
{
  static ALCenum error;

  error = alGetError();
  if (error != AL_NO_ERROR) {
    std::cerr << "OpenAL error in speaker" << std::endl;
  }
}

void Speaker::Play(std::vector<std::uint8_t> data)
{
  /* Create a new buffer */
  ALuint buffer;
  alGenBuffers((ALuint)1, &buffer);
  CheckForError();

  /* Decode if needed (which is not) */
  alBufferData(buffer, AL_FORMAT_STEREO16, data.data(), data.size(), RATE);
  CheckForError();

  /* Bind it and play it */
//  alSourceQueueBuffers(source_, 1, (ALuint*)&buffer);
  alSourcei(source_, AL_BUFFER, (ALint)buffer);

  alSourcePlay(source_);
  int sourceState = AL_PLAYING;
  do {
    alGetSourcei(source_, AL_SOURCE_STATE, &sourceState);
  } while(sourceState == AL_PLAYING);
  alDeleteBuffers((ALuint)1, &buffer);
}

Speaker::~Speaker()
{
  alDeleteSources(1, &source_);
//  alDeleteBuffers(1, &buffer_);
}
