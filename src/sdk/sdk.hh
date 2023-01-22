#pragma once

#include "../utils/utils.hh"

#include "structs.hh"
#include "definitions.hh"

#include "datatypes/recv_prop.hh"
#include "datatypes/client_class.hh"
#include "datatypes/c_utl_vector.hh"
#include "datatypes/c_cvar.hh"
#include "datatypes/key_values.hh"
#include "datatypes/i_material_var.hh"
#include "datatypes/i_material.hh"

#include "other/i_collideable.hh"
#include "other/i_client_entity.hh"
#include "datatypes/c_base_handle.hh"
#include "datatypes/i_trace_filter.hh"

#include "interfaces/i_base_client.hh"
#include "interfaces/i_global_vars.hh"
#include "interfaces/i_engine_client.hh"
#include "interfaces/i_client_entity_list.hh"
#include "interfaces/i_client_mode.hh"
#include "interfaces/i_input.hh"
#include "interfaces/i_model_info.hh"
#include "interfaces/i_model_render.hh"
#include "interfaces/i_material_system.hh"
#include "interfaces/i_engine_trace.hh"
#include "interfaces/i_cvar_system.hh"
#include "interfaces/i_engine_sound.hh"
#include "interfaces/i_surface.hh"
#include "interfaces/i_localize.hh"
#include "interfaces/i_game_event_manager.hh"
#include "interfaces/i_move_helper.hh"
#include "interfaces/i_prediction.hh"
#include "interfaces/i_game_movement.hh"
#include "interfaces/i_studio_render.hh"
#include "interfaces/i_game_rules.hh"

#include "entity.hh"