#ifndef HARF_BISIM_SRC_AUDIO_MIC_H_
#define HARF_BISIM_SRC_AUDIO_MIC_H_

#include <string>
#include <vector>

#include <AL/al.h>

#include "audio/device.h"
#include "audio/speaker.h"
#include "net/client.h"

namespace audio {

class Mic
{
 public:
  explicit Mic(Device &dev, net::Client &socket, Speaker &speaker);
  ~Mic();
  Mic(const Mic&) = delete;
  Mic& operator=(const Mic&) = delete;

  void StartCapture();
  void StopCapture();

 private:
  static void CheckForError();
  void captureLoop();

  static constexpr int RATE = 44100;
  static constexpr int BUFSIZE = 3072;
  audio::Device &device_;
  net::Client &socket_;
  audio::Speaker speaker_;
  ALCdevice *capture_device_ = nullptr;
  ALbyte *buffer_ = nullptr;
};

}

#endif  // HARF_BISIM_SRC_AUDIO_MIC_H_
