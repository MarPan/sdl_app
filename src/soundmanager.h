#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <map>
#include "multiplatformSDL.h"

#define theSoundManager SoundManager::getInstance()

enum class SoundType
{
  MUSIC = 0,
  SFX = 1
};

class SoundManager
{
public:
  static SoundManager& getInstance();
  bool load(std::string fileName, std::string id, SoundType type);
  void playSound(std::string id, int loop);
  void playMusic(std::string id, int loop);

private:
  std::map<std::string, Mix_Chunk*> m_sfxs;
  std::map<std::string, Mix_Music*> m_music;

  SoundManager();
  ~SoundManager();
  SoundManager(const SoundManager&);
  SoundManager &operator=(const SoundManager&);
};
#endif // SOUNDMANAGER_H
