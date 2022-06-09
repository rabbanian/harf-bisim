#ifndef HARF_BISIM_SRC_AUDIO_SPEAKER_H_
#define HARF_BISIM_SRC_AUDIO_SPEAKER_H_

#include "device.h"

#include <AL/al.h>

namespace audio {

class Speaker
{
 public:
  explicit Speaker(Device& dev);
  ~Speaker();
  void Play(std::vector<std::uint8_t> data);

 private:
  static void CheckForError();

  static constexpr int RATE = 44100;
  audio::Device& device_;
  ALuint source_;
};

}  // namespace audio

#endif  // HARF_BISIM_SRC_AUDIO_SPEAKER_H_
