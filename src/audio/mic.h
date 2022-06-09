#ifndef HARF_BISIM_SRC_AUDIO_MIC_H_
#define HARF_BISIM_SRC_AUDIO_MIC_H_

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

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
  void CaptureLoop();

  std::thread capture_thread_;
  std::condition_variable cv_;
  std::mutex mx_;
  std::atomic_bool done_ = false;
  std::atomic_bool started_ = false;
  static constexpr int RATE = 44100;
  static constexpr int BUFSIZE = 3072;

  audio::Device &device_;
  audio::Speaker speaker_;
  net::Client &socket_;

  ALCdevice *capture_device_ = nullptr;
  ALbyte *buffer_ = nullptr;
};

}

#endif  // HARF_BISIM_SRC_AUDIO_MIC_H_
