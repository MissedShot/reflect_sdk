#pragma once
#include "../../globals.hh"

class c_engine_prediction: public c_singleton<c_engine_prediction> {
private:
    struct {
        ALWAYS_INLINE void store() {
            m_cur_time = interfaces::m_global_vars->m_cur_time;
            m_frame_time = interfaces::m_global_vars->m_frame_time;

            m_in_prediction = interfaces::m_prediction->m_in_prediction;
            m_first_time_predicted = interfaces::m_prediction->m_first_time_predicted;
        }

        ALWAYS_INLINE void restore() {
            interfaces::m_global_vars->m_cur_time = m_cur_time;
            interfaces::m_global_vars->m_frame_time = m_frame_time;

            interfaces::m_prediction->m_in_prediction = m_in_prediction;
            interfaces::m_prediction->m_first_time_predicted = m_first_time_predicted;
        }

        float m_frame_time, m_cur_time;
        bool m_first_time_predicted, m_in_prediction;
    } m_backup;

    void predict();

    int* m_random_seed;

    move_data_t* m_move_data;
public:
    c_engine_prediction() {
        m_random_seed = SIG("/client_client.so", "48 8D 05 ? ? ? ? 8B 38 E8 ? ? ? ? 89 C7").self_rel32(0x3).cast<int*>();

        m_move_data = reinterpret_cast<move_data_t*>(malloc(sizeof(move_data_t)));
    }

    void process();
    void restore();
};
#define engine_prediction c_engine_prediction::instance()