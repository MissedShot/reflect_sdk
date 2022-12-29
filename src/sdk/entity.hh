#pragma once
#include "sdk.hh"

// disable optimization for this file 
// its just a workaround because
// VFUNC's gets unstable sometimes
#pragma GCC push_options
#pragma GCC optimize ("O0")

class c_base_entity : public i_client_entity {
public:
	template <typename T>
	ALWAYS_INLINE T& get(int offset) { return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset); }

	VFUNC(get_pred_desc_map(), 21, data_map_t* (*)(void*))

	NETVAR(get_last_made_noise_time(), float, "CBaseEntity->m_flLastMadeNoiseTime")
	NETVAR(get_rotation(), qangle_t, "CBaseEntity->m_angRotation")
	NETVAR(get_team(), e_team_id, "CBaseEntity->m_iTeamNum")
	NETVAR(get_origin(), vec3_t, "CBaseEntity->m_vecOrigin")
	NETVAR(get_owner_entity(), c_base_handle , "CBaseEntity->m_hOwnerEntity")
	NETVAR(get_thrower_handle(), c_base_handle, "CBaseGrenade->m_hThrower");
	NETVAR(get_model_index(), int, "CBaseEntity->m_nModelIndex")
	NETVAR(is_spotted(), bool, "CBaseEntity->m_bSpotted")
	NETVAR(get_sim_time(), float, "CBaseEntity->m_flSimulationTime")
		
	VFUNC(get_abs_origin(), 12, vec3_t& (*)(void*))
	VFUNC(get_abs_angles(), 13, qangle_t& (*)(void*))

	VFUNC(is_player(), 210, bool(*)(void*))
	VFUNC(is_weapon(), 218, bool(*)(void*))
	VFUNC(set_model_index(int id), 111, void(*)(void*, int), id)

	DATA_MAP(get_effects(), bit_flag_t<uint32_t>, "m_fEffects")
	DATA_MAP(get_eflags(), bit_flag_t<uint32_t>, "m_iEFlags")
	DATA_MAP(get_abs_velocity(), vec3_t, "m_vecAbsVelocity")
	DATA_MAP(get_abs_rotation(), qangle_t, "m_angAbsRotation")
};

class c_inferno : public c_base_entity {
public:
};

class c_smoke_grenade_projectile : public c_base_entity {
public:
};

class c_base_view_model : public c_base_entity {
public:
	NETVAR(get_owner(), c_base_handle, "CBaseViewModel->m_hOwner")
	NETVAR(get_weapon(), c_base_handle, "CBaseViewModel->m_hWeapon")
	NETVAR(get_sequence(), int, "CBaseViewModel->m_nSequence")
};

class c_base_weapon_world_model : public c_base_entity {
public:
};

class c_planted_c4 : public c_base_entity {
public:
	NETVAR(is_ticking(), bool, "CPlantedC4->m_bBombTicking")
	NETVAR(get_site(), int, "CPlantedC4->m_nBombSite")
	NETVAR(get_c4_blow(), float, "CPlantedC4->m_flC4Blow")
	NETVAR(get_timer_length(), float, "CPlantedC4->m_flTimerLength")
	NETVAR(get_defuse_length(), float, "CPlantedC4->m_flDefuseLength")
	NETVAR(get_defuse_countdown(), float, "CPlantedC4->m_flDefuseCountDown")
	NETVAR(is_defused(), bool, "CPlantedC4->m_bBombDefused")
	NETVAR(get_defuser(), c_base_handle, "CPlantedC4->m_hBombDefuser")
};

class c_base_attributable_item : public c_base_entity {
public:
	NETVAR(get_item_definition_index(), short, "CBaseAttributableItem->m_iItemDefinitionIndex")
	NETVAR(get_account_id(), int, "CBaseAttributableItem->m_iAccountID")
	NETVAR(get_item_quality(), int, "CBaseAttributableItem->m_iEntityQuality")
	NETVAR(get_item_id_high(), int, "CBaseAttributableItem->m_iItemIDHigh")
	NETVAR(get_item_id_low(), int, "CBaseAttributableItem->m_iItemIDLow")
	NETVAR(get_fallback_paint_kit(), int, "CBaseAttributableItem->m_nFallbackPaintKit")
	NETVAR(get_fallback_seed(), int, "CBaseAttributableItem->m_nFallbackSeed")
	NETVAR(get_fallback_wear(), float, "CBaseAttributableItem->m_flFallbackWear")
	NETVAR(get_fallback_stat_trak(), int, "CBaseAttributableItem->m_nFallbackStatTrak")
	NETVAR(get_original_owner_xuid_low(), int, "CBaseAttributableItem->m_OriginalOwnerXuidLow")
	NETVAR(get_original_owner_xuid_high(), int, "CBaseAttributableItem->m_OriginalOwnerXuidHigh")
	NETVAR(get_initialized(), bool, "CBaseAttributableItem->m_bInitialized")
};

