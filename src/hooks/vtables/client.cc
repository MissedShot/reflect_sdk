#include "../hooks.hh"

void hooks::client::frame_stage_notify::hook(void* ptr, e_client_frame_stage stage) {
    globals::m_local = reinterpret_cast<c_cs_player*>(interfaces::m_entity_list->get_client_entity(interfaces::m_engine->get_local_player()));

    switch ( stage ) {
    case FRAME_UNDEFINED:
      break;

    case FRAME_START:
      break;

    case FRAME_NET_UPDATE_START:
      break;

    case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
      break;

    case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
      break;

    case FRAME_NET_UPDATE_END:
      break;

    case FRAME_RENDER_START:
      break;

    case FRAME_RENDER_END:
      break;

    default: break;
    }

    original(ptr, stage);
}