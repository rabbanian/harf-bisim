#include "device.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <cstring>
#include <iostream>

using namespace audio;

Device::Device()
{
  /* Reset OpenAL error stack */
  alGetError();

  /* Choose a Device */
  active_device_ = GetAllDeviceName()[0];
  device_ = alcOpenDevice(active_device_.c_str());
  if (!device_) {
    CheckForError();
  }

  context_ = alcCreateContext(device_, nullptr);
  if (!context_) {
      CheckForError();
  }

  if (!alcMakeContextCurrent(context_)) {
    CheckForError();
  }
}

Device::~Device()
{
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context_);
  alcCloseDevice(device_);
}

std::vector<std::string> Device::GetAllDeviceName()
{
  std::vector<std::string> result;

  const ALCchar *devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
  const ALCchar *device = devices, *next = devices + 1;
  std::size_t len = 0;

  while (device && *device != '\0' && next && *next != '\0') {
    std::string dev_name(device);
    result.emplace_back(dev_name);

    len = std::strlen(device);
    device += (len + 1);
    next += (len + 2);
  }

  return result;
}

void Device::CheckForError()
{
  static ALCenum error;

  error = alGetError();
  if (error != AL_NO_ERROR) {
    std::cerr << "OpenAL error in device" << std::endl;
  }
}

std::string Device::GetDeviceName() { return active_device_; }
