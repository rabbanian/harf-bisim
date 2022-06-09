#include "mic.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <cstring>
#include <iostream>

using namespace audio;

Mic::Mic(Device &dev, net::Client &socket, Speaker &speaker)
    : device_(dev), socket_(socket), speaker_(speaker)
{
  capture_device_ = alcCaptureOpenDevice(device_.GetDeviceName().c_str(), RATE,
                                         AL_FORMAT_STEREO16, 1102);
  if (!capture_device_) {
    CheckForError();
  }

  buffer_ = new ALbyte[BUFSIZE];
  capture_thread_ = std::thread(std::bind(&Mic::CaptureLoop, this));
}

Mic::~Mic()
{
  alcCaptureCloseDevice(capture_device_);
  delete[] buffer_;
  done_ = true;
  cv_.notify_all();
  capture_thread_.join();
}

void Mic::CheckForError()
{
  static ALCenum error;

  error = alGetError();
  if (error != AL_NO_ERROR) {
    std::cerr << "OpenAL error in mic" << std::endl;
  }
}

void Mic::StartCapture()
{
  alcCaptureStart(capture_device_);
  started_ = true;
  cv_.notify_all();
}

void Mic::StopCapture()
{
  alcCaptureStop(capture_device_);
  started_ = false;
}

void Mic::CaptureLoop()
{
  while (!done_) {
    while (!started_ && !done_) {
      std::unique_lock lock(mx_);
      cv_.wait(lock);
    }
    if (done_) break;

    ALint sample;
    alcGetIntegerv(capture_device_, ALC_CAPTURE_SAMPLES,
                   (ALCsizei)sizeof(ALint), &sample);
    CheckForError();
    if (sample > BUFSIZE) {
      std::cerr << "Buffer size is small" << std::endl;
      return;
    }
    alcCaptureSamples(capture_device_, (ALCvoid *)buffer_, sample);
    CheckForError();
    std::vector<std::uint8_t> data;
    data.resize(BUFSIZE);
    data.assign(buffer_, buffer_ + BUFSIZE - 1);
    speaker_.Play(data);
    //    socket_.Send(net::Packet(data));
  }
}
