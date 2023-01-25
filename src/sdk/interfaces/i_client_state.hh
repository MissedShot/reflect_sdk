#pragma once

class i_client_state {
public:
    char  pad0[296];
    void* m_net_channel;
    char  pad1[124];
    float m_next_cmd_time;
    int   m_server_count;
    int   m_cur_sequence;
    char  pad2[72];

    struct {
        int			m_cur_clock_offset;
        int			m_server_tick;
        int			m_client_tick;
    } m_clock_drift_mgr;

    int     m_delta_tick;
    bool    m_paused;
    char    pad3[15];
    char    m_level_name[260];
    char    m_level_name_short[80];
    char    m_group_name[80];
};