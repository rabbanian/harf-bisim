#ifndef HARF_BISIM_SRC_AUDIO_DEVICE_H_
#define HARF_BISIM_SRC_AUDIO_DEVICE_H_

#include <string>
#include <vector>

struct ALCcontext;
struct ALCdevice;

namespace audio {

class Device
{
 public:
  Device();
  ~Device();

  std::string GetDeviceName();
  std::vector<std::string> GetAllDeviceName();

 private:
  void CheckForError();

  std::string active_device_;
  ALCcontext *context_ = nullptr;
  ALCdevice *device_ = nullptr;
};

}  // namespace audio

#endif  // HARF_BISIM_SRC_AUDIO_DEVICE_H_
