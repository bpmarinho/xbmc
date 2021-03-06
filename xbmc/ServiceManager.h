/*
 *      Copyright (C) 2005-2016 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <memory>
#include "platform/Platform.h"

class CAppParamParser;

namespace ADDON {
class CAddonMgr;
class CBinaryAddonManager;
class CBinaryAddonCache;
class CVFSAddonCache;
class CServiceAddonManager;
class CRepositoryUpdater;
}

namespace ANNOUNCEMENT
{
class CAnnouncementManager;
}

namespace PVR
{
class CPVRManager;
}

namespace PLAYLIST
{
  class CPlayListPlayer;
}

class CContextMenuManager;
#ifdef HAS_PYTHON
class XBPython;
#endif
class CDataCacheCore;
class CSettings;
class CFavouritesService;
class CNetwork;
class CWinSystemBase;
class CPowerManager;
class CWeatherManager;

namespace KODI
{
namespace GAME
{
  class CControllerManager;
  class CGameServices;
}

namespace RETRO
{
  class CGUIGameRenderManager;
}
}

namespace PERIPHERALS
{
  class CPeripherals;
}

class CInputManager;
class CFileExtensionProvider;
class CPlayerCoreFactory;
class CDatabaseManager;
class CProfilesManager;
class CEventLog;

class CServiceManager
{
public:
  CServiceManager();
  ~CServiceManager();

  bool InitForTesting();
  bool InitStageOne();
  bool InitStageOnePointFive(); // Services that need our DllLoaders emu env
  bool InitStageTwo(const CAppParamParser &params);
  bool InitStageThree();
  void DeinitTesting();
  void DeinitStageThree();
  void DeinitStageTwo();
  void DeinitStageOnePointFive();
  void DeinitStageOne();
  ADDON::CAddonMgr& GetAddonMgr();
  ADDON::CBinaryAddonManager& GetBinaryAddonManager();
  ADDON::CBinaryAddonCache& GetBinaryAddonCache();
  ADDON::CVFSAddonCache& GetVFSAddonCache();
  ADDON::CServiceAddonManager& GetServiceAddons();
  ADDON::CRepositoryUpdater& GetRepositoryUpdater();
  ANNOUNCEMENT::CAnnouncementManager& GetAnnouncementManager();
  CNetwork& GetNetwork();
#ifdef HAS_PYTHON
  XBPython& GetXBPython();
#endif
  PVR::CPVRManager& GetPVRManager();
  CContextMenuManager& GetContextMenuManager();
  CDataCacheCore& GetDataCacheCore();
  /**\brief Get the platform object. This is save to be called after Init1() was called
   */
  CPlatform& GetPlatform();
  KODI::GAME::CControllerManager& GetGameControllerManager();
  KODI::GAME::CGameServices& GetGameServices();
  KODI::RETRO::CGUIGameRenderManager& GetGameRenderManager();
  PERIPHERALS::CPeripherals& GetPeripherals();

  PLAYLIST::CPlayListPlayer& GetPlaylistPlayer();
  int init_level = 0;

  CSettings& GetSettings();
  CFavouritesService& GetFavouritesService();
  CInputManager &GetInputManager();
  CFileExtensionProvider &GetFileExtensionProvider();

  CPowerManager &GetPowerManager();

  CWeatherManager &GetWeatherManager();

  CPlayerCoreFactory &GetPlayerCoreFactory();

  CDatabaseManager &GetDatabaseManager();

  CProfilesManager &GetProfileManager();

  CEventLog &GetEventLog();

protected:
  struct delete_dataCacheCore
  {
    void operator()(CDataCacheCore *p) const;
  };

  struct delete_contextMenuManager
  {
    void operator()(CContextMenuManager *p) const;
  };

  struct delete_favouritesService
  {
    void operator()(CFavouritesService *p) const;
  };

  //! \brief Initialize appropriate networking instance.
  CNetwork* SetupNetwork() const;

  std::unique_ptr<ADDON::CAddonMgr> m_addonMgr;
  std::unique_ptr<ADDON::CBinaryAddonManager> m_binaryAddonManager;
  std::unique_ptr<ADDON::CBinaryAddonCache> m_binaryAddonCache;
  std::unique_ptr<ADDON::CVFSAddonCache> m_vfsAddonCache;
  std::unique_ptr<ADDON::CServiceAddonManager> m_serviceAddons;
  std::unique_ptr<ADDON::CRepositoryUpdater> m_repositoryUpdater;
  std::unique_ptr<ANNOUNCEMENT::CAnnouncementManager> m_announcementManager;
#ifdef HAS_PYTHON
  std::unique_ptr<XBPython> m_XBPython;
#endif
  std::unique_ptr<PVR::CPVRManager> m_PVRManager;
  std::unique_ptr<CContextMenuManager, delete_contextMenuManager> m_contextMenuManager;
  std::unique_ptr<CDataCacheCore, delete_dataCacheCore> m_dataCacheCore;
  std::unique_ptr<CPlatform> m_Platform;
  std::unique_ptr<PLAYLIST::CPlayListPlayer> m_playlistPlayer;
  std::unique_ptr<CSettings> m_settings;
  std::unique_ptr<KODI::GAME::CControllerManager> m_gameControllerManager;
  std::unique_ptr<KODI::GAME::CGameServices> m_gameServices;
  std::unique_ptr<KODI::RETRO::CGUIGameRenderManager> m_gameRenderManager;
  std::unique_ptr<PERIPHERALS::CPeripherals> m_peripherals;
  std::unique_ptr<CFavouritesService, delete_favouritesService> m_favouritesService;
  std::unique_ptr<CInputManager> m_inputManager;
  std::unique_ptr<CFileExtensionProvider> m_fileExtensionProvider;
  std::unique_ptr<CNetwork> m_network;
  std::unique_ptr<CPowerManager> m_powerManager;
  std::unique_ptr<CWeatherManager> m_weatherManager;
  std::unique_ptr<CPlayerCoreFactory> m_playerCoreFactory;
  std::unique_ptr<CDatabaseManager> m_databaseManager;
  std::unique_ptr<CProfilesManager> m_profileManager;
};