class c_base_combat_weapon;

class c_base_combat_character : public c_base_entity {
public:
	PNETVAR(get_weapons(), c_base_handle, "CBaseCombatCharacter->m_hMyWeapons")
	PNETVAR(get_wearables(), c_base_handle, "CBaseCombatCharacter->m_hMyWearables")
	NETVAR(get_active_weapon_handle(), c_base_handle, "CBaseCombatCharacter->m_hActiveWeapon")

	c_base_combat_weapon* get_active_weapon();
};

class c_base_player : public c_base_combat_character {
public:
	DATA_MAP(get_duck_amount(), float, "m_flDuckAmount")
	DATA_MAP(get_ground_entity(), c_base_handle, "m_hGroundEntity")
	DATA_MAP(get_move_type(), uint8_t, "m_MoveType")
	DATA_MAP(get_next_attack(), float, "m_flNextAttack")

	DATA_MAP(get_impulse(), int, "m_nImpulse")
	DATA_MAP(get_buttons(), bit_flag_t<uint32_t>, "m_nButtons")
	DATA_MAP(get_buttons_last(), bit_flag_t<uint32_t>, "m_afButtonLast")
	DATA_MAP(get_buttons_pressed(), bit_flag_t<uint32_t>, "m_afButtonPressed")
	DATA_MAP(get_buttons_released(), bit_flag_t<uint32_t>, "m_afButtonReleased")

	NETVAR_OFFSET(get_button_disabled(), bit_flag_t<uint32_t>, "CBasePlayer->m_hViewEntity", -0xC)
	NETVAR_OFFSET(get_button_forced(), bit_flag_t<uint32_t>, "CBasePlayer->m_hViewEntity", -0x8)

	DATA_MAP(get_collision_state(), int, "m_vphysicsCollisionState")
	
	NETVAR(get_fall_velocity(), float, "CBasePlayer->m_flFallVelocity")
	NETVAR(get_observer_mode(), e_observer_mode, "CBasePlayer->m_iObserverMode")
	NETVAR(get_observer_target(), c_base_handle, "CBasePlayer->m_hObserverTarget")
	NETVAR(get_flags(), bit_flag_t<uint32_t>, "CBasePlayer->m_fFlags")
	NETVAR(get_velocity(), vec3_t, "CBasePlayer->m_vecVelocity[0]")
	NETVAR(get_vehicle(), c_base_handle, "CBasePlayer->m_hVehicle")
	NETVAR(get_water_level(), int, "CBasePlayer->m_nWaterLevel")
	NETVAR(get_next_think_tick(), int, "CBasePlayer->m_nNextThinkTick")
	NETVAR(get_tick_base(), int, "CBasePlayer->m_nTickBase")
	NETVAR(get_duck_speed(), float, "CBasePlayer->m_flDuckSpeed")
	NETVAR(get_view_offset(), vec3_t, "CBasePlayer->m_vecViewOffset[0]")
	NETVAR(get_health(), int, "CBasePlayer->m_iHealth")
	NETVAR(get_life_state(), e_life_state, "CBasePlayer->m_lifeState")
	NETVAR(get_view_punch_angle(), qangle_t, "CBasePlayer->m_viewPunchAngle")
	NETVAR(get_aim_punch_angle(), qangle_t, "CBasePlayer->m_aimPunchAngle")
	NETVAR(get_aim_punch_angle_vel(), vec3_t, "CBasePlayer->m_aimPunchAngleVel")
	NETVAR(get_view_model(), c_base_handle, "CBasePlayer->m_hViewModel[0]")

	ALWAYS_INLINE bool is_alive() { return get_life_state() == LIFE_ALIVE && get_health(); }

