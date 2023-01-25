#pragma once

class i_cs_player_resource {
public:
    NETVAR(get_player_c4(), int, "CCSPlayerResource->m_iPlayerC4")
    NETVAR_OFFSET(get_competitive_wins(int index), int, "CCSPlayerResource->m_iCompetitiveWins", index * sizeof(int))
    NETVAR_OFFSET(get_competitive_rank(int index), int, "CCSPlayerResource->m_iCompetitiveRanking", index * sizeof(int))
};