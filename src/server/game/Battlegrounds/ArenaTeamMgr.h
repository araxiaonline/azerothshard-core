/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _ARENATEAMMGR_H
#define _ARENATEAMMGR_H

#include "ArenaTeam.h"

#define MAX_ARENA_TEAM_ID 0xFFF00000
#define MAX_TEMP_ARENA_TEAM_ID 0xFFFFFFFE

class ArenaTeamMgr
{
    friend class ACE_Singleton<ArenaTeamMgr, ACE_Null_Mutex>;
    ArenaTeamMgr();
    ~ArenaTeamMgr();

public:
    typedef std::unordered_map<uint32, ArenaTeam*> ArenaTeamContainer;

    ArenaTeam* GetArenaTeamById(uint32 arenaTeamId) const;
    ArenaTeam* GetArenaTeamByName(std::string const& arenaTeamName) const;
    ArenaTeam* GetArenaTeamByCaptain(uint64 guid) const;

    void LoadArenaTeams();
    void AddArenaTeam(ArenaTeam* arenaTeam);
    void RemoveArenaTeam(uint32 Id);

    ArenaTeamContainer::iterator GetArenaTeamMapBegin() { return ArenaTeamStore.begin(); }
    ArenaTeamContainer::iterator GetArenaTeamMapEnd()   { return ArenaTeamStore.end(); }
    ArenaTeamContainer& GetArenaTeams() { return ArenaTeamStore; }

    void DistributeArenaPoints();

    uint32 GenerateArenaTeamId();
    void SetNextArenaTeamId(uint32 Id) { NextArenaTeamId = Id; }

    uint32 GetNextArenaLogId() { return ++LastArenaLogId; }
    void SetLastArenaLogId(uint32 id) { LastArenaLogId = id; }

    uint32 GenerateTempArenaTeamId();

protected:
    uint32 NextArenaTeamId;
    ArenaTeamContainer ArenaTeamStore;
    uint32 LastArenaLogId;
    uint32 NextTempArenaTeamId;
};

#define sArenaTeamMgr ACE_Singleton<ArenaTeamMgr, ACE_Null_Mutex>::instance()

#endif