	ALWAYS_INLINE vec3_t get_eye_pos() { return get_origin() + get_view_offset(); }
};

class c_base_animating : public c_base_player {
public:
	NETPROP(get_client_side_animation_prop(), "CBaseAnimating->m_bClientSideAnimation")
	NETVAR(get_client_side_animation(), bool, "CBaseAnimating->m_bClientSideAnimation")
	NETVAR(get_sequence(), int, "CBaseAnimating->m_nSequence")
};

class c_cs_player : public c_base_animating {
public:
	NETVAR(get_velocity_modifier(), float, "CCSPlayer->m_flVelocityModifier")
	NETVAR(has_defuser(), bool, "CCSPlayer->m_bHasDefuser")
	NETVAR(has_helmet(), bool, "CCSPlayer->m_bHasHelmet")
	NETVAR(get_armor_value(), int, "CCSPlayer->m_ArmorValue")
	NETVAR(has_heavy_armor(), bool, "CCSPlayer->m_bHasHeavyArmor")
	NETVAR(get_eye_angles(), qangle_t, "CCSPlayer->m_angEyeAngles")
	NETVAR(is_scoped(), bool, "CCSPlayer->m_bIsScoped")
	NETVAR(is_immune(), bool, "CCSPlayer->m_bGunGameImmunity")
	NETVAR(is_ghost(), bool, "CCSPlayer->m_bIsPlayerGhost")
	NETVAR(get_health_boost_time(), float, "CCSPlayer->m_flHealthShotBoostExpirationTime")
	NETVAR(get_lby(), float, "CCSPlayer->m_flLowerBodyYawTarget")
	NETVAR(get_shots_fired(), int, "CCSPlayer->m_iShotsFired")
	NETVAR(get_survival_team(), int, "CCSPlayer->m_nSurvivalTeam")
	NETVAR_OFFSET(get_flash_alpha(), float, "CCSPlayer->m_flFlashMaxAlpha", -0x8)
		
	player_info_t get_info();

	bool 	is_enemy(c_cs_player* from);
	bool 	is_valid();
	vec3_t 	get_bone_pos(int bone);
	bool 	can_see_player(const vec3_t& pos, const bool smoke);
};

class c_base_combat_weapon : public c_base_attributable_item {
public:
	NETVAR(get_pin_pulled(), bool, "CBaseCSGrenade->m_bPinPulled")
	NETVAR(get_throw_time(), float, "CBaseCSGrenade->m_fThrowTime")
	NETVAR(get_throw_strength(), float, "CBaseCSGrenade->m_flThrowStrength")

	NETVAR(get_post_pone_fire_ready_time(), float, "CWeaponCSBase->m_flPostponeFireReadyTime")
	NETVAR(get_accuracy_penalty(), float, "CWeaponCSBase->m_fAccuracyPenalty")
	NETVAR(get_recoil_index(), float, "CWeaponCSBase->m_flRecoilIndex")
	NETVAR(get_last_shot_time(), float, "CWeaponCSBase->m_fLastShotTime")
	NETVAR(get_ammo(), int, "CBaseCombatWeapon->m_iClip1")
	NETVAR(get_zoom_level(), int, "CWeaponCSBaseGun->m_zoomLevel")
	NETVAR(get_next_primary_attack(), float, "CBaseCombatWeapon->m_flNextPrimaryAttack")
	NETVAR(get_next_secondary_attack(), float, "CBaseCombatWeapon->m_flNextSecondaryAttack")
	NETVAR(get_world_model(), c_base_handle, "CBaseCombatWeapon->m_hWeaponWorldModel")
	NETVAR(get_view_model_index(), c_base_handle, "CBaseCombatWeapon->m_iViewModelIndex")
	NETVAR(get_world_model_index(), c_base_handle, "CBaseCombatWeapon->m_iWorldModelIndex")
		
	VFUNC(get_cs_weapon_data(), 529, c_cs_weapon_data*(*)(void*))

	ALWAYS_INLINE bool is_knife() { return (get_cs_weapon_data()->m_weapon_type == WEAPON_TYPE_KNIFE && get_item_definition_index() != WEAPON_ZEUS_X27); }

	bool invalid_weapon();

	std::wstring get_name();
};

#pragma GCC pop_options