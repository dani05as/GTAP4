# Reporte de port de natives (PS3 -> PS4 gen8 / 1.57)

| métrica | valor |
|---|---|
| natives en el `Natives.h` de PS3 | 4646 |
| mapeados a hash de 64 bits | 4577 (98.5%) |
| resueltos por rename | 2069 |
| ya no existen en 1.57 (stub) | 69 |
| diferencia de cantidad de args | 189 |
| punteros 32->64 corregidos por deref | 33 |
| punteros que hay que revisar a mano | 956 |

## Natives que ya no existen en 1.57 (stub seguro)

| namespace | nombre | hash PS3 |
|---|---|---|
| PLAYER | `_0x725C6174` | `0x725C6174` |
| PLAYER | `_0xF8A62EFC` | `0xF8A62EFC` |
| PED | `_0xC21C8A56` | `0xC21C8A56` |
| PED | `_0x5D2FC042` | `0x5D2FC042` |
| PED | `_0x761F8F48` | `0x761F8F48` |
| PED | `_0xFC942D7C` | `0xFC942D7C` |
| PED | `_0x89EEE07B` | `0x89EEE07B` |
| PED | `_0xD315978E` | `0xD315978E` |
| PED | `SET_PEDHEADSHOT_CUSTOM_LIGHTING` | `0xAB688DAB` |
| PED | `SET_PEDHEADSHOT_CUSTOM_LIGHT` | `0xF48A9155` |
| VEHICLE | `_0xE39DAF36` | `0xE39DAF36` |
| AI | `ADD_FOLLOW_NAVMESH_TO_PHONE_TASK` | `0x00D7303F` |
| GAMEPLAY | `_0x96B2FD08` | `0x96B2FD08` |
| GAMEPLAY | `IS_BIT_SET` | `0x902E26AC` |
| STREAMING | `NETWORK_STOP_LOAD_SCENE` | `0x24857907` |
| UI | `_0x76FB0F21` | `0x76FB0F21` |
| UI | `_ADD_TEXT_COMPONENT_STRING` | `0x00000000` |
| UI | `_0x30D72A4B` | `0x30D72A4B` |
| GRAPHICS | `_0x72B36815` | `0x72B36815` |
| GRAPHICS | `_0xD820ADD4` | `0xD820ADD4` |
| GRAPHICS | `_0xD6844637` | `0xD6844637` |
| GRAPHICS | `_0x805BAB08` | `0x805BAB08` |
| GRAPHICS | `_0x908A335E` | `0x908A335E` |
| GRAPHICS | `_0x6776720A` | `0x6776720A` |
| GRAPHICS | `_0x6BBDE6CD` | `0x6BBDE6CD` |
| STATS | `_0xDFC25D66` | `0xDFC25D66` |
| STATS | `_0xB5BF87B2` | `0xB5BF87B2` |
| STATS | `_0x3F8E893B` | `0x3F8E893B` |
| STATS | `STAT_GET_BOOL_MASKED` | `0x6ACE1B7D` |
| STATS | `STAT_SET_BOOL_MASKED` | `0x7842C4D6` |
| STATS | `_0x30558CFD` | `0x30558CFD` |
| STATS | `LEADERBOARDS2_READ_BY_ROW` | `0xCA931F34` |
| STATS | `_0x54E775E0` | `0x54E775E0` |
| MOBILE | `_0x66DCD9D2` | `0x66DCD9D2` |
| CONTROLS | `_0x3551727A` | `0x3551727A` |
| CONTROLS | `_0x3EE71F6A` | `0x3EE71F6A` |
| CONTROLS | `SET_PAD_SHAKE` | `0x5D38BD2F` |
| CONTROLS | `STOP_PAD_SHAKE` | `0x8F75657E` |
| CONTROLS | `_0x7D65EB6E` | `0x7D65EB6E` |
| ROPE | `_0x67522E25` | `0x67522E25` |
| NETWORK | `NETWORK_SESSION_ENTER` | `0x543CD2BE` |
| NETWORK | `_0x4E53202A` | `0x4E53202A` |
| NETWORK | `_0xD7624E6B` | `0xD7624E6B` |
| NETWORK | `_0x3F75CC38` | `0x3F75CC38` |
| NETWORK | `NETWORK_SESSION_END` | `0xBCACBEA2` |
| NETWORK | `NETWORK_IS_IN_PARTY` | `0xF9D7D67D` |
| NETWORK | `NETWORK_IS_PARTY_MEMBER` | `0x1D0C929D` |
| NETWORK | `_0x8179C48A` | `0x8179C48A` |
| NETWORK | `_0xF9A51B92` | `0xF9A51B92` |
| NETWORK | `NETWORK_GET_GAME_REGION` | `0xEE4D173E` |
| NETWORK | `VEHICLE_NET_ATTACH_CHAR_TO_CHAR_PHYSICALLY` | `0xAC00A5BE` |
| NETWORK | `_0x29532731` | `0x29532731` |
| NETWORK | `NETWORK_SET_PROPERTY_ID` | `0x5A74E873` |
| NETWORK | `_0x38BC35C8` | `0x38BC35C8` |
| NETWORKCASH | `NETWORK_CHECK_RECEIVE_PLAYER_CASH` | `0xD6B69D67` |
| NETWORKCASH | `_0x6F1C592C` | `0x6F1C592C` |
| NETWORKCASH | `_0x5E81F55C` | `0x5E81F55C` |
| NETWORKCASH | `NETWORK_EARN_FROM_ROCKSTAR` | `0x5A3733CC` |
| NETWORKCASH | `_0x451A2644` | `0x451A2644` |
| DLC1 | `GET_SHOP_PED_OUTFIT_PROP` | `0x6C767148` |
| DLC1 | `GET_SHOP_PED_OUTFIT_COMPONENT` | `0x99EE4570` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_DATA_FLOAT` | `0x6A67FC31` |
| UNK_SC | `_0x628F489B` | `0x628F489B` |
| UNK_SC | `_0x095D5EBD` | `0x095D5EBD` |
| UNK_SC | `_0xDB75CDD1` | `0xDB75CDD1` |
| UNK_SC | `_0xC98160E1` | `0xC98160E1` |
| UNK_SC | `_0x2B240E0A` | `0x2B240E0A` |
| UNK_SC | `_0xD268255C` | `0xD268255C` |
| UNK_SC | `_0xA3EFE4A1` | `0xA3EFE4A1` |

## Parámetros nuevos en 1.57 que son punteros (revisar a mano)

El native moderno espera un puntero de salida que la firma de 2015 no
declara; la llamada se deja con menos argumentos y hay que envolverla.

| namespace | native | índice del param |
|---|---|---|
| NETWORK | `NETWORK_REGISTER_HOST_BROADCAST_VARIABLES` | 2 |
| NETWORK | `NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES` | 2 |
| NETWORKCASH | `_0xC5D8B1E9` | 2 |

## Argumentos extra de PS3 descartados (no los usa el native)

| namespace | native | descartados |
|---|---|---|
| ENTITY | `DELETE_ENTITY` | 1 |
| GAMEPLAY | `SET_WEATHER_TYPE_NOW_PERSIST` | 1 |
| STATS | `PLAYSTATS_MATCH_STARTED` | 4 |
| STATS | `_0x06CE3692` | 6 |
| NETWORK | `NETWORK_SET_IN_MP_CUTSCENE` | 1 |

## Diferencia de argumentos (revisar a mano)

| namespace | native | args PS3 | args 1.57 | nombre moderno | vía |
|---|---|---|---|---|---|
| PLAYER | `SPECIAL_ABILITY_DEACTIVATE` | 1 | 2 | `SPECIAL_ABILITY_DEACTIVATE` | jhash |
| PLAYER | `_0x0751908A` | 1 | 2 | `SPECIAL_ABILITY_DEACTIVATE_FAST` | jhash |
| PLAYER | `SPECIAL_ABILITY_RESET` | 1 | 2 | `SPECIAL_ABILITY_RESET` | jhash |
| PLAYER | `_0x4136829A` | 1 | 2 | `SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED` | jhash |
| PLAYER | `_0x6F463F56` | 3 | 4 | `SPECIAL_ABILITY_CHARGE_SMALL` | jhash |
| PLAYER | `_0xAB55D8F3` | 3 | 4 | `SPECIAL_ABILITY_CHARGE_MEDIUM` | jhash |
| PLAYER | `_0xF440C04D` | 3 | 4 | `SPECIAL_ABILITY_CHARGE_LARGE` | jhash |
| PLAYER | `_0x5FEE98A2` | 2 | 3 | `SPECIAL_ABILITY_CHARGE_CONTINUOUS` | jhash |
| PLAYER | `_0x72429998` | 3 | 4 | `SPECIAL_ABILITY_CHARGE_ABSOLUTE` | jhash |
| PLAYER | `RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC` | 3 | 4 | `SPECIAL_ABILITY_CHARGE_NORMALIZED` | jhash |
| PLAYER | `_0xB71589DA` | 2 | 3 | `SPECIAL_ABILITY_FILL_METER` | jhash |
| PLAYER | `_0x9F80F6DF` | 2 | 3 | `SPECIAL_ABILITY_DEPLETE_METER` | jhash |
| PLAYER | `SPECIAL_ABILITY_LOCK` | 1 | 2 | `SPECIAL_ABILITY_LOCK` | jhash |
| PLAYER | `SPECIAL_ABILITY_UNLOCK` | 1 | 2 | `SPECIAL_ABILITY_UNLOCK` | jhash |
| PLAYER | `IS_SPECIAL_ABILITY_ACTIVE` | 1 | 2 | `IS_SPECIAL_ABILITY_ACTIVE` | jhash |
| PLAYER | `IS_SPECIAL_ABILITY_METER_FULL` | 1 | 2 | `IS_SPECIAL_ABILITY_METER_FULL` | jhash |
| PLAYER | `ENABLE_SPECIAL_ABILITY` | 2 | 3 | `ENABLE_SPECIAL_ABILITY` | jhash |
| PLAYER | `IS_SPECIAL_ABILITY_ENABLED` | 1 | 2 | `IS_SPECIAL_ABILITY_ENABLED` | jhash |
| PLAYER | `_0x5D0FE25B` | 1 | 2 | `UPDATE_SPECIAL_ABILITY_FROM_STAT` | jhash |
| PLAYER | `_0x362E69AD` | 2 | 3 | `SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER` | jhash |
| PLAYER | `SIMULATE_PLAYER_INPUT_GAIT` | 6 | 7 | `SIMULATE_PLAYER_INPUT_GAIT` | jhash |
| ENTITY | `IS_ENTITY_DEAD` | 1 | 2 | `IS_ENTITY_DEAD` | jhash |
| ENTITY | `ATTACH_ENTITY_TO_ENTITY` | 15 | 16 | `ATTACH_ENTITY_TO_ENTITY` | jhash |
| ENTITY | `DELETE_ENTITY` | 2 | 1 | `DELETE_ENTITY` | jhash |
| ENTITY | `SET_ENTITY_HEALTH` | 2 | 4 | `SET_ENTITY_HEALTH` | jhash |
| ENTITY | `SET_ENTITY_INVINCIBLE` | 2 | 3 | `SET_ENTITY_INVINCIBLE` | jhash |
| ENTITY | `SET_ENTITY_LOAD_COLLISION_FLAG` | 2 | 3 | `SET_ENTITY_LOAD_COLLISION_FLAG` | jhash |
| ENTITY | `SET_ENTITY_VISIBLE` | 2 | 3 | `SET_ENTITY_VISIBLE` | jhash |
| PED | `APPLY_DAMAGE_TO_PED` | 3 | 5 | `APPLY_DAMAGE_TO_PED` | jhash |
| PED | `GET_PED_PROP_INDEX` | 2 | 3 | `GET_PED_PROP_INDEX` | jhash |
| PED | `SET_PED_PROP_INDEX` | 5 | 6 | `SET_PED_PROP_INDEX` | jhash |
| PED | `CLEAR_PED_PROP` | 2 | 3 | `CLEAR_PED_PROP` | jhash |
| PED | `CLEAR_ALL_PED_PROPS` | 1 | 2 | `CLEAR_ALL_PED_PROPS` | jhash |
| PED | `ADD_SCENARIO_BLOCKING_AREA` | 10 | 11 | `ADD_SCENARIO_BLOCKING_AREA` | jhash |
| PED | `SET_PED_HELMET_PROP_INDEX` | 2 | 3 | `SET_PED_HELMET_PROP_INDEX` | jhash |
| VEHICLE | `CREATE_VEHICLE` | 7 | 8 | `CREATE_VEHICLE` | jhash |
| VEHICLE | `_0xBB54ECCA` | 2 | 3 | `SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON` | jhash |
| VEHICLE | `SET_VEHICLE_ON_GROUND_PROPERLY` | 1 | 2 | `SET_VEHICLE_ON_GROUND_PROPERLY` | jhash |
| VEHICLE | `GET_VEHICLE_NUMBER_OF_PASSENGERS` | 1 | 3 | `GET_VEHICLE_NUMBER_OF_PASSENGERS` | jhash |
| VEHICLE | `IS_VEHICLE_SEAT_FREE` | 2 | 3 | `IS_VEHICLE_SEAT_FREE` | jhash |
| VEHICLE | `GET_PED_IN_VEHICLE_SEAT` | 2 | 3 | `GET_PED_IN_VEHICLE_SEAT` | jhash |
| VEHICLE | `CREATE_MISSION_TRAIN` | 5 | 7 | `CREATE_MISSION_TRAIN` | jhash |
| VEHICLE | `SET_VEHICLE_ENGINE_ON` | 3 | 4 | `SET_VEHICLE_ENGINE_ON` | jhash |
| VEHICLE | `REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA` | 6 | 7 | `REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA` | jhash |
| VEHICLE | `_0x4D3C9A99` | 1 | 2 | `CREATE_PICK_UP_ROPE_FOR_CARGOBOB` | jhash |
| VEHICLE | `_0xAA8BD440` | 2 | 3 | `SET_VEHICLE_EXCLUSIVE_DRIVER` | jhash |
| OBJECT | `CREATE_OBJECT_2` | 2 | 7 | `CREATE_OBJECT` | jhash |
| OBJECT | `CREATE_OBJECT_NO_OFFSET` | 7 | 8 | `CREATE_OBJECT_NO_OFFSET` | jhash |
| OBJECT | `SET_OBJECT_TARGETTABLE` | 2 | 3 | `SET_OBJECT_TARGETTABLE` | jhash |
| OBJECT | `GET_CLOSEST_OBJECT_OF_TYPE` | 6 | 8 | `GET_CLOSEST_OBJECT_OF_TYPE` | jhash |
| OBJECT | `HAS_OBJECT_BEEN_BROKEN` | 1 | 2 | `HAS_OBJECT_BEEN_BROKEN` | jhash |
| OBJECT | `ADD_DOOR_TO_SYSTEM` | 8 | 9 | `ADD_DOOR_TO_SYSTEM` | jhash |
| OBJECT | `REMOVE_DOOR_FROM_SYSTEM` | 1 | 2 | `REMOVE_DOOR_FROM_SYSTEM` | jhash |
| AI | `TASK_JUMP` | 2 | 4 | `TASK_JUMP` | jhash |
| AI | `TASK_SKY_DIVE` | 1 | 2 | `TASK_SKY_DIVE` | jhash |
| AI | `TASK_PARACHUTE` | 2 | 3 | `TASK_PARACHUTE` | jhash |
| AI | `_0x094B75EF` | 12 | 13 | `TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS` | jhash |
| AI | `_0x86DC03F9` | 13 | 14 | `TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED` | jhash |
| AI | `TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT` | 2 | 3 | `TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT` | jhash |
| AI | `TASK_PLANE_MISSION` | 13 | 14 | `TASK_PLANE_MISSION` | jhash |
| AI | `_0x98713C68` | 6 | 8 | `SET_MOUNTED_WEAPON_TARGET` | jhash |
| AI | `TASK_USE_MOBILE_PHONE` | 2 | 3 | `TASK_USE_MOBILE_PHONE` | jhash |
| AI | `SET_DRIVE_TASK_MAX_CRUISE_SPEED` | 2 | 3 | `SET_DRIVE_TASK_MAX_CRUISE_SPEED` | jhash |
| AI | `TASK_THROW_PROJECTILE` | 4 | 6 | `TASK_THROW_PROJECTILE` | jhash |
| AI | `TASK_WRITHE` | 4 | 6 | `TASK_WRITHE` | jhash |
| GAMEPLAY | `SET_WEATHER_TYPE_NOW_PERSIST` | 2 | 1 | `SET_WEATHER_TYPE_NOW_PERSIST` | jhash |
| GAMEPLAY | `GET_GROUND_Z_FOR_3D_COORD` | 4 | 6 | `GET_GROUND_Z_FOR_3D_COORD` | jhash |
| GAMEPLAY | `CLEAR_AREA_OF_VEHICLES` | 9 | 11 | `CLEAR_AREA_OF_VEHICLES` | jhash |
| GAMEPLAY | `CLEAR_ANGLED_AREA_OF_VEHICLES` | 12 | 14 | `CLEAR_ANGLED_AREA_OF_VEHICLES` | jhash |
| GAMEPLAY | `_0x52ACCB7B` | 14 | 15 | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY` | jhash |
| GAMEPLAY | `ADD_STUNT_JUMP` | 17 | 18 | `ADD_STUNT_JUMP` | jhash |
| GAMEPLAY | `ADD_STUNT_JUMP_ANGLED` | 19 | 20 | `ADD_STUNT_JUMP_ANGLED` | jhash |
| GAMEPLAY | `CREATE_INCIDENT` | 7 | 9 | `CREATE_INCIDENT` | jhash |
| GAMEPLAY | `CREATE_INCIDENT_WITH_ENTITY` | 5 | 7 | `CREATE_INCIDENT_WITH_ENTITY` | jhash |
| GAMEPLAY | `_0x42BF09B3` | 9 | 10 | `ADD_POP_MULTIPLIER_AREA` | jhash |
| AUDIO | `ADD_LINE_TO_CONVERSATION` | 12 | 13 | `ADD_LINE_TO_CONVERSATION` | jhash |
| AUDIO | `REQUEST_MISSION_AUDIO_BANK` | 2 | 3 | `REQUEST_MISSION_AUDIO_BANK` | jhash |
| AUDIO | `REQUEST_AMBIENT_AUDIO_BANK` | 2 | 3 | `REQUEST_AMBIENT_AUDIO_BANK` | jhash |
| AUDIO | `REQUEST_SCRIPT_AUDIO_BANK` | 2 | 3 | `REQUEST_SCRIPT_AUDIO_BANK` | jhash |
| AUDIO | `HINT_AMBIENT_AUDIO_BANK` | 2 | 3 | `HINT_AMBIENT_AUDIO_BANK` | jhash |
| AUDIO | `HINT_SCRIPT_AUDIO_BANK` | 2 | 3 | `HINT_SCRIPT_AUDIO_BANK` | jhash |
| AUDIO | `PLAY_SOUND` | 5 | 6 | `PLAY_SOUND` | jhash |
| AUDIO | `PLAY_SOUND_FRONTEND` | 3 | 4 | `PLAY_SOUND_FRONTEND` | jhash |
| AUDIO | `_PLAY_AMBIENT_SPEECH1` | 3 | 4 | `PLAY_PED_AMBIENT_SPEECH_NATIVE` | jhash |
| AUDIO | `_PLAY_AMBIENT_SPEECH2` | 3 | 4 | `PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE` | jhash |
| AUDIO | `PLAY_PAIN` | 3 | 4 | `PLAY_PAIN` | jhash |
| AUDIO | `SET_EMITTER_RADIO_STATION` | 2 | 3 | `SET_EMITTER_RADIO_STATION` | jhash |
| CAM | `RENDER_SCRIPT_CAMS` | 5 | 6 | `RENDER_SCRIPT_CAMS` | jhash |
| CAM | `_0xD3C08183` | 3 | 4 | `STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP` | jhash |
| CAM | `SET_CAM_ROT` | 3 | 5 | `SET_CAM_ROT` | jhash |
| WEAPON | `_0x5D73CD20` | 1 | 2 | `GET_CURRENT_PED_WEAPON_ENTITY_INDEX` | jhash |
| WEAPON | `SET_PED_AMMO` | 3 | 4 | `SET_PED_AMMO` | jhash |
| WEAPON | `SET_PED_CURRENT_WEAPON_VISIBLE` | 4 | 5 | `SET_PED_CURRENT_WEAPON_VISIBLE` | jhash |
| WEAPON | `CREATE_WEAPON_OBJECT` | 7 | 10 | `CREATE_WEAPON_OBJECT` | jhash |
| WEAPON | `GET_WEAPON_OBJECT_FROM_PED` | 1 | 2 | `GET_WEAPON_OBJECT_FROM_PED` | jhash |
| UI | `_0xDEB491C8` | 9 | 10 | `END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON` | jhash |
| UI | `_0x5E93FBFA` | 6 | 8 | `END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU` | jhash |
| UI | `_DRAW_TEXT` | 2 | 3 | `END_TEXT_COMMAND_DISPLAY_TEXT` | jhash |
| UI | `SET_BLIP_SHOW_CONE` | 2 | 3 | `SET_BLIP_SHOW_CONE` | jhash |
| UI | `SET_MINIMAP_COMPONENT` | 2 | 3 | `SET_MINIMAP_COMPONENT` | jhash |
| UI | `_0x0308EDF6` | 1 | 3 | `SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT` | jhash |
| UI | `_0xD41DF479` | 3 | 4 | `SET_MP_GAMER_TAG_VISIBILITY` | jhash |
| UI | `SET_WARNING_MESSAGE` | 8 | 9 | `SET_WARNING_MESSAGE` | jhash |
| UI | `_0x2DB9EAB5` | 9 | 10 | `SET_WARNING_MESSAGE_WITH_HEADER` | jhash |
| UI | `SET_DANCE_MAPPERS` | 10 | 11 | `SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS` | jhash |
| UI | `_0x57218529` | 0 | 1 | `OPEN_SOCIAL_CLUB_MENU` | jhash |
| GRAPHICS | `DRAW_RECT` | 8 | 9 | `DRAW_RECT` | name |
| GRAPHICS | `DRAW_SPRITE` | 11 | 13 | `DRAW_SPRITE` | name |
| GRAPHICS | `_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2` | 11 | 12 | `START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD` | jhash |
| GRAPHICS | `_0x110752B2` | 12 | 16 | `START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY` | jhash |
| GRAPHICS | `SET_PARTICLE_FX_LOOPED_EVOLUTION` | 3 | 4 | `SET_PARTICLE_FX_LOOPED_EVOLUTION` | jhash |
| GRAPHICS | `_0x12077738` | 13 | 15 | `ADD_VEHICLE_CREW_EMBLEM` | jhash |
| GRAPHICS | `_0x667046A8` | 1 | 2 | `REMOVE_VEHICLE_CREW_EMBLEM` | jhash |
| GRAPHICS | `_0x4F4D76E8` | 1 | 2 | `GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE` | jhash |
| GRAPHICS | `_0x6D58F73B` | 1 | 2 | `DOES_VEHICLE_HAVE_CREW_EMBLEM` | jhash |
| GRAPHICS | `DRAW_SCALEFORM_MOVIE` | 9 | 10 | `DRAW_SCALEFORM_MOVIE` | jhash |
| GRAPHICS | `_0x7B48E696` | 5 | 6 | `DRAW_SCALEFORM_MOVIE_FULLSCREEN` | jhash |
| STATS | `STAT_SAVE` | 3 | 4 | `STAT_SAVE` | jhash |
| STATS | `_0x1A66945F` | 2 | 3 | `PLAYSTATS_ACTIVITY_DONE` | jhash |
| STATS | `PLAYSTATS_MATCH_STARTED` | 7 | 3 | `PLAYSTATS_MATCH_STARTED` | jhash |
| STATS | `_0x6602CED6` | 6 | 8 | `PLAYSTATS_CRATE_DROP_MISSION_DONE` | jhash |
| STATS | `_0x06CE3692` | 10 | 4 | `PLAYSTATS_RACE_TO_POINT_MISSION_DONE` | jhash |
| PATHFIND | `SET_PED_PATHS_IN_AREA` | 7 | 8 | `SET_PED_PATHS_IN_AREA` | jhash |
| PATHFIND | `SET_ROADS_BACK_TO_ORIGINAL` | 6 | 7 | `SET_ROADS_BACK_TO_ORIGINAL` | jhash |
| PATHFIND | `SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA` | 7 | 8 | `SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA` | jhash |
| PATHFIND | `SET_PED_PATHS_BACK_TO_ORIGINAL` | 6 | 7 | `SET_PED_PATHS_BACK_TO_ORIGINAL` | jhash |
| CONTROLS | `DISABLE_CONTROL_ACTION` | 2 | 3 | `DISABLE_CONTROL_ACTION` | jhash |
| CONTROLS | `ENABLE_CONTROL_ACTION` | 2 | 3 | `ENABLE_CONTROL_ACTION` | jhash |
| DATAFILE | `_0xB41064A4` | 1 | 2 | `DATAFILE_SELECT_ACTIVE_FILE` | jhash |
| DATAFILE | `_0xF09157B0` | 7 | 8 | `UGC_CREATE_CONTENT` | jhash |
| DATAFILE | `_0xD96860FC` | 5 | 6 | `UGC_CREATE_MISSION` | jhash |
| DATAFILE | `_0x459F2683` | 7 | 8 | `UGC_UPDATE_CONTENT` | jhash |
| DATAFILE | `_0xDBB83E2B` | 5 | 6 | `UGC_UPDATE_MISSION` | jhash |
| DATAFILE | `_0xBB6321BD` | 3 | 4 | `UGC_SET_PLAYER_DATA` | jhash |
| DATAFILE | `_0xE8D56DA2` | 1 | 2 | `DATAFILE_SELECT_UGC_DATA` | jhash |
| DATAFILE | `_0xCB6A351E` | 2 | 3 | `DATAFILE_SELECT_UGC_STATS` | jhash |
| DATAFILE | `_0xA4D1B30E` | 1 | 2 | `DATAFILE_SELECT_UGC_PLAYER_DATA` | jhash |
| DATAFILE | `_0xB8515B2F` | 1 | 2 | `DATAFILE_SELECT_CREATOR_STATS` | jhash |
| DATAFILE | `_0x660C468E` | 1 | 2 | `DATAFILE_LOAD_OFFLINE_UGC` | jhash |
| DATAFILE | `DATAFILE_CREATE` | 0 | 1 | `DATAFILE_CREATE` | jhash |
| DATAFILE | `DATAFILE_DELETE` | 0 | 1 | `DATAFILE_DELETE` | jhash |
| DATAFILE | `_0x4E03F632` | 0 | 1 | `DATAFILE_STORE_MISSION_HEADER` | jhash |
| DATAFILE | `PRELOAD_FIND` | 0 | 1 | `DATAFILE_GET_FILE_DICT` | jhash |
| DATAFILE | `_0x768CBB35` | 1 | 2 | `DATAFILE_START_SAVE_TO_CLOUD` | jhash |
| FIRE | `ADD_EXPLOSION` | 8 | 9 | `ADD_EXPLOSION` | jhash |
| NETWORK | `NETWORK_BAIL` | 0 | 3 | `NETWORK_BAIL` | jhash |
| NETWORK | `NETWORK_HOST_TRANSITION` | 6 | 10 | `NETWORK_HOST_TRANSITION` | jhash |
| NETWORK | `_0x2FF65C0B` | 4 | 6 | `NETWORK_DO_TRANSITION_QUICKMATCH` | jhash |
| NETWORK | `_0x47D61C99` | 4 | 6 | `NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC` | jhash |
| NETWORK | `_0x5CE60A11` | 6 | 8 | `NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP` | jhash |
| NETWORK | `_0xB59D74CA` | 0 | 3 | `NETWORK_BAIL_TRANSITION` | jhash |
| NETWORK | `NETWORK_DO_TRANSITION_TO_FREEMODE` | 4 | 5 | `NETWORK_DO_TRANSITION_TO_FREEMODE` | jhash |
| NETWORK | `NETWORK_DO_TRANSITION_TO_NEW_FREEMODE` | 5 | 6 | `NETWORK_DO_TRANSITION_TO_NEW_FREEMODE` | jhash |
| NETWORK | `NETWORK_REGISTER_HOST_BROADCAST_VARIABLES` | 2 | 3 | `NETWORK_REGISTER_HOST_BROADCAST_VARIABLES` | jhash |
| NETWORK | `NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES` | 2 | 3 | `NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES` | jhash |
| NETWORK | `NETWORK_RESURRECT_LOCAL_PLAYER` | 6 | 9 | `NETWORK_RESURRECT_LOCAL_PLAYER` | jhash |
| NETWORK | `_NETWORK_RESPAWN_COORDS` | 4 | 6 | `NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP` | jhash |
| NETWORK | `_0xCEAE5AFC` | 1 | 2 | `REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY` | jhash |
| NETWORK | `NETWORK_FADE_IN_ENTITY` | 2 | 3 | `NETWORK_FADE_IN_ENTITY` | jhash |
| NETWORK | `GET_NUM_RESERVED_MISSION_OBJECTS` | 1 | 2 | `GET_NUM_RESERVED_MISSION_OBJECTS` | jhash |
| NETWORK | `GET_NUM_RESERVED_MISSION_PEDS` | 1 | 2 | `GET_NUM_RESERVED_MISSION_PEDS` | jhash |
| NETWORK | `GET_NUM_RESERVED_MISSION_VEHICLES` | 1 | 2 | `GET_NUM_RESERVED_MISSION_VEHICLES` | jhash |
| NETWORK | `NETWORK_SET_IN_MP_CUTSCENE` | 3 | 2 | `NETWORK_SET_IN_MP_CUTSCENE` | jhash |
| NETWORK | `SET_NETWORK_VEHICLE_RESPOT_TIMER` | 2 | 4 | `SET_NETWORK_VEHICLE_RESPOT_TIMER` | jhash |
| NETWORK | `NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE` | 9 | 10 | `NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE` | jhash |
| NETWORK | `_0x72052DB3` | 2 | 3 | `NETWORK_CONCEAL_PLAYER` | jhash |
| NETWORK | `_0x365C50EE` | 2 | 3 | `OPEN_COMMERCE_STORE` | jhash |
| NETWORKCASH | `_0x5AA379D9` | 5 | 6 | `NETWORK_CAN_SPEND_MONEY` | jhash |
| NETWORKCASH | `NETWORK_SPENT_BUY_WANTEDLEVEL` | 4 | 5 | `NETWORK_SPENT_BUY_WANTEDLEVEL` | jhash |
| NETWORKCASH | `_0xC5D8B1E9` | 2 | 3 | `PROCESS_CASH_GIFT` | jhash |
| NETWORKCASH | `NETWORK_EARN_FROM_VEHICLE` | 2 | 8 | `NETWORK_EARN_FROM_VEHICLE` | jhash |
| NETWORKCASH | `_0x96B8BEE8` | 2 | 9 | `NETWORK_EARN_FROM_PERSONAL_VEHICLE` | jhash |
| NETWORKCASH | `NETWORK_SPENT_TAXI` | 3 | 5 | `NETWORK_SPENT_TAXI` | jhash |
| NETWORKCASH | `NETWORK_BUY_AIRSTRIKE` | 3 | 4 | `NETWORK_BUY_AIRSTRIKE` | jhash |
| NETWORKCASH | `_0x047547D4` | 3 | 4 | `NETWORK_BUY_HELI_STRIKE` | jhash |
| NETWORKCASH | `NETWORK_SPENT_AMMO_DROP` | 3 | 4 | `NETWORK_SPENT_AMMO_DROP` | jhash |
| NETWORKCASH | `NETWORK_BUY_BOUNTY` | 4 | 5 | `NETWORK_BUY_BOUNTY` | jhash |
| NETWORKCASH | `NETWORK_SPENT_HELI_PICKUP` | 3 | 4 | `NETWORK_SPENT_HELI_PICKUP` | jhash |
| NETWORKCASH | `NETWORK_SPENT_BOAT_PICKUP` | 3 | 4 | `NETWORK_SPENT_BOAT_PICKUP` | jhash |
| NETWORKCASH | `_0xDE7D398C` | 3 | 4 | `NETWORK_SPENT_BULL_SHARK` | jhash |
| NETWORKCASH | `_0xE792C4A5` | 3 | 4 | `NETWORK_SPENT_HIRE_MUGGER` | jhash |
| NETWORKCASH | `_0xE6AAA0D5` | 3 | 4 | `NETWORK_SPENT_ROBBED_BY_MUGGER` | jhash |
| NETWORKCASH | `_0x99CF02C4` | 3 | 4 | `NETWORK_SPENT_HIRE_MERCENARY` | jhash |
| NETWORKCASH | `_0x20DDCF2F` | 3 | 4 | `NETWORK_SPENT_BUY_OFFTHERADAR` | jhash |
| NETWORKCASH | `_0x2F7836E2` | 3 | 4 | `NETWORK_SPENT_BUY_REVEAL_PLAYERS` | jhash |
| NETWORKCASH | `_0x7E97C92C` | 3 | 4 | `NETWORK_SPENT_BUY_PASSIVE_MODE` | jhash |
| NETWORKCASH | `_0x2E51C61C` | 3 | 4 | `NETWORK_SPENT_NO_COPS` | jhash |
| NETWORKCASH | `_0xD57A5125` | 3 | 4 | `NETWORK_SPENT_REQUEST_JOB` | jhash |
| NETWORKCASH | `_0xD9622D64` | 4 | 5 | `NETWORK_BUY_FAIRGROUND_RIDE` | jhash |

## Punteros sospechosos (PS3 pasaba un valor, PS4 espera puntero)

| namespace | native | param | tipo PS3 | tipo 1.57 |
|---|---|---|---|---|
| PLAYER | `_0x04256C73` | `p0` | `Any` | `const char*` |
| PLAYER | `GET_PLAYER_PARACHUTE_TINT_INDEX` | `p1` | `Any` | `int*` |
| PLAYER | `_0x77B8EF01` | `p1` | `Any` | `int*` |
| PLAYER | `_0x4E418E13` | `p1` | `Any` | `int*` |
| PLAYER | `_0xF66E5CDD` | `p1` | `Any` | `int*` |
| PLAYER | `_0xF66E5CDD` | `p2` | `Any` | `int*` |
| PLAYER | `_0xF66E5CDD` | `p3` | `Any` | `int*` |
| ENTITY | `HAS_ENTITY_ANIM_FINISHED` | `p1` | `Any` | `const char*` |
| ENTITY | `HAS_ENTITY_ANIM_FINISHED` | `p2` | `Any` | `const char*` |
| ENTITY | `GET_ENTITY_ANIM_CURRENT_TIME` | `p1` | `Any` | `const char*` |
| ENTITY | `GET_ENTITY_ANIM_CURRENT_TIME` | `p2` | `Any` | `const char*` |
| ENTITY | `GET_ENTITY_ANIM_TOTAL_TIME` | `p1` | `Any` | `const char*` |
| ENTITY | `GET_ENTITY_ANIM_TOTAL_TIME` | `p2` | `Any` | `const char*` |
| ENTITY | `GET_ENTITY_MATRIX` | `p1` | `Any` | `Vector3*` |
| ENTITY | `GET_ENTITY_MATRIX` | `p2` | `Any` | `Vector3*` |
| ENTITY | `GET_ENTITY_MATRIX` | `p3` | `Any` | `Vector3*` |
| ENTITY | `GET_ENTITY_MATRIX` | `p4` | `Any` | `Vector3*` |
| ENTITY | `GET_ENTITY_QUATERNION` | `p1` | `Any` | `float*` |
| ENTITY | `GET_ENTITY_QUATERNION` | `p2` | `Any` | `float*` |
| ENTITY | `GET_ENTITY_QUATERNION` | `p3` | `Any` | `float*` |
| ENTITY | `GET_ENTITY_QUATERNION` | `p4` | `Any` | `float*` |
| ENTITY | `GET_ENTITY_SCRIPT` | `p1` | `Any` | `ScrHandle*` |
| ENTITY | `IS_ENTITY_IN_ZONE` | `p1` | `Any` | `const char*` |
| ENTITY | `IS_ENTITY_PLAYING_ANIM` | `p1` | `Any` | `const char*` |
| ENTITY | `IS_ENTITY_PLAYING_ANIM` | `p2` | `Any` | `const char*` |
| ENTITY | `PLAY_ENTITY_ANIM` | `p1` | `Any` | `const char*` |
| ENTITY | `PLAY_ENTITY_ANIM` | `p2` | `Any` | `const char*` |
| ENTITY | `PLAY_SYNCHRONIZED_ENTITY_ANIM` | `p2` | `Any` | `const char*` |
| ENTITY | `PLAY_SYNCHRONIZED_ENTITY_ANIM` | `p3` | `Any` | `const char*` |
| ENTITY | `_0xEB4CBA74` | `p6` | `Any` | `const char*` |
| ENTITY | `_0xEB4CBA74` | `p7` | `Any` | `const char*` |
| ENTITY | `STOP_ENTITY_ANIM` | `p1` | `Any` | `const char*` |
| ENTITY | `STOP_ENTITY_ANIM` | `p2` | `Any` | `const char*` |
| ENTITY | `_0xC41DDA62` | `p0` | `Any` | `const char*` |
| ENTITY | `_0xC41DDA62` | `p1` | `Any` | `const char*` |
| ENTITY | `_0xC41DDA62` | `p2` | `Any` | `const char*` |
| ENTITY | `_0xC41DDA62` | `p3` | `Any` | `Any*` |
| ENTITY | `_0xC41DDA62` | `p4` | `Any` | `Any*` |
| ENTITY | `SET_ENTITY_ANIM_CURRENT_TIME` | `p1` | `Any` | `const char*` |
| ENTITY | `SET_ENTITY_ANIM_CURRENT_TIME` | `p2` | `Any` | `const char*` |
| PED | `REMOVE_PED_ELEGANTLY` | `PedHandle` | `Ped` | `Ped*` |
| PED | `GET_PED_LAST_DAMAGE_BONE` | `p1` | `Any` | `int*` |
| PED | `GET_PED_PARACHUTE_TINT_INDEX` | `p1` | `Any` | `int*` |
| PED | `SET_PED_STEALTH_MOVEMENT` | `p2` | `Any` | `const char*` |
| PED | `ADD_RELATIONSHIP_GROUP` | `p1` | `Any` | `Hash*` |
| PED | `GET_GROUP_SIZE` | `p1` | `Any` | `Any*` |
| PED | `GET_GROUP_SIZE` | `p2` | `Any` | `int*` |
| PED | `SET_PED_STRAFE_CLIPSET` | `p1` | `Any` | `const char*` |
| PED | `SET_PED_WEAPON_MOVEMENT_CLIPSET` | `p1` | `Any` | `const char*` |
| PED | `_0xD4C73595` | `p1` | `Any` | `const char*` |
| PED | `_0x3C30B447` | `p1` | `Any` | `const char*` |
| PED | `_0x3C30B447` | `p2` | `Any` | `const char*` |
| PED | `_0x895E1D67` | `p1` | `Any` | `const char*` |
| PED | `_0x895E1D67` | `p2` | `Any` | `const char*` |
| PED | `SET_PED_ALTERNATE_MOVEMENT_ANIM` | `p2` | `Any` | `const char*` |
| PED | `SET_PED_ALTERNATE_MOVEMENT_ANIM` | `p3` | `Any` | `const char*` |
| PED | `SET_PED_GESTURE_GROUP` | `p1` | `Any` | `const char*` |
| PED | `_0xC59D4268` | `p0` | `Any` | `const char*` |
| PED | `_0xC59D4268` | `p1` | `Any` | `const char*` |
| PED | `_0x5F7789E6` | `p0` | `Any` | `const char*` |
| PED | `_0x5F7789E6` | `p1` | `Any` | `const char*` |
| PED | `GET_CLOSEST_PED` | `handle` | `int` | `Ped*` |
| PED | `SET_PED_NAME_DEBUG` | `p1` | `Any` | `const char*` |
| PED | `_0x8F3F3A9C` | `p4` | `Any` | `const char*` |
| PED | `_0xFC13CE80` | `p8` | `Any` | `const char*` |
| PED | `APPLY_PED_DAMAGE_PACK` | `p1` | `Any` | `const char*` |
| PED | `_0x70AA5B7D` | `p2` | `Any` | `const char*` |
| PED | `IS_PED_USING_SCENARIO` | `p1` | `Any` | `const char*` |
| PED | `PLAY_FACIAL_ANIM` | `p1` | `Any` | `const char*` |
| PED | `PLAY_FACIAL_ANIM` | `p2` | `Any` | `const char*` |
| PED | `SET_FACIAL_IDLE_ANIM_OVERRIDE` | `p1` | `Any` | `const char*` |
| PED | `SET_FACIAL_IDLE_ANIM_OVERRIDE` | `p2` | `Any` | `const char*` |
| PED | `IS_PED_EVASIVE_DIVING` | `p1` | `Any` | `Entity*` |
| PED | `SET_PED_COWER_HASH` | `p1` | `Any` | `const char*` |
| PED | `SET_PED_USING_ACTION_MODE` | `p3` | `Any` | `const char*` |
| PED | `_0x36A4AC65` | `p1` | `Any` | `float*` |
| PED | `_0x36A4AC65` | `p2` | `Any` | `float*` |
| PED | `_0x36A4AC65` | `p3` | `Any` | `float*` |
| PED | `_0xBA699DDF` | `p1` | `Any` | `int*` |
| PED | `REQUEST_ACTION_MODE_ASSET` | `p0` | `Any` | `const char*` |
| PED | `HAS_ACTION_MODE_ASSET_LOADED` | `p0` | `Any` | `const char*` |
| PED | `REMOVE_ACTION_MODE_ASSET` | `p0` | `Any` | `const char*` |
| PED | `REQUEST_STEALTH_MODE_ASSET` | `p0` | `Any` | `const char*` |
| PED | `HAS_STEALTH_MODE_ASSET_LOADED` | `p0` | `Any` | `const char*` |
| PED | `REMOVE_STEALTH_MODE_ASSET` | `p0` | `Any` | `const char*` |
| VEHICLE | `IS_VEHICLE_IN_GARAGE_AREA` | `p0` | `Any` | `const char*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_PRIMARY_COLOUR` | `r` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_PRIMARY_COLOUR` | `g` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_PRIMARY_COLOUR` | `b` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_SECONDARY_COLOUR` | `p1` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_SECONDARY_COLOUR` | `p2` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_CUSTOM_SECONDARY_COLOUR` | `p3` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_LIGHTS_STATE` | `p1` | `Any` | `BOOL*` |
| VEHICLE | `GET_VEHICLE_LIGHTS_STATE` | `p2` | `Any` | `BOOL*` |
| VEHICLE | `GET_VEHICLE_RECORDING_ID` | `p1` | `Any` | `const char*` |
| VEHICLE | `REQUEST_VEHICLE_RECORDING` | `p1` | `Any` | `const char*` |
| VEHICLE | `HAS_VEHICLE_RECORDING_BEEN_LOADED` | `p1` | `Any` | `const char*` |
| VEHICLE | `REMOVE_VEHICLE_RECORDING` | `p1` | `Any` | `const char*` |
| VEHICLE | `GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME` | `p2` | `Any` | `const char*` |
| VEHICLE | `GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME` | `p2` | `Any` | `const char*` |
| VEHICLE | `GET_TOTAL_DURATION_OF_VEHICLE_RECORDING` | `p1` | `Any` | `const char*` |
| VEHICLE | `START_PLAYBACK_RECORDED_VEHICLE` | `p2` | `Any` | `const char*` |
| VEHICLE | `START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS` | `p2` | `Any` | `const char*` |
| VEHICLE | `START_PLAYBACK_RECORDED_VEHICLE_USING_AI` | `p2` | `Any` | `const char*` |
| VEHICLE | `DELETE_MISSION_TRAIN` | `p0` | `Any` | `Vehicle*` |
| VEHICLE | `SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED` | `p0` | `Any` | `Vehicle*` |
| VEHICLE | `SET_VEHICLE_NAME_DEBUG` | `p1` | `Any` | `const char*` |
| VEHICLE | `_0x34E02FCD` | `p0` | `Any` | `Vector3*` |
| VEHICLE | `_0x34E02FCD` | `p2` | `Any` | `Vector3*` |
| VEHICLE | `GET_VEHICLE_TRAILER_VEHICLE` | `p1` | `Any` | `Vehicle*` |
| VEHICLE | `GET_VEHICLE_MOD_COLOR_1` | `p1` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_MOD_COLOR_1` | `p2` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_MOD_COLOR_1` | `p3` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_MOD_COLOR_2` | `p1` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_MOD_COLOR_2` | `p2` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_TYRE_SMOKE_COLOR` | `R` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_TYRE_SMOKE_COLOR` | `G` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_TYRE_SMOKE_COLOR` | `B` | `int` | `int*` |
| VEHICLE | `GET_VEHICLE_COLOR` | `p1` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_COLOR` | `p2` | `Any` | `int*` |
| VEHICLE | `GET_VEHICLE_COLOR` | `p3` | `Any` | `int*` |
| VEHICLE | `_0x4A557117` | `p1` | `Any` | `Entity*` |
| VEHICLE | `DOES_VEHICLE_EXIST_WITH_DECORATOR` | `p0` | `Any` | `const char*` |
| OBJECT | `_0x65213FC3` | `p5` | `Any` | `Vector3*` |
| OBJECT | `_0x65213FC3` | `p6` | `Any` | `Vector3*` |
| OBJECT | `GET_STATE_OF_CLOSEST_DOOR_OF_TYPE` | `locked` | `BOOL` | `BOOL*` |
| OBJECT | `_0xE9AE494F` | `p4` | `Any` | `Hash*` |
| OBJECT | `_0xA286DE96` | `p4` | `Any` | `const char*` |
| AI | `TASK_ENTER_VEHICLE` | `p6` | `Any` | `const char*` |
| AI | `GET_NAVMESH_ROUTE_DISTANCE_REMAINING` | `p1` | `Any` | `float*` |
| AI | `GET_NAVMESH_ROUTE_DISTANCE_REMAINING` | `p2` | `Any` | `BOOL*` |
| AI | `_0x3DDEB0E6` | `p1` | `Any` | `const char*` |
| AI | `_0x3DDEB0E6` | `p2` | `Any` | `const char*` |
| AI | `STOP_ANIM_TASK` | `p1` | `Any` | `const char*` |
| AI | `STOP_ANIM_TASK` | `p2` | `Any` | `const char*` |
| AI | `_0x1582162C` | `p1` | `Any` | `const char*` |
| AI | `_0x1582162C` | `p2` | `Any` | `const char*` |
| AI | `_0x1582162C` | `p3` | `Any` | `const char*` |
| AI | `TASK_VEHICLE_PLAY_ANIM` | `p1` | `Any` | `const char*` |
| AI | `TASK_VEHICLE_PLAY_ANIM` | `p2` | `Any` | `const char*` |
| AI | `TASK_STAND_GUARD` | `p5` | `Any` | `const char*` |
| AI | `TASK_START_SCENARIO_AT_POSITION` | `p1` | `Any` | `const char*` |
| AI | `_0x0FB138A5` | `p3` | `Any` | `const char*` |
| AI | `_0x1984A5D1` | `p1` | `Any` | `const char*` |
| AI | `_0x1984A5D1` | `p2` | `Any` | `const char*` |
| AI | `DOES_SCENARIO_GROUP_EXIST` | `p0` | `Any` | `const char*` |
| AI | `IS_SCENARIO_GROUP_ENABLED` | `p0` | `Any` | `const char*` |
| AI | `SET_SCENARIO_GROUP_ENABLED` | `p0` | `Any` | `const char*` |
| AI | `SET_EXCLUSIVE_SCENARIO_GROUP` | `p0` | `Any` | `const char*` |
| AI | `IS_SCENARIO_TYPE_ENABLED` | `p0` | `Any` | `const char*` |
| AI | `SET_SCENARIO_TYPE_ENABLED` | `p0` | `Any` | `const char*` |
| AI | `OPEN_PATROL_ROUTE` | `p0` | `Any` | `const char*` |
| AI | `ADD_PATROL_ROUTE_NODE` | `p1` | `Any` | `const char*` |
| AI | `DELETE_PATROL_ROUTE` | `p0` | `Any` | `const char*` |
| AI | `TASK_PATROL` | `p1` | `Any` | `const char*` |
| AI | `REQUEST_WAYPOINT_RECORDING` | `p0` | `Any` | `const char*` |
| AI | `_0x87125F5D` | `p0` | `Any` | `const char*` |
| AI | `REMOVE_WAYPOINT_RECORDING` | `p0` | `Any` | `const char*` |
| AI | `_0xF5F9B71E` | `p0` | `Any` | `const char*` |
| AI | `_0xF5F9B71E` | `p1` | `Any` | `int*` |
| AI | `_0x19266913` | `p0` | `Any` | `const char*` |
| AI | `_0x19266913` | `p2` | `Any` | `Vector3*` |
| AI | `_0xC765633A` | `p0` | `Any` | `const char*` |
| AI | `_0xC4CD35AF` | `p0` | `Any` | `const char*` |
| AI | `_0xC4CD35AF` | `p4` | `Any` | `int*` |
| AI | `TASK_FOLLOW_WAYPOINT_RECORDING` | `p1` | `Any` | `const char*` |
| AI | `_0xE8422AC4` | `p0` | `Any` | `const char*` |
| AI | `_0x4DFD5FEC` | `p0` | `Any` | `const char*` |
| AI | `ASSISTED_MOVEMENT_REMOVE_ROUTE` | `p0` | `Any` | `const char*` |
| AI | `_0x79B067AF` | `p0` | `Any` | `const char*` |
| AI | `_0x01CAAFCC` | `p0` | `Any` | `const char*` |
| AI | `TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING` | `p2` | `Any` | `const char*` |
| AI | `_0x885724DE` | `p1` | `Any` | `const char*` |
| AI | `_0xA79BE783` | `p1` | `Any` | `const char*` |
| AI | `_0xF3538041` | `p1` | `Any` | `const char*` |
| AI | `_0x1EBB6F3D` | `p1` | `Any` | `const char*` |
| AI | `_0x72FA5EF2` | `p1` | `Any` | `const char*` |
| AI | `TASK_SYNCHRONIZED_SCENE` | `p2` | `Any` | `const char*` |
| AI | `TASK_SYNCHRONIZED_SCENE` | `p3` | `Any` | `const char*` |
| AI | `_0x1683FE66` | `p1` | `Any` | `const char*` |
| AI | `_0x1683FE66` | `p2` | `Any` | `const char*` |
| AI | `_0x1683FE66` | `p3` | `Any` | `const char*` |
| AI | `_0x1683FE66` | `p4` | `Any` | `const char*` |
| GAMEPLAY | `_0xE77199F7` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `IS_PREV_WEATHER_TYPE` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `IS_NEXT_WEATHER_TYPE` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `_0x9A5C1D56` | `p0` | `Any` | `Hash*` |
| GAMEPLAY | `_0x9A5C1D56` | `p1` | `Any` | `Hash*` |
| GAMEPLAY | `_0x9A5C1D56` | `p2` | `Any` | `float*` |
| GAMEPLAY | `_0x8727A4C5` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `_0xC9FA6E07` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `_0x64D91CED` | `p3` | `Any` | `float*` |
| GAMEPLAY | `_0x64D91CED` | `p4` | `Any` | `Vector3*` |
| GAMEPLAY | `_0xC6CC812C` | `p12` | `Any` | `float*` |
| GAMEPLAY | `_0x87B92190` | `p9` | `Any` | `float*` |
| GAMEPLAY | `_0x87B92190` | `p10` | `Any` | `float*` |
| GAMEPLAY | `_0x87B92190` | `p11` | `Any` | `float*` |
| GAMEPLAY | `_0x87B92190` | `p12` | `Any` | `float*` |
| GAMEPLAY | `REGISTER_SAVE_HOUSE` | `p4` | `Any` | `const char*` |
| GAMEPLAY | `_0xC4D71AB4` | `p0` | `Any` | `Vector3*` |
| GAMEPLAY | `_0xC4D71AB4` | `p1` | `Any` | `float*` |
| GAMEPLAY | `_0xC4D71AB4` | `p2` | `Any` | `BOOL*` |
| GAMEPLAY | `_0xC4D71AB4` | `p3` | `Any` | `BOOL*` |
| GAMEPLAY | `COMPARE_STRINGS` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `COMPARE_STRINGS` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0x1A40454B` | `p7` | `Any` | `Vector3*` |
| GAMEPLAY | `_0x6BDE5CE4` | `p3` | `Any` | `Vector3*` |
| GAMEPLAY | `IS_STRING_NULL` | `p0` | `Any` | `const char*` |
| GAMEPLAY | `SET_BITS_IN_RANGE` | `p0` | `Any` | `int*` |
| GAMEPLAY | `START_SAVE_DATA` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `REGISTER_INT_TO_SAVE` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `REGISTER_INT_TO_SAVE` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0x9B38374A` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0x9B38374A` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `REGISTER_FLOAT_TO_SAVE` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `REGISTER_FLOAT_TO_SAVE` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `REGISTER_BOOL_TO_SAVE` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `REGISTER_BOOL_TO_SAVE` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `REGISTER_TEXT_LABEL_TO_SAVE` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `REGISTER_TEXT_LABEL_TO_SAVE` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xE2089749` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0xE2089749` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xF91B8C33` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0xF91B8C33` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0x74E8FAD9` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0x74E8FAD9` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0x6B4335DD` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0x6B4335DD` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xFB45728E` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0xFB45728E` | `p2` | `Any` | `const char*` |
| GAMEPLAY | `_0x893A342C` | `p0` | `Any` | `Any*` |
| GAMEPLAY | `_0x893A342C` | `p2` | `Any` | `const char*` |
| GAMEPLAY | `CREATE_INCIDENT` | `p6` | `Any` | `int*` |
| GAMEPLAY | `CREATE_INCIDENT_WITH_ENTITY` | `p4` | `Any` | `int*` |
| GAMEPLAY | `FIND_SPAWN_POINT_IN_DIRECTION` | `p7` | `Any` | `Vector3*` |
| GAMEPLAY | `_0xC20A7D2B` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xC20A7D2B` | `p2` | `Any` | `const char*` |
| GAMEPLAY | `_0x49F977A9` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p1` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p2` | `Any` | `Any*` |
| GAMEPLAY | `_0xD2688412` | `p3` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p4` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p5` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p6` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p7` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p8` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p9` | `Any` | `const char*` |
| GAMEPLAY | `_0xD2688412` | `p10` | `Any` | `const char*` |
| GAMEPLAY | `_0x07FF553F` | `p1` | `Any` | `int*` |
| GAMEPLAY | `_0x07FF553F` | `p2` | `Any` | `int*` |
| AUDIO | `PLAY_PED_RINGTONE` | `p0` | `Any` | `const char*` |
| AUDIO | `ADD_LINE_TO_CONVERSATION` | `p1` | `Any` | `const char*` |
| AUDIO | `ADD_LINE_TO_CONVERSATION` | `p2` | `Any` | `const char*` |
| AUDIO | `ADD_PED_TO_CONVERSATION` | `p2` | `Any` | `const char*` |
| AUDIO | `INTERRUPT_CONVERSATION` | `p1` | `Any` | `const char*` |
| AUDIO | `INTERRUPT_CONVERSATION` | `p2` | `Any` | `const char*` |
| AUDIO | `_0xB58B8FF3` | `p0` | `Any` | `Any*` |
| AUDIO | `REQUEST_MISSION_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `REQUEST_AMBIENT_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `REQUEST_SCRIPT_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `HINT_AMBIENT_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `HINT_SCRIPT_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `RELEASE_NAMED_SCRIPT_AUDIO_BANK` | `p0` | `Any` | `const char*` |
| AUDIO | `PLAY_SOUND` | `p1` | `Any` | `const char*` |
| AUDIO | `PLAY_SOUND` | `p2` | `Any` | `const char*` |
| AUDIO | `_0xC70E6CFA` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xC70E6CFA` | `p1` | `Any` | `const char*` |
| AUDIO | `SET_VARIABLE_ON_SOUND` | `p1` | `Any` | `const char*` |
| AUDIO | `SET_VARIABLE_ON_STREAM` | `p0` | `Any` | `const char*` |
| AUDIO | `OVERRIDE_UNDERWATER_STREAM` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x62D026BE` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x8386AE28` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x8386AE28` | `p2` | `Any` | `const char*` |
| AUDIO | `_0x8386AE28` | `p3` | `Any` | `const char*` |
| AUDIO | `_0xA1A1402E` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xA1A1402E` | `p1` | `Any` | `const char*` |
| AUDIO | `_0xA1A1402E` | `p5` | `Any` | `const char*` |
| AUDIO | `OVERRIDE_TREVOR_RAGE` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x59A3A17D` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x0E387BFE` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x8BD5F11E` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x498849F3` | `p2` | `Any` | `const char*` |
| AUDIO | `SET_EMITTER_RADIO_STATION` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_EMITTER_RADIO_STATION` | `p1` | `Any` | `const char*` |
| AUDIO | `SET_STATIC_EMITTER_ENABLED` | `p0` | `Any` | `const char*` |
| AUDIO | `FREEZE_RADIO_STATION` | `p0` | `Any` | `const char*` |
| AUDIO | `UNFREEZE_RADIO_STATION` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_INITIAL_PLAYER_STATION` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_RADIO_TRACK` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_RADIO_TRACK` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x128C3873` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x128C3873` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x1D766976` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xB1FF7137` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xBE998184` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xBE998184` | `p1` | `Any` | `const char*` |
| AUDIO | `SET_AMBIENT_ZONE_STATE` | `p0` | `Any` | `const char*` |
| AUDIO | `CLEAR_AMBIENT_ZONE_STATE` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AMBIENT_ZONE_LIST_STATE` | `p0` | `Any` | `const char*` |
| AUDIO | `CLEAR_AMBIENT_ZONE_LIST_STATE` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AMBIENT_ZONE_STATE_PERSISTENT` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT` | `p0` | `Any` | `const char*` |
| AUDIO | `IS_AMBIENT_ZONE_ENABLED` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_CUTSCENE_AUDIO_OVERRIDE` | `p0` | `Any` | `const char*` |
| AUDIO | `GET_PLAYER_HEADSET_SOUND_ALTERNATE` | `p0` | `Any` | `const char*` |
| AUDIO | `LOAD_STREAM` | `p0` | `Any` | `const char*` |
| AUDIO | `LOAD_STREAM` | `p1` | `Any` | `const char*` |
| AUDIO | `LOAD_STREAM_WITH_START_OFFSET` | `p0` | `Any` | `const char*` |
| AUDIO | `LOAD_STREAM_WITH_START_OFFSET` | `p2` | `Any` | `const char*` |
| AUDIO | `_0x33B0B007` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x1C0C5E4C` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x1C0C5E4C` | `p2` | `Any` | `const char*` |
| AUDIO | `START_AUDIO_SCENE` | `p0` | `Any` | `const char*` |
| AUDIO | `STOP_AUDIO_SCENE` | `p0` | `Any` | `const char*` |
| AUDIO | `IS_AUDIO_SCENE_ACTIVE` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AUDIO_SCENE_VARIABLE` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AUDIO_SCENE_VARIABLE` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x2BC93264` | `p1` | `Any` | `const char*` |
| AUDIO | `PREPARE_MUSIC_EVENT` | `p0` | `Any` | `const char*` |
| AUDIO | `CANCEL_MUSIC_EVENT` | `p0` | `Any` | `const char*` |
| AUDIO | `TRIGGER_MUSIC_EVENT` | `p0` | `Any` | `const char*` |
| AUDIO | `PREPARE_ALARM` | `p0` | `Any` | `const char*` |
| AUDIO | `START_ALARM` | `p0` | `Any` | `const char*` |
| AUDIO | `STOP_ALARM` | `p0` | `Any` | `const char*` |
| AUDIO | `IS_ALARM_PLAYING` | `p0` | `Any` | `const char*` |
| AUDIO | `SET_AUDIO_FLAG` | `p0` | `Any` | `const char*` |
| AUDIO | `PREPARE_SYNCHRONIZED_AUDIO_EVENT` | `p0` | `Any` | `const char*` |
| AUDIO | `PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE` | `p1` | `Any` | `const char*` |
| AUDIO | `_0x55A21772` | `p0` | `Any` | `const char*` |
| AUDIO | `_0xA17F9AB0` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x8AD670EC` | `p0` | `Any` | `const char*` |
| AUDIO | `_0x8AD670EC` | `p1` | `Any` | `const char*` |
| AUDIO | `_0xD24B4D0C` | `p0` | `Any` | `const char*` |
| CUTSCENE | `_0xD98F656A` | `p0` | `Any` | `const char*` |
| CUTSCENE | `HAS_THIS_CUTSCENE_LOADED` | `p0` | `Any` | `const char*` |
| CUTSCENE | `_0x47DB08A9` | `p0` | `Any` | `const char*` |
| CUTSCENE | `GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY` | `p0` | `Any` | `const char*` |
| CUTSCENE | `REGISTER_ENTITY_FOR_CUTSCENE` | `p1` | `Any` | `const char*` |
| CUTSCENE | `GET_ENTITY_INDEX_OF_REGISTERED_ENTITY` | `p0` | `Any` | `const char*` |
| CUTSCENE | `CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY` | `p0` | `Any` | `const char*` |
| CUTSCENE | `CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY` | `p0` | `Any` | `const char*` |
| CUTSCENE | `SET_CUTSCENE_PED_COMPONENT_VARIATION` | `p0` | `Any` | `const char*` |
| CUTSCENE | `_0x1E7DA95E` | `p0` | `Any` | `const char*` |
| CUTSCENE | `DOES_CUTSCENE_ENTITY_EXIST` | `p0` | `Any` | `const char*` |
| CUTSCENE | `_0x22E9A9DE` | `p0` | `Any` | `const char*` |
| INTERIOR | `_0x1F6B4B13` | `p0` | `Any` | `const char*` |
| INTERIOR | `ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME` | `p1` | `Any` | `const char*` |
| INTERIOR | `_0xC80A5DDF` | `p1` | `Any` | `const char*` |
| INTERIOR | `_0xDBA768A1` | `p1` | `Any` | `const char*` |
| INTERIOR | `_0x39A3CC6F` | `p1` | `Any` | `const char*` |
| CAM | `SET_CAM_DEBUG_NAME` | `p1` | `Any` | `const char*` |
| CAM | `SHAKE_CAM` | `p1` | `Any` | `const char*` |
| CAM | `ANIMATED_SHAKE_CAM` | `p1` | `Any` | `const char*` |
| CAM | `ANIMATED_SHAKE_CAM` | `p2` | `Any` | `const char*` |
| CAM | `ANIMATED_SHAKE_CAM` | `p3` | `Any` | `const char*` |
| CAM | `_0x2B0F05CD` | `p0` | `Any` | `const char*` |
| CAM | `_0xCB75BD9C` | `p0` | `Any` | `const char*` |
| CAM | `_0xCB75BD9C` | `p1` | `Any` | `const char*` |
| CAM | `_0xCB75BD9C` | `p2` | `Any` | `const char*` |
| CAM | `PLAY_CAM_ANIM` | `p1` | `Any` | `const char*` |
| CAM | `PLAY_CAM_ANIM` | `p2` | `Any` | `const char*` |
| CAM | `IS_CAM_PLAYING_ANIM` | `p1` | `Any` | `const char*` |
| CAM | `IS_CAM_PLAYING_ANIM` | `p2` | `Any` | `const char*` |
| CAM | `PLAY_SYNCHRONIZED_CAM_ANIM` | `p2` | `Any` | `const char*` |
| CAM | `PLAY_SYNCHRONIZED_CAM_ANIM` | `p3` | `Any` | `const char*` |
| CAM | `SHAKE_GAMEPLAY_CAM` | `p0` | `Any` | `const char*` |
| CAM | `SET_FOLLOW_PED_CAM_CUTSCENE_CHAT` | `p0` | `Any` | `const char*` |
| CAM | `SHAKE_CINEMATIC_CAM` | `p0` | `Any` | `const char*` |
| WEAPON | `GET_CURRENT_PED_VEHICLE_WEAPON` | `p1` | `Any` | `Hash*` |
| WEAPON | `GET_AMMO_IN_CLIP` | `p2` | `BOOL` | `int*` |
| WEAPON | `GET_WEAPON_HUD_STATS` | `p1` | `Any` | `Any*` |
| WEAPON | `GET_WEAPON_COMPONENT_HUD_STATS` | `p1` | `Any` | `Any*` |
| STREAMING | `_0x939243FB` | `p1` | `Any` | `const char*` |
| STREAMING | `_0xCD31C872` | `p0` | `Any` | `const char*` |
| STREAMING | `REMOVE_ANIM_DICT` | `p0` | `Any` | `const char*` |
| STREAMING | `REQUEST_ANIM_SET` | `p0` | `Any` | `const char*` |
| STREAMING | `HAS_ANIM_SET_LOADED` | `p0` | `Any` | `const char*` |
| STREAMING | `REMOVE_ANIM_SET` | `p0` | `Any` | `const char*` |
| STREAMING | `_0x403CD434` | `p0` | `Any` | `const char*` |
| STREAMING | `_0x279077B0` | `p0` | `Any` | `const char*` |
| STREAMING | `_0x9EF0A9CF` | `p0` | `Any` | `const char*` |
| STREAMING | `_0x9EF0A9CF` | `p1` | `Any` | `const char*` |
| STREAMING | `PREFETCH_SRL` | `p0` | `Any` | `const char*` |
| UI | `_0xED130FA1` | `p0` | `Any` | `const char*` |
| UI | `_0xED130FA1` | `p5` | `Any` | `const char*` |
| UI | `_0xED130FA1` | `p6` | `Any` | `const char*` |
| UI | `_0x0EB382B7` | `p0` | `Any` | `const char*` |
| UI | `_0x0EB382B7` | `p1` | `Any` | `const char*` |
| UI | `_0x0EB382B7` | `p4` | `Any` | `const char*` |
| UI | `_0x0EB382B7` | `p5` | `Any` | `const char*` |
| UI | `_0x3E807FE3` | `p0` | `Any` | `const char*` |
| UI | `_0x3E807FE3` | `p1` | `Any` | `const char*` |
| UI | `_0x3E807FE3` | `p4` | `Any` | `const char*` |
| UI | `_0x3E807FE3` | `p5` | `Any` | `const char*` |
| UI | `_0x3E807FE3` | `p7` | `Any` | `const char*` |
| UI | `_0xDEB491C8` | `p0` | `Any` | `const char*` |
| UI | `_0xDEB491C8` | `p1` | `Any` | `const char*` |
| UI | `_0xDEB491C8` | `p4` | `Any` | `const char*` |
| UI | `_0xDEB491C8` | `p5` | `Any` | `const char*` |
| UI | `_0xDEB491C8` | `p7` | `Any` | `const char*` |
| UI | `_0x02DED2B8` | `p0` | `Any` | `const char*` |
| UI | `_0x02DED2B8` | `p1` | `Any` | `const char*` |
| UI | `_0x02DED2B8` | `p4` | `Any` | `const char*` |
| UI | `_0xA9CCEF66` | `p2` | `Any` | `int*` |
| UI | `_0xE05E7052` | `p0` | `Any` | `const char*` |
| UI | `_0xE05E7052` | `p2` | `Any` | `const char*` |
| UI | `_0x4FA43BA4` | `p0` | `Any` | `const char*` |
| UI | `_0x4FA43BA4` | `p2` | `Any` | `const char*` |
| UI | `_0x5E93FBFA` | `p0` | `Any` | `const char*` |
| UI | `_0x5E93FBFA` | `p1` | `Any` | `const char*` |
| UI | `_0x5E93FBFA` | `p3` | `Any` | `const char*` |
| UI | `_0x5E93FBFA` | `p4` | `Any` | `const char*` |
| UI | `_0xDD524A11` | `p0` | `Any` | `const char*` |
| UI | `_0x00E20F2D` | `p0` | `Any` | `const char*` |
| UI | `_0xF4C211F6` | `p0` | `Any` | `const char*` |
| UI | `_0x0E103475` | `p0` | `Any` | `const char*` |
| UI | `_0x550665AE` | `p0` | `Any` | `const char*` |
| UI | `_0xBF855650` | `p0` | `Any` | `const char*` |
| UI | `_0x65E1D404` | `p0` | `Any` | `const char*` |
| UI | `_0x0183A66C` | `p0` | `Any` | `const char*` |
| UI | `_0xFA6373BB` | `p0` | `Any` | `const char*` |
| UI | `CLEAR_THIS_PRINT` | `p0` | `Any` | `const char*` |
| UI | `DOES_TEXT_BLOCK_EXIST` | `p0` | `Any` | `const char*` |
| UI | `_0xF4D27EBE` | `p0` | `Any` | `const char*` |
| UI | `HAS_THIS_ADDITIONAL_TEXT_LOADED` | `p0` | `Any` | `const char*` |
| UI | `DOES_TEXT_LABEL_EXIST` | `p0` | `Any` | `const char*` |
| UI | `GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL` | `p0` | `Any` | `const char*` |
| UI | `_0x7DBC0764` | `p0` | `Any` | `const char*` |
| UI | `REGISTER_NAMED_RENDERTARGET` | `p0` | `Any` | `const char*` |
| UI | `IS_NAMED_RENDERTARGET_REGISTERED` | `p0` | `Any` | `const char*` |
| UI | `RELEASE_NAMED_RENDERTARGET` | `p0` | `Any` | `const char*` |
| UI | `GET_NAMED_RENDERTARGET_RENDER_ID` | `p0` | `Any` | `const char*` |
| UI | `REMOVE_BLIP` | `BlipID` | `int` | `Blip*` |
| UI | `SET_MISSION_NAME` | `p1` | `Any` | `const char*` |
| UI | `_0x8D9A1734` | `p1` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p1` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p2` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p3` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p4` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p5` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p6` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p7` | `Any` | `const char*` |
| UI | `_0xD2161E77` | `p8` | `Any` | `const char*` |
| UI | `_0xC969F2D0` | `p1` | `Any` | `const char*` |
| UI | `_0xC969F2D0` | `p4` | `Any` | `const char*` |
| UI | `_0xF5CD2AA4` | `p1` | `Any` | `const char*` |
| UI | `_0xF5CD2AA4` | `p4` | `Any` | `const char*` |
| UI | `_0x627A559B` | `p1` | `Any` | `const char*` |
| UI | `_0x939218AB` | `p1` | `Any` | `const char*` |
| UI | `SET_WARNING_MESSAGE` | `p0` | `Any` | `const char*` |
| UI | `SET_WARNING_MESSAGE` | `p2` | `Any` | `const char*` |
| UI | `SET_WARNING_MESSAGE` | `p5` | `Any` | `const char*` |
| UI | `SET_WARNING_MESSAGE` | `p6` | `Any` | `const char*` |
| UI | `_0x2DB9EAB5` | `p0` | `Any` | `const char*` |
| UI | `_0x2DB9EAB5` | `p1` | `Any` | `const char*` |
| UI | `_0x2DB9EAB5` | `p3` | `Any` | `const char*` |
| UI | `_0x2DB9EAB5` | `p6` | `Any` | `Any*` |
| UI | `_0x2DB9EAB5` | `p7` | `Any` | `Any*` |
| UI | `SET_DANCE_MAPPERS` | `p0` | `Any` | `const char*` |
| UI | `SET_DANCE_MAPPERS` | `p1` | `Any` | `const char*` |
| UI | `SET_DANCE_MAPPERS` | `p3` | `Any` | `const char*` |
| UI | `SET_DANCE_MAPPERS` | `p7` | `Any` | `const char*` |
| UI | `SET_DANCE_MAPPERS` | `p8` | `Any` | `const char*` |
| UI | `_0x2DFD35C7` | `p0` | `Any` | `const char*` |
| UI | `_0x8543AAC8` | `p0` | `Any` | `int*` |
| UI | `_0x8543AAC8` | `p1` | `Any` | `int*` |
| UI | `_0x6025AA2F` | `p0` | `Any` | `int*` |
| UI | `_0x6025AA2F` | `p1` | `Any` | `int*` |
| UI | `_0x6025AA2F` | `p2` | `Any` | `int*` |
| UI | `_0x46794EB2` | `p0` | `Any` | `int*` |
| UI | `_0x46794EB2` | `p1` | `Any` | `int*` |
| UI | `_0x46794EB2` | `p2` | `Any` | `int*` |
| UI | `SET_USERIDS_UIHIDDEN` | `p1` | `Any` | `Any*` |
| UI | `_0xD6CC4766` | `p1` | `Any` | `int*` |
| UI | `_0x51972B04` | `p1` | `Any` | `float*` |
| UI | `_0xD43BB56D` | `p1` | `Any` | `BOOL*` |
| UI | `_0x7AD67C95` | `p0` | `Any` | `const char*` |
| GRAPHICS | `DRAW_DEBUG_TEXT` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x56C1E488` | `p0` | `Any` | `Any*` |
| GRAPHICS | `_0x226B08EA` | `p0` | `Any` | `Any*` |
| GRAPHICS | `ADD_ENTITY_ICON` | `p1` | `Any` | `const char*` |
| GRAPHICS | `LOAD_MOVIE_MESH_SET` | `p0` | `Any` | `const char*` |
| GRAPHICS | `GET_TEXTURE_RESOLUTION` | `p0` | `Any` | `const char*` |
| GRAPHICS | `GET_TEXTURE_RESOLUTION` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0xDE10BA1F` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0xD63FCB3E` | `p0` | `Any` | `const char*` |
| GRAPHICS | `START_PARTICLE_FX_NON_LOOPED_AT_COORD` | `p0` | `Any` | `const char*` |
| GRAPHICS | `START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x161780C1` | `p0` | `Any` | `const char*` |
| GRAPHICS | `START_PARTICLE_FX_NON_LOOPED_ON_ENTITY` | `p0` | `Any` | `const char*` |
| GRAPHICS | `START_PARTICLE_FX_LOOPED_ON_PED_BONE` | `p0` | `Any` | `const char*` |
| GRAPHICS | `START_PARTICLE_FX_LOOPED_ON_ENTITY` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x110752B2` | `p0` | `Any` | `const char*` |
| GRAPHICS | `SET_PARTICLE_FX_LOOPED_EVOLUTION` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0xC92719A7` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0xC92719A7` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x9E8D8B72` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x335695CF` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x335695CF` | `p2` | `Any` | `const char*` |
| GRAPHICS | `_0x0F486429` | `p0` | `Any` | `const char*` |
| GRAPHICS | `SET_TRANSITION_TIMECYCLE_MODIFIER` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x85BA15A4` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x554BA16E` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0xE8F538B5` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0xE8F538B5` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x7CC8057D` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x7AB77B57` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x557EDA1D` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p2` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p3` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p4` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p5` | `Any` | `const char*` |
| GRAPHICS | `_0x91A7FCEB` | `p6` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p7` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p8` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p9` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p10` | `Any` | `const char*` |
| GRAPHICS | `_0x6EAF56DE` | `p11` | `Any` | `const char*` |
| GRAPHICS | `_0x5D66CE1E` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0xF6015178` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x5E219B67` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0xB262DE67` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x78C4DCBE` | `p1` | `Any` | `const char*` |
| GRAPHICS | `_0x2E7D9B98` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x9A0E3BFE` | `p0` | `Any` | `const char*` |
| GRAPHICS | `_0x089D5921` | `p0` | `Any` | `const char*` |
| STATS | `_0xC1224AA7` | `p1` | `Any` | `const char*` |
| STATS | `STAT_SET_DATE` | `p1` | `Any` | `Any*` |
| STATS | `STAT_SET_USER_ID` | `p1` | `Any` | `const char*` |
| STATS | `STAT_GET_DATE` | `p1` | `Any` | `Any*` |
| STATS | `STAT_GET_POS` | `p1` | `Any` | `float*` |
| STATS | `STAT_GET_POS` | `p2` | `Any` | `float*` |
| STATS | `STAT_GET_POS` | `p3` | `Any` | `float*` |
| STATS | `STAT_GET_MASKED_INT` | `p1` | `Any` | `int*` |
| STATS | `_0x3507D253` | `p1` | `Any` | `const char*` |
| STATS | `_0xC4110917` | `p2` | `Any` | `float*` |
| STATS | `_0x61ECC465` | `p0` | `Any` | `const char*` |
| STATS | `PLAYSTATS_NPC_INVITE` | `p0` | `Any` | `const char*` |
| STATS | `PLAYSTATS_MISSION_STARTED` | `p0` | `Any` | `const char*` |
| STATS | `PLAYSTATS_MISSION_OVER` | `p0` | `Any` | `const char*` |
| STATS | `PLAYSTATS_MISSION_CHECKPOINT` | `p0` | `Any` | `const char*` |
| STATS | `_0xAC2C7C63` | `p0` | `Any` | `const char*` |
| STATS | `_0x489E27E7` | `p0` | `Any` | `int*` |
| STATS | `_0x489E27E7` | `p1` | `Any` | `int*` |
| STATS | `PLAYSTATS_CHEAT_APPLIED` | `p0` | `Any` | `const char*` |
| STATS | `_0x04181752` | `p0` | `Any` | `Any*` |
| STATS | `_0x04181752` | `p1` | `Any` | `Any*` |
| STATS | `_0x04181752` | `p2` | `Any` | `Any*` |
| STATS | `_0x04181752` | `p3` | `Any` | `Any*` |
| STATS | `_0x31002201` | `p0` | `Any` | `Any*` |
| STATS | `_0x31002201` | `p1` | `Any` | `Any*` |
| STATS | `_0x31002201` | `p2` | `Any` | `Any*` |
| STATS | `_0x31002201` | `p3` | `Any` | `Any*` |
| STATS | `_0xDDD1F1F3` | `p0` | `Any` | `Any*` |
| STATS | `_0xDDD1F1F3` | `p1` | `Any` | `Any*` |
| STATS | `_0xDDD1F1F3` | `p2` | `Any` | `Any*` |
| STATS | `_0xDDD1F1F3` | `p3` | `Any` | `Any*` |
| STATS | `_0x66FEB701` | `p1` | `Any` | `const char*` |
| STATS | `LEADERBOARDS2_READ_FRIENDS_BY_ROW` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_FRIENDS_BY_ROW` | `p1` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_HANDLE` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_HANDLE` | `p1` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_RANK` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_RADIUS` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_RADIUS` | `p2` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_SCORE_INT` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_READ_BY_SCORE_FLOAT` | `p0` | `Any` | `Any*` |
| STATS | `_0x9BEC3401` | `p0` | `Any` | `Any*` |
| STATS | `_0x9BEC3401` | `p1` | `Any` | `Any*` |
| STATS | `_0x9BEC3401` | `p2` | `Any` | `Any*` |
| STATS | `_0xC977D6E2` | `p0` | `Any` | `Any*` |
| STATS | `_0x766A74FE` | `p1` | `Any` | `Any*` |
| STATS | `LEADERBOARDS2_WRITE_DATA` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS_CACHE_DATA_ROW` | `p0` | `Any` | `Any*` |
| STATS | `LEADERBOARDS_GET_CACHE_DATA_ROW` | `p2` | `Any` | `Any*` |
| STATS | `_0x2FFD2FA5` | `p3` | `Any` | `const char*` |
| STATS | `_0x62C19A3D` | `p0` | `Any` | `Any*` |
| STATS | `_0x62C19A3D` | `p1` | `Any` | `Any*` |
| STATS | `_0xE3F0D62D` | `p0` | `Any` | `Any*` |
| BRAIN | `ADD_SCRIPT_TO_RANDOM_PED` | `p0` | `Any` | `const char*` |
| BRAIN | `REGISTER_OBJECT_SCRIPT_BRAIN` | `p0` | `Any` | `const char*` |
| BRAIN | `REGISTER_WORLD_POINT_SCRIPT_BRAIN` | `p0` | `Any` | `const char*` |
| BRAIN | `_0x949FE53E` | `p0` | `Any` | `const char*` |
| BRAIN | `_0x29CE8BAA` | `p0` | `Any` | `const char*` |
| MOBILE | `GET_MOBILE_PHONE_ROTATION` | `p0` | `Any` | `Vector3*` |
| MOBILE | `GET_MOBILE_PHONE_POSITION` | `p0` | `Any` | `Vector3*` |
| APP | `APP_GET_INT` | `p0` | `Any` | `const char*` |
| APP | `APP_GET_FLOAT` | `p0` | `Any` | `const char*` |
| APP | `APP_GET_STRING` | `p0` | `Any` | `const char*` |
| APP | `APP_SET_INT` | `p0` | `Any` | `const char*` |
| APP | `APP_SET_FLOAT` | `p0` | `Any` | `const char*` |
| APP | `APP_SET_STRING` | `p0` | `Any` | `const char*` |
| APP | `APP_SET_STRING` | `p1` | `Any` | `const char*` |
| APP | `APP_SET_APP` | `p0` | `Any` | `const char*` |
| APP | `APP_SET_BLOCK` | `p0` | `Any` | `const char*` |
| APP | `APP_HAS_SYNCED_DATA` | `p0` | `Vehicle` | `const char*` |
| APP | `APP_DELETE_APP_DATA` | `p0` | `Any` | `const char*` |
| TIME | `GET_POSIX_TIME` | `p0` | `Any` | `int*` |
| TIME | `GET_POSIX_TIME` | `p1` | `Any` | `int*` |
| TIME | `GET_POSIX_TIME` | `p2` | `Any` | `int*` |
| TIME | `GET_POSIX_TIME` | `p3` | `Any` | `int*` |
| TIME | `GET_POSIX_TIME` | `p4` | `Any` | `int*` |
| TIME | `GET_POSIX_TIME` | `p5` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p0` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p1` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p2` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p3` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p4` | `Any` | `int*` |
| TIME | `GET_LOCAL_TIME` | `p5` | `Any` | `int*` |
| PATHFIND | `GET_CLOSEST_MAJOR_VEHICLE_NODE` | `p3` | `Any` | `Vector3*` |
| PATHFIND | `GET_CLOSEST_VEHICLE_NODE_WITH_HEADING` | `p3` | `Any` | `Vector3*` |
| PATHFIND | `GET_CLOSEST_VEHICLE_NODE_WITH_HEADING` | `p4` | `Any` | `float*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE` | `p4` | `Any` | `Vector3*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING` | `p4` | `Any` | `Vector3*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING` | `p5` | `Any` | `float*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING` | `p6` | `Any` | `int*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING` | `p4` | `Any` | `float*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING` | `p5` | `Any` | `int*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION` | `p7` | `Any` | `Vector3*` |
| PATHFIND | `GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION` | `p8` | `Any` | `float*` |
| PATHFIND | `GET_VEHICLE_NODE_PROPERTIES` | `p3` | `Any` | `int*` |
| PATHFIND | `GET_VEHICLE_NODE_PROPERTIES` | `p4` | `Any` | `int*` |
| PATHFIND | `GET_VEHICLE_NODE_POSITION` | `p1` | `Any` | `Vector3*` |
| PATHFIND | `GET_CLOSEST_ROAD` | `p5` | `Any` | `Vector3*` |
| PATHFIND | `GET_CLOSEST_ROAD` | `p6` | `Any` | `Vector3*` |
| PATHFIND | `GET_CLOSEST_ROAD` | `p7` | `Any` | `Any*` |
| PATHFIND | `GET_CLOSEST_ROAD` | `p8` | `Any` | `Any*` |
| PATHFIND | `GET_CLOSEST_ROAD` | `p9` | `Any` | `float*` |
| PATHFIND | `GET_RANDOM_VEHICLE_NODE` | `p7` | `Any` | `Vector3*` |
| PATHFIND | `GET_RANDOM_VEHICLE_NODE` | `p8` | `Any` | `int*` |
| PATHFIND | `GET_STREET_NAME_AT_COORD` | `p3` | `Any` | `Hash*` |
| PATHFIND | `GET_STREET_NAME_AT_COORD` | `p4` | `Any` | `Hash*` |
| PATHFIND | `GENERATE_DIRECTIONS_TO_COORD` | `p4` | `Any` | `int*` |
| PATHFIND | `GENERATE_DIRECTIONS_TO_COORD` | `p5` | `Any` | `float*` |
| PATHFIND | `GENERATE_DIRECTIONS_TO_COORD` | `p6` | `Any` | `float*` |
| PATHFIND | `_0xF6422F9A` | `p4` | `Any` | `Vector3*` |
| CONTROLS | `_0xBBFC9050` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0xF09157B0` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xF09157B0` | `p2` | `Any` | `const char*` |
| DATAFILE | `_0xF09157B0` | `p3` | `Any` | `const char*` |
| DATAFILE | `_0xF09157B0` | `p4` | `Any` | `const char*` |
| DATAFILE | `_0xF09157B0` | `p5` | `Any` | `const char*` |
| DATAFILE | `_0xD96860FC` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0xD96860FC` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xD96860FC` | `p2` | `Any` | `const char*` |
| DATAFILE | `_0xD96860FC` | `p3` | `Any` | `const char*` |
| DATAFILE | `_0x459F2683` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0x459F2683` | `p1` | `Any` | `Any*` |
| DATAFILE | `_0x459F2683` | `p3` | `Any` | `const char*` |
| DATAFILE | `_0x459F2683` | `p4` | `Any` | `const char*` |
| DATAFILE | `_0x459F2683` | `p5` | `Any` | `const char*` |
| DATAFILE | `_0x459F2683` | `p6` | `Any` | `const char*` |
| DATAFILE | `_0xDBB83E2B` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0xDBB83E2B` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xDBB83E2B` | `p2` | `Any` | `const char*` |
| DATAFILE | `_0xDBB83E2B` | `p3` | `Any` | `const char*` |
| DATAFILE | `_0xDBB83E2B` | `p4` | `Any` | `const char*` |
| DATAFILE | `_0xBB6321BD` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0xBB6321BD` | `p2` | `Any` | `const char*` |
| DATAFILE | `_0x660C468E` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0x768CBB35` | `p0` | `Any` | `const char*` |
| DATAFILE | `_0x0B4087F7` | `p0` | `Any` | `BOOL*` |
| DATAFILE | `_0x9B29D99B` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x9B29D99B` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xEFCF554A` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xEFCF554A` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xE972CACF` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xE972CACF` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xD437615C` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xD437615C` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xD437615C` | `p2` | `Any` | `const char*` |
| DATAFILE | `_0x75FC6C3C` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x75FC6C3C` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x96A8E05F` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x96A8E05F` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x03939B8D` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x03939B8D` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x8876C872` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x8876C872` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xA6C68693` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xA6C68693` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xA92C1AF4` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xA92C1AF4` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x942160EC` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x942160EC` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xE84A127A` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xE84A127A` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0xC9C13D8D` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xC9C13D8D` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x1F2F7D00` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x1F2F7D00` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x2678342A` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x2678342A` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x08174B90` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xF29C0B36` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xE4302123` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xF3C01350` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xF3C01350` | `p1` | `Any` | `const char*` |
| DATAFILE | `_0x16F464B6` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xC174C71B` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xA2E5F921` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xBB120CFC` | `p0` | `Any` | `Any*` |
| DATAFILE | `FOCUS_USE_SPLINE` | `p0` | `Any` | `Any*` |
| DATAFILE | `OVERIDE_TEXTURENAMES` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0x80E3DA55` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xECE81278` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xA8A21766` | `p0` | `Any` | `Any*` |
| DATAFILE | `_0xFA2402C8` | `p0` | `Any` | `Any*` |
| FIRE | `GET_CLOSEST_FIRE_POS` | `p0` | `Any` | `Vector3*` |
| ZONE | `_0x8EC68304` | `p0` | `Any` | `const char*` |
| ROPE | `ADD_ROPE` | `p16` | `int` | `Any*` |
| ROPE | `_0x51523B8C` | `p0` | `Any` | `int*` |
| ROPE | `ATTACH_ENTITIES_TO_ROPE` | `p12` | `BOOL` | `Any*` |
| ROPE | `ATTACH_ENTITIES_TO_ROPE` | `p13` | `BOOL` | `Any*` |
| ROPE | `_0x7A18BB9C` | `p0` | `Any` | `int*` |
| WATER | `GET_WATER_HEIGHT` | `p3` | `float` | `float*` |
| WATER | `GET_WATER_HEIGHT_NO_WAVES` | `p3` | `Any` | `float*` |
| WATER | `_0xAA4AE00C` | `p6` | `Any` | `Vector3*` |
| WATER | `_0x4A962D55` | `p7` | `Any` | `float*` |
| WATER | `_0x4C71D143` | `p4` | `Any` | `float*` |
| WORLDPROBE | `_0x4301E10C` | `p1` | `Any` | `BOOL*` |
| WORLDPROBE | `_0x4301E10C` | `p2` | `Any` | `Vector3*` |
| WORLDPROBE | `_0x4301E10C` | `p3` | `Any` | `Vector3*` |
| WORLDPROBE | `_0x4301E10C` | `p4` | `Any` | `Hash*` |
| WORLDPROBE | `_0x4301E10C` | `p5` | `Any` | `Entity*` |
| NETWORK | `_0xA520B982` | `p0` | `Any` | `int*` |
| NETWORK | `_0x0EC62629` | `p0` | `Any` | `int*` |
| NETWORK | `_0x74E8C53E` | `p0` | `Any` | `int*` |
| NETWORK | `_0x74E8C53E` | `p1` | `Any` | `int*` |
| NETWORK | `_0x74E8C53E` | `p2` | `Any` | `int*` |
| NETWORK | `_0xB5ABC4B4` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_SESSION_GET_INVITER` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_SEND_TEXT_MESSAGE` | `FreeMemPointer` | `int` | `Any*` |
| NETWORK | `NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x5CE60A11` | `p4` | `Any` | `Any*` |
| NETWORK | `NETWORK_SET_TRANSITION_CREATOR_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_INVITE_GAMERS_TO_TRANSITION` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_SET_GAMER_INVITED_TO_TRANSITION` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_DO_TRANSITION_TO_FREEMODE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_DO_TRANSITION_TO_NEW_FREEMODE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_GET_TRANSITION_MEMBERS` | `p0` | `Any` | `Any*` |
| NETWORK | `_0xE0C28DB5` | `p1` | `Any` | `const char*` |
| NETWORK | `NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_IS_TRANSITION_HOST_FROM_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_GET_TRANSITION_HOST` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x4F41DF6B` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x8B99B72B` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x8B99B72B` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x877C0E1C` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x877C0E1C` | `p1` | `Any` | `const char*` |
| NETWORK | `NETWORK_GET_PRESENCE_INVITE_HANDLE` | `p1` | `Any` | `Any*` |
| NETWORK | `NETWORK_REMOVE_TRANSITION_INVITE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_INVITE_GAMERS` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_INVITE_GAMERS` | `p2` | `Any` | `Any*` |
| NETWORK | `_0xEC651BC0` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x0808D4CC` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x0808D4CC` | `p1` | `Any` | `Any*` |
| NETWORK | `_0x11378777` | `p0` | `Any` | `Any*` |
| NETWORK | `FILLOUT_PM_PLAYER_LIST` | `p0` | `Any` | `Any*` |
| NETWORK | `FILLOUT_PM_PLAYER_LIST_WITH_NAMES` | `p0` | `Any` | `Any*` |
| NETWORK | `FILLOUT_PM_PLAYER_LIST_WITH_NAMES` | `p1` | `Any` | `Any*` |
| NETWORK | `_0xF30E5814` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x51367B34` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x4C2C6B6A` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_REGISTER_HOST_BROADCAST_VARIABLES` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_IS_SCRIPT_ACTIVE` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x8F7D9F46` | `p0` | `Any` | `const char*` |
| NETWORK | `_0xCEA55F4C` | `p1` | `Any` | `const char*` |
| NETWORK | `NETWORK_GET_DESTROYER_OF_NETWORK_ID` | `p1` | `Any` | `Hash*` |
| NETWORK | `_0x28A45454` | `p2` | `Any` | `int*` |
| NETWORK | `NETWORK_GET_ENTITY_KILLER_OF_PLAYER` | `p1` | `Any` | `Hash*` |
| NETWORK | `NETWORK_GET_LOCAL_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_HANDLE_FROM_FRIEND` | `p1` | `Any` | `Any*` |
| NETWORK | `NETWORK_GAMERTAG_FROM_HANDLE_START` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_ARE_HANDLES_THE_SAME` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_ARE_HANDLES_THE_SAME` | `p1` | `Any` | `Any*` |
| NETWORK | `NETWORK_GET_PLAYER_FROM_GAMER_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_MEMBER_ID_FROM_GAMER_HANDLE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_IS_GAMER_IN_MY_SESSION` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_SHOW_PROFILE_UI` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x4EC0D983` | `p1` | `Any` | `int*` |
| NETWORK | `NETWORK_IS_INACTIVE_PROFILE` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_IS_FRIEND_IN_SAME_TITLE` | `p0` | `Any` | `const char*` |
| NETWORK | `NETWORK_IS_FRIEND_IN_MULTIPLAYER` | `p0` | `Any` | `const char*` |
| NETWORK | `NETWORK_IS_FRIEND` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_ADD_FRIEND` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_ADD_FRIEND` | `p1` | `Any` | `const char*` |
| NETWORK | `NETWORK_GAMER_HAS_HEADSET` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_IS_GAMER_TALKING` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_CAN_COMMUNICATE_WITH_GAMER` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_IS_GAMER_MUTED_BY_ME` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x7685B333` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x3FDCC8D7` | `p0` | `Any` | `Any*` |
| NETWORK | `_0xD19B312C` | `p0` | `Any` | `Any*` |
| NETWORK | `_0xF633805A` | `p0` | `Any` | `Any*` |
| NETWORK | `_0xF633805A` | `p2` | `Any` | `char*` |
| NETWORK | `_0x3369DD1F` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_CLAN_DOWNLOAD_MEMBERSHIP` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x40202867` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_CLAN_GET_MEMBERSHIP_COUNT` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_CLAN_GET_MEMBERSHIP_VALID` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_CLAN_GET_MEMBERSHIP` | `p0` | `Any` | `int*` |
| NETWORK | `NETWORK_CLAN_GET_MEMBERSHIP` | `p1` | `Any` | `Any*` |
| NETWORK | `_0xBDA90BAC` | `p0` | `Any` | `const char*` |
| NETWORK | `_0xBDA90BAC` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x8E952B12` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xBA672146` | `p0` | `Any` | `Any*` |
| NETWORK | `_0xBA672146` | `p1` | `Any` | `char*` |
| NETWORK | `_0x88B13CDC` | `p1` | `Any` | `Any*` |
| NETWORK | `_0x89DB0EC7` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x9B8631EB` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x9B8631EB` | `p1` | `Any` | `Any*` |
| NETWORK | `_0xBB7CCE49` | `p1` | `Any` | `Any*` |
| NETWORK | `_0xBFFE8B5C` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xBFFE8B5C` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x90700C7D` | `p0` | `Any` | `Any*` |
| NETWORK | `NETWORK_GET_RESPAWN_RESULT` | `p1` | `Any` | `Vector3*` |
| NETWORK | `NETWORK_GET_RESPAWN_RESULT` | `p2` | `Any` | `float*` |
| NETWORK | `NETWORK_DOES_TUNABLE_EXIST` | `p0` | `Any` | `const char*` |
| NETWORK | `NETWORK_DOES_TUNABLE_EXIST` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xE4B3726A` | `p0` | `Any` | `const char*` |
| NETWORK | `_0xE4B3726A` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xE4B3726A` | `p2` | `Any` | `int*` |
| NETWORK | `_0x41E8912A` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x41E8912A` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x41E8912A` | `p2` | `Any` | `float*` |
| NETWORK | `_0x8A04E1FE` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x8A04E1FE` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x365C50EE` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x365C50EE` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x2B7B57B3` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x08243B79` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x08243B79` | `p1` | `Any` | `Any*` |
| NETWORK | `_0xCBA7242F` | `p2` | `Any` | `Any*` |
| NETWORK | `_0xDED82A6E` | `p0` | `Any` | `const char*` |
| NETWORK | `_0xDED82A6E` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x40CF0783` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x4609D596` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x4609D596` | `p3` | `Any` | `Any*` |
| NETWORK | `_0x4C2C0D1F` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x4C2C0D1F` | `p3` | `Any` | `Any*` |
| NETWORK | `_0x9EFBD5D1` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x9EFBD5D1` | `p3` | `Any` | `Any*` |
| NETWORK | `_0xA6D8B798` | `p3` | `Any` | `const char*` |
| NETWORK | `_0xA6D8B798` | `p4` | `Any` | `Any*` |
| NETWORK | `_0x67E74842` | `p3` | `Any` | `const char*` |
| NETWORK | `_0x67E74842` | `p4` | `Any` | `Any*` |
| NETWORK | `SET_BALANCE_ADD_MACHINE` | `p0` | `Any` | `const char*` |
| NETWORK | `SET_BALANCE_ADD_MACHINE` | `p1` | `Any` | `const char*` |
| NETWORK | `SET_BALANCE_ADD_MACHINES` | `p0` | `Any` | `Any*` |
| NETWORK | `SET_BALANCE_ADD_MACHINES` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x37F5BD93` | `p2` | `Any` | `Any*` |
| NETWORK | `_0x37F5BD93` | `p3` | `Any` | `Any*` |
| NETWORK | `_0x1CFB3F51` | `p2` | `Any` | `Any*` |
| NETWORK | `_0x1CFB3F51` | `p3` | `Any` | `Any*` |
| NETWORK | `_0x87D1E6BD` | `p2` | `Any` | `Any*` |
| NETWORK | `_0x87D1E6BD` | `p3` | `Any` | `Any*` |
| NETWORK | `_0xA19A238D` | `p1` | `Any` | `Any*` |
| NETWORK | `_0x38FC2EEB` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x38FC2EEB` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xAD334B40` | `p0` | `Any` | `const char*` |
| NETWORK | `_0xAD334B40` | `p1` | `Any` | `const char*` |
| NETWORK | `_0xAD334B40` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x980D45D7` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x980D45D7` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x48CCC328` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x48CCC328` | `p2` | `Any` | `const char*` |
| NETWORK | `_0x9567392B` | `p0` | `Any` | `Any*` |
| NETWORK | `_0x9567392B` | `p1` | `Any` | `Any*` |
| NETWORK | `_0x30B51753` | `p0` | `Any` | `const char*` |
| NETWORK | `TEXTURE_DOWNLOAD_REQUEST` | `PlayerHandle` | `int` | `Any*` |
| NETWORK | `_0x1856D008` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x1856D008` | `p1` | `Any` | `const char*` |
| NETWORK | `_0x68C9AF69` | `p0` | `Any` | `const char*` |
| NETWORK | `_0x68C9AF69` | `p4` | `Any` | `const char*` |
| NETWORK | `_0x8570DD34` | `p1` | `Any` | `int*` |
| NETWORK | `_0x8570DD34` | `p2` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_GIVE_PLAYER_JOBSHARE_CASH` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_EARN_FROM_BOUNTY` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_EARN_FROM_BOUNTY` | `p2` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_BUY_ITEM` | `p5` | `Any` | `const char*` |
| NETWORKCASH | `NETWORK_SPENT_BUY_WANTEDLEVEL` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM` | `p2` | `Any` | `Any*` |
| NETWORKCASH | `NETWORK_SPENT_CALL_PLAYER` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `_0xC5D8B1E9` | `p0` | `Any` | `int*` |
| NETWORKCASH | `_0xC5D8B1E9` | `p1` | `Any` | `int*` |
| NETWORKCASH | `_0x07C92F21` | `p1` | `Any` | `const char*` |
| NETWORKCASH | `_0x07C92F21` | `p2` | `Any` | `const char*` |
| NETWORKCASH | `NETWORK_EARN_FROM_BETTING` | `p1` | `Any` | `const char*` |
| NETWORKCASH | `NETWORK_EARN_FROM_JOB` | `p1` | `Any` | `const char*` |
| NETWORKCASH | `_0x2BEFB6C4` | `p1` | `Any` | `Any*` |
| NETWORKCASH | `_0x224A3488` | `p1` | `Any` | `const char*` |
| NETWORKCASH | `NETWORK_SPENT_BETTING` | `p2` | `Any` | `const char*` |
| DLC1 | `_0x2E9D628C` | `p2` | `Any` | `Any*` |
| DLC1 | `INIT_SHOP_PED_COMPONENT` | `p0` | `Any` | `Any*` |
| DLC1 | `INIT_SHOP_PED_PROP` | `p0` | `Any` | `Any*` |
| DLC1 | `GET_SHOP_PED_QUERY_COMPONENT` | `p1` | `Any` | `Any*` |
| DLC1 | `GET_SHOP_PED_COMPONENT` | `p1` | `Any` | `Any*` |
| DLC1 | `GET_SHOP_PED_QUERY_PROP` | `p1` | `Any` | `Any*` |
| DLC1 | `GET_SHOP_PED_PROP` | `p1` | `Any` | `Any*` |
| DLC1 | `_0xE4FF7103` | `p2` | `Any` | `Hash*` |
| DLC1 | `_0xE4FF7103` | `p3` | `Any` | `int*` |
| DLC1 | `_0xE4FF7103` | `p4` | `Any` | `int*` |
| DLC1 | `GET_FORCED_COMPONENT` | `p2` | `Any` | `Hash*` |
| DLC1 | `GET_FORCED_COMPONENT` | `p3` | `Any` | `int*` |
| DLC1 | `GET_FORCED_COMPONENT` | `p4` | `Any` | `int*` |
| DLC1 | `GET_FORCED_PROP` | `p2` | `Any` | `Hash*` |
| DLC1 | `GET_FORCED_PROP` | `p3` | `Any` | `int*` |
| DLC1 | `GET_FORCED_PROP` | `p4` | `Any` | `int*` |
| DLC1 | `GET_SHOP_PED_QUERY_OUTFIT` | `p1` | `Any` | `Any*` |
| DLC1 | `_0xCAFE9209` | `p1` | `Any` | `Any*` |
| DLC1 | `_0x6641A864` | `p2` | `Any` | `Any*` |
| DLC1 | `_0x818534AC` | `p2` | `Any` | `Any*` |
| DLC1 | `GET_DLC_VEHICLE_DATA` | `p1` | `Any` | `Any*` |
| DLC1 | `GET_DLC_WEAPON_DATA` | `p1` | `Any` | `Any*` |
| DLC1 | `GET_DLC_WEAPON_COMPONENT_DATA` | `p2` | `Any` | `Any*` |
| DLC2 | `_0x6087C10C` | `p0` | `Any` | `BOOL*` |
| SYSTEM | `START_NEW_SCRIPT_WITH_ARGS` | `Args` | `Any` | `Any*` |
| SYSTEM | `_NULL_START_NEW_SCRIPT_WITH_ARGS` | `p1` | `Any` | `Any*` |
| DECORATOR | `_0xBBAEEF94` | `p1` | `Any` | `const char*` |
| DECORATOR | `_0x8E101F5C` | `p1` | `Any` | `const char*` |
| DECORATOR | `_0xDBCE51E0` | `p1` | `Any` | `const char*` |
| DECORATOR | `_0x74EF9C40` | `p1` | `Any` | `const char*` |
| DECORATOR | `_0xE0E2640B` | `p1` | `Any` | `const char*` |
| DECORATOR | `_0x68BD42A9` | `p0` | `Any` | `const char*` |
| DECORATOR | `_0x7CF0971D` | `p0` | `Any` | `const char*` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_DATA_INT` | `p1` | `Any` | `const char*` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_DATA_INT` | `p2` | `Any` | `int*` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_DATA_STRING` | `p1` | `Any` | `const char*` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_DATA_STRING` | `p2` | `Any` | `char*` |
| UNK_SC | `_0x75324674` | `p0` | `Any` | `Any*` |
| UNK_SC | `SC_INBOX_MESSAGE_GET_UGCDATA` | `p1` | `Any` | `Any*` |
| UNK_SC | `_0xAB3346B5` | `p1` | `Any` | `Any*` |
| UNK_SC | `_0x9A703A2B` | `p0` | `Any` | `Any*` |
| UNK_SC | `_0xAF3C081B` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0x3ACE6D6B` | `p1` | `Any` | `const char*` |
| UNK_SC | `_0xDF45B2A7` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0xDF084A6B` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0xDF084A6B` | `p1` | `Any` | `int*` |
| UNK_SC | `_0x7AA36406` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0x7AA36406` | `p1` | `Any` | `int*` |
| UNK_SC | `_0x8E7AEEB7` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0xE778B2A7` | `p1` | `Any` | `const char*` |
| UNK_SC | `_0xE778B2A7` | `p2` | `Any` | `int*` |
| UNK_SC | `_0xCE7D50A8` | `p1` | `Any` | `const char*` |
| UNK_SC | `_0xCE7D50A8` | `p2` | `Any` | `char*` |
| UNK_SC | `_0xD26CCA46` | `p1` | `Any` | `char*` |
| UNK_SC | `_0xAED95A6F` | `p0` | `Any` | `const char*` |
| UNK_SC | `_0xAED95A6F` | `p1` | `Any` | `int*` |

## Ajustes de firma aplicados automáticamente

PS3 pasaba estos handles por puntero; el native de PS4 los recibe por valor,
así que se genera `*param` automáticamente.

| namespace | native | param | tipo PS3 | tipo 1.57 |
|---|---|---|---|---|
| PLAYER | `_0x3A7E5FB6` | `p0f` | `float*` | `Player` |
| PLAYER | `GET_PLAYER_CURRENT_STEALTH_NOISE` | `p0` | `Vehicle*` | `Player` |
| PED | `_0xFC70EEC7` | `pedHandle` | `Ped*` | `Ped` |
| PED | `IS_PED_AIMING_FROM_COVER` | `p0` | `Player*` | `Ped` |
| OBJECT | `CREATE_OBJECT_2` | `coord` | `float *` | `float` |
| OBJECT | `CREATE_MONEY_PICKUPS` | `XCoord` | `float*` | `float` |
| OBJECT | `CREATE_MONEY_PICKUPS` | `YCoord` | `float*` | `float` |
| OBJECT | `CREATE_MONEY_PICKUPS` | `ZCoord` | `float*` | `float` |
| GAMEPLAY | `CLEAR_AREA_OF_PEDS` | `XCoord` | `float*` | `float` |
| GAMEPLAY | `CLEAR_AREA_OF_PEDS` | `YCoord` | `float*` | `float` |
| GAMEPLAY | `CLEAR_AREA_OF_PEDS` | `zCoord` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `StartPositionX` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `StartPositionY` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `StartPositionZ` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `HitPositionX` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `HitPositionY` | `float*` | `float` |
| GAMEPLAY | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS` | `HitPositionZ` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `posX` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `posY` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `posZ` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `rotX` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `rotY` | `float*` | `float` |
| CAM | `CREATE_CAM_WITH_PARAMS` | `rotZ` | `float*` | `float` |
| CAM | `SET_CAM_FOV` | `camName` | `char*` | `Cam` |
| CAM | `DETACH_CAM` | `camName` | `char*` | `Cam` |
| GRAPHICS | `DRAW_LIGHT_WITH_RANGE` | `XCoord` | `float*` | `float` |
| GRAPHICS | `DRAW_LIGHT_WITH_RANGE` | `YCoord` | `float*` | `float` |
| GRAPHICS | `DRAW_LIGHT_WITH_RANGE` | `ZCoord` | `float*` | `float` |
| STATS | `STAT_INCREMENT` | `statName` | `char*` | `Hash` |
| FIRE | `_0xCF358946` | `XCoord` | `float*` | `float` |
| FIRE | `_0xCF358946` | `YCoord` | `float*` | `float` |
| FIRE | `_0xCF358946` | `ZCoord` | `float*` | `float` |
| NETWORK | `_NETWORK_RESPAWN_COORDS` | `coords` | `float *` | `float` |

## Renombrados por Rockstar (remapeados)

| namespace | nombre PS3 | nombre 1.57 | vía |
|---|---|---|---|
| PLAYER | `_0x274631FE` | `SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE` | jhash |
| PLAYER | `_0x02DF7AF4` | `SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME` | jhash |
| PLAYER | `_0x59B5C2A2` | `SUPPRESS_CRIME_THIS_FRAME` | jhash |
| PLAYER | `_0x6B34A160` | `UPDATE_WANTED_POSITION_THIS_FRAME` | jhash |
| PLAYER | `_0xB9FB142F` | `SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME` | jhash |
| PLAYER | `_0x85725848` | `FORCE_START_HIDDEN_EVASION` | jhash |
| PLAYER | `_0x3A7E5FB6` | `SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME` | jhash |
| PLAYER | `_0xD15C4B1C` | `REPORT_POLICE_SPOTTED_PLAYER` | jhash |
| PLAYER | `_0xBF6993C7` | `SET_LAW_RESPONSE_DELAY_OVERRIDE` | jhash |
| PLAYER | `_0x47CAB814` | `RESET_LAW_RESPONSE_DELAY_OVERRIDE` | jhash |
| PLAYER | `_GET_AIMED_ENTITY` | `GET_ENTITY_PLAYER_IS_FREE_AIMING_AT` | jhash |
| PLAYER | `_0x74D42C03` | `SET_PLAYER_LOCKON_RANGE_OVERRIDE` | jhash |
| PLAYER | `_0x47017C90` | `GET_PLAYER_SPRINT_STAMINA_REMAINING` | jhash |
| PLAYER | `_0x453C7CAB` | `RESET_PLAYER_ARREST_STATE` | jhash |
| PLAYER | `_0x98F3B274` | `INT_TO_PARTICIPANTINDEX` | jhash |
| PLAYER | `_0x8DD5B838` | `NETWORK_PLAYER_ID_TO_INT` | jhash |
| PLAYER | `_0x4B37333C` | `HAS_FORCE_CLEANUP_OCCURRED` | jhash |
| PLAYER | `_0x04256C73` | `FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME` | jhash |
| PLAYER | `_0x882D3EB3` | `FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID` | jhash |
| PLAYER | `_0x39AA9FC8` | `GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP` | jhash |
| PLAYER | `_0xAF7AFCC4` | `SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE` | jhash |
| PLAYER | `_0x00563E0D` | `SET_PLAYER_CAN_COLLECT_DROPPED_MONEY` | jhash |
| PLAYER | `_0x7E3BFBC5` | `CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED` | jhash |
| PLAYER | `_0xA3707DFC` | `HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED` | jhash |
| PLAYER | `_0xB986FF47` | `SET_SWIM_MULTIPLIER_FOR_PLAYER` | jhash |
| PLAYER | `_0x825423C2` | `SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER` | jhash |
| PLAYER | `_0x374F42F0` | `SET_PLAYER_FORCE_SKIP_AIM_INTRO` | jhash |
| PLAYER | `_0xCCD937E7` | `SET_DISABLE_AMBIENT_MELEE_MOVE` | jhash |
| PLAYER | `_0x0751908A` | `SPECIAL_ABILITY_DEACTIVATE_FAST` | jhash |
| PLAYER | `_0x4136829A` | `SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED` | jhash |
| PLAYER | `_0x6F463F56` | `SPECIAL_ABILITY_CHARGE_SMALL` | jhash |
| PLAYER | `_0xAB55D8F3` | `SPECIAL_ABILITY_CHARGE_MEDIUM` | jhash |
| PLAYER | `_0xF440C04D` | `SPECIAL_ABILITY_CHARGE_LARGE` | jhash |
| PLAYER | `_0x5FEE98A2` | `SPECIAL_ABILITY_CHARGE_CONTINUOUS` | jhash |
| PLAYER | `_0x72429998` | `SPECIAL_ABILITY_CHARGE_ABSOLUTE` | jhash |
| PLAYER | `RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC` | `SPECIAL_ABILITY_CHARGE_NORMALIZED` | jhash |
| PLAYER | `_0xB71589DA` | `SPECIAL_ABILITY_FILL_METER` | jhash |
| PLAYER | `_0x9F80F6DF` | `SPECIAL_ABILITY_DEPLETE_METER` | jhash |
| PLAYER | `_0x5D0FE25B` | `UPDATE_SPECIAL_ABILITY_FROM_STAT` | jhash |
| PLAYER | `_0x46E7E31D` | `GET_IS_PLAYER_DRIVING_ON_HIGHWAY` | jhash |
| PLAYER | `_0x1E359CC8` | `GET_IS_PLAYER_DRIVING_WRECKLESS` | jhash |
| PLAYER | `_0x8CB53C9F` | `GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER` | jhash |
| PLAYER | `_0x45514731` | `SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER` | jhash |
| PLAYER | `_0xAE446344` | `SET_PLAYER_WEAPON_DEFENSE_MODIFIER` | jhash |
| PLAYER | `_0x362E69AD` | `SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER` | jhash |
| PLAYER | `_0x9F3D577F` | `SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER` | jhash |
| PLAYER | `_0xA16626C7` | `SET_PLAYER_VEHICLE_DEFENSE_MODIFIER` | jhash |
| PLAYER | `_0x70689638` | `SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX` | jhash |
| PLAYER | `_0x77B8EF01` | `GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX` | jhash |
| PLAYER | `_0x4E418E13` | `GET_PLAYER_PARACHUTE_PACK_TINT_INDEX` | jhash |
| PLAYER | `_0xA3E4798E` | `SET_PLAYER_HAS_RESERVE_PARACHUTE` | jhash |
| PLAYER | `_0x30DA1DA1` | `GET_PLAYER_HAS_RESERVE_PARACHUTE` | jhash |
| PLAYER | `_0x832DEB7A` | `SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL` | jhash |
| PLAYER | `_0x14FE9264` | `SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR` | jhash |
| PLAYER | `_0xF66E5CDD` | `GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR` | jhash |
| PLAYER | `_0x8D2D89C4` | `SET_PLAYER_SNEAKING_NOISE_MULTIPLIER` | jhash |
| PLAYER | `_0x1C70B2EB` | `CAN_PED_HEAR_PLAYER` | jhash |
| PLAYER | `_0xA97C2059` | `SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE` | jhash |
| PLAYER | `_0xA25D767E` | `SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE` | jhash |
| PLAYER | `_0x3D26105F` | `SET_PLAYER_STEALTH_PERCEPTION_MODIFIER` | jhash |
| PLAYER | `_0x1D371529` | `IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE` | jhash |
| PLAYER | `_0xE30A64DC` | `INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE` | jhash |
| PLAYER | `_0xF7A0F00F` | `SET_PLAYER_CLOTH_PIN_FRAMES` | jhash |
| PLAYER | `_0xB8209F16` | `SET_PLAYER_CLOTH_PACKAGE_INDEX` | jhash |
| PLAYER | `_0x8D9FD4D1` | `SET_PLAYER_CLOTH_LOCK_COUNTER` | jhash |
| PLAYER | `_0xECD12E60` | `PLAYER_ATTACH_VIRTUAL_BOUND` | jhash |
| PLAYER | `_0x96100EA4` | `PLAYER_DETACH_VIRTUAL_BOUND` | jhash |
| PLAYER | `_0x4A01B76A` | `HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE` | jhash |
| PLAYER | `_0x013B4F72` | `IS_PLAYER_BATTLE_AWARE` | jhash |
| PLAYER | `_0x9DF75B2A` | `GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY` | jhash |
| PLAYER | `_0x64DDB07D` | `EXTEND_WORLD_BOUNDARY_FOR_PLAYER` | jhash |
| PLAYER | `_0xA97C2F6C` | `RESET_WORLD_BOUNDARY_FOR_PLAYER` | jhash |
| PLAYER | `_0xFEA40B6C` | `HAS_PLAYER_LEFT_THE_WORLD` | jhash |
| PLAYER | `_0xAD8383FA` | `SET_PLAYER_LEAVE_PED_BEHIND` | jhash |
| PLAYER | `_0x9254249D` | `SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE` | jhash |
| PLAYER | `_0xFD60F5AB` | `CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE` | jhash |
| PLAYER | `_0x5D382498` | `SET_PLAYER_PARACHUTE_MODEL_OVERRIDE` | jhash |
| PLAYER | `_0x6FF034BB` | `CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE` | jhash |
| PLAYER | `_0xA877FF5E` | `SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE` | jhash |
| PLAYER | `_0xBB62AAC5` | `CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE` | jhash |
| PLAYER | `_0x8C6E611D` | `DISABLE_PLAYER_VEHICLE_REWARDS` | jhash |
| PLAYER | `_0x2849D4B2` | `SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE` | jhash |
| ENTITY | `_0xACFEB3F9` | `DOES_ENTITY_BELONG_TO_THIS_SCRIPT` | jhash |
| ENTITY | `_0xC0E3AA47` | `GET_LAST_MATERIAL_HIT_BY_ENTITY` | jhash |
| ENTITY | `_0xAB415C07` | `GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY` | jhash |
| ENTITY | `_0x58D9775F` | `FORCE_ENTITY_AI_AND_ANIMATION_UPDATE` | jhash |
| ENTITY | `_0xBC5A9C58` | `GET_OBJECT_INDEX_FROM_ENTITY_INDEX` | jhash |
| ENTITY | `_0xC46F74AC` | `GET_PED_INDEX_FROM_ENTITY_INDEX` | jhash |
| ENTITY | `_0xC69CF43D` | `GET_VEHICLE_INDEX_FROM_ENTITY_INDEX` | jhash |
| ENTITY | `_0x7C6339DF` | `GET_WORLD_POSITION_OF_ENTITY_BONE` | jhash |
| ENTITY | `_0xB1808F56` | `GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM` | jhash |
| ENTITY | `_0x0170F68C` | `GET_ENTITY_SUBMERGED_LEVEL` | jhash |
| ENTITY | `_0x40C84A74` | `SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK` | jhash |
| ENTITY | `_0x307E7611` | `IS_ENTITY_TOUCHING_MODEL` | jhash |
| ENTITY | `_0xEA127CBC` | `WOULD_ENTITY_BE_OCCLUDED` | jhash |
| ENTITY | `_0x28924E98` | `APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS` | jhash |
| ENTITY | `_0x6909BA59` | `PROCESS_ENTITY_ATTACHMENTS` | jhash |
| ENTITY | `_0xE4ECAC22` | `GET_ENTITY_BONE_INDEX_BY_NAME` | jhash |
| ENTITY | `_0xD3850671` | `SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION` | jhash |
| ENTITY | `_0xEB4CBA74` | `PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM` | jhash |
| ENTITY | `_0x7253D5B2` | `STOP_SYNCHRONIZED_MAP_ENTITY_ANIM` | jhash |
| ENTITY | `_0x66571CA0` | `HAS_ANIM_EVENT_FIRED` | jhash |
| ENTITY | `_0xC41DDA62` | `FIND_ANIM_EVENT_PHASE` | jhash |
| ENTITY | `_0xCCF1E97BEFDAE480` | `GET_ENTITY_COLLISION_DISABLED` | jhash |
| ENTITY | `_0x851687F9` | `HAS_COLLISION_LOADED_AROUND_ENTITY` | jhash |
| ENTITY | `_0x4DA3D51F` | `GET_ENTITY_LOD_DIST` | jhash |
| ENTITY | `_0xD8FF798A` | `SET_ENTITY_ALWAYS_PRERENDER` | jhash |
| ENTITY | `_0xC47F5B91` | `SET_ENTITY_TRAFFICLIGHT_OVERRIDE` | jhash |
| ENTITY | `_0x07AAF22C` | `CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS` | jhash |
| ENTITY | `_0x44767B31` | `SET_CAN_AUTO_VAULT_ON_ENTITY` | jhash |
| ENTITY | `_0xE224A6A5` | `SET_CAN_CLIMB_ON_ENTITY` | jhash |
| PED | `_0xFC70EEC7` | `CLONE_PED_TO_TARGET` | jhash |
| PED | `_IS_PED_DEAD` | `IS_PED_DEAD_OR_DYING` | jhash |
| PED | `_0x290421BE` | `FORCE_ALL_HEADING_VALUES_TO_ALIGN` | jhash |
| PED | `_0x58A80BD5` | `SET_PED_ALLOW_VEHICLES_OVERRIDE` | jhash |
| PED | `_0x7018BE31` | `CAN_CREATE_RANDOM_BIKE_RIDER` | jhash |
| PED | `_0x6CD58238` | `SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS` | jhash |
| PED | `_0xB48C0C04` | `SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME` | jhash |
| PED | `_0x25EA2AA5` | `SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME` | jhash |
| PED | `_0x8C555ADD` | `INSTANTLY_FILL_PED_POPULATION` | jhash |
| PED | `_0xD41C9AED` | `SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS` | jhash |
| PED | `_0x30B98369` | `SET_AMBIENT_PEDS_DROP_MONEY` | jhash |
| PED | `_0x02A080C8` | `SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME` | jhash |
| PED | `_0x1572022A` | `SET_PED_UPPER_BODY_DAMAGE_ONLY` | jhash |
| PED | `_0x0F9A401F` | `SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER` | jhash |
| PED | `_0x97886238` | `RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER` | jhash |
| PED | `_0xCC9D7F1A` | `SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON` | jhash |
| PED | `_0x7DA12905` | `SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY` | jhash |
| PED | `SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE` | `SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST` | jhash |
| PED | `_0xA819680B` | `FORCE_PED_TO_OPEN_PARACHUTE` | jhash |
| PED | `_0xCD71F11B` | `IS_PED_IN_PARACHUTE_FREE_FALL` | jhash |
| PED | `_0xC3169BDA` | `IS_PED_VAULTING` | jhash |
| PED | `_0xB19215F6` | `IS_PED_JUMPING_OUT_OF_VEHICLE` | jhash |
| PED | `_0x01F3B035` | `GET_PED_PARACHUTE_LANDING_TYPE` | jhash |
| PED | `_0x177EFC79` | `SET_PED_RESERVE_PARACHUTE_TINT_INDEX` | jhash |
| PED | `_0x9A2180FF` | `SET_PED_HIGHLY_PERCEPTIVE` | jhash |
| PED | `_0xF30658D2` | `SET_PED_INJURED_ON_GROUND_BEHAVIOUR` | jhash |
| PED | `_0x43709044` | `DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR` | jhash |
| PED | `_0xE57202A1` | `SET_PED_VISUAL_FIELD_CENTER_ANGLE` | jhash |
| PED | `_0xD0D8BDBC` | `SET_PED_CAN_TELEPORT_TO_GROUP_LEADER` | jhash |
| PED | `_0x9678D4FF` | `IS_PED_HANGING_ON_TO_VEHICLE` | jhash |
| PED | `_0x2F0D0973` | `SET_PED_MIN_GROUND_TIME_FOR_STUNGUN` | jhash |
| PED | `_0xCCD525E1` | `CAN_PED_IN_COMBAT_SEE_TARGET` | jhash |
| PED | `_0xACF162E0` | `GET_SEAT_PED_IS_TRYING_TO_ENTER` | jhash |
| PED | `_0x99968B37` | `GET_VEHICLE_PED_IS_TRYING_TO_ENTER` | jhash |
| PED | `_0x84ADF9EB` | `GET_PED_SOURCE_OF_DEATH` | jhash |
| PED | `_0xEF0B78E6` | `COUNT_PEDS_IN_COMBAT_WITH_TARGET` | jhash |
| PED | `_0xFB18CB19` | `COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS` | jhash |
| PED | `_0xDE7442EE` | `GET_PLAYER_PED_IS_FOLLOWING` | jhash |
| PED | `_0x267FCEAD` | `RESET_GROUP_FORMATION_DEFAULT_SPACING` | jhash |
| PED | `SET_EXCLUSIVE_PHONE_RELATIONSHIPS` | `GET_VEHICLE_PED_IS_ENTERING` | jhash |
| PED | `_0x373CC405` | `SET_CORPSE_RAGDOLL_FRICTION` | jhash |
| PED | `_0xC9D098B3` | `CAN_KNOCK_PED_OFF_VEHICLE` | jhash |
| PED | `_0x397F06E3` | `SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED` | jhash |
| PED | `_0x82E548CC` | `SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS` | jhash |
| PED | `_0xEDC31475` | `SET_CREATE_RANDOM_COPS_ON_SCENARIOS` | jhash |
| PED | `_0x7BF61471` | `SET_ENABLE_SCUBA` | jhash |
| PED | `_0xD4C73595` | `SET_PED_DRIVE_BY_CLIPSET_OVERRIDE` | jhash |
| PED | `_0xAEC9163B` | `CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE` | jhash |
| PED | `_0x3C30B447` | `IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM` | jhash |
| PED | `_0x895E1D67` | `SET_PED_ALTERNATE_WALK_ANIM` | jhash |
| PED | `_0x5736FB23` | `CLEAR_PED_ALTERNATE_WALK_ANIM` | jhash |
| PED | `_0xC59D4268` | `GET_ANIM_INITIAL_OFFSET_POSITION` | jhash |
| PED | `_0x5F7789E6` | `GET_ANIM_INITIAL_OFFSET_ROTATION` | jhash |
| PED | `_0xC9780B95` | `GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS` | jhash |
| PED | `REMOVE_NIGHTVISION_MELEE` | `GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS` | jhash |
| PED | `_0xFF43C18D` | `GET_PED_HEAD_OVERLAY_NUM` | jhash |
| PED | `_0x894314A4` | `FINALIZE_HEAD_BLEND` | jhash |
| PED | `_0x57E5B3F9` | `SET_HEAD_BLEND_PALETTE_COLOR` | jhash |
| PED | `_0xC6F36292` | `DISABLE_HEAD_BLEND_PALETTE_COLOR` | jhash |
| PED | `_0x211DEFEC` | `GET_PED_HEAD_BLEND_FIRST_INDEX` | jhash |
| PED | `_0x095D3BD8` | `GET_PED_HEAD_BLEND_NUM_HEADS` | jhash |
| PED | `_0x45F3BDFB` | `SET_PED_PRELOAD_VARIATION_DATA` | jhash |
| PED | `_0xC6517D52` | `HAS_PED_PRELOAD_VARIATION_DATA_FINISHED` | jhash |
| PED | `_0x6435F67F` | `RELEASE_PED_PRELOAD_VARIATION_DATA` | jhash |
| PED | `_0xC0E23671` | `SET_PED_PRELOAD_PROP_DATA` | jhash |
| PED | `_0x3B0CA391` | `HAS_PED_PRELOAD_PROP_DATA_FINISHED` | jhash |
| PED | `_0xFD103BA7` | `RELEASE_PED_PRELOAD_PROP_DATA` | jhash |
| PED | `_0x7BCD8991` | `CLEAR_PED_PARACHUTE_PACK_VARIATION` | jhash |
| PED | `_0x080275EE` | `CLEAR_PED_SCUBA_GEAR_VARIATION` | jhash |
| PED | `_0x18DD76A1` | `GET_CAN_PED_BE_GRABBED_BY_SCRIPT` | jhash |
| PED | `_0x6D55B3B3` | `SET_DRIVER_RACING_MODIFIER` | jhash |
| PED | `_0x97353375` | `IS_MOBILE_PHONE_TO_PED_EAR` | jhash |
| PED | `_0x9C8F830D` | `SET_RAGDOLL_BLOCKING_FLAGS` | jhash |
| PED | `_0x77CBA290` | `CLEAR_RAGDOLL_BLOCKING_FLAGS` | jhash |
| PED | `_0x40638BDC` | `SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED` | jhash |
| PED | `_0x4763B2C6` | `SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE` | jhash |
| PED | `_0xB66B0C9A` | `SET_PED_DEFENSIVE_AREA_DIRECTION` | jhash |
| PED | `_0xF3B7EFBF` | `SET_PED_PREFERRED_COVER_SET` | jhash |
| PED | `_0xA0134498` | `REMOVE_PED_PREFERRED_COVER_SET` | jhash |
| PED | `_0x141CC936` | `SPECIAL_FUNCTION_DO_NOT_USE` | jhash |
| PED | `_0x1E54DB12` | `APPLY_PED_BLOOD_DAMAGE_BY_ZONE` | jhash |
| PED | `_0x8F3F3A9C` | `APPLY_PED_BLOOD_BY_ZONE` | jhash |
| PED | `_0xFC13CE80` | `APPLY_PED_BLOOD_SPECIFIC` | jhash |
| PED | `_0xF210BE69` | `CLEAR_PED_BLOOD_DAMAGE_BY_ZONE` | jhash |
| PED | `_0x0CB6C4ED` | `HIDE_PED_BLOOD_DAMAGE_BY_ZONE` | jhash |
| PED | `_0x70AA5B7D` | `CLEAR_PED_DAMAGE_DECAL_BY_ZONE` | jhash |
| PED | `_0x47187F7F` | `GET_PED_DECORATIONS_STATE` | jhash |
| PED | `_0xA993915F` | `CLEAR_PED_ENV_DIRT` | jhash |
| PED | `_0x70559AC7` | `ADD_PED_DECORATION_FROM_HASHES` | jhash |
| PED | `_0x3543019E` | `GET_PED_DECORATION_ZONE_FROM_HASHES` | jhash |
| PED | `_0xEFD58EB9` | `CLEAR_PED_DECORATIONS_LEAVE_SCARS` | jhash |
| PED | `_0x59DE73AC` | `SET_PED_PANIC_EXIT_SCENARIO` | jhash |
| PED | `_0xC08FE5F6` | `TOGGLE_SCENARIO_PED_COWER_IN_PLACE` | jhash |
| PED | `_0x58C0F6CF` | `TRIGGER_PED_SCENARIO_PANICEXITTOFLEE` | jhash |
| PED | `_0x033F43FA` | `SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT` | jhash |
| PED | `_0x4C684C81` | `SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT` | jhash |
| PED | `_0x7B4C3E6F` | `SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT` | jhash |
| PED | `_0x5BC276AE` | `SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS` | jhash |
| PED | `_0xADB2511A` | `SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS` | jhash |
| PED | `_0xB7CD0A49` | `TRIGGER_IDLE_ANIMATION_ON_PED` | jhash |
| PED | `_0x343B4DE0` | `SET_PED_CAN_ARM_IK` | jhash |
| PED | `_0x8E5D4EAB` | `SET_PED_CAN_TORSO_IK` | jhash |
| PED | `_0x7B0040A8` | `SET_PED_CAN_TORSO_REACT_IK` | jhash |
| PED | `_0x0FDA62DE` | `SET_PED_CAN_TORSO_VEHICLE_IK` | jhash |
| PED | `_0xFF1F6AEB` | `BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD` | jhash |
| PED | `_0x24A1284E` | `CLEAR_PED_STORED_HAT_PROP` | jhash |
| PED | `_0x8A3A3116` | `GET_PED_HELMET_STORED_HAT_PROP_INDEX` | jhash |
| PED | `_0x74EB662D` | `GET_PED_HELMET_STORED_HAT_TEX_INDEX` | jhash |
| PED | `_0xFFF149FE` | `IS_CURRENT_HEAD_PROP_A_HELMET` | jhash |
| PED | `_0x77BB7CB8` | `SET_LADDER_CLIMB_INPUT_STATE` | jhash |
| PED | `_0x139C0875` | `IS_PED_PERFORMING_MELEE_ACTION` | jhash |
| PED | `_0x9BE7C860` | `IS_PED_PERFORMING_A_COUNTER_ATTACK` | jhash |
| PED | `_0xAFEC26A4` | `GET_MELEE_TARGET_FOR_PED` | jhash |
| PED | `_0x3993092B` | `WAS_PED_KNOCKED_OUT` | jhash |
| PED | `_0xA6F2C057` | `SET_PED_STEERS_AROUND_DEAD_BODIES` | jhash |
| PED | `_0x2276DE0D` | `SET_PED_IS_AVOIDED_BY_OTHERS` | jhash |
| PED | `_0x59C52BE6` | `SET_PED_INCREASED_AVOIDANCE_RADIUS` | jhash |
| PED | `_0x1D87DDC1` | `SET_PED_BLOCKS_PATHING_WHEN_DEAD` | jhash |
| PED | `_0xB52BA5F5` | `SET_PED_NO_TIME_DELAY_BEFORE_SHOT` | jhash |
| PED | `_0x187B9070` | `FORCE_PED_AI_AND_ANIMATION_UPDATE` | jhash |
| PED | `_0x45037B9B` | `IS_PED_HEADING_TOWARDS_POSITION` | jhash |
| PED | `_0x840D24D3` | `REQUEST_PED_VISIBILITY_TRACKING` | jhash |
| PED | `GET_PED_FLOOD_INVINCIBILITY` | `REQUEST_PED_VEHICLE_VISIBILITY_TRACKING` | jhash |
| PED | `_0x9194DB71` | `REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING` | jhash |
| PED | `_0x5B1B70AA` | `GET_TRACKED_PED_PIXELCOUNT` | jhash |
| PED | `_0x74A0F291` | `CAN_PED_SEE_HATED_PED` | jhash |
| PED | `_0x3B882533` | `SET_PED_ENVEFF_CPV_ADD` | jhash |
| PED | `_0x87A0C174` | `SET_PED_ENVEFF_COLOR_MODULATOR` | jhash |
| PED | `_0x7BD26837` | `REQUEST_RAGDOLL_BOUNDS_UPDATE` | jhash |
| PED | `_0x98E29ED0` | `SET_PED_AO_BLOB_RENDERING` | jhash |
| PED | `_0xF3876894` | `CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT` | jhash |
| PED | `_0x2DE48DA1` | `SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME` | jhash |
| PED | `_0x72CF2514` | `IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME` | jhash |
| PED | `_0xBF7F9035` | `TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE` | jhash |
| PED | `_0x79543043` | `PED_HAS_SEXINESS_FLAG_SET` | jhash |
| PED | `_0xF9FB4B71` | `HAVE_ALL_STREAMING_REQUESTS_COMPLETED` | jhash |
| PED | `_0x4DD03628` | `REGISTER_PEDHEADSHOT_TRANSPARENT` | jhash |
| PED | `_0x10F2C023` | `REQUEST_PEDHEADSHOT_IMG_UPLOAD` | jhash |
| PED | `_0x0DBB2FA7` | `RELEASE_PEDHEADSHOT_IMG_UPLOAD` | jhash |
| PED | `_0x810158F8` | `IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE` | jhash |
| PED | `_0x05023F8F` | `HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED` | jhash |
| PED | `_0xAA39FD6C` | `HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED` | jhash |
| PED | `_0xEF9142DB` | `SET_PED_HEATSCALE_OVERRIDE` | jhash |
| PED | `_0x0688DE64` | `DISABLE_PED_HEATSCALE_OVERRIDE` | jhash |
| PED | `_0x909A1D76` | `SPAWNPOINTS_START_SEARCH` | jhash |
| PED | `_0x4AAD0ECB` | `SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA` | jhash |
| PED | `_0x492C9E46` | `SPAWNPOINTS_CANCEL_SEARCH` | jhash |
| PED | `_0x814A28F4` | `SPAWNPOINTS_IS_SEARCH_ACTIVE` | jhash |
| PED | `_0x0B60D2BA` | `SPAWNPOINTS_IS_SEARCH_COMPLETE` | jhash |
| PED | `_0x6B83ABDF` | `SPAWNPOINTS_IS_SEARCH_FAILED` | jhash |
| PED | `_0xF46B4DC8` | `SPAWNPOINTS_GET_NUM_SEARCH_RESULTS` | jhash |
| PED | `_0x36A4AC65` | `SPAWNPOINTS_GET_SEARCH_RESULT` | jhash |
| PED | `_0xBA699DDF` | `SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS` | jhash |
| PED | `_0xFB4000DC` | `FORCE_INSTANT_LEG_IK_SETUP` | jhash |
| PED | `_0x2F9550C2` | `SET_PED_CAN_LOSE_PROPS_ON_DAMAGE` | jhash |
| PED | `_0x37DBC2AD` | `SET_FORCE_FOOTSTEP_UPDATE` | jhash |
| PED | `_0xC0F1BC91` | `SET_FORCE_STEP_TYPE` | jhash |
| PED | `_0x1A464167` | `IS_ANY_HOSTILE_PED_NEAR_POINT` | jhash |
| PED | `_0xD0567D41` | `IS_TARGET_PED_IN_PERCEPTION_AREA` | jhash |
| PED | `_0x4BBE5E2C` | `SET_POP_CONTROL_SPHERE_THIS_FRAME` | jhash |
| PED | `_0xA89A53F2` | `FORCE_ZERO_MASS_IN_COLLISIONS` | jhash |
| VEHICLE | `_0xBB54ECCA` | `SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON` | jhash |
| VEHICLE | `_0xFBDE9FD8` | `GET_VEHICLE_HOMING_LOCKON_STATE` | jhash |
| VEHICLE | `_0x935A95DA` | `SET_VEHICLE_GENERATOR_AREA_OF_INTEREST` | jhash |
| VEHICLE | `_0x6C73E45A` | `CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST` | jhash |
| VEHICLE | `SET_ALL_VEHICLES_SPAWN` | `SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION` | jhash |
| VEHICLE | `_GET_VEHICLE_MODEL_MAX_NUMBER_OF_PASSENGERS` | `GET_VEHICLE_MODEL_NUMBER_OF_SEATS` | jhash |
| VEHICLE | `_769E5CF2` | `IS_SEAT_WARP_ONLY` | jhash |
| VEHICLE | `_0x09462665` | `SET_DISABLE_RANDOM_TRAINS_THIS_FRAME` | jhash |
| VEHICLE | `_0xDAE2A2BE` | `SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME` | jhash |
| VEHICLE | `SET_PED_TARGETTABLE_VEHICLE_DESTROY` | `SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED` | jhash |
| VEHICLE | `DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION` | `SET_VEHICLE_HAS_MUTED_SIRENS` | jhash |
| VEHICLE | `_0xE4EF6514` | `SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS` | jhash |
| VEHICLE | `_0x811373DE` | `ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE` | jhash |
| VEHICLE | `_0xA4E69134` | `HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE` | jhash |
| VEHICLE | `_0x65255524` | `DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE` | jhash |
| VEHICLE | `STEER_UNLOCK_BIAS` | `SET_VEHICLE_IS_RACING` | jhash |
| VEHICLE | `_0x8332730C` | `SET_VEHICLE_ENVEFF_SCALE` | jhash |
| VEHICLE | `_0xD5F1EEE1` | `GET_VEHICLE_ENVEFF_SCALE` | jhash |
| VEHICLE | `_0x54E9EE75` | `FORCE_SUBMARINE_SURFACE_MODE` | jhash |
| VEHICLE | `_0x4A46E814` | `SET_SUBMARINE_CRUSH_DEPTHS` | jhash |
| VEHICLE | `_0x0ED84792` | `SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER` | jhash |
| VEHICLE | `_0xA739012A` | `SET_FORCE_LOW_LOD_ANCHOR_MODE` | jhash |
| VEHICLE | `_0x66FA450C` | `SET_BOAT_LOW_LOD_ANCHOR_DISTANCE` | jhash |
| VEHICLE | `_0x35614622` | `SET_BOAT_SINKS_WHEN_WRECKED` | jhash |
| VEHICLE | `_0xF7C6792D` | `GET_LAST_PED_IN_VEHICLE_SEAT` | jhash |
| VEHICLE | `_0xCBC7D3C8` | `BRING_VEHICLE_TO_HALT` | jhash |
| VEHICLE | `_0x943A6CFC` | `SET_FORKLIFT_FORK_HEIGHT` | jhash |
| VEHICLE | `SET_PED_ENABLED_BIKE_RINGTONE` | `IS_ENTITY_ATTACHED_TO_HANDLER_FRAME` | jhash |
| VEHICLE | `_0x593143B9` | `IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME` | jhash |
| VEHICLE | `_0x70DD5E25` | `FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO` | jhash |
| VEHICLE | `_0xFBF5536A` | `IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER` | jhash |
| VEHICLE | `_0x20AB5783` | `ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP` | jhash |
| VEHICLE | `_0x0F11D01F` | `DETACH_CONTAINER_FROM_HANDLER_FRAME` | jhash |
| VEHICLE | `_0xAE040377` | `SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE` | jhash |
| VEHICLE | `_0x4C0E4031` | `SET_BOAT_DISABLE_AVOIDANCE` | jhash |
| VEHICLE | `_0x6346B7CC` | `IS_HELI_LANDING_AREA_BLOCKED` | jhash |
| VEHICLE | `_0xCCB41A55` | `SET_HELI_TURBULENCE_SCALAR` | jhash |
| VEHICLE | `_DETACH_VEHICLE_WINDSCREEN` | `POP_OUT_VEHICLE_WINDSCREEN` | jhash |
| VEHICLE | `_0xFDA7B6CA` | `POP_OFF_VEHICLE_ROOF_WITH_IMPULSE` | jhash |
| VEHICLE | `_0x4221E435` | `SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS` | jhash |
| VEHICLE | `_0x12AC1A16` | `ATTACH_VEHICLE_ON_TO_TRAILER` | jhash |
| VEHICLE | `_0x40C4763F` | `STABILISE_ENTITY_ATTACHED_TO_HELI` | jhash |
| VEHICLE | `_0xE74E85CE` | `SET_TRAILER_INVERSE_MASS_SCALE` | jhash |
| VEHICLE | `_0x06C47A6F` | `SET_TRAILER_LEGS_RAISED` | jhash |
| VEHICLE | `_0xD5774FB7` | `SET_TRAIN_TRACK_SPAWN_FREQUENCY` | jhash |
| VEHICLE | `_0xF31973BB` | `GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME` | jhash |
| VEHICLE | `_0x4D1C15C2` | `GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME` | jhash |
| VEHICLE | `_0x01B91CD0` | `FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE` | jhash |
| VEHICLE | `_0x943A58EB` | `SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK` | jhash |
| VEHICLE | `_0x5C9F477C` | `SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK` | jhash |
| VEHICLE | `_0xCD83C393` | `SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK` | jhash |
| VEHICLE | `_0x2EF8435C` | `SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING` | jhash |
| VEHICLE | `_0x1128A45B` | `FORCE_SUB_THROTTLE_FOR_TIME` | jhash |
| VEHICLE | `_0x486C1280` | `SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER` | jhash |
| VEHICLE | `_0x009AB49E` | `SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS` | jhash |
| VEHICLE | `_0x758C5E2E` | `SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER` | jhash |
| VEHICLE | `_0xDAC523BC` | `GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS` | jhash |
| VEHICLE | `_0xA6D8D7A5` | `SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP` | jhash |
| VEHICLE | `_0xACAB8FF3` | `SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON` | jhash |
| VEHICLE | `_0xF0E5C41D` | `SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS` | jhash |
| VEHICLE | `_0x2F98B4B7` | `SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS` | jhash |
| VEHICLE | `_0x065B92B3` | `SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF` | jhash |
| VEHICLE | `_0xB3A2CC4F` | `IS_VEHICLE_BUMPER_BOUNCING` | jhash |
| VEHICLE | `_0x88F0F7E7` | `SET_VEHICLE_CAN_LEAK_OIL` | jhash |
| VEHICLE | `_0x90D6EE57` | `SET_VEHICLE_CAN_LEAK_PETROL` | jhash |
| VEHICLE | `_0xC40192B5` | `SET_DISABLE_VEHICLE_PETROL_TANK_FIRES` | jhash |
| VEHICLE | `_0x1784BA1A` | `SET_DISABLE_VEHICLE_ENGINE_FIRES` | jhash |
| VEHICLE | `_0x40C323AE` | `SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE` | jhash |
| VEHICLE | `_0x847F1304` | `SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE` | jhash |
| VEHICLE | `_0xCBD98BA1` | `SET_DISABLE_PRETEND_OCCUPANTS` | jhash |
| VEHICLE | `_0x968E5770` | `SET_VEHICLE_IN_CAR_MOD_SHOP` | jhash |
| VEHICLE | `_0xBB619744` | `ARE_ALL_VEHICLE_WINDOWS_INTACT` | jhash |
| VEHICLE | `_0x648E685A` | `ARE_ANY_VEHICLE_SEATS_FREE` | jhash |
| VEHICLE | `_0xF01E2AAB` | `GET_HELI_MAIN_ROTOR_HEALTH` | jhash |
| VEHICLE | `_0xA41BC13D` | `GET_HELI_TAIL_ROTOR_HEALTH` | jhash |
| VEHICLE | `_0x8A68388F` | `GET_HELI_TAIL_BOOM_HEALTH` | jhash |
| VEHICLE | `WAS_COUNTER_ACTIVATED` | `SET_HELI_TAIL_BOOM_CAN_BREAK_OFF` | jhash |
| VEHICLE | `_0xC306A9A3` | `SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT` | jhash |
| VEHICLE | `_0x95A9ACCB` | `SET_VEHICLE_DISABLE_TOWING` | jhash |
| VEHICLE | `_0x24F873FB` | `CONTROL_LANDING_GEAR` | jhash |
| VEHICLE | `_0xA6F02670` | `GET_LANDING_GEAR_STATE` | jhash |
| VEHICLE | `_0x88236E22` | `SET_VEHICLE_TOW_TRUCK_ARM_POSITION` | jhash |
| VEHICLE | `_0xED23C8A3` | `SET_VEHICLE_BULLDOZER_ARM_POSITION` | jhash |
| VEHICLE | `_0xB1A52EF7` | `SET_VEHICLE_TANK_TURRET_POSITION` | jhash |
| VEHICLE | `_0xF30C566F` | `SET_VEHICLE_TURRET_SPEED_THIS_FRAME` | jhash |
| VEHICLE | `_0xA7DF64D7` | `SET_VEHICLE_FLIGHT_NOZZLE_POSITION` | jhash |
| VEHICLE | `_0xDD7936F5` | `SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE` | jhash |
| VEHICLE | `_0x34E02FCD` | `GENERATE_VEHICLE_CREATION_POS_FROM_PATHS` | jhash |
| VEHICLE | `_0x37BC6ACB` | `INSTANTLY_FILL_VEHICLE_POPULATION` | jhash |
| VEHICLE | `_0x71D898EF` | `HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED` | jhash |
| VEHICLE | `_0x0B0523B0` | `NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL` | jhash |
| VEHICLE | `_0x0B200CE2` | `SET_VEHICLE_USES_LARGE_REAR_RAMP` | jhash |
| VEHICLE | `_0x0858678C` | `SET_CONVERTIBLE_ROOF_LATCH_STATE` | jhash |
| VEHICLE | `_0x7D1A0616` | `GET_VEHICLE_ESTIMATED_MAX_SPEED` | jhash |
| VEHICLE | `_0x8F291C4A` | `GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED` | jhash |
| VEHICLE | `_0xF3A7293F` | `GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS` | jhash |
| VEHICLE | `_0x37FBA7BC` | `GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS` | jhash |
| VEHICLE | `_0x95BB67EB` | `GET_FLYING_VEHICLE_MODEL_AGILITY` | jhash |
| VEHICLE | `_0x87C5D271` | `GET_BOAT_VEHICLE_MODEL_AGILITY` | jhash |
| VEHICLE | `_0xCE67162C` | `GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED` | jhash |
| VEHICLE | `_0xD6685803` | `ADD_ROAD_NODE_SPEED_ZONE` | jhash |
| VEHICLE | `_0x0C0332A6` | `REMOVE_ROAD_NODE_SPEED_ZONE` | jhash |
| VEHICLE | `_0x6574041D` | `OPEN_BOMB_BAY_DOORS` | jhash |
| VEHICLE | `_0xF8EC5751` | `CLOSE_BOMB_BAY_DOORS` | jhash |
| VEHICLE | `_0xAB0E79EB` | `IS_ENTRY_POINT_FOR_SEAT_CLEAR` | jhash |
| VEHICLE | `_0x9A0840FD` | `GET_VEHICLE_MOD_COLOR_1_NAME` | jhash |
| VEHICLE | `_0x9BDC0B49` | `GET_VEHICLE_MOD_COLOR_2_NAME` | jhash |
| VEHICLE | `_0x112D637A` | `HAVE_VEHICLE_MODS_STREAMED_IN` | jhash |
| VEHICLE | `_0x94850968` | `GET_VEHICLE_MOD_IDENTIFIER_HASH` | jhash |
| VEHICLE | `_0x749DEEA2` | `GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET` | jhash |
| VEHICLE | `_0xA0777943` | `GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED` | jhash |
| VEHICLE | `_0xF178390B` | `GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED` | jhash |
| VEHICLE | `_0xE943B09C` | `MODIFY_VEHICLE_TOP_SPEED` | jhash |
| VEHICLE | `_0xDF594D8D` | `SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP` | jhash |
| VEHICLE | `_0x4D840FC4` | `SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING` | jhash |
| VEHICLE | `_0x5AB26C2B` | `ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA` | jhash |
| VEHICLE | `_0xEF05F807` | `REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA` | jhash |
| VEHICLE | `_0xD656E7E5` | `IS_ANY_PED_RAPPELLING_FROM_HELI` | jhash |
| VEHICLE | `_0x642DA5AA` | `SET_VEHICLE_CHEAT_POWER_INCREASE` | jhash |
| VEHICLE | `_0x04F5546C` | `SET_VEHICLE_INFLUENCES_WANTED_LEVEL` | jhash |
| VEHICLE | `_0xA25CCB8C` | `SWING_BOAT_BOOM_TO_RATIO` | jhash |
| VEHICLE | `_0x00966934` | `SWING_BOAT_BOOM_FREELY` | jhash |
| VEHICLE | `_0x113DF5FD` | `ALLOW_BOAT_BOOM_TO_ANIMATE` | jhash |
| VEHICLE | `_0x7C8D6464` | `GET_BOAT_BOOM_POSITION_RATIO` | jhash |
| VEHICLE | `_0x7DC6D022` | `GET_IS_VEHICLE_ENGINE_RUNNING` | jhash |
| VEHICLE | `_0xA03E42DF` | `SET_VEHICLE_USE_ALTERNATE_HANDLING` | jhash |
| VEHICLE | `_0x15D40761` | `SET_BIKE_ON_STAND` | jhash |
| VEHICLE | `_0x1984F88D` | `SET_VEHICLE_NOT_STEALABLE_AMBIENTLY` | jhash |
| VEHICLE | `_0x3FBE904F` | `LOCK_DOORS_WHEN_NO_LONGER_NEEDED` | jhash |
| VEHICLE | `_0xD1B71A25` | `SET_LAST_DRIVEN_VEHICLE` | jhash |
| VEHICLE | `_0xFEB0C0C8` | `GET_LAST_DRIVEN_VEHICLE` | jhash |
| VEHICLE | `_0x08CD58F9` | `SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG` | jhash |
| VEHICLE | `_0x8C4B63E2` | `SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN` | jhash |
| VEHICLE | `_0x1604C2F5` | `SET_VEHICLE_CAN_SAVE_IN_GARAGE` | jhash |
| VEHICLE | `_0x8CDB0C09` | `GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS` | jhash |
| VEHICLE | `_0xABC99E21` | `GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS` | jhash |
| VEHICLE | `_0x900C878C` | `SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET` | jhash |
| VEHICLE | `_0xB3200F72` | `SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS` | jhash |
| VEHICLE | `_0xBAE491C7` | `COPY_VEHICLE_DAMAGES` | jhash |
| VEHICLE | `_0xF0E59BC1` | `DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS` | jhash |
| VEHICLE | `_0x929801C6` | `SET_LIGHTS_CUTOFF_DISTANCE_TWEAK` | jhash |
| VEHICLE | `_0x4A557117` | `GET_VEHICLE_LOCK_ON_TARGET` | jhash |
| VEHICLE | `_0xE0FC6A32` | `SET_FORCE_HD_VEHICLE` | jhash |
| VEHICLE | `_0x7D0DE7EA` | `SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS` | jhash |
| VEHICLE | `_0xD2B8ACBD` | `SET_ENABLE_VEHICLE_SLIPSTREAMING` | jhash |
| VEHICLE | `_0xA4A75FCF` | `GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM` | jhash |
| VEHICLE | `_0x50F89338` | `SET_VEHICLE_INACTIVE_DURING_PLAYBACK` | jhash |
| VEHICLE | `_0xEB7D7C27` | `SET_VEHICLE_ACTIVE_DURING_PLAYBACK` | jhash |
| VEHICLE | `_0x5EB00A6A` | `IS_VEHICLE_SPRAYABLE` | jhash |
| VEHICLE | `_0x5BD8D82D` | `DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES` | jhash |
| VEHICLE | `_0x450AD03A` | `ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES` | jhash |
| VEHICLE | `_0xBD085DCA` | `IS_PLANE_LANDING_GEAR_INTACT` | jhash |
| VEHICLE | `_0xABBDD5C6` | `ARE_PLANE_PROPELLERS_INTACT` | jhash |
| VEHICLE | `_0x9B581DE7` | `SET_VEHICLE_CAN_DEFORM_WHEELS` | jhash |
| VEHICLE | `_0xED159AE6` | `SET_PLANE_TURBULENCE_MULTIPLIER` | jhash |
| VEHICLE | `_0xAF8CB3DF` | `ARE_WINGS_OF_PLANE_INTACT` | jhash |
| VEHICLE | `_0x45F72495` | `ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS` | jhash |
| VEHICLE | `_0xAF769B81` | `DOES_CARGOBOB_HAVE_PICK_UP_ROPE` | jhash |
| VEHICLE | `_0x4D3C9A99` | `CREATE_PICK_UP_ROPE_FOR_CARGOBOB` | jhash |
| VEHICLE | `GET_CLOSEST_VEHICLE_TURNING_BLOODSPRAY` | `REMOVE_PICK_UP_ROPE_FOR_CARGOBOB` | jhash |
| VEHICLE | `GET_VEHICLE_HAS_BACK_RECURSIVE` | `SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB` | jhash |
| VEHICLE | `_0x2EC19A8B` | `SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY` | jhash |
| VEHICLE | `_0x123E5B90` | `SET_VEHICLE_USED_FOR_PILOT_SCHOOL` | jhash |
| VEHICLE | `_0xEBC225C1` | `SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION` | jhash |
| VEHICLE | `_0x5130DB1E` | `SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS` | jhash |
| VEHICLE | `_0xB6BE07E0` | `SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR` | jhash |
| VEHICLE | `_0x4BB5605D` | `SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP` | jhash |
| VEHICLE | `_0x51E0064F` | `SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED` | jhash |
| VEHICLE | `_0xAEF9611C` | `SET_VEHICLE_EXTENDED_REMOVAL_RANGE` | jhash |
| VEHICLE | `_0x585E49B6` | `SET_VEHICLE_STEERING_BIAS_SCALAR` | jhash |
| VEHICLE | `_0x6E67FD35` | `SET_HELI_CONTROL_LAGGING_RATE_SCALAR` | jhash |
| VEHICLE | `SET_VEHICLE_MAX_STR_TRAP` | `SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP` | jhash |
| VEHICLE | `GET_VEHICLE_DEFORMATION_GET_TREE` | `SET_VEHICLE_CEILING_HEIGHT` | jhash |
| VEHICLE | `_0xBC649C49` | `SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER` | jhash |
| VEHICLE | `_0x8DD9AA0C` | `CLEAR_VEHICLE_ROUTE_HISTORY` | jhash |
| VEHICLE | `_0xAA8BD440` | `SET_VEHICLE_EXCLUSIVE_DRIVER` | jhash |
| VEHICLE | `_0x004926A3` | `DISABLE_INDIVIDUAL_PLANE_PROPELLER` | jhash |
| VEHICLE | `_0xC195803B` | `SET_VEHICLE_FORCE_AFTERBURNER` | jhash |
| VEHICLE | `_0xB5CC548B` | `SET_DISTANT_CARS_ENABLED` | jhash |
| VEHICLE | `_0x2B2FCC28` | `GET_VEHICLE_BODY_HEALTH` | jhash |
| VEHICLE | `_0x920C2517` | `SET_VEHICLE_BODY_HEALTH` | jhash |
| VEHICLE | `_0xB73A1486` | `GET_FAKE_SUSPENSION_LOWERING_AMOUNT` | jhash |
| OBJECT | `CREATE_OBJECT_2` | `CREATE_OBJECT` | jhash |
| OBJECT | `_0x483C5C88` | `SET_OBJECT_FORCE_VEHICLES_TO_AVOID` | jhash |
| OBJECT | `_0x7DB578DD` | `HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED` | jhash |
| OBJECT | `_0x87A42A12` | `GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS` | jhash |
| OBJECT | `_0x65213FC3` | `GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE` | jhash |
| OBJECT | `_0x4E0A260B` | `SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE` | jhash |
| OBJECT | `_0xDF83DB47` | `DOOR_SYSTEM_SET_DOOR_STATE` | jhash |
| OBJECT | `_0xD42A41C2` | `DOOR_SYSTEM_GET_DOOR_STATE` | jhash |
| OBJECT | `_0xD649B7E1` | `DOOR_SYSTEM_GET_DOOR_PENDING_STATE` | jhash |
| OBJECT | `_0x4F44AF21` | `DOOR_SYSTEM_SET_AUTOMATIC_RATE` | jhash |
| OBJECT | `_0x47531446` | `DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE` | jhash |
| OBJECT | `_0x34883DE3` | `DOOR_SYSTEM_SET_OPEN_RATIO` | jhash |
| OBJECT | `_0xB74C3BD7` | `DOOR_SYSTEM_GET_OPEN_RATIO` | jhash |
| OBJECT | `_0xB4A9A558` | `DOOR_SYSTEM_SET_SPRING_REMOVED` | jhash |
| OBJECT | `_0xECE58AE0` | `DOOR_SYSTEM_SET_HOLD_OPEN` | jhash |
| OBJECT | `_0xF736227C` | `DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES` | jhash |
| OBJECT | `_0x5AFCD8A1` | `IS_DOOR_REGISTERED_WITH_SYSTEM` | jhash |
| OBJECT | `_0x9BF33E41` | `OPEN_ALL_BARRIERS_FOR_RACE` | jhash |
| OBJECT | `_0xF592AD10` | `CLOSE_ALL_BARRIERS_FOR_RACE` | jhash |
| OBJECT | `_0x17FF9393` | `DOOR_SYSTEM_GET_IS_PHYSICS_LOADED` | jhash |
| OBJECT | `_0xE9AE494F` | `DOOR_SYSTEM_FIND_EXISTING_DOOR` | jhash |
| OBJECT | `_0xC33ED360` | `IS_PLAYER_ENTIRELY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x41924877` | `IS_PLAYER_PARTIALLY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x4BD59750` | `ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x7B44D659` | `IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x142C8F76` | `IS_OBJECT_ENTIRELY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x95A9AB2B` | `IS_OBJECT_PARTIALLY_INSIDE_GARAGE` | jhash |
| OBJECT | `_0xA565E27E` | `CLEAR_OBJECTS_INSIDE_GARAGE` | jhash |
| OBJECT | `_0x43BB7E48` | `ENABLE_SAVING_IN_GARAGE` | jhash |
| OBJECT | `_0x6158959E` | `CLOSE_SAFEHOUSE_GARAGES` | jhash |
| OBJECT | `_0x19B17769` | `SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY` | jhash |
| OBJECT | `_0xE3261B35` | `REMOVE_OBJECT_HIGH_DETAIL_MODEL` | jhash |
| OBJECT | `_0x1E82C2AE` | `BREAK_OBJECT_FRAGMENT_CHILD` | jhash |
| OBJECT | `_0xF4A1A14A` | `SET_OBJECT_IS_SPECIAL_GOLFBALL` | jhash |
| OBJECT | `_0xAF016CC1` | `SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS` | jhash |
| OBJECT | `_0x3A68AA46` | `SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME` | jhash |
| OBJECT | `_0xA286DE96` | `GET_RAYFIRE_MAP_OBJECT` | jhash |
| OBJECT | `_0x21F51560` | `SET_STATE_OF_RAYFIRE_MAP_OBJECT` | jhash |
| OBJECT | `_0xF1B8817A` | `GET_STATE_OF_RAYFIRE_MAP_OBJECT` | jhash |
| OBJECT | `_0xE08C834D` | `DOES_RAYFIRE_MAP_OBJECT_EXIST` | jhash |
| OBJECT | `_0x020497DE` | `GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE` | jhash |
| OBJECT | `_0x56A02502` | `CREATE_NON_NETWORKED_PORTABLE_PICKUP` | jhash |
| OBJECT | `_0x7EFBA039` | `SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER` | jhash |
| OBJECT | `_0xA3CDF152` | `SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS` | jhash |
| OBJECT | `_0x6052E62E` | `GET_PICKUP_OBJECT` | jhash |
| OBJECT | `_0xF139681B` | `DOES_PICKUP_OF_TYPE_EXIST_IN_AREA` | jhash |
| OBJECT | `_0x7FADB4B9` | `SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE` | jhash |
| OBJECT | `_0x3A8F1BF7` | `SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL` | jhash |
| OBJECT | `_0xCBB5F9B6` | `PREVENT_COLLECTION_OF_PORTABLE_PICKUP` | jhash |
| OBJECT | `_0x276A7807` | `SET_PICKUP_OBJECT_GLOW_OFFSET` | jhash |
| OBJECT | `_0x000E92DC` | `GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP` | jhash |
| OBJECT | `_0x9879AC51` | `SET_PICKUP_GENERATION_RANGE_MULTIPLIER` | jhash |
| OBJECT | `_0xDB18FA01` | `SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW` | jhash |
| OBJECT | `_0xA7E936FD` | `SUPPRESS_PICKUP_REWARD_TYPE` | jhash |
| OBJECT | `_0xB241806C` | `CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION` | jhash |
| OBJECT | `_0xD1BAAFB7` | `CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION` | jhash |
| OBJECT | `_0x63B02FAD` | `RENDER_FAKE_PICKUP_GLOW` | jhash |
| OBJECT | `_0x132B6D92` | `SET_ENTITY_FLAG_RENDER_SMALL_SHADOW` | jhash |
| OBJECT | `_0xEDD01937` | `GET_WEAPON_TYPE_FROM_PICKUP_TYPE` | jhash |
| OBJECT | `_0x6AE36192` | `CONVERT_OLD_PICKUP_TYPE_TO_NEW` | jhash |
| OBJECT | `_0x2048A7DD` | `ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE` | jhash |
| AI | `_0x3AA39BE9` | `UPDATE_TASK_HANDS_UP_DURATION` | jhash |
| AI | `_0x55E06443` | `SET_PED_PATH_CLIMB_COST_MODIFIER` | jhash |
| AI | `SET_PED_PATHS_WIDTH_PLANT` | `SET_PED_PATH_MAY_ENTER_WATER` | jhash |
| AI | `_0x2AFB14B8` | `SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT` | jhash |
| AI | `_0x094B75EF` | `TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS` | jhash |
| AI | `_0x86DC03F9` | `TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED` | jhash |
| AI | `_0x3DDEB0E6` | `TASK_PLAY_ANIM_ADVANCED` | jhash |
| AI | `_0x1582162C` | `TASK_PLAY_PHONE_GESTURE_ANIMATION` | jhash |
| AI | `_0x500B6805` | `IS_PLAYING_PHONE_GESTURE_ANIM` | jhash |
| AI | `_0x7B72AFD1` | `GET_PHONE_GESTURE_ANIM_CURRENT_TIME` | jhash |
| AI | `_0xEF8C3959` | `GET_PHONE_GESTURE_ANIM_TOTAL_TIME` | jhash |
| AI | `_0xAFA914EF` | `GET_ACTIVE_VEHICLE_MISSION_TYPE` | jhash |
| AI | `_0x67E73525` | `UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET` | jhash |
| AI | `_0x249EB4EB` | `GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK` | jhash |
| AI | `_0x2A83083F` | `SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG` | jhash |
| AI | `_0x04FD3EE7` | `SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE` | jhash |
| AI | `_0x9B76F7E6` | `CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK` | jhash |
| AI | `_0xB23F46E6` | `IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK` | jhash |
| AI | `_0x500D9244` | `CONTROL_MOUNTED_WEAPON` | jhash |
| AI | `_0x98713C68` | `SET_MOUNTED_WEAPON_TARGET` | jhash |
| AI | `_0x291E938C` | `IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK` | jhash |
| AI | `_IS_COVER_POINT_AT_COORDS` | `DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS` | jhash |
| AI | `_0xC6B6CCC1` | `GET_SCRIPTED_COVER_POINT_COORDS` | jhash |
| AI | `_0x7AF0133D` | `TASK_GUARD_ASSIGNED_DEFENSIVE_AREA` | jhash |
| AI | `_0x0FB138A5` | `DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA` | jhash |
| AI | `_0x9BE9C691` | `PED_HAS_USE_SCENARIO_TASK` | jhash |
| AI | `_0x1984A5D1` | `PLAY_ANIM_ON_RUNNING_SCENARIO` | jhash |
| AI | `_0xBF55025D` | `RESET_SCENARIO_GROUPS_ENABLED` | jhash |
| AI | `_0xF58FDEB4` | `RESET_SCENARIO_TYPES_ENABLED` | jhash |
| AI | `_0x50779A2C` | `ADD_VEHICLE_SUBTASK_ATTACK_COORD` | jhash |
| AI | `_0x87125F5D` | `GET_IS_WAYPOINT_RECORDING_LOADED` | jhash |
| AI | `_0xF5F9B71E` | `WAYPOINT_RECORDING_GET_NUM_POINTS` | jhash |
| AI | `_0x19266913` | `WAYPOINT_RECORDING_GET_COORD` | jhash |
| AI | `_0xC765633A` | `WAYPOINT_RECORDING_GET_SPEED_AT_POINT` | jhash |
| AI | `_0xC4CD35AF` | `WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT` | jhash |
| AI | `_0xE8422AC4` | `GET_WAYPOINT_DISTANCE_ALONG_ROUTE` | jhash |
| AI | `_0x4DFD5FEC` | `USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE` | jhash |
| AI | `_0x79B067AF` | `ASSISTED_MOVEMENT_IS_ROUTE_LOADED` | jhash |
| AI | `_0x01CAAFCC` | `ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES` | jhash |
| AI | `_0x8FB923EC` | `ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME` | jhash |
| AI | `_0x6F5D215F` | `TASK_MOVE_NETWORK_BY_NAME` | jhash |
| AI | `_0x71A5C5DB` | `TASK_MOVE_NETWORK_ADVANCED_BY_NAME` | jhash |
| AI | `_0x902656EB` | `IS_TASK_MOVE_NETWORK_ACTIVE` | jhash |
| AI | `_0x92FDBAE6` | `IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION` | jhash |
| AI | `_0x885724DE` | `REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION` | jhash |
| AI | `_0x96C0277B` | `GET_TASK_MOVE_NETWORK_STATE` | jhash |
| AI | `_0xA79BE783` | `SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT` | jhash |
| AI | `_0xF3538041` | `SET_TASK_MOVE_NETWORK_SIGNAL_BOOL` | jhash |
| AI | `_0x1EBB6F3D` | `GET_TASK_MOVE_NETWORK_SIGNAL_BOOL` | jhash |
| AI | `_0x72FA5EF2` | `GET_TASK_MOVE_NETWORK_EVENT` | jhash |
| AI | `_0xE9DAF877` | `IS_MOVE_BLEND_RATIO_STILL` | jhash |
| AI | `_0xD21639A8` | `IS_MOVE_BLEND_RATIO_WALKING` | jhash |
| AI | `_0xE76A2353` | `IS_MOVE_BLEND_RATIO_RUNNING` | jhash |
| AI | `_0xDD616893` | `IS_MOVE_BLEND_RATIO_SPRINTING` | jhash |
| AI | `_0x4D210467` | `TASK_SWEEP_AIM_ENTITY` | jhash |
| AI | `_0xF65F0F4F` | `UPDATE_TASK_SWEEP_AIM_ENTITY` | jhash |
| AI | `_0x1683FE66` | `TASK_SWEEP_AIM_POSITION` | jhash |
| AI | `_0x6345EC80` | `UPDATE_TASK_SWEEP_AIM_POSITION` | jhash |
| GAMEPLAY | `_SET_ALLOCATED_STACK_SIZE` | `GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE` | jhash |
| GAMEPLAY | `_0x8B2DE971` | `SET_THIS_IS_A_TRIGGER_SCRIPT` | jhash |
| GAMEPLAY | `_0xE77199F7` | `INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION` | jhash |
| GAMEPLAY | `_0xA8171E9E` | `GET_PREV_WEATHER_TYPE_HASH_NAME` | jhash |
| GAMEPLAY | `_0x353E8056` | `GET_NEXT_WEATHER_TYPE_HASH_NAME` | jhash |
| GAMEPLAY | `_SET_WEATHER_TYPE_OVER_TIME` | `SET_WEATHER_TYPE_OVERTIME_PERSIST` | jhash |
| GAMEPLAY | `_0x9A5C1D56` | `GET_CURR_WEATHER_STATE` | jhash |
| GAMEPLAY | `_0x5CA74040` | `SET_CURR_WEATHER_STATE` | jhash |
| GAMEPLAY | `_0x625181DC` | `WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE` | jhash |
| GAMEPLAY | `_0xBEBBFDC8` | `WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE` | jhash |
| GAMEPLAY | `_0x6926AB03` | `WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE` | jhash |
| GAMEPLAY | `_0xD447439D` | `WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE` | jhash |
| GAMEPLAY | `_0x584E9C59` | `WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE` | jhash |
| GAMEPLAY | `_0x5656D578` | `WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE` | jhash |
| GAMEPLAY | `_0x0DE40C28` | `WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE` | jhash |
| GAMEPLAY | `_0x98C9138B` | `WATER_OVERRIDE_SET_RIPPLEBUMPINESS` | jhash |
| GAMEPLAY | `_0xFB1A9CDE` | `WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS` | jhash |
| GAMEPLAY | `_0x1C0CAE89` | `WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS` | jhash |
| GAMEPLAY | `_0x4671AC2E` | `WATER_OVERRIDE_SET_RIPPLEDISTURB` | jhash |
| GAMEPLAY | `_0xDA02F415` | `WATER_OVERRIDE_SET_STRENGTH` | jhash |
| GAMEPLAY | `_0x5F3DDEC0` | `WATER_OVERRIDE_FADE_IN` | jhash |
| GAMEPLAY | `_0x63A89684` | `WATER_OVERRIDE_FADE_OUT` | jhash |
| GAMEPLAY | `_0xDF38165E` | `FORCE_LIGHTNING_FLASH` | jhash |
| GAMEPLAY | `_0x8727A4C5` | `PRELOAD_CLOUD_HAT` | jhash |
| GAMEPLAY | `_0xED88FC61` | `LOAD_CLOUD_HAT` | jhash |
| GAMEPLAY | `_0xC9FA6E07` | `UNLOAD_CLOUD_HAT` | jhash |
| GAMEPLAY | `_0x2D7787BC` | `UNLOAD_ALL_CLOUD_HATS` | jhash |
| GAMEPLAY | `_0x64D91CED` | `GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD` | jhash |
| GAMEPLAY | `_0x89459F0A` | `GET_RATIO_OF_CLOSEST_POINT_ON_LINE` | jhash |
| GAMEPLAY | `_0xCAECF37E` | `GET_CLOSEST_POINT_ON_LINE` | jhash |
| GAMEPLAY | `_0xC6CC812C` | `GET_LINE_PLANE_INTERSECTION` | jhash |
| GAMEPLAY | `_0x87B92190` | `SLERP_NEAR_QUATERNION` | jhash |
| GAMEPLAY | `_CLEAR_AREA_OF_EVERYTHING` | `CLEAR_AREA_LEAVE_VEHICLE_HEALTH` | jhash |
| GAMEPLAY | `_0x39771F21` | `GET_STATUS_OF_MANUAL_SAVE` | jhash |
| GAMEPLAY | `_0x75B06B5A` | `SET_CREDITS_FADE_OUT_WITH_SCREEN` | jhash |
| GAMEPLAY | `_0x2569C9A7` | `HAVE_CREDITS_REACHED_END` | jhash |
| GAMEPLAY | `_0x296574AE` | `PAUSE_DEATH_ARREST_RESTART` | jhash |
| GAMEPLAY | `_0xC9F6F0BC` | `SET_FADE_OUT_AFTER_DEATH` | jhash |
| GAMEPLAY | `_0xCB074B9D` | `SET_FADE_OUT_AFTER_ARREST` | jhash |
| GAMEPLAY | `_0xC4D71AB4` | `GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD` | jhash |
| GAMEPLAY | `_0xA8546914` | `GET_IS_AUTO_SAVE_OFF` | jhash |
| GAMEPLAY | `_0x78350773` | `HAS_CODE_REQUESTED_AUTOSAVE` | jhash |
| GAMEPLAY | `_0x5A45B11A` | `CLEAR_CODE_REQUESTED_AUTOSAVE` | jhash |
| GAMEPLAY | `_0x81216EE0` | `ADD_REPLAY_STAT_VALUE` | jhash |
| GAMEPLAY | `_0xC58250F1` | `HAVE_REPLAY_STATS_BEEN_STORED` | jhash |
| GAMEPLAY | `_0x50C39926` | `GET_REPLAY_STAT_MISSION_ID` | jhash |
| GAMEPLAY | `_0x710E5D1E` | `GET_REPLAY_STAT_MISSION_TYPE` | jhash |
| GAMEPLAY | `_0xC7BD1AF0` | `GET_REPLAY_STAT_COUNT` | jhash |
| GAMEPLAY | `_0x22BE2423` | `GET_REPLAY_STAT_AT_INDEX` | jhash |
| GAMEPLAY | `_0xF62B3C48` | `QUEUE_MISSION_REPEAT_LOAD` | jhash |
| GAMEPLAY | `_0x3589452B` | `QUEUE_MISSION_REPEAT_SAVE` | jhash |
| GAMEPLAY | `_0x144AAF22` | `GET_STATUS_OF_MISSION_REPEAT_SAVE` | jhash |
| GAMEPLAY | `_0x52ACCB7B` | `SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY` | jhash |
| GAMEPLAY | `_0x0022A430` | `GET_FAKE_WANTED_LEVEL` | jhash |
| GAMEPLAY | `_0x082BA6F2` | `ALLOW_MISSION_CREATOR_WARP` | jhash |
| GAMEPLAY | `_0xBAF17315` | `SHOULD_USE_METRIC_MEASUREMENTS` | jhash |
| GAMEPLAY | `_0xBE81F1E2` | `IS_PROJECTILE_TYPE_WITHIN_DISTANCE` | jhash |
| GAMEPLAY | `_0x1A40454B` | `GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA` | jhash |
| GAMEPLAY | `_0x6BDE5CE4` | `GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE` | jhash |
| GAMEPLAY | `_GET_PROJECTILE_NEAR_PED` | `GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE` | jhash |
| GAMEPLAY | `_0x3C806A2D` | `SET_STUNT_JUMPS_CAN_TRIGGER` | jhash |
| GAMEPLAY | `_0x021636EE` | `IS_STUNT_JUMP_MESSAGE_SHOWING` | jhash |
| GAMEPLAY | `_0x006F9BA2` | `GET_NUM_SUCCESSFUL_STUNT_JUMPS` | jhash |
| GAMEPLAY | `_0xFF6191E1` | `HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED` | jhash |
| GAMEPLAY | `_0x721B2492` | `SET_INSTANCE_PRIORITY_MODE` | jhash |
| GAMEPLAY | `_0xE202879D` | `SET_INSTANCE_PRIORITY_HINT` | jhash |
| GAMEPLAY | `_0x9EF0BC64` | `GET_SIZE_OF_SAVE_DATA` | jhash |
| GAMEPLAY | `_0x9B38374A` | `REGISTER_ENUM_TO_SAVE` | jhash |
| GAMEPLAY | `_0xE2089749` | `REGISTER_TEXT_LABEL_15_TO_SAVE` | jhash |
| GAMEPLAY | `_0xF91B8C33` | `REGISTER_TEXT_LABEL_23_TO_SAVE` | jhash |
| GAMEPLAY | `_0x74E8FAD9` | `REGISTER_TEXT_LABEL_31_TO_SAVE` | jhash |
| GAMEPLAY | `_0x6B4335DD` | `REGISTER_TEXT_LABEL_63_TO_SAVE` | jhash |
| GAMEPLAY | `_0xFB45728E` | `START_SAVE_STRUCT_WITH_SIZE` | jhash |
| GAMEPLAY | `_0x893A342C` | `START_SAVE_ARRAY_WITH_SIZE` | jhash |
| GAMEPLAY | `_0x0B710A51` | `ENABLE_DISPATCH_SERVICE` | jhash |
| GAMEPLAY | `_0xE0F0684F` | `BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION` | jhash |
| GAMEPLAY | `_0x3CE5BF6B` | `GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL` | jhash |
| GAMEPLAY | `_0x0242D88E` | `SET_INCIDENT_REQUESTED_UNITS` | jhash |
| GAMEPLAY | `_0x1F38102E` | `SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT` | jhash |
| GAMEPLAY | `_0x42BF09B3` | `ADD_POP_MULTIPLIER_AREA` | jhash |
| GAMEPLAY | `_0xFBDBE374` | `REMOVE_POP_MULTIPLIER_AREA` | jhash |
| GAMEPLAY | `_0xC20A7D2B` | `PLAY_TENNIS_SWING_ANIM` | jhash |
| GAMEPLAY | `_0x8501E727` | `GET_TENNIS_SWING_ANIM_COMPLETE` | jhash |
| GAMEPLAY | `_0x1A332D2D` | `GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED` | jhash |
| GAMEPLAY | `_0x0C8865DF` | `PLAY_TENNIS_DIVE_ANIM` | jhash |
| GAMEPLAY | `_0x49F977A9` | `SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT` | jhash |
| GAMEPLAY | `_0x6F009E33` | `SET_DISPATCH_SPAWN_LOCATION` | jhash |
| GAMEPLAY | `_0xF557BAF9` | `ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA` | jhash |
| GAMEPLAY | `_0xE0C9307E` | `RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN` | jhash |
| GAMEPLAY | `_0xA0D8C749` | `SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN` | jhash |
| GAMEPLAY | `_0x24A4E0B2` | `ADD_TACTICAL_NAV_MESH_POINT` | jhash |
| GAMEPLAY | `_0x66C3C59C` | `CLEAR_TACTICAL_NAV_MESH_POINTS` | jhash |
| GAMEPLAY | `_0xD9660339` | `SET_RIOT_MODE_ENABLED` | jhash |
| GAMEPLAY | `_0xD2688412` | `DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING` | jhash |
| GAMEPLAY | `_0x3301EA47` | `NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS` | jhash |
| GAMEPLAY | `_0x42B484ED` | `ACTION_MANAGER_ENABLE_ACTION` | jhash |
| GAMEPLAY | `_0x8F60366E` | `SUPRESS_RANDOM_EVENT_THIS_FRAME` | jhash |
| GAMEPLAY | `_0xC3C10FCC` | `HAS_GAME_INSTALLED_THIS_SESSION` | jhash |
| GAMEPLAY | `_0x054EC103` | `SET_TICKER_JOHNMARSTON_IS_DONE` | jhash |
| GAMEPLAY | `_0x46B5A15C` | `ARE_PROFILE_SETTINGS_VALID` | jhash |
| GAMEPLAY | `_0x5D209F25` | `FORCE_GAME_STATE_PLAYING` | jhash |
| GAMEPLAY | `_0x2D33F15A` | `SCRIPT_RACE_INIT` | jhash |
| GAMEPLAY | `_0xDF99925C` | `SCRIPT_RACE_SHUTDOWN` | jhash |
| GAMEPLAY | `_0xA27F4472` | `SCRIPT_RACE_PLAYER_HIT_CHECKPOINT` | jhash |
| GAMEPLAY | `_0x07FF553F` | `SCRIPT_RACE_GET_PLAYER_SPLIT_TIME` | jhash |
| AUDIO | `_0x16FB88B5` | `IS_MOBILE_INTERFERENCE_ACTIVE` | jhash |
| AUDIO | `_0x73C6F979` | `SET_POSITION_FOR_NULL_CONV_PED` | jhash |
| AUDIO | `_0x88203DDA` | `SET_ENTITY_FOR_NULL_CONV_PED` | jhash |
| AUDIO | `_0x1193ED6E` | `SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM` | jhash |
| AUDIO | `_0x336F3D35` | `GET_IS_PRELOADED_CONVERSATION_READY` | jhash |
| AUDIO | `_0xB58B8FF3` | `GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE` | jhash |
| AUDIO | `_0x789D8C6C` | `SET_NO_DUCKING_FOR_CONVERSATION` | jhash |
| AUDIO | `_0xA58BBF4F` | `UNHINT_AMBIENT_AUDIO_BANK` | jhash |
| AUDIO | `_0xC70E6CFA` | `PLAY_DEFERRED_SOUND_FRONTEND` | jhash |
| AUDIO | `_0xD064D4DC` | `GET_SOUND_ID_FROM_NETWORK_ID` | jhash |
| AUDIO | `_0x62D026BE` | `SET_VARIABLE_ON_UNDER_WATER_STREAM` | jhash |
| AUDIO | `_PLAY_AMBIENT_SPEECH1` | `PLAY_PED_AMBIENT_SPEECH_NATIVE` | jhash |
| AUDIO | `_PLAY_AMBIENT_SPEECH2` | `PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE` | jhash |
| AUDIO | `_0x8386AE28` | `PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE` | jhash |
| AUDIO | `_0xA1A1402E` | `PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE` | jhash |
| AUDIO | `_0x59A3A17D` | `ACTIVATE_AUDIO_SLOWMO_MODE` | jhash |
| AUDIO | `_0x0E387BFE` | `DEACTIVATE_AUDIO_SLOWMO_MODE` | jhash |
| AUDIO | `_0x8BD5F11E` | `DOES_CONTEXT_EXIST_FOR_THIS_PED` | jhash |
| AUDIO | `_0x498849F3` | `PLAY_ANIMAL_VOCALIZATION` | jhash |
| AUDIO | `_0x0CBAF2EF` | `IS_ANIMAL_VOCALIZATION_PLAYING` | jhash |
| AUDIO | `_0x53DB6994` | `SET_RADIO_RETUNE_UP` | jhash |
| AUDIO | `_0xD70ECC80` | `SET_RADIO_RETUNE_DOWN` | jhash |
| AUDIO | `_0x7ABB89D2` | `SET_VEH_FORCED_RADIO_THIS_FRAME` | jhash |
| AUDIO | `GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS` | `IS_MISSION_NEWS_STORY_UNLOCKED` | jhash |
| AUDIO | `_0xCBA99F4A` | `CAN_VEHICLE_RECEIVE_CB_RADIO` | jhash |
| AUDIO | `_0x46B0C696` | `DOES_PLAYER_VEH_HAVE_RADIO` | jhash |
| AUDIO | `_0x2A3E5E8B` | `IS_PLAYER_VEH_RADIO_ENABLE` | jhash |
| AUDIO | `_0x128C3873` | `SET_CUSTOM_RADIO_TRACK_LIST` | jhash |
| AUDIO | `_0x1D766976` | `CLEAR_CUSTOM_RADIO_TRACK_LIST` | jhash |
| AUDIO | `_0xCC91FCF5` | `GET_NUM_UNLOCKED_RADIO_STATIONS` | jhash |
| AUDIO | `_0xB1FF7137` | `SET_RADIO_STATION_MUSIC_ONLY` | jhash |
| AUDIO | `_0xC8B514E2` | `SET_RADIO_FRONTEND_FADE_TIME` | jhash |
| AUDIO | `_0xBE998184` | `UNLOCK_RADIO_STATION_TRACK_LIST` | jhash |
| AUDIO | `_0x8AFC488D` | `SET_VEHICLE_MISSILE_WARNING_ENABLED` | jhash |
| AUDIO | `GET_PLAYER_HEADSET_SOUND_ALTERNATE` | `SET_VARIABLE_ON_SYNCH_SCENE_AUDIO` | jhash |
| AUDIO | `_0x3C395AEE` | `SET_RADIO_POSITION_AUDIO_MUTE` | jhash |
| AUDIO | `_0x8CE63FA1` | `SET_VEHICLE_CONVERSATIONS_PERSIST` | jhash |
| AUDIO | `_0xA1D7FABE` | `PLAY_STREAM_FROM_PED` | jhash |
| AUDIO | `SPECIAL_FRONTEND_EQUAL` | `PLAY_STREAM_FROM_POSITION` | jhash |
| AUDIO | `_0xDE8BA3CD` | `SET_HORN_PERMANENTLY_ON` | jhash |
| AUDIO | `_0x2F0A16D1` | `SET_HORN_PERMANENTLY_ON_TIME` | jhash |
| AUDIO | `_0x33B0B007` | `FORCE_USE_AUDIO_GAME_OBJECT` | jhash |
| AUDIO | `_0x1C0C5E4C` | `SET_VEHICLE_STARTUP_REV_SOUND` | jhash |
| AUDIO | `_0x6E660D3F` | `IS_VEHICLE_AUDIBLY_DAMAGED` | jhash |
| AUDIO | `_0x23BE6432` | `SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR` | jhash |
| AUDIO | `_0xE81FAC68` | `SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR` | jhash |
| AUDIO | `_0x9365E042` | `ENABLE_VEHICLE_FANBELT_DAMAGE` | jhash |
| AUDIO | `_0x2A60A90E` | `ENABLE_VEHICLE_EXHAUST_POPS` | jhash |
| AUDIO | `_0x934BE749` | `SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE` | jhash |
| AUDIO | `_0xE61110A2` | `SET_SCRIPT_UPDATE_DOOR_AUDIO` | jhash |
| AUDIO | `_0x563B635D` | `ENABLE_STALL_WARNING_SOUNDS` | jhash |
| AUDIO | `_0xCBE09AEC` | `IS_MISSION_COMPLETE_READY_FOR_UI` | jhash |
| AUDIO | `_0xD2858D8A` | `BLOCK_DEATH_JINGLE` | jhash |
| AUDIO | `_0xE812925D` | `SET_AUDIO_SCRIPT_CLEANUP_TIME` | jhash |
| AUDIO | `_0x2BC93264` | `ADD_ENTITY_TO_AUDIO_MIX_GROUP` | jhash |
| AUDIO | `_0x308ED0EC` | `REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP` | jhash |
| AUDIO | `_0x2705C4D5` | `IS_MUSIC_ONESHOT_PLAYING` | jhash |
| AUDIO | `_0x53FC3FEC` | `RECORD_BROKEN_GLASS` | jhash |
| AUDIO | `_0x95050CAD` | `SCRIPT_OVERRIDES_WIND_ELEVATION` | jhash |
| AUDIO | `_0xE64F97A0` | `SET_PED_WALLA_DENSITY` | jhash |
| AUDIO | `_0xD87AF337` | `FORCE_PED_PANIC_WALLA` | jhash |
| AUDIO | `_0xFD4B5B3B` | `GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS` | jhash |
| AUDIO | `_0xC307D531` | `OVERRIDE_PLAYER_GROUND_MATERIAL` | jhash |
| AUDIO | `_0x13EB5861` | `DISTANT_COP_CAR_SIRENS` | jhash |
| AUDIO | `_0x7BED1872` | `SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO` | jhash |
| AUDIO | `_0x55A21772` | `INIT_SYNCH_SCENE_AUDIO_WITH_POSITION` | jhash |
| AUDIO | `_0xA17F9AB0` | `INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY` | jhash |
| AUDIO | `_0x62B43677` | `SET_AUDIO_SPECIAL_EFFECT_MODE` | jhash |
| AUDIO | `_0x8AD670EC` | `SET_PORTAL_SETTINGS_OVERRIDE` | jhash |
| AUDIO | `_0xD24B4D0C` | `REMOVE_PORTAL_SETTINGS_OVERRIDE` | jhash |
| AUDIO | `_0x7262B5BA` | `STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS` | jhash |
| AUDIO | `_0x93A44A1F` | `GET_MUSIC_VOL_SLIDER` | jhash |
| AUDIO | `_0x13777A0B` | `REQUEST_TENNIS_BANKS` | jhash |
| AUDIO | `_0x1134F68B` | `UNREQUEST_TENNIS_BANKS` | jhash |
| AUDIO | `_0xE0047BFD` | `SET_SKIP_MINIGUN_SPIN_UP_AUDIO` | jhash |
| CUTSCENE | `_0xD98F656A` | `REQUEST_CUTSCENE_WITH_PLAYBACK_LIST` | jhash |
| CUTSCENE | `_0x25A2CABC` | `SET_SCRIPT_CAN_START_CUTSCENE` | jhash |
| CUTSCENE | `_0xDD8878E9` | `CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY` | jhash |
| CUTSCENE | `_0x7B93CDAA` | `IS_CUTSCENE_PLAYBACK_FLAG_SET` | jhash |
| CUTSCENE | `_0x47DB08A9` | `SET_CUTSCENE_ENTITY_STREAMING_FLAGS` | jhash |
| CUTSCENE | `_0x5AE68AE6` | `GET_CUTSCENE_CONCAT_SECTION_PLAYING` | jhash |
| CUTSCENE | `_0x35721A08` | `SET_PAD_CAN_SHAKE_DURING_CUTSCENE` | jhash |
| CUTSCENE | `_0x8338DA1D` | `NETWORK_SET_MOCAP_CUTSCENE_CAN_BE_SKIPPED` | jhash |
| CUTSCENE | `_0x04377C10` | `SET_CAR_GENERATORS_CAN_UPDATE_DURING_CUTSCENE` | jhash |
| CUTSCENE | `_0xDBD88708` | `CAN_USE_MOBILE_PHONE_DURING_CUTSCENE` | jhash |
| CUTSCENE | `_0x28D54A7F` | `SET_CUTSCENE_CAN_BE_SKIPPED` | jhash |
| CUTSCENE | `REGISTER_SYNCHRONISED_SCRIPT_SPEECH` | `SET_CAN_DISPLAY_MINIMAP_DURING_CUTSCENE_THIS_UPDATE` | jhash |
| CUTSCENE | `_0x1E7DA95E` | `SET_CUTSCENE_PED_COMPONENT_VARIATION_FROM_PED` | jhash |
| CUTSCENE | `_0x22E9A9DE` | `SET_CUTSCENE_PED_PROP_VARIATION` | jhash |
| CUTSCENE | `_0x4315A7C5` | `HAS_CUTSCENE_CUT_THIS_FRAME` | jhash |
| INTERIOR | `_0xE645E162` | `RETAIN_ENTITY_IN_INTERIOR` | jhash |
| INTERIOR | `_0xD79803B5` | `FORCE_ROOM_FOR_GAME_VIEWPORT` | jhash |
| INTERIOR | `_0x1F6B4B13` | `SET_ROOM_FOR_GAME_VIEWPORT_BY_NAME` | jhash |
| INTERIOR | `_0x0E9529CC` | `SET_ROOM_FOR_GAME_VIEWPORT_BY_KEY` | jhash |
| INTERIOR | `_0x4FF3D3F5` | `GET_ROOM_KEY_FOR_GAME_VIEWPORT` | jhash |
| INTERIOR | `_0x617DC75D` | `CLEAR_ROOM_FOR_GAME_VIEWPORT` | jhash |
| INTERIOR | `_0x3ADA414E` | `PIN_INTERIOR_IN_MEMORY` | jhash |
| INTERIOR | `_0x96525B06` | `GET_INTERIOR_AT_COORDS_WITH_TYPE` | jhash |
| INTERIOR | `_0x7762249C` | `IS_COLLISION_MARKED_OUTSIDE` | jhash |
| INTERIOR | `_0xC80A5DDF` | `ACTIVATE_INTERIOR_ENTITY_SET` | jhash |
| INTERIOR | `_0xDBA768A1` | `DEACTIVATE_INTERIOR_ENTITY_SET` | jhash |
| INTERIOR | `_0x39A3CC6F` | `IS_INTERIOR_ENTITY_SET_ACTIVE` | jhash |
| INTERIOR | `_0x1F375B4C` | `ENABLE_EXTERIOR_CULL_MODEL_THIS_FRAME` | jhash |
| INTERIOR | `_0x5EF9C5C2` | `DISABLE_METRO_SYSTEM` | jhash |
| CAM | `_0xD3C08183` | `STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP` | jhash |
| CAM | `_0x8306C256` | `SET_CAM_USE_SHALLOW_DOF_MODE` | jhash |
| CAM | `_0x8BBF2950` | `SET_USE_HI_DOF` | jhash |
| CAM | `_0x0C74F9AF` | `SET_CAM_AFFECTS_AIMING` | jhash |
| CAM | `_0xE1A0B2F1` | `SET_CAM_CONTROLS_MINI_MAP_HEADING` | jhash |
| CAM | `_0x43220969` | `ALLOW_MOTION_BLUR_DECAY` | jhash |
| CAM | `_0x30510511` | `ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME` | jhash |
| CAM | `_0xBA6C085B` | `ADD_CAM_SPLINE_NODE_USING_CAMERA` | jhash |
| CAM | `_0xB4737F03` | `ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME` | jhash |
| CAM | `_0x15E141CE` | `SET_CAM_SPLINE_SMOOTHING_STYLE` | jhash |
| CAM | `_0x21D275DA` | `SET_CAM_SPLINE_NODE_EASE` | jhash |
| CAM | `_0xA3BD9E94` | `SET_CAM_SPLINE_NODE_VELOCITY_SCALE` | jhash |
| CAM | `_0xC90B2DDC` | `SET_CAM_SPLINE_NODE_EXTRA_FLAGS` | jhash |
| CAM | `_0x2B0F05CD` | `SHAKE_SCRIPT_GLOBAL` | jhash |
| CAM | `_0xCB75BD9C` | `ANIMATED_SHAKE_SCRIPT_GLOBAL` | jhash |
| CAM | `_0x6AEFE6A5` | `IS_SCRIPT_GLOBAL_SHAKING` | jhash |
| CAM | `_0x26FCFB96` | `STOP_SCRIPT_GLOBAL_SHAKING` | jhash |
| CAM | `_0x56F9ED27` | `SET_FLY_CAM_HORIZONTAL_RESPONSE` | jhash |
| CAM | `_0x71570DBA` | `SET_FLY_CAM_MAX_HEIGHT` | jhash |
| CAM | `_0x60B345DE` | `SET_FLY_CAM_COORD_AND_CONSTRAIN` | jhash |
| CAM | `_0x44473EFC` | `SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE` | jhash |
| CAM | `_0xDA931D65` | `WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE` | jhash |
| CAM | `_0xA6E73135` | `SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE` | jhash |
| CAM | `_0x1126E37C` | `SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE` | jhash |
| CAM | `_0x7D3007A2` | `SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE` | jhash |
| CAM | `_0xC0B00C20` | `IS_INTERPOLATING_FROM_SCRIPT_CAMS` | jhash |
| CAM | `_0x60C23785` | `IS_INTERPOLATING_TO_SCRIPT_CAMS` | jhash |
| CAM | `_0x20BFF6E5` | `SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE` | jhash |
| CAM | `_0xA61FF9AC` | `DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE` | jhash |
| CAM | `_0x2701A9AD` | `SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE` | jhash |
| CAM | `_0xC4736ED3` | `DISABLE_CAM_COLLISION_FOR_OBJECT` | jhash |
| CAM | `_0x6B0E9D57` | `SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE` | jhash |
| CAM | `SET_FOLLOW_PED_CAM_CUTSCENE_CHAT` | `SET_FOLLOW_PED_CAM_THIS_UPDATE` | jhash |
| CAM | `_0x8DC53629` | `USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME` | jhash |
| CAM | `_0x1F9DE6E4` | `SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE` | jhash |
| CAM | `_CLAMP_GAMEPLAY_CAM_YAW` | `SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_CLAMP_GAMEPLAY_CAM_PITCH` | `SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_ANIMATE_GAMEPLAY_CAM_ZOOM` | `SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_0x4B22C5CB` | `SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE` | jhash |
| CAM | `_0x9DB5D391` | `SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE` | jhash |
| CAM | `_0x92302899` | `SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE` | jhash |
| CAM | `_0xF3B148A6` | `GET_CAM_VIEW_MODE_FOR_CONTEXT` | jhash |
| CAM | `_0x1DEBCB45` | `SET_CAM_VIEW_MODE_FOR_CONTEXT` | jhash |
| CAM | `_0x8F320DE4` | `IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE` | jhash |
| CAM | `_0x1BAA7182` | `DISABLE_AIM_CAM_THIS_UPDATE` | jhash |
| CAM | `_0x33951005` | `GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR` | jhash |
| CAM | `_0x9F4AF763` | `SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR` | jhash |
| CAM | `_0x68BA0730` | `SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_0x2F29F0D5` | `SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_0x76DAC96C` | `SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE` | jhash |
| CAM | `_0x0E21069D` | `SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE` | jhash |
| CAM | `_0x71E9C63E` | `SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE` | jhash |
| CAM | `_0xD1EEBC45` | `SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE` | jhash |
| CAM | `_0x9C84BDA0` | `GET_FINAL_RENDERED_CAM_COORD` | jhash |
| CAM | `_0x1FFBEFC5` | `GET_FINAL_RENDERED_CAM_ROT` | jhash |
| CAM | `_0xACADF916` | `GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT` | jhash |
| CAM | `_0x721B763B` | `GET_FINAL_RENDERED_CAM_FOV` | jhash |
| CAM | `_0x23E3F106` | `GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV` | jhash |
| CAM | `_0x457AE195` | `GET_FINAL_RENDERED_CAM_NEAR_CLIP` | jhash |
| CAM | `_0x46CB3A49` | `GET_FINAL_RENDERED_CAM_FAR_CLIP` | jhash |
| CAM | `_0x19297A7A` | `GET_FINAL_RENDERED_CAM_NEAR_DOF` | jhash |
| CAM | `_0xF24777CA` | `GET_FINAL_RENDERED_CAM_FAR_DOF` | jhash |
| CAM | `_0x38992E83` | `GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH` | jhash |
| CAM | `_0x2ED5E2F8` | `SET_GAMEPLAY_OBJECT_HINT` | jhash |
| CAM | `_0xCAFEE798` | `STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE` | jhash |
| CAM | `_0x72E8CD3A` | `SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR` | jhash |
| CAM | `_0x79472AE3` | `SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET` | jhash |
| CAM | `_0xFC7464A0` | `SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET` | jhash |
| CAM | `_0x3554AA0E` | `SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET` | jhash |
| CAM | `GET_IS_MULTIPLAYER_BRIEF` | `SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE` | jhash |
| CAM | `_0x5AC6DAC9` | `DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE` | jhash |
| CAM | `_0x837F8581` | `DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE` | jhash |
| CAM | `_0x65DDE8AF` | `INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE` | jhash |
| CAM | `_0xD75CDD75` | `INVALIDATE_IDLE_CAM` | jhash |
| CAM | `_0x96A07066` | `IS_CINEMATIC_IDLE_CAM_RENDERING` | jhash |
| CAM | `_0xFBB85E02` | `FORCE_CINEMATIC_RENDERING_THIS_UPDATE` | jhash |
| CAM | `_0x4938C82F` | `SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE` | jhash |
| CAM | `_0x6739AD55` | `IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING` | jhash |
| CAM | `_0x067BA6F5` | `SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE` | jhash |
| CAM | `_0xFD99BE2B` | `GET_FOCUS_PED_ON_SCREEN` | jhash |
| CAM | `_0xE206C450` | `DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE` | jhash |
| CAM | `_0xB06CCD38` | `SET_CAM_DEATH_FAIL_EFFECT_STATE` | jhash |
| WEAPON | `_0x324FA47A` | `GET_WEAPON_COMPONENT_TYPE_MODEL` | jhash |
| WEAPON | `_0x5D73CD20` | `GET_CURRENT_PED_WEAPON_ENTITY_INDEX` | jhash |
| WEAPON | `_0x02A32CB0` | `IS_PED_WEAPON_READY_TO_SHOOT` | jhash |
| WEAPON | `_0xD6460EA2` | `SET_PICKUP_AMMO_AMOUNT_SCALER` | jhash |
| WEAPON | `_0x09337863` | `GET_PED_AMMO_TYPE_FROM_WEAPON` | jhash |
| WEAPON | `_0x8DDD0B5B` | `GET_IS_PED_GADGET_EQUIPPED` | jhash |
| WEAPON | `_0x3612110D` | `GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON` | jhash |
| WEAPON | `_0xB2B2BBAA` | `GET_MAX_RANGE_OF_CURRENT_PED_WEAPON` | jhash |
| WEAPON | `_0x82EEAF0F` | `REFILL_AMMO_INSTANTLY` | jhash |
| WEAPON | `_0xB1817BAA` | `DOES_WEAPON_TAKE_WEAPON_COMPONENT` | jhash |
| WEAPON | `_0xB4F44C6E` | `SET_PED_CHANCE_OF_FIRING_BLANKS` | jhash |
| WEAPON | `_0xEC2E5304` | `SET_PED_SHOOT_ORDNANCE_WEAPON` | jhash |
| WEAPON | `_0xE3BD00F9` | `REQUEST_WEAPON_HIGH_DETAIL_MODEL` | jhash |
| WEAPON | `_0xBAF7BFBE` | `IS_PED_CURRENT_WEAPON_SILENCED` | jhash |
| WEAPON | `SET_WEAPON_SMOKEGRENADE_ASSIGNED` | `IS_FLASH_LIGHT_ON` | jhash |
| WEAPON | `_0xB0127EA7` | `SET_FLASH_LIGHT_FADE_DISTANCE` | jhash |
| WEAPON | `_0x64646F1D` | `SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED` | jhash |
| WEAPON | `_0x135E7AD4` | `CAN_USE_WEAPON_ON_PARACHUTE` | jhash |
| STREAMING | `_0x48CEB6B4` | `REQUEST_MENU_PED_MODEL` | jhash |
| STREAMING | `_0x939243FB` | `REQUEST_MODELS_IN_ROOM` | jhash |
| STREAMING | `_0xCD31C872` | `DOES_ANIM_DICT_EXIST` | jhash |
| STREAMING | `_REQUEST_DLC_PTFX_ASSET` | `REQUEST_NAMED_PTFX_ASSET` | jhash |
| STREAMING | `_HAS_DLC_PTFX_LOADED` | `HAS_NAMED_PTFX_ASSET_LOADED` | jhash |
| STREAMING | `_REMOVE_DLC_PTFX_ASSET` | `REMOVE_NAMED_PTFX_ASSET` | jhash |
| STREAMING | `_0x14680A60` | `SET_FOCUS_POS_AND_VEL` | jhash |
| STREAMING | `_0x403CD434` | `SET_MAPDATACULLBOX_ENABLED` | jhash |
| STREAMING | `_0xA07BAEB9` | `SET_ALL_MAPDATA_CULLED` | jhash |
| STREAMING | `_0x10B6AB36` | `STREAMVOL_CREATE_SPHERE` | jhash |
| STREAMING | `_0x72344191` | `STREAMVOL_CREATE_FRUSTUM` | jhash |
| STREAMING | `_0xC0157255` | `STREAMVOL_CREATE_LINE` | jhash |
| STREAMING | `_0xE80F8ABE` | `STREAMVOL_DELETE` | jhash |
| STREAMING | `_0x1B3521F4` | `STREAMVOL_HAS_LOADED` | jhash |
| STREAMING | `_0x42CFE9C0` | `STREAMVOL_IS_VALID` | jhash |
| STREAMING | `_0x56253356` | `IS_STREAMVOL_ACTIVE` | jhash |
| STREAMING | `_0xFA037FEB` | `NEW_LOAD_SCENE_START_SPHERE` | jhash |
| STREAMING | `_0xEAA51103` | `IS_SAFE_TO_START_PLAYER_SWITCH` | jhash |
| STREAMING | `STOP_PLAYER_REMAIN_ARCADE` | `IS_PLAYER_SWITCH_IN_PROGRESS` | jhash |
| STREAMING | `_0xF0BD420D` | `SET_PLAYER_SHORT_SWITCH_STYLE` | jhash |
| STREAMING | `_0x02BA7AC2` | `GET_PLAYER_SWITCH_JUMP_CUT_INDEX` | jhash |
| STREAMING | `_0x47352E14` | `SET_PLAYER_SWITCH_OUTRO` | jhash |
| STREAMING | `_0x279077B0` | `SET_PLAYER_SWITCH_ESTABLISHING_SHOT` | jhash |
| STREAMING | `_0x55CB21F9` | `ALLOW_PLAYER_SWITCH_PAN` | jhash |
| STREAMING | `_0x1084F2F4` | `ALLOW_PLAYER_SWITCH_OUTRO` | jhash |
| STREAMING | `_0x5B1E995D` | `ALLOW_PLAYER_SWITCH_ASCENT` | jhash |
| STREAMING | `_0x4B4B9A13` | `ALLOW_PLAYER_SWITCH_DESCENT` | jhash |
| STREAMING | `_0x408F7148` | `IS_SWITCH_READY_FOR_DESCENT` | jhash |
| STREAMING | `_0xFB4D062D` | `SWITCH_TO_MULTI_FIRSTPART` | jhash |
| STREAMING | `_0x2349373B` | `SWITCH_TO_MULTI_SECONDPART` | jhash |
| STREAMING | `_0x74C16879` | `IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED` | jhash |
| STREAMING | `SET_PLAYER_INVERTED_UP` | `GET_PLAYER_SWITCH_INTERP_OUT_DURATION` | jhash |
| STREAMING | `_0xC7A3D279` | `GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME` | jhash |
| STREAMING | `DESTROY_PLAYER_IN_PAUSE_MENU` | `IS_SWITCH_SKIPPING_DESCENT` | jhash |
| STREAMING | `_0x7154B6FD` | `GET_LODSCALE` | jhash |
| STREAMING | `_0xE5612C1A` | `OVERRIDE_LODSCALE_THIS_FRAME` | jhash |
| STREAMING | `_0x9CD6A451` | `REMAP_LODSCALE_RANGE_THIS_FRAME` | jhash |
| STREAMING | `_0x4267DA87` | `SUPPRESS_HD_MAP_STREAMING_THIS_FRAME` | jhash |
| STREAMING | `_0x9FA4AF99` | `SET_RENDER_HD_ONLY` | jhash |
| STREAMING | `_0x9EF0A9CF` | `IPL_GROUP_SWAP_START` | jhash |
| STREAMING | `_0xF2CDD6A8` | `IPL_GROUP_SWAP_CANCEL` | jhash |
| STREAMING | `_0x17B0A1CD` | `IPL_GROUP_SWAP_IS_READY` | jhash |
| STREAMING | `_0x3DA7AA5D` | `IPL_GROUP_SWAP_FINISH` | jhash |
| STREAMING | `_0xDAB4BAC0` | `IPL_GROUP_SWAP_IS_ACTIVE` | jhash |
| STREAMING | `_0x814D0752` | `SET_SRL_POST_CUTSCENE_CAMERA` | jhash |
| STREAMING | `_0x62F02485` | `SET_SRL_READAHEAD_TIMES` | jhash |
| STREAMING | `_0xA6459CAA` | `SET_SRL_LONG_JUMP_MODE` | jhash |
| STREAMING | `_0xF8F515E4` | `SET_SRL_FORCE_PRESTREAM` | jhash |
| STREAMING | `_0xE243B2AF` | `INIT_CREATOR_BUDGET` | jhash |
| STREAMING | `_0x897A510F` | `SHUTDOWN_CREATOR_BUDGET` | jhash |
| STREAMING | `_0xC0E83320` | `ADD_MODEL_TO_CREATOR_BUDGET` | jhash |
| STREAMING | `_0x1C576388` | `REMOVE_MODEL_FROM_CREATOR_BUDGET` | jhash |
| STREAMING | `_0x3E9C4CBE` | `GET_USED_CREATOR_BUDGET` | jhash |
| SCRIPT | `_0x1C68D9DC` | `REQUEST_SCRIPT_WITH_NAME_HASH` | jhash |
| SCRIPT | `_0x96C26F66` | `SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED` | jhash |
| SCRIPT | `_0x06674818` | `HAS_SCRIPT_WITH_NAME_HASH_LOADED` | jhash |
| SCRIPT | `_GET_THREAD_NAME` | `GET_NAME_OF_SCRIPT_WITH_THIS_ID` | jhash |
| SCRIPT | `_0xBB4E2F66` | `SCRIPT_THREAD_ITERATOR_RESET` | jhash |
| SCRIPT | `_0x1E28B28F` | `SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID` | jhash |
| SCRIPT | `_0x029D3841` | `GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH` | jhash |
| SCRIPT | `_0x2BEE1F45` | `GET_HASH_OF_THIS_SCRIPT_NAME` | jhash |
| SCRIPT | `_0xB03BCCDF` | `COMMIT_TO_LOADINGSCREEN_SELCTION` | jhash |
| UI | `_0xCB7C8994` | `BEGIN_TEXT_COMMAND_BUSYSPINNER_ON` | jhash |
| UI | `_0x903F5EE4` | `END_TEXT_COMMAND_BUSYSPINNER_ON` | jhash |
| UI | `_0x94119534` | `BUSYSPINNER_OFF` | jhash |
| UI | `_0x71077FBD` | `PRELOAD_BUSYSPINNER` | jhash |
| UI | `_0xB8B3A5D0` | `BUSYSPINNER_IS_ON` | jhash |
| UI | `_0xA7C8594B` | `THEFEED_ONLY_SHOW_TOOLTIPS` | jhash |
| UI | `_0x1DA7E41A` | `THEFEED_SET_SCRIPTED_MENU_HEIGHT` | jhash |
| UI | `_0x1E63088A` | `THEFEED_HIDE_THIS_FRAME` | jhash |
| UI | `_0x5205C6F5` | `THEFEED_FLUSH_QUEUE` | jhash |
| UI | `_0xECA8ACB9` | `THEFEED_REMOVE_ITEM` | jhash |
| UI | `_0x520FCB6D` | `THEFEED_FORCE_RENDER_ON` | jhash |
| UI | `_0xC8BAB2F2` | `THEFEED_FORCE_RENDER_OFF` | jhash |
| UI | `_0x4D0449C6` | `THEFEED_PAUSE` | jhash |
| UI | `_0xD3F40140` | `THEFEED_RESUME` | jhash |
| UI | `_0xC5223796` | `THEFEED_IS_PAUSED` | jhash |
| UI | `_0x709B4BCB` | `THEFEED_REPORT_LOGO_ON` | jhash |
| UI | `_0x4A4A40A4` | `THEFEED_REPORT_LOGO_OFF` | jhash |
| UI | `_0x294405D4` | `THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID` | jhash |
| UI | `_0xF881AB87` | `THEFEED_AUTO_POST_GAMETIPS_ON` | jhash |
| UI | `_0x1D6859CA` | `THEFEED_AUTO_POST_GAMETIPS_OFF` | jhash |
| UI | `_0xCF14D7F2` | `THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE` | jhash |
| UI | `_0x24A97AF8` | `THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE` | jhash |
| UI | `_0x44018EDB` | `THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE` | jhash |
| UI | `_0xA4524B23` | `THEFEED_RESET_ALL_PARAMETERS` | jhash |
| UI | `_0xAFA1148B` | `THEFEED_FREEZE_NEXT_POST` | jhash |
| UI | `_0x3CD4307C` | `THEFEED_CLEAR_FROZEN_POST` | jhash |
| UI | `_0x574EE85C` | `BEGIN_TEXT_COMMAND_THEFEED_POST` | jhash |
| UI | `_0xED130FA1` | `END_TEXT_COMMAND_THEFEED_POST_STATS` | jhash |
| UI | `_SET_NOTIFICATION_MESSAGE` | `END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT` | jhash |
| UI | `_0x0EB382B7` | `END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU` | jhash |
| UI | `_0x3E807FE3` | `END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG` | jhash |
| UI | `_0xDEB491C8` | `END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON` | jhash |
| UI | `_DRAW_NOTIFICATION` | `END_TEXT_COMMAND_THEFEED_POST_TICKER` | jhash |
| UI | `_0x57B8D0D4` | `END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED` | jhash |
| UI | `_0x02BCAF9B` | `END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS` | jhash |
| UI | `_0x02DED2B8` | `END_TEXT_COMMAND_THEFEED_POST_AWARD` | jhash |
| UI | `_0xA9CCEF66` | `END_TEXT_COMMAND_THEFEED_POST_CREWTAG` | jhash |
| UI | `_0x88B9B909` | `END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME` | jhash |
| UI | `_0xE05E7052` | `END_TEXT_COMMAND_THEFEED_POST_UNLOCK` | jhash |
| UI | `_0x4FA43BA4` | `END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU` | jhash |
| UI | `_0x8C90D22F` | `END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR` | jhash |
| UI | `_0x8E319AB8` | `END_TEXT_COMMAND_THEFEED_POST_MPTICKER` | jhash |
| UI | `_0x5E93FBFA` | `END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU` | jhash |
| UI | `_0xF42C43C7` | `BEGIN_TEXT_COMMAND_PRINT` | jhash |
| UI | `_0x38F82261` | `END_TEXT_COMMAND_PRINT` | jhash |
| UI | `_0xDD524A11` | `BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED` | jhash |
| UI | `_0x672EFB45` | `END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED` | jhash |
| UI | `_SET_TEXT_ENTRY` | `BEGIN_TEXT_COMMAND_DISPLAY_TEXT` | jhash |
| UI | `_DRAW_TEXT` | `END_TEXT_COMMAND_DISPLAY_TEXT` | jhash |
| UI | `_0x51E7A037` | `BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT` | jhash |
| UI | `_0xD12A643A` | `END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT` | jhash |
| UI | `_SET_TEXT_GXT_ENTRY` | `BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING` | jhash |
| UI | `_0xAA318785` | `END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING` | jhash |
| UI | `_SET_TEXT_COMPONENT_FORMAT` | `BEGIN_TEXT_COMMAND_DISPLAY_HELP` | jhash |
| UI | `_0xB59B530D` | `END_TEXT_COMMAND_DISPLAY_HELP` | jhash |
| UI | `_0x00E20F2D` | `BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED` | jhash |
| UI | `_0xF63A13EC` | `END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED` | jhash |
| UI | `_0xF4C211F6` | `BEGIN_TEXT_COMMAND_SET_BLIP_NAME` | jhash |
| UI | `_0xE8E59820` | `END_TEXT_COMMAND_SET_BLIP_NAME` | jhash |
| UI | `_0x0E103475` | `BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS` | jhash |
| UI | `_0x2944A6C5` | `END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS` | jhash |
| UI | `_0x550665AE` | `BEGIN_TEXT_COMMAND_CLEAR_PRINT` | jhash |
| UI | `_0x67785AF2` | `END_TEXT_COMMAND_CLEAR_PRINT` | jhash |
| UI | `_0xBF855650` | `BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT` | jhash |
| UI | `_0x6E7FDA1C` | `END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT` | jhash |
| UI | `_ADD_TEXT_COMPONENT_ITEM_STRING` | `ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL` | jhash |
| UI | `_0x150E03B6` | `ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY` | jhash |
| UI | `_0x5DE98F0A` | `ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME` | jhash |
| UI | `_0x12929BDF` | `ADD_TEXT_COMPONENT_FORMATTED_INTEGER` | jhash |
| UI | `_0x65E1D404` | `ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER` | jhash |
| UI | `_ADD_TEXT_COMPONENT_STRING2` | `ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE` | jhash |
| UI | `_ADD_TEXT_COMPONENT_STRING3` | `ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY` | jhash |
| UI | `_0x6F1A1901` | `SET_COLOUR_OF_NEXT_TEXT_COMPONENT` | jhash |
| UI | `_0x0183A66C` | `GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT` | jhash |
| UI | `_0xFA6373BB` | `GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES` | jhash |
| UI | `_0x95C4B5AD` | `GET_FILENAME_FOR_AUDIO_CONVERSATION` | jhash |
| UI | `_0xF4D27EBE` | `REQUEST_ADDITIONAL_TEXT_FOR_DLC` | jhash |
| UI | `_0x7DBC0764` | `GET_LENGTH_OF_LITERAL_STRING_IN_BYTES` | jhash |
| UI | `_0xC380AC85` | `DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME` | jhash |
| UI | `_0xC47AB1B0` | `DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME` | jhash |
| UI | `_0x9854485F` | `FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST` | jhash |
| UI | `RESPONDING_AS_TEMP` | `SET_RADAR_ZOOM_PRECISE` | jhash |
| UI | `_0x25EC28C0` | `SET_RADAR_ZOOM_TO_BLIP` | jhash |
| UI | `_0x09CF1CE5` | `SET_RADAR_ZOOM_TO_DISTANCE` | jhash |
| UI | `_0xE8D3A910` | `UPDATE_RADAR_ZOOM_TO_BLIP` | jhash |
| UI | `_0x0E41E45C` | `SET_SCRIPT_VARIABLE_HUD_COLOUR` | jhash |
| UI | `_0x6BE3ACA8` | `SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR` | jhash |
| UI | `_0x3B216749` | `REPLACE_HUD_COLOUR` | jhash |
| UI | `_0xF6E7E92B` | `REPLACE_HUD_COLOUR_WITH_RGBA` | jhash |
| UI | `_0x3330175B` | `GET_RENDERED_CHARACTER_HEIGHT` | jhash |
| UI | `_0x68CDFA60` | `SET_TEXT_JUSTIFICATION` | jhash |
| UI | `_0x812CBE0E` | `HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME` | jhash |
| UI | `_0x87871CE0` | `GET_STANDARD_BLIP_ENUM_ID` | jhash |
| UI | `_GET_BLIP_INFO_ID_ITERATOR` | `GET_WAYPOINT_BLIP_ENUM_ID` | jhash |
| UI | `_0xBF25E7B2` | `TRIGGER_SONAR_BLIP` | jhash |
| UI | `_0xE7E1E32B` | `ALLOW_SONAR_BLIPS` | jhash |
| UI | `_0x3E47F357` | `DOES_BLIP_HAVE_GPS_ROUTE` | jhash |
| UI | `_0x43996428` | `SET_BLIP_HIDDEN_ON_LEGEND` | jhash |
| UI | `DISABLE_BLIP_NAME_FOR_VAR` | `GET_NEW_SELECTED_MISSION_CREATOR_BLIP` | jhash |
| UI | `_0xC5EB849A` | `IS_HOVERING_OVER_MISSION_CREATOR_BLIP` | jhash |
| UI | `_0xA2CAAB4F` | `SHOW_START_MISSION_INSTRUCTIONAL_BUTTON` | jhash |
| UI | `_0x1D99F676` | `SHOW_HEIGHT_ON_BLIP` | jhash |
| UI | `_0x3DCF0092` | `SHOW_TICK_ON_BLIP` | jhash |
| UI | `_0xD1C3D71B` | `SHOW_HEADING_INDICATOR_ON_BLIP` | jhash |
| UI | `_0x8DE82C15` | `SHOW_OUTLINE_INDICATOR_ON_BLIP` | jhash |
| UI | `_0x4C8F02B4` | `SHOW_FRIEND_INDICATOR_ON_BLIP` | jhash |
| UI | `_0xABBE1E45` | `SHOW_CREW_INDICATOR_ON_BLIP` | jhash |
| UI | `_0x6AA6A1CC` | `SET_BLIP_EXTENDED_HEIGHT_THRESHOLD` | jhash |
| UI | `_0xC575F0BC` | `SET_BLIP_AS_MINIMAL_ON_EDGE` | jhash |
| UI | `_0x40E25DB8` | `SET_RADIUS_BLIP_EDGE` | jhash |
| UI | `_0x62BABF2C` | `DELETE_WAYPOINTS_FROM_THIS_PLAYER` | jhash |
| UI | `_0x41B0D022` | `REMOVE_COP_BLIP_FROM_PED` | jhash |
| UI | `_0x54E75C7D` | `SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME` | jhash |
| UI | `_0x199DED14` | `IS_PAUSEMAP_IN_INTERIOR_MODE` | jhash |
| UI | `_0x1A4318F7` | `HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME` | jhash |
| UI | `_0xCE36E3FE` | `HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME` | jhash |
| UI | `_0x334EFD46` | `DONT_TILT_MINIMAP_THIS_FRAME` | jhash |
| UI | `_0x5476B9FD` | `ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT` | jhash |
| UI | `_0xF4F3C796` | `SET_MULTIPLAYER_WALLET_CASH` | jhash |
| UI | `_0x7BFFE82F` | `REMOVE_MULTIPLAYER_WALLET_CASH` | jhash |
| UI | `_0x1EFFB02A` | `HUD_FORCE_WEAPON_WHEEL` | jhash |
| UI | `_0xB26FED2B` | `HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME` | jhash |
| UI | `_0x22E9F555` | `HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED` | jhash |
| UI | `_0x83B608A0` | `HUD_SET_WEAPON_WHEEL_TOP_SLOT` | jhash |
| UI | `_0xE70D1F43` | `HUD_SHOWING_CHARACTER_SWITCH_SELECTION` | jhash |
| UI | `_0xFB9BABF5` | `SET_RACE_TRACK_RENDER` | jhash |
| UI | `_0x7F93799B` | `START_GPS_CUSTOM_ROUTE` | jhash |
| UI | `_0xEEBDFE55` | `ADD_POINT_TO_GPS_CUSTOM_ROUTE` | jhash |
| UI | `_0xDA0AF00E` | `SET_GPS_CUSTOM_ROUTE_RENDER` | jhash |
| UI | `_0xCF2E3E24` | `CLEAR_GPS_CUSTOM_ROUTE` | jhash |
| UI | `_0xC3DCBEDB` | `START_GPS_MULTI_ROUTE` | jhash |
| UI | `_0xFE485135` | `ADD_POINT_TO_GPS_MULTI_ROUTE` | jhash |
| UI | `_0xE87CBE4C` | `SET_GPS_MULTI_ROUTE_RENDER` | jhash |
| UI | `_0x0D9969E4` | `CLEAR_GPS_MULTI_ROUTE` | jhash |
| UI | `_0x79A6CAF6` | `FLASH_MINIMAP_DISPLAY_WITH_COLOR` | jhash |
| UI | `KEY_HUD_COLOUR` | `SET_MINIMAP_IN_SPECTATOR_MODE` | jhash |
| UI | `_0x8D9A1734` | `SET_MISSION_NAME_FOR_UGC_MISSION` | jhash |
| UI | `_0xD2161E77` | `SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS` | jhash |
| UI | `_0x02F5F1D1` | `SET_MINIMAP_IN_PROLOGUE` | jhash |
| UI | `_0xD8D77733` | `SET_MINIMAP_HIDE_FOW` | jhash |
| UI | `_0xA4098ACC` | `GET_MINIMAP_FOW_DISCOVERY_RATIO` | jhash |
| UI | `_0x65B705F6` | `GET_MINIMAP_FOW_COORDINATE_IS_REVEALED` | jhash |
| UI | `_0xE010F081` | `SET_MINIMAP_FOW_REVEAL_COORDINATE` | jhash |
| UI | `_0x5133A750` | `SET_MINIMAP_GOLF_COURSE` | jhash |
| UI | `_0x20FD3E87` | `SET_MINIMAP_GOLF_COURSE_OFF` | jhash |
| UI | `_0x0308EDF6` | `SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT` | jhash |
| UI | `_0x7FB6FB2A` | `SET_HEALTH_HUD_DISPLAY_VALUES` | jhash |
| UI | `_0xF07D8CEF` | `SET_MAX_HEALTH_HUD_DISPLAY` | jhash |
| UI | `_0x827F14DE` | `SET_MAX_ARMOUR_HUD_DISPLAY` | jhash |
| UI | `_0x08EB83D2` | `SET_BIGMAP_ACTIVE` | jhash |
| UI | `_0xE8C8E535` | `IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME` | jhash |
| UI | `_0x52746FE1` | `HIDE_STREET_AND_CAR_NAMES_THIS_FRAME` | jhash |
| UI | `_0x5BBCC934` | `CLEAR_REMINDER_MESSAGE` | jhash |
| UI | `_GET_SCREEN_COORD_FROM_WORLD_COORD` | `GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION` | jhash |
| UI | `_0x10DE5150` | `OPEN_REPORTUGC_MENU` | jhash |
| UI | `_0x67649EE0` | `FORCE_CLOSE_REPORTUGC_MENU` | jhash |
| UI | `_0x9D2C94FA` | `IS_REPORTUGC_MENU_OPEN` | jhash |
| UI | `_0x45472FD5` | `IS_FLOATING_HELP_TEXT_ON_SCREEN` | jhash |
| UI | `_0x198F32D7` | `SET_FLOATING_HELP_TEXT_SCREEN_POSITION` | jhash |
| UI | `_0x93045157` | `SET_FLOATING_HELP_TEXT_WORLD_POSITION` | jhash |
| UI | `_0x18B012B7` | `SET_FLOATING_HELP_TEXT_TO_ENTITY` | jhash |
| UI | `_0x97852A82` | `SET_FLOATING_HELP_TEXT_STYLE` | jhash |
| UI | `_0xC969F2D0` | `CREATE_MP_GAMER_TAG_WITH_CREW_COLOR` | jhash |
| UI | `_0xEFD2564A` | `IS_MP_GAMER_TAG_MOVIE_ACTIVE` | jhash |
| UI | `_0xF5CD2AA4` | `CREATE_FAKE_MP_GAMER_TAG` | jhash |
| UI | `_0x3D081FE4` | `REMOVE_MP_GAMER_TAG` | jhash |
| UI | `_0x60118951` | `IS_MP_GAMER_TAG_ACTIVE` | jhash |
| UI | `ADD_TREVOR_RANDOM_MODIFIER` | `IS_MP_GAMER_TAG_FREE` | jhash |
| UI | `_0xD41DF479` | `SET_MP_GAMER_TAG_VISIBILITY` | jhash |
| UI | `_0x767DED29` | `SET_ALL_MP_GAMER_TAGS_VISIBILITY` | jhash |
| UI | `_0xB01A5434` | `SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH` | jhash |
| UI | `_0x7E3AA40A` | `SET_MP_GAMER_TAG_COLOUR` | jhash |
| UI | `_0x5777EC77` | `SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR` | jhash |
| UI | `_0xF4418611` | `SET_MP_GAMER_TAG_ALPHA` | jhash |
| UI | `_0x0EBB003F` | `SET_MP_GAMER_TAG_WANTED_LEVEL` | jhash |
| UI | `_0x627A559B` | `SET_MP_GAMER_TAG_NAME` | jhash |
| UI | `_0xF11414C4` | `IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS` | jhash |
| UI | `_0x939218AB` | `SET_MP_GAMER_TAG_BIG_TEXT` | jhash |
| UI | `_0xAB5B7C18` | `GET_CURRENT_WEBPAGE_ID` | jhash |
| UI | `_0xD217EE7E` | `GET_GLOBAL_ACTIONSCRIPT_FLAG` | jhash |
| UI | `_0x2DB9EAB5` | `SET_WARNING_MESSAGE_WITH_HEADER` | jhash |
| UI | `SET_DANCE_MAPPERS` | `SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS` | jhash |
| UI | `_0x94C834AD` | `IS_WARNING_MESSAGE_ACTIVE` | jhash |
| UI | `_0x2F9A309C` | `CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE` | jhash |
| UI | `_0xE4FD20D8` | `CUSTOM_MINIMAP_SET_ACTIVE` | jhash |
| UI | `_0x13E7A5A9` | `CUSTOM_MINIMAP_SET_BLIP_OBJECT` | jhash |
| UI | `_0x786CA0A2` | `CUSTOM_MINIMAP_CREATE_BLIP` | jhash |
| UI | `_0xCBEC9369` | `CUSTOM_MINIMAP_CLEAR_BLIPS` | jhash |
| UI | `_0x3F4AFB13` | `FORCE_SONAR_BLIPS_THIS_FRAME` | jhash |
| UI | `_0x2F28F0A6` | `DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS` | jhash |
| UI | `_0x801D0D86` | `DRAW_FRONTEND_BACKGROUND_THIS_FRAME` | jhash |
| UI | `_0x317775DF` | `DRAW_HUD_OVER_FADE_THIS_FRAME` | jhash |
| UI | `_0x33D6868F` | `GET_CURRENT_FRONTEND_MENU_VERSION` | jhash |
| UI | `_0x7F349900` | `SUPPRESS_FRONTEND_RENDERING_THIS_FRAME` | jhash |
| UI | `_0x630CD8EE` | `ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME` | jhash |
| UI | `_0xC85C4487` | `IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN` | jhash |
| UI | `_0x2DFD35C7` | `FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE` | jhash |
| UI | `_0x0A89336C` | `PAUSE_MENUCEPTION_GO_DEEPER` | jhash |
| UI | `_0xC84BE309` | `PAUSE_MENUCEPTION_THE_KICK` | jhash |
| UI | `_0x9FE8FD5E` | `PAUSE_MENU_ACTIVATE_CONTEXT` | jhash |
| UI | `OBJECT_DECAL_TOGGLE` | `PAUSE_MENU_DEACTIVATE_CONTEXT` | jhash |
| UI | `_0xC51BC42F` | `PAUSE_MENU_IS_CONTEXT_ACTIVE` | jhash |
| UI | `_0x016D7AF9` | `PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE` | jhash |
| UI | `ENABLE_DEATHBLOOD_SEETHROUGH` | `PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS` | jhash |
| UI | `_0x6C67131A` | `PAUSE_MENU_SET_BUSY_SPINNER` | jhash |
| UI | `_0x11D09737` | `PAUSE_MENU_SET_WARN_ON_TAB_CHANGE` | jhash |
| UI | `_0xD3BF3ABD` | `IS_FRONTEND_READY_FOR_CONTROL` | jhash |
| UI | `_0xC06B763D` | `TAKE_CONTROL_OF_FRONTEND` | jhash |
| UI | `_0xB9392CE7` | `RELEASE_CONTROL_OF_FRONTEND` | jhash |
| UI | `_0x92DAFA78` | `CODE_WANTS_SCRIPT_TO_TAKE_CONTROL` | jhash |
| UI | `_0x22CA9F2A` | `GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL` | jhash |
| UI | `_0xDA7951A2` | `IS_NAVIGATING_MENU_CONTENT` | jhash |
| UI | `_0x7D95AFFF` | `HAS_MENU_TRIGGER_EVENT_OCCURRED` | jhash |
| UI | `_0x96863460` | `HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED` | jhash |
| UI | `_0x8543AAC8` | `GET_MENU_TRIGGER_EVENT_DETAILS` | jhash |
| UI | `_0x6025AA2F` | `GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS` | jhash |
| UI | `_0x46794EB2` | `GET_PM_PLAYER_CREW_COLOR` | jhash |
| UI | `SET_USERIDS_UIHIDDEN` | `GET_MENU_PED_INT_STAT` | jhash |
| UI | `_0xD6CC4766` | `GET_MENU_PED_MASKED_INT_STAT` | jhash |
| UI | `_0x51972B04` | `GET_MENU_PED_FLOAT_STAT` | jhash |
| UI | `_0xD43BB56D` | `GET_MENU_PED_BOOL_STAT` | jhash |
| UI | `_0x127310EB` | `SET_PAUSE_MENU_PED_LIGHTING` | jhash |
| UI | `_0x8F45D327` | `SET_PAUSE_MENU_PED_SLEEP_STATE` | jhash |
| UI | `_0x19FCBBB2` | `OPEN_ONLINE_POLICIES_MENU` | jhash |
| UI | `_0x850690FF` | `ARE_ONLINE_POLICIES_UP_TO_DATE` | jhash |
| UI | `_0x9D4934F4` | `IS_ONLINE_POLICIES_MENU_ACTIVE` | jhash |
| UI | `_0x57218529` | `OPEN_SOCIAL_CLUB_MENU` | jhash |
| UI | `_0x5F86AA39` | `CLOSE_SOCIAL_CLUB_MENU` | jhash |
| UI | `_0x7AD67C95` | `SET_SOCIAL_CLUB_TOUR` | jhash |
| UI | `_0xD4DA14EF` | `IS_SOCIAL_CLUB_ACTIVE` | jhash |
| UI | `_0xFF06772A` | `FLAG_PLAYER_CONTEXT_IN_TOURNAMENT` | jhash |
| UI | `_0x96C4C4DD` | `SET_PED_HAS_AI_BLIP` | jhash |
| UI | `_0xD8E31B1A` | `SET_PED_AI_BLIP_GANG_ID` | jhash |
| UI | `HIDE_SPECIAL_ABILITY_LOCKON_OPERATION` | `SET_PED_AI_BLIP_HAS_CONE` | jhash |
| UI | `_0xFFDF46F0` | `SET_PED_AI_BLIP_FORCED_ON` | jhash |
| UI | `_0xF9DC2AF7` | `SET_PED_AI_BLIP_NOTICE_RANGE` | jhash |
| UI | `_0x06349065` | `GET_AI_PED_PED_BLIP_INDEX` | jhash |
| UI | `_0xCA52CF43` | `GET_AI_PED_VEHICLE_BLIP_INDEX` | jhash |
| GRAPHICS | `_0xB6DF3709` | `DRAW_DEBUG_CROSS` | jhash |
| GRAPHICS | `_0xCD4D9DD5` | `DRAW_BOX` | jhash |
| GRAPHICS | `_0xC44C2F44` | `SET_BACKFACECULLING` | jhash |
| GRAPHICS | `_0xBA9AD458` | `BEGIN_TAKE_MISSION_CREATOR_PHOTO` | jhash |
| GRAPHICS | `_0xADBBA287` | `GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO` | jhash |
| GRAPHICS | `_0x9E553002` | `FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO` | jhash |
| GRAPHICS | `_0x56C1E488` | `LOAD_MISSION_CREATOR_PHOTO` | jhash |
| GRAPHICS | `_0x226B08EA` | `GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO` | jhash |
| GRAPHICS | `_0x1F3CADB0` | `BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW` | jhash |
| GRAPHICS | `_0xA9DC8558` | `GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW` | jhash |
| GRAPHICS | `_0x88EAF398` | `FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW` | jhash |
| GRAPHICS | `_0x47B0C137` | `BEGIN_TAKE_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `MELEE_SEETHROUGH_SKIPPED` | `GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0x9CBA682A` | `FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0x3B15D33C` | `SAVE_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0xEC5D0317` | `GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0x25D569EB` | `BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO` | jhash |
| GRAPHICS | `_0xCFCDC518` | `GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO` | jhash |
| GRAPHICS | `_0x108F36CC` | `FREE_MEMORY_FOR_LOW_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0xE9F2B68F` | `DRAW_LOW_QUALITY_PHOTO_TO_PHONE` | jhash |
| GRAPHICS | `_0x239272BD` | `GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS` | jhash |
| GRAPHICS | `_0x21DBF0C9` | `GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS` | jhash |
| GRAPHICS | `_0x199FABF0` | `QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS` | jhash |
| GRAPHICS | `_0x596B900D` | `GET_STATUS_OF_SORTED_LIST_OPERATION` | jhash |
| GRAPHICS | `_0xC9EF81ED` | `CLEAR_STATUS_OF_SORTED_LIST_OPERATION` | jhash |
| GRAPHICS | `_0x9D84554C` | `DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO` | jhash |
| GRAPHICS | `_0x9C106AD9` | `LOAD_HIGH_QUALITY_PHOTO` | jhash |
| GRAPHICS | `_0x762E5C5F` | `GET_LOAD_HIGH_QUALITY_PHOTO_STATUS` | jhash |
| GRAPHICS | `_0x32BF9598` | `DRAW_SHADOWED_SPOT_LIGHT` | jhash |
| GRAPHICS | `_0x93628786` | `FADE_UP_PED_LIGHT` | jhash |
| GRAPHICS | `_0x80151CCF` | `SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE` | jhash |
| GRAPHICS | `_0xA5456DBB` | `SET_CHECKPOINT_RGBA2` | jhash |
| GRAPHICS | `_0x20EABD0F` | `SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM` | jhash |
| GRAPHICS | `_0x1E3A3126` | `SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT` | jhash |
| GRAPHICS | `_0x932FDB81` | `DONT_RENDER_IN_GAME_UI` | jhash |
| GRAPHICS | `_0x7E946E87` | `FORCE_RENDER_IN_GAME_UI` | jhash |
| GRAPHICS | `_0xF8FBCC25` | `SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU` | jhash |
| GRAPHICS | `_0xADF81D24` | `SET_SCRIPT_GFX_DRAW_ORDER` | jhash |
| GRAPHICS | `_SET_SCREEN_DRAW_POSITION` | `SET_SCRIPT_GFX_ALIGN` | jhash |
| GRAPHICS | `_0x3FE33BD6` | `RESET_SCRIPT_GFX_ALIGN` | jhash |
| GRAPHICS | `_0x76C641E4` | `SET_SCRIPT_GFX_ALIGN_PARAMS` | jhash |
| GRAPHICS | `_0x3F0D1A6F` | `GET_SAFE_ZONE_SIZE` | jhash |
| GRAPHICS | `_0x9D5D9B38` | `QUERY_MOVIE_MESH_SET_STATE` | jhash |
| GRAPHICS | `_0x62619061` | `GET_USINGNIGHTVISION` | jhash |
| GRAPHICS | `_0x455F1084` | `SET_DISTANCE_BLUR_STRENGTH_OVERRIDE` | jhash |
| GRAPHICS | `_0x0DCC0B8B` | `DISABLE_OCCLUSION_THIS_FRAME` | jhash |
| GRAPHICS | `_0xAA2A0EAF` | `SET_ARTIFICIAL_LIGHTS_STATE` | jhash |
| GRAPHICS | `_0x48F16186` | `CASCADE_SHADOWS_INIT_SESSION` | jhash |
| GRAPHICS | `_0x13D4ABC0` | `CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE` | jhash |
| GRAPHICS | `_0xD2157428` | `CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE` | jhash |
| GRAPHICS | `_0xC07C64C9` | `CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT` | jhash |
| GRAPHICS | `_0xFE903D0F` | `CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER` | jhash |
| GRAPHICS | `_0xDE10BA1F` | `CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE` | jhash |
| GRAPHICS | `_0x9F470BE3` | `CASCADE_SHADOWS_SET_AIRCRAFT_MODE` | jhash |
| GRAPHICS | `_0x4A124267` | `CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE` | jhash |
| GRAPHICS | `_0xB19B2764` | `CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE` | jhash |
| GRAPHICS | `_0x342FA2B4` | `CASCADE_SHADOWS_ENABLE_FREEZER` | jhash |
| GRAPHICS | `_0x5D3BFFC9` | `GOLF_TRAIL_SET_ENABLED` | jhash |
| GRAPHICS | `_0xD9653728` | `GOLF_TRAIL_SET_PATH` | jhash |
| GRAPHICS | `_0x72BA8A14` | `GOLF_TRAIL_SET_RADIUS` | jhash |
| GRAPHICS | `_0x804F444C` | `GOLF_TRAIL_SET_COLOUR` | jhash |
| GRAPHICS | `_0xBB1A1294` | `GOLF_TRAIL_SET_TESSELLATION` | jhash |
| GRAPHICS | `_0x1A1A72EF` | `GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE` | jhash |
| GRAPHICS | `_0x3BB12B75` | `GOLF_TRAIL_SET_FIXED_CONTROL_POINT` | jhash |
| GRAPHICS | `_0x4EA70FB4` | `GOLF_TRAIL_SET_SHADER_PARAMS` | jhash |
| GRAPHICS | `_0x0D830DC7` | `GOLF_TRAIL_SET_FACING` | jhash |
| GRAPHICS | `_0xA08B46AD` | `GOLF_TRAIL_GET_MAX_HEIGHT` | jhash |
| GRAPHICS | `_0xECD470F0` | `GOLF_TRAIL_GET_VISUAL_CONTROL_POINT` | jhash |
| GRAPHICS | `_0x1FE547F2` | `GET_USINGSEETHROUGH` | jhash |
| GRAPHICS | `_0x654F0287` | `SEETHROUGH_SET_HEATSCALE` | jhash |
| GRAPHICS | `_0xF6B837F0` | `SET_MOTIONBLUR_MAX_VEL_SCALER` | jhash |
| GRAPHICS | `_0xD906A3A9` | `GET_MOTIONBLUR_MAX_VEL_SCALER` | jhash |
| GRAPHICS | `_0xD34A6CBA` | `TOGGLE_PLAYER_DAMAGE_OVERLAY` | jhash |
| GRAPHICS | `_0xD8CC7221` | `RESET_ADAPTATION` | jhash |
| GRAPHICS | `_0x5604B890` | `TRIGGER_SCREENBLUR_FADE_IN` | jhash |
| GRAPHICS | `_0x46617502` | `TRIGGER_SCREENBLUR_FADE_OUT` | jhash |
| GRAPHICS | `_0xDB7AECDA` | `DISABLE_SCREENBLUR_FADE` | jhash |
| GRAPHICS | `IS_PARTICLE_FX_DELAYED_BLINK` | `GET_SCREENBLUR_FADE_CURRENT_TIME` | jhash |
| GRAPHICS | `_0x926B8734` | `IS_SCREENBLUR_FADE_RUNNING` | jhash |
| GRAPHICS | `_0x30ADE541` | `TOGGLE_PAUSED_RENDERPHASES` | jhash |
| GRAPHICS | `_0x0113EAE4` | `RESET_PAUSED_RENDERPHASES` | jhash |
| GRAPHICS | `_0xDCBA251B` | `GRAB_PAUSEMENU_OWNERSHIP` | jhash |
| GRAPHICS | `_0x513D444B` | `SET_HIDOF_OVERRIDE` | jhash |
| GRAPHICS | `_0xB2410EAB` | `PHONEPHOTOEDITOR_TOGGLE` | jhash |
| GRAPHICS | `_0x5AB94128` | `PHONEPHOTOEDITOR_IS_ACTIVE` | jhash |
| GRAPHICS | `_0xD63FCB3E` | `PHONEPHOTOEDITOR_SET_FRAME_TXD` | jhash |
| GRAPHICS | `_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2` | `START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD` | jhash |
| GRAPHICS | `_0x161780C1` | `START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE` | jhash |
| GRAPHICS | `_0x7B689E20` | `SET_PARTICLE_FX_NON_LOOPED_COLOUR` | jhash |
| GRAPHICS | `_0x110752B2` | `START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY` | jhash |
| GRAPHICS | `_0x233DE879` | `SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST` | jhash |
| GRAPHICS | `_0x6B125A02` | `SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE` | jhash |
| GRAPHICS | `_0xD938DEE0` | `SET_PARTICLE_FX_SHOOTOUT_BOAT` | jhash |
| GRAPHICS | `SET_CAMERA_ENDTIME` | `ENABLE_CLOWN_BLOOD_VFX` | jhash |
| GRAPHICS | `_0xCE8B8748` | `ENABLE_ALIEN_BLOOD_VFX` | jhash |
| GRAPHICS | `_0xC1AD5DDF` | `SET_PARTICLE_FX_BULLET_IMPACT_SCALE` | jhash |
| GRAPHICS | `_0x3968E915` | `SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE` | jhash |
| GRAPHICS | `_0x64BA4648` | `SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT` | jhash |
| GRAPHICS | `_0x8BE3D47F` | `SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE` | jhash |
| GRAPHICS | `_0xE3880F5A` | `SET_PARTICLE_FX_FOOT_LODRANGE_SCALE` | jhash |
| GRAPHICS | `_0x9C720B61` | `USE_PARTICLE_FX_ASSET` | jhash |
| GRAPHICS | `_0xC92719A7` | `SET_PARTICLE_FX_OVERRIDE` | jhash |
| GRAPHICS | `_0x9E8D8B72` | `RESET_PARTICLE_FX_OVERRIDE` | jhash |
| GRAPHICS | `_0xE3938B0B` | `START_PETROL_TRAIL_DECALS` | jhash |
| GRAPHICS | `_0xBAEC6ADD` | `ADD_PETROL_TRAIL_DECAL_INFO` | jhash |
| GRAPHICS | `SET_CAMERA_CAMERA_FORWARD` | `END_PETROL_TRAIL_DECALS` | jhash |
| GRAPHICS | `_0xEAB6417C` | `SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME` | jhash |
| GRAPHICS | `_0xC2703B88` | `SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME` | jhash |
| GRAPHICS | `_0xA706E84D` | `SET_DISABLE_DECAL_RENDERING_THIS_FRAME` | jhash |
| GRAPHICS | `_0x242C6A04` | `GET_IS_PETROL_DECAL_IN_RANGE` | jhash |
| GRAPHICS | `_0x335695CF` | `PATCH_DECAL_DIFFUSE_MAP` | jhash |
| GRAPHICS | `_0x7B786555` | `UNPATCH_DECAL_DIFFUSE_MAP` | jhash |
| GRAPHICS | `_0x12077738` | `ADD_VEHICLE_CREW_EMBLEM` | jhash |
| GRAPHICS | `_0x667046A8` | `REMOVE_VEHICLE_CREW_EMBLEM` | jhash |
| GRAPHICS | `_0x4F4D76E8` | `GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE` | jhash |
| GRAPHICS | `_0x6D58F73B` | `DOES_VEHICLE_HAVE_CREW_EMBLEM` | jhash |
| GRAPHICS | `_0x9BABCBA4` | `DISABLE_COMPOSITE_SHOTGUN_DECALS` | jhash |
| GRAPHICS | `_0xFDF6D8DA` | `DISABLE_SCUFF_DECALS` | jhash |
| GRAPHICS | `_0x2056A015` | `SET_DECAL_BULLET_IMPACT_RANGE_SCALE` | jhash |
| GRAPHICS | `_0x0F486429` | `OVERRIDE_INTERIOR_SMOKE_NAME` | jhash |
| GRAPHICS | `_0xD87CC710` | `OVERRIDE_INTERIOR_SMOKE_LEVEL` | jhash |
| GRAPHICS | `_0xE29EE145` | `OVERRIDE_INTERIOR_SMOKE_END` | jhash |
| GRAPHICS | `_0x60F72371` | `RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS` | jhash |
| GRAPHICS | `_0xC53576CA` | `USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED` | jhash |
| GRAPHICS | `_0x7158B1EA` | `USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED` | jhash |
| GRAPHICS | `_0x56345F6B` | `SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER` | jhash |
| GRAPHICS | `_0x03C44E4B` | `GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX` | jhash |
| GRAPHICS | `_0x85BA15A4` | `SET_CURRENT_PLAYER_TCMODIFIER` | jhash |
| GRAPHICS | `_0x9559BB38` | `SET_PLAYER_TCMODIFIER_TRANSITION` | jhash |
| GRAPHICS | `_0x554BA16E` | `SET_NEXT_PLAYER_TCMODIFIER` | jhash |
| GRAPHICS | `_0xE8F538B5` | `ADD_TCMODIFIER_OVERRIDE` | jhash |
| GRAPHICS | `_0x7CC8057D` | `REQUEST_SCALEFORM_MOVIE_INSTANCE` | jhash |
| GRAPHICS | `_0x1DFE8D8A` | `HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT` | jhash |
| GRAPHICS | `_0x18C9DE8D` | `SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME` | jhash |
| GRAPHICS | `_0x7B48E696` | `DRAW_SCALEFORM_MOVIE_FULLSCREEN` | jhash |
| GRAPHICS | `_0x9C59FC06` | `DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED` | jhash |
| GRAPHICS | `_0xC4F63A89` | `DRAW_SCALEFORM_MOVIE_3D` | jhash |
| GRAPHICS | `_0x899933C8` | `DRAW_SCALEFORM_MOVIE_3D_SOLID` | jhash |
| GRAPHICS | `_0x7AB77B57` | `CALL_SCALEFORM_MOVIE_METHOD` | jhash |
| GRAPHICS | `_0x557EDA1D` | `CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER` | jhash |
| GRAPHICS | `_0x91A7FCEB` | `CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING` | jhash |
| GRAPHICS | `_0x6EAF56DE` | `CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING` | jhash |
| GRAPHICS | `_0x5D66CE1E` | `BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD` | jhash |
| GRAPHICS | `_PUSH_SCALEFORM_MOVIE_FUNCTION` | `BEGIN_SCALEFORM_MOVIE_METHOD` | jhash |
| GRAPHICS | `_0xF6015178` | `BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND` | jhash |
| GRAPHICS | `_0x5E219B67` | `BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER` | jhash |
| GRAPHICS | `_POP_SCALEFORM_MOVIE_FUNCTION_VOID` | `END_SCALEFORM_MOVIE_METHOD` | jhash |
| GRAPHICS | `_0x2F38B526` | `END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE` | jhash |
| GRAPHICS | `_0x5CD7C3C0` | `IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY` | jhash |
| GRAPHICS | `_0x2CFB0E6D` | `GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT` | jhash |
| GRAPHICS | `SITTING_TV` | `GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING` | jhash |
| GRAPHICS | `_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT` | jhash |
| GRAPHICS | `_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT` | jhash |
| GRAPHICS | `_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL` | jhash |
| GRAPHICS | `_BEGIN_TEXT_COMPONENT` | `BEGIN_TEXT_COMMAND_SCALEFORM_STRING` | jhash |
| GRAPHICS | `_END_TEXT_COMPONENT` | `END_TEXT_COMMAND_SCALEFORM_STRING` | jhash |
| GRAPHICS | `_0x2E80DB52` | `END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING` | jhash |
| GRAPHICS | `_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING` | jhash |
| GRAPHICS | `_0xCCBF0334` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING` | jhash |
| GRAPHICS | `_0x91A081A1` | `DOES_LATEST_BRIEF_STRING_EXIST` | jhash |
| GRAPHICS | `_0x83A9811D` | `SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING` | jhash |
| GRAPHICS | `_0x7AF85862` | `REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE` | jhash |
| GRAPHICS | `_0x79B43255` | `HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED` | jhash |
| GRAPHICS | `_0x03D87600` | `REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE` | jhash |
| GRAPHICS | `_0xE9183D3A` | `PASS_KEYBOARD_INPUT_TO_SCALEFORM` | jhash |
| GRAPHICS | `_0xB262DE67` | `SET_TV_CHANNEL_PLAYLIST` | jhash |
| GRAPHICS | `_0x78C4DCBE` | `SET_TV_CHANNEL_PLAYLIST_AT_HOUR` | jhash |
| GRAPHICS | `_0xCBE7068F` | `CLEAR_TV_CHANNEL_PLAYLIST` | jhash |
| GRAPHICS | `_0x4D1EB0FB` | `IS_TVSHOW_CURRENTLY_PLAYING` | jhash |
| GRAPHICS | `_0x796DE696` | `ENABLE_MOVIE_KEYFRAME_WAIT` | jhash |
| GRAPHICS | `_0xD99EC000` | `SET_TV_PLAYER_WATCHING_THIS_FRAME` | jhash |
| GRAPHICS | `_0xE40A0F1A` | `UI3DSCENE_IS_AVAILABLE` | jhash |
| GRAPHICS | `_0x2E7D9B98` | `UI3DSCENE_PUSH_PRESET` | jhash |
| GRAPHICS | `_0x9A0E3BFE` | `UI3DSCENE_ASSIGN_PED_TO_SLOT` | jhash |
| GRAPHICS | `_0x431AA036` | `UI3DSCENE_CLEAR_PATCHED_DATA` | jhash |
| GRAPHICS | `_0x24A7A7F6` | `UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT` | jhash |
| GRAPHICS | `_0xA1CB6C94` | `TERRAINGRID_ACTIVATE` | jhash |
| GRAPHICS | `_0x3B637AA7` | `TERRAINGRID_SET_PARAMS` | jhash |
| GRAPHICS | `_0xDF552973` | `TERRAINGRID_SET_COLOURS` | jhash |
| GRAPHICS | `_0x1D980479` | `ANIMPOSTFX_PLAY` | jhash |
| GRAPHICS | `_0x06BB5CDA` | `ANIMPOSTFX_STOP` | jhash |
| GRAPHICS | `_0x089D5921` | `ANIMPOSTFX_IS_RUNNING` | jhash |
| GRAPHICS | `_0x4E6D875B` | `ANIMPOSTFX_STOP_ALL` | jhash |
| STATS | `_0x84BDD475` | `STAT_CLEAR_SLOT_FOR_RELOAD` | jhash |
| STATS | `_0xC62406A6` | `STAT_SET_OPEN_SAVETYPE_IN_JOB` | jhash |
| STATS | `_0xA3407CA3` | `STAT_SAVE_PENDING_OR_REQUESTED` | jhash |
| STATS | `_0x7A299C13` | `STAT_SLOT_IS_LOADED` | jhash |
| STATS | `_0x0BF0F4B2` | `STAT_CLOUD_SLOT_LOAD_FAILED` | jhash |
| STATS | `_0xCE6B62B5` | `STAT_CLOUD_SLOT_LOAD_FAILED_CODE` | jhash |
| STATS | `_0xCE7A2411` | `STAT_SET_BLOCK_SAVES` | jhash |
| STATS | `_0x22804C20` | `STAT_CLOUD_SLOT_SAVE_FAILED` | jhash |
| STATS | `_0x395D18B1` | `STAT_CLEAR_PENDING_SAVES` | jhash |
| STATS | `_0xED7000C8` | `STAT_LOAD_DIRTY_READ_DETECTED` | jhash |
| STATS | `_0x099FCC86` | `STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP` | jhash |
| STATS | `_0xC1224AA7` | `STAT_SET_GXT_LABEL` | jhash |
| STATS | `_0xA286F015` | `STAT_SET_CURRENT_POSIX_TIME` | jhash |
| STATS | `_0x1544B29F` | `STAT_GET_LICENSE_PLATE` | jhash |
| STATS | `_0x3507D253` | `STAT_SET_LICENSE_PLATE` | jhash |
| STATS | `_0x46F21343` | `STAT_COMMUNITY_START_SYNCH` | jhash |
| STATS | `_0x02F283CE` | `STAT_COMMUNITY_SYNCH_IS_PENDING` | jhash |
| STATS | `_0xC4110917` | `STAT_COMMUNITY_GET_HISTORY` | jhash |
| STATS | `_0x343B27E2` | `STAT_RESET_ALL_ONLINE_CHARACTER_STATS` | jhash |
| STATS | `_0xE3247582` | `STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS` | jhash |
| STATS | `_0xFD66A429` | `STAT_GET_NUMBER_OF_DAYS` | jhash |
| STATS | `_0x9B431236` | `STAT_GET_NUMBER_OF_HOURS` | jhash |
| STATS | `_0x347B4436` | `STAT_GET_NUMBER_OF_MINUTES` | jhash |
| STATS | `_0x2C1D6C31` | `STAT_GET_NUMBER_OF_SECONDS` | jhash |
| STATS | `_0x24DD4929` | `STAT_SET_PROFILE_SETTING_VALUE` | jhash |
| STATS | `_0xCA160BCC` | `PACKED_STAT_GET_INT_STAT_INDEX` | jhash |
| STATS | `_0x1F938864` | `GET_PACKED_INT_STAT_KEY` | jhash |
| STATS | `_0xFB93C5A2` | `GET_PACKED_TU_INT_STAT_KEY` | jhash |
| STATS | `_0x61ECC465` | `PLAYSTATS_BACKGROUND_SCRIPT_ACTION` | jhash |
| STATS | `_0x896CDF8D` | `PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE` | jhash |
| STATS | `_0x1A66945F` | `PLAYSTATS_ACTIVITY_DONE` | jhash |
| STATS | `_0xC960E161` | `PLAYSTATS_LEAVE_JOB_CHAIN` | jhash |
| STATS | `_0xAC2C7C63` | `PLAYSTATS_RANDOM_MISSION_DONE` | jhash |
| STATS | `_0x413539BC` | `PLAYSTATS_ROS_BET` | jhash |
| STATS | `_0x489E27E7` | `PLAYSTATS_CREATE_MATCH_HISTORY_ID_2` | jhash |
| STATS | `_0x6602CED6` | `PLAYSTATS_CRATE_DROP_MISSION_DONE` | jhash |
| STATS | `_0x759E0EC9` | `PLAYSTATS_HOLD_UP_MISSION_DONE` | jhash |
| STATS | `_0x62073DF7` | `PLAYSTATS_IMPORT_EXPORT_MISSION_DONE` | jhash |
| STATS | `_0x06CE3692` | `PLAYSTATS_RACE_TO_POINT_MISSION_DONE` | jhash |
| STATS | `_0x8D5C7B37` | `PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE` | jhash |
| STATS | `_0x37D152BB` | `PLAYSTATS_WEBSITE_VISITED` | jhash |
| STATS | `_0x79716890` | `PLAYSTATS_WEAPON_MODE_CHANGE` | jhash |
| STATS | `_0x04181752` | `PLAYSTATS_JOB_ACTIVITY_END` | jhash |
| STATS | `_0x31002201` | `PLAYSTATS_JOB_LTS_END` | jhash |
| STATS | `_0xDDD1F1F3` | `PLAYSTATS_JOB_LTS_ROUND_END` | jhash |
| STATS | `_0x66FEB701` | `PLAYSTATS_QUICKFIX_TOOL` | jhash |
| STATS | `_0x9E2B9522` | `PLAYSTATS_IDLE_KICK` | jhash |
| STATS | `_0x1789437B` | `LEADERBOARDS_READ_ANY_PENDING` | jhash |
| STATS | `_0x9BEC3401` | `LEADERBOARDS2_READ_RANK_PREDICTION` | jhash |
| STATS | `_0xC977D6E2` | `LEADERBOARDS2_READ_GET_ROW_DATA_START` | jhash |
| STATS | `_0xF2DB6A82` | `LEADERBOARDS2_READ_GET_ROW_DATA_END` | jhash |
| STATS | `_0x766A74FE` | `LEADERBOARDS2_READ_GET_ROW_DATA_INFO` | jhash |
| STATS | `_0x6B90E730` | `LEADERBOARDS2_READ_GET_ROW_DATA_INT` | jhash |
| STATS | `_0x509A286F` | `LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT` | jhash |
| STATS | `_0x7524E27B` | `LEADERBOARDS_WRITE_ADD_COLUMN` | jhash |
| STATS | `_0x1C5CCC3A` | `LEADERBOARDS_WRITE_ADD_COLUMN_LONG` | jhash |
| STATS | `_0x88AE9667` | `LEADERBOARDS_CLEAR_CACHE_DATA_ID` | jhash |
| STATS | `_0xCE7CB520` | `LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS` | jhash |
| STATS | `_0x4AC39C6C` | `PRESENCE_EVENT_UPDATESTAT_INT` | jhash |
| STATS | `_0x3E69E7C3` | `PRESENCE_EVENT_UPDATESTAT_FLOAT` | jhash |
| STATS | `_0x2FFD2FA5` | `PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING` | jhash |
| STATS | `_0x23D70C39` | `GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES` | jhash |
| STATS | `_0x0AD43306` | `SET_HAS_POSTED_ALL_VEHICLES_DRIVEN` | jhash |
| STATS | `_0xC7DE5C30` | `SET_PROFILE_SETTING_PROLOGUE_COMPLETE` | jhash |
| STATS | `_0xA3DAC790` | `SET_PROFILE_SETTING_CREATOR_RACES_DONE` | jhash |
| STATS | `_0x726FAE66` | `SET_PROFILE_SETTING_CREATOR_DM_DONE` | jhash |
| STATS | `_0xF03895A4` | `SET_PROFILE_SETTING_CREATOR_CTF_DONE` | jhash |
| STATS | `_0x4C39CF10` | `SET_JOB_ACTIVITY_ID_STARTED` | jhash |
| STATS | `_0x2180AE13` | `SET_FREEMODE_PROLOGUE_DONE` | jhash |
| STATS | `_0xEE292B91` | `STAT_NETWORK_INCREMENT_ON_SUICIDE` | jhash |
| STATS | `_0xA063CABD` | `STAT_SET_CHEAT_IS_ACTIVE` | jhash |
| STATS | `_0x62C19A3D` | `LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE` | jhash |
| STATS | `_0x3B4EF322` | `FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE` | jhash |
| STATS | `_0xE3F0D62D` | `STAT_GET_SAVE_MIGRATION_STATUS` | jhash |
| BRAIN | `_0x19B27825` | `REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE` | jhash |
| BRAIN | `_0xF3A3AB08` | `REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE` | jhash |
| BRAIN | `_0x949FE53E` | `REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE` | jhash |
| BRAIN | `_0x29CE8BAA` | `REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE` | jhash |
| MOBILE | `_0x4479B304` | `CELL_CAM_ACTIVATE_SELFIE_MODE` | jhash |
| MOBILE | `_0xC273BB4D` | `CELL_CAM_ACTIVATE_SHALLOW_DOF_MODE` | jhash |
| APP | `_0xD368BA15` | `APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT` | jhash |
| APP | `_0x784D550B` | `APP_GET_DELETED_FILE_STATUS` | jhash |
| TIME | `_0x57B8DA7C` | `ADVANCE_CLOCK_TIME_TO` | jhash |
| TIME | `_0x3B74095C` | `GET_MILLISECONDS_PER_GAME_MINUTE` | jhash |
| PATHFIND | `_0xEE4B1219` | `GET_VEHICLE_NODE_IS_GPS_ALLOWED` | jhash |
| PATHFIND | `_0x56737A3C` | `GET_VEHICLE_NODE_IS_SWITCHED_OFF` | jhash |
| PATHFIND | `_0xD6A3B458` | `SET_ALLOW_STREAM_PROLOGUE_NODES` | jhash |
| PATHFIND | `_0x86E80A17` | `ARE_NODES_LOADED_FOR_AREA` | jhash |
| PATHFIND | `_0x2CDA5012` | `REQUEST_PATH_NODES_IN_AREA_THIS_FRAME` | jhash |
| PATHFIND | `_0x3C5085E4` | `SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME` | jhash |
| PATHFIND | `_0xD0F51299` | `ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME` | jhash |
| PATHFIND | `_0x90DF7A4C` | `SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE` | jhash |
| PATHFIND | `_0x4B770634` | `GET_GPS_BLIP_ROUTE_LENGTH` | jhash |
| PATHFIND | `_0x286F82CC` | `GET_GPS_BLIP_ROUTE_FOUND` | jhash |
| PATHFIND | `_0xF6422F9A` | `GET_POSITION_BY_SIDE_OF_ROAD` | jhash |
| PATHFIND | `_0x4B67D7EE` | `DOES_NAVMESH_BLOCKING_OBJECT_EXIST` | jhash |
| PATHFIND | `_0x3FE8C5A0` | `GET_APPROX_HEIGHT_FOR_POINT` | jhash |
| PATHFIND | `_0x3ED21C90` | `GET_APPROX_HEIGHT_FOR_AREA` | jhash |
| PATHFIND | `_0xA07C5B7D` | `GET_APPROX_FLOOR_FOR_POINT` | jhash |
| PATHFIND | `_0x76751DD4` | `GET_APPROX_FLOOR_FOR_AREA` | jhash |
| CONTROLS | `_0xC49343BB` | `GET_CONTROL_UNBOUND_NORMAL` | jhash |
| CONTROLS | `_0xF2A65A4C` | `GET_DISABLED_CONTROL_UNBOUND_NORMAL` | jhash |
| CONTROLS | `_0x0E8EF929` | `GET_CONTROL_HOW_LONG_AGO` | jhash |
| CONTROLS | `_0xD2C80B2E` | `INIT_PC_SCRIPTED_CONTROLS` | jhash |
| CONTROLS | `_0xBBFC9050` | `SWITCH_PC_SCRIPTED_CONTROLS` | jhash |
| CONTROLS | `_0x42140FF9` | `SHUTDOWN_PC_SCRIPTED_CONTROLS` | jhash |
| CONTROLS | `_0x2CEDE6C5` | `ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT` | jhash |
| DATAFILE | `_0x621388FF` | `DATAFILE_WATCH_REQUEST_ID` | jhash |
| DATAFILE | `_0xB41064A4` | `DATAFILE_SELECT_ACTIVE_FILE` | jhash |
| DATAFILE | `_0x9DB63CFF` | `DATAFILE_DELETE_REQUESTED_FILE` | jhash |
| DATAFILE | `_0xF09157B0` | `UGC_CREATE_CONTENT` | jhash |
| DATAFILE | `_0xD96860FC` | `UGC_CREATE_MISSION` | jhash |
| DATAFILE | `_0x459F2683` | `UGC_UPDATE_CONTENT` | jhash |
| DATAFILE | `_0xDBB83E2B` | `UGC_UPDATE_MISSION` | jhash |
| DATAFILE | `_0xBB6321BD` | `UGC_SET_PLAYER_DATA` | jhash |
| DATAFILE | `_0xE8D56DA2` | `DATAFILE_SELECT_UGC_DATA` | jhash |
| DATAFILE | `_0xCB6A351E` | `DATAFILE_SELECT_UGC_STATS` | jhash |
| DATAFILE | `_0xA4D1B30E` | `DATAFILE_SELECT_UGC_PLAYER_DATA` | jhash |
| DATAFILE | `_0xB8515B2F` | `DATAFILE_SELECT_CREATOR_STATS` | jhash |
| DATAFILE | `_0x660C468E` | `DATAFILE_LOAD_OFFLINE_UGC` | jhash |
| DATAFILE | `_0x4E03F632` | `DATAFILE_STORE_MISSION_HEADER` | jhash |
| DATAFILE | `_0xF11F956F` | `DATAFILE_FLUSH_MISSION_HEADER` | jhash |
| DATAFILE | `PRELOAD_FIND` | `DATAFILE_GET_FILE_DICT` | jhash |
| DATAFILE | `_0x768CBB35` | `DATAFILE_START_SAVE_TO_CLOUD` | jhash |
| DATAFILE | `_0x0B4087F7` | `DATAFILE_UPDATE_SAVE_TO_CLOUD` | jhash |
| DATAFILE | `_0x5DCD0796` | `DATAFILE_IS_SAVE_PENDING` | jhash |
| DATAFILE | `_0x9B29D99B` | `DATADICT_SET_BOOL` | jhash |
| DATAFILE | `_0xEFCF554A` | `DATADICT_SET_INT` | jhash |
| DATAFILE | `_0xE972CACF` | `DATADICT_SET_FLOAT` | jhash |
| DATAFILE | `_0xD437615C` | `DATADICT_SET_STRING` | jhash |
| DATAFILE | `_0x75FC6C3C` | `DATADICT_SET_VECTOR` | jhash |
| DATAFILE | `_0x96A8E05F` | `DATADICT_CREATE_DICT` | jhash |
| DATAFILE | `_0x03939B8D` | `DATADICT_CREATE_ARRAY` | jhash |
| DATAFILE | `_0x8876C872` | `DATADICT_GET_BOOL` | jhash |
| DATAFILE | `_0xA6C68693` | `DATADICT_GET_INT` | jhash |
| DATAFILE | `_0xA92C1AF4` | `DATADICT_GET_FLOAT` | jhash |
| DATAFILE | `_0x942160EC` | `DATADICT_GET_STRING` | jhash |
| DATAFILE | `_0xE84A127A` | `DATADICT_GET_VECTOR` | jhash |
| DATAFILE | `_0xC9C13D8D` | `DATADICT_GET_DICT` | jhash |
| DATAFILE | `_0x1F2F7D00` | `DATADICT_GET_ARRAY` | jhash |
| DATAFILE | `_0x2678342A` | `DATADICT_GET_TYPE` | jhash |
| DATAFILE | `_0x08174B90` | `DATAARRAY_ADD_BOOL` | jhash |
| DATAFILE | `_0xF29C0B36` | `DATAARRAY_ADD_INT` | jhash |
| DATAFILE | `_0xE4302123` | `DATAARRAY_ADD_FLOAT` | jhash |
| DATAFILE | `_0xF3C01350` | `DATAARRAY_ADD_STRING` | jhash |
| DATAFILE | `_0x16F464B6` | `DATAARRAY_ADD_VECTOR` | jhash |
| DATAFILE | `_0xC174C71B` | `DATAARRAY_ADD_DICT` | jhash |
| DATAFILE | `_0xA2E5F921` | `DATAARRAY_GET_BOOL` | jhash |
| DATAFILE | `_0xBB120CFC` | `DATAARRAY_GET_INT` | jhash |
| DATAFILE | `FOCUS_USE_SPLINE` | `DATAARRAY_GET_FLOAT` | jhash |
| DATAFILE | `OVERIDE_TEXTURENAMES` | `DATAARRAY_GET_STRING` | jhash |
| DATAFILE | `_0x80E3DA55` | `DATAARRAY_GET_VECTOR` | jhash |
| DATAFILE | `_0xECE81278` | `DATAARRAY_GET_DICT` | jhash |
| DATAFILE | `_0xA8A21766` | `DATAARRAY_GET_COUNT` | jhash |
| DATAFILE | `_0xFA2402C8` | `DATAARRAY_GET_TYPE` | jhash |
| FIRE | `_0xCF358946` | `ADD_EXPLOSION_WITH_USER_VFX` | jhash |
| FIRE | `_0xAEC0D176` | `GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA` | jhash |
| DECISIONEVENT | `_0x57506EA6` | `BLOCK_DECISION_MAKER_EVENT` | jhash |
| DECISIONEVENT | `_0x62A3161D` | `UNBLOCK_DECISION_MAKER_EVENT` | jhash |
| DECISIONEVENT | `_0xA0CE89C8` | `REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS` | jhash |
| DECISIONEVENT | `_0x4CC674B5` | `SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME` | jhash |
| DECISIONEVENT | `_0xA0FDCB82` | `SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME` | jhash |
| DECISIONEVENT | `_0x80340396` | `SUPPRESS_AGITATION_EVENTS_NEXT_FRAME` | jhash |
| ZONE | `_0x8EC68304` | `GET_ZONE_FROM_NAME_ID` | jhash |
| ZONE | `_0x3F0A3680` | `OVERRIDE_POPSCHEDULE_VEHICLE_MODEL` | jhash |
| ZONE | `_0x7A72A24E` | `CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL` | jhash |
| ZONE | `_0xB5C5C99B` | `GET_HASH_OF_MAP_AREA_AT_COORDS` | jhash |
| ROPE | `_0x51523B8C` | `ROPE_DRAW_SHADOW_ENABLED` | jhash |
| ROPE | `_0xEAF291A0` | `ROPE_SET_UPDATE_PINVERTS` | jhash |
| ROPE | `_0x80DB77A7` | `ROPE_SET_UPDATE_ORDER` | jhash |
| ROPE | `_0xC67D5CF6` | `ROPE_SET_SMOOTH_REELIN` | jhash |
| ROPE | `_0x7A18BB9C` | `IS_ROPE_ATTACHED_AT_BOTH_ENDS` | jhash |
| ROPE | `_0x5187BED3` | `START_ROPE_WINDING` | jhash |
| ROPE | `_0x46826B53` | `STOP_ROPE_WINDING` | jhash |
| ROPE | `_0xFC0DB4C3` | `START_ROPE_UNWINDING_FRONT` | jhash |
| ROPE | `_0x2EEDB18F` | `STOP_ROPE_UNWINDING_FRONT` | jhash |
| ROPE | `_0x43E92628` | `ROPE_CONVERT_TO_SIMPLE` | jhash |
| ROPE | `_0x5FDC1047` | `ROPE_ARE_TEXTURES_LOADED` | jhash |
| ROPE | `_0x106BA127` | `ROPE_ATTACH_VIRTUAL_BOUND_GEOM` | jhash |
| ROPE | `_0x7C6F7668` | `ROPE_CHANGE_SCRIPT_OWNER` | jhash |
| ROPE | `_0x686672DD` | `ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER` | jhash |
| ROPE | `_0xFD309DC8` | `ROPE_GET_DISTANCE_BETWEEN_ENDS` | jhash |
| ROPE | `_0xA2A5C9FE` | `APPLY_IMPULSE_TO_CLOTH` | jhash |
| ROPE | `_0x59910AB2` | `SET_CGOFFSET` | jhash |
| ROPE | `_0x49A11F0D` | `GET_CGOFFSET` | jhash |
| ROPE | `_0xA5B55421` | `SET_CG_AT_BOUNDCENTER` | jhash |
| ROPE | `_0x97269DC8` | `SET_DISABLE_FRAG_DAMAGE` | jhash |
| WATER | `_0xAA4AE00C` | `TEST_PROBE_AGAINST_WATER` | jhash |
| WATER | `_0x4A962D55` | `TEST_PROBE_AGAINST_ALL_WATER` | jhash |
| WATER | `_0x4C71D143` | `TEST_VERTICAL_PROBE_AGAINST_ALL_WATER` | jhash |
| WORLDPROBE | `_0xEFAF4BA6` | `START_SHAPE_TEST_LOS_PROBE` | jhash |
| WORLDPROBE | `_0x8251485D` | `START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE` | jhash |
| WORLDPROBE | `_0xCEEAD94B` | `START_SHAPE_TEST_BOUNDING_BOX` | jhash |
| WORLDPROBE | `_0x249BC876` | `START_SHAPE_TEST_BOX` | jhash |
| WORLDPROBE | `_0x13BC46C0` | `START_SHAPE_TEST_BOUND` | jhash |
| WORLDPROBE | `_0x591EA833` | `START_SHAPE_TEST_CAPSULE` | jhash |
| WORLDPROBE | `_0x4559460A` | `START_SHAPE_TEST_SWEPT_SPHERE` | jhash |
| WORLDPROBE | `_0xF3C2875A` | `GET_SHAPE_TEST_RESULT` | jhash |
| WORLDPROBE | `_0x4301E10C` | `GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL` | jhash |
| WORLDPROBE | `_0xEC2AAF06` | `RELEASE_SCRIPT_GUID_FROM_ENTITY` | jhash |
| NETWORK | `_0x99F58A07` | `NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA` | jhash |
| NETWORK | `_0x3FB40673` | `NETWORK_HAS_VALID_ROS_CREDENTIALS` | jhash |
| NETWORK | `_0x66EC713F` | `NETWORK_HAS_SOCIAL_CLUB_ACCOUNT` | jhash |
| NETWORK | `_0x358D1D77` | `NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT` | jhash |
| NETWORK | `_0x1F88819D` | `NETWORK_HAVE_USER_CONTENT_PRIVILEGES` | jhash |
| NETWORK | `_0x2D817A5E` | `NETWORK_HAVE_COMMUNICATION_PRIVILEGES` | jhash |
| NETWORK | `_0xBB54AA3D` | `NETWORK_CHECK_USER_CONTENT_PRIVILEGES` | jhash |
| NETWORK | `_0xA79E5B05` | `NETWORK_CHECK_COMMUNICATION_PRIVILEGES` | jhash |
| NETWORK | `_0xEB864288` | `NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV` | jhash |
| NETWORK | `_0xAB07CBBE` | `NETWORK_GET_AGE_GROUP` | jhash |
| NETWORK | `_0x60E1FEDF` | `NETWORK_CAN_BAIL` | jhash |
| NETWORK | `_0x96E28FE2` | `NETWORK_ON_RETURN_TO_SINGLE_PLAYER` | jhash |
| NETWORK | `_0xA520B982` | `NETWORK_CAN_ACCESS_MULTIPLAYER` | jhash |
| NETWORK | `_0x05518C0F` | `NETWORK_IS_MULTIPLAYER_DISABLED` | jhash |
| NETWORK | `_0x8AC9EA19` | `NETWORK_SESSION_HOST_CLOSED` | jhash |
| NETWORK | `_0x56E75FE4` | `NETWORK_SESSION_IS_CLOSED_FRIENDS` | jhash |
| NETWORK | `_0xA95299B9` | `NETWORK_SESSION_IS_CLOSED_CREW` | jhash |
| NETWORK | `_0x3D2C1916` | `NETWORK_SESSION_IS_SOLO` | jhash |
| NETWORK | `_0xDB67785D` | `NETWORK_SESSION_IS_PRIVATE` | jhash |
| NETWORK | `_0x8A559D26` | `NETWORK_SESSION_GET_KICK_VOTE` | jhash |
| NETWORK | `_0x3C3E2AB6` | `NETWORK_SESSION_SET_MATCHMAKING_GROUP` | jhash |
| NETWORK | `_0x5F29A7E0` | `NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX` | jhash |
| NETWORK | `_0x36EAD960` | `NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE` | jhash |
| NETWORK | `_0x5BE529F7` | `NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP` | jhash |
| NETWORK | `_0x454C7B67` | `NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT` | jhash |
| NETWORK | `_0xE5961511` | `NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION` | jhash |
| NETWORK | `_0xAE396263` | `NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION` | jhash |
| NETWORK | `_0x913FD7D6` | `NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION` | jhash |
| NETWORK | `_0xB3D9A67F` | `NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID` | jhash |
| NETWORK | `_0x6CC062FC` | `NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE` | jhash |
| NETWORK | `_0x57F9BC83` | `NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN` | jhash |
| NETWORK | `_0xF3768F90` | `NETWORK_SESSION_VALIDATE_JOIN` | jhash |
| NETWORK | `_0x0EC62629` | `NETWORK_ADD_FOLLOWERS` | jhash |
| NETWORK | `_0x5E557307` | `NETWORK_CLEAR_FOLLOWERS` | jhash |
| NETWORK | `_0x74E8C53E` | `NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK` | jhash |
| NETWORK | `_0x959E43A3` | `NETWORK_SESSION_SET_GAMEMODE` | jhash |
| NETWORK | `_0x7771AB83` | `NETWORK_FIND_GAMERS_IN_CREW` | jhash |
| NETWORK | `_0xA13045D4` | `NETWORK_FIND_MATCHED_GAMERS` | jhash |
| NETWORK | `_0xBEDC4503` | `NETWORK_DID_FIND_GAMERS_SUCCEED` | jhash |
| NETWORK | `_0x42BD0780` | `NETWORK_QUEUE_GAMER_FOR_STATUS` | jhash |
| NETWORK | `_0xBEB98840` | `NETWORK_GET_GAMER_STATUS_FROM_QUEUE` | jhash |
| NETWORK | `_0x08029970` | `NETWORK_IS_GETTING_GAMER_STATUS` | jhash |
| NETWORK | `_0xC871E745` | `NETWORK_DID_GET_GAMER_STATUS_SUCCEED` | jhash |
| NETWORK | `_0xB5ABC4B4` | `NETWORK_GET_GAMER_STATUS_RESULT` | jhash |
| NETWORK | `_0x3F7EDBBD` | `NETWORK_CLEAR_GET_GAMER_STATUS` | jhash |
| NETWORK | `NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED` | `NETWORK_SESSION_JOIN_INVITE` | jhash |
| NETWORK | `_0x3FD49D3B` | `NETWORK_SESSION_FORCE_CANCEL_INVITE` | jhash |
| NETWORK | `_0xFBBAC350` | `NETWORK_HAS_CONFIRMED_INVITE` | jhash |
| NETWORK | `_0x0907A6BF` | `NETWORK_REQUEST_INVITE_CONFIRMED_EVENT` | jhash |
| NETWORK | `_0x6A0BEA60` | `NETWORK_SESSION_WAS_INVITED` | jhash |
| NETWORK | `_0x3EA9D44C` | `NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE` | jhash |
| NETWORK | `_0x32B7A076` | `NETWORK_STORE_INVITE_THROUGH_RESTART` | jhash |
| NETWORK | `_0x0FCE995D` | `NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH` | jhash |
| NETWORK | `_0xA639DCA2` | `NETWORK_SET_SCRIPT_READY_FOR_EVENTS` | jhash |
| NETWORK | `_0x70ED476A` | `NETWORK_IS_OFFLINE_INVITE_PENDING` | jhash |
| NETWORK | `_0x50507BED` | `NETWORK_CLEAR_OFFLINE_INVITE_PENDING` | jhash |
| NETWORK | `_0x7017257D` | `NETWORK_SESSION_MARK_VISIBLE` | jhash |
| NETWORK | `_0x4977AC28` | `NETWORK_SESSION_IS_VISIBLE` | jhash |
| NETWORK | `_0xE6EEF8AF` | `NETWORK_SESSION_BLOCK_JOIN_REQUESTS` | jhash |
| NETWORK | `_0x6BB93227` | `NETWORK_SESSION_CHANGE_SLOTS` | jhash |
| NETWORK | `_0xE642F2FD` | `NETWORK_SESSION_GET_PRIVATE_SLOTS` | jhash |
| NETWORK | `_0x9DFD89E6` | `NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER` | jhash |
| NETWORK | `NETWORK_SET_KEEP_FOCUSPOINT` | `NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST` | jhash |
| NETWORK | `_0x6EFC2FD0` | `NETWORK_SESSION_VOICE_SET_TIMEOUT` | jhash |
| NETWORK | `_0x60AA4AA1` | `NETWORK_SESSION_IS_IN_VOICE_SESSION` | jhash |
| NETWORK | `_0x132CA01E` | `NETWORK_SESSION_IS_VOICE_SESSION_BUSY` | jhash |
| NETWORK | `_0x2FF65C0B` | `NETWORK_DO_TRANSITION_QUICKMATCH` | jhash |
| NETWORK | `_0x47D61C99` | `NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC` | jhash |
| NETWORK | `_0x5CE60A11` | `NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP` | jhash |
| NETWORK | `_0x0D7E5CF9` | `NETWORK_JOIN_GROUP_ACTIVITY` | jhash |
| NETWORK | `_0x36A5F2DA` | `NETWORK_RETAIN_ACTIVITY_GROUP` | jhash |
| NETWORK | `_0x95FFACF8` | `NETWORK_IS_TRANSITION_CLOSED_FRIENDS` | jhash |
| NETWORK | `_0xB97A966B` | `NETWORK_IS_TRANSITION_CLOSED_CREW` | jhash |
| NETWORK | `_0x7EF353E1` | `NETWORK_MARK_AS_PREFERRED_ACTIVITY` | jhash |
| NETWORK | `_0xF60986FC` | `NETWORK_MARK_AS_WAITING_ASYNC` | jhash |
| NETWORK | `_0xB59D74CA` | `NETWORK_BAIL_TRANSITION` | jhash |
| NETWORK | `_0xCEE79711` | `NETWORK_APPLY_TRANSITION_PARAMETER` | jhash |
| NETWORK | `_0xE0C28DB5` | `NETWORK_APPLY_TRANSITION_PARAMETER_STRING` | jhash |
| NETWORK | `_0x8262C70E` | `NETWORK_IS_TRANSITION_MATCHMAKING` | jhash |
| NETWORK | `_0xC71E607B` | `NETWORK_OPEN_TRANSITION_MATCHMAKING` | jhash |
| NETWORK | `_0x82D32D07` | `NETWORK_CLOSE_TRANSITION_MATCHMAKING` | jhash |
| NETWORK | `_0xC901AA9F` | `NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING` | jhash |
| NETWORK | `_0xCCA9C022` | `NETWORK_SET_TRANSITION_ACTIVITY_ID` | jhash |
| NETWORK | `_0x1E5F6AEF` | `NETWORK_CHANGE_TRANSITION_SLOTS` | jhash |
| NETWORK | `_0x0532DDD2` | `NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS` | jhash |
| NETWORK | `_0xCDEBCCE7` | `NETWORK_ARE_TRANSITION_DETAILS_VALID` | jhash |
| NETWORK | `_0x4F41DF6B` | `NETWORK_HAS_INVITED_GAMER_TO_TRANSITION` | jhash |
| NETWORK | `_0x18F03AFD` | `NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED` | jhash |
| NETWORK | `_0x8B99B72B` | `NETWORK_SEND_INVITE_VIA_PRESENCE` | jhash |
| NETWORK | `_0x877C0E1C` | `NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE` | jhash |
| NETWORK | `_0x5E832444` | `NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID` | jhash |
| NETWORK | `_0x3FDA00F3` | `NETWORK_GET_NUM_PRESENCE_INVITES` | jhash |
| NETWORK | `_0x93C665FA` | `NETWORK_REMOVE_PRESENCE_INVITE` | jhash |
| NETWORK | `_0xD50DF46C` | `NETWORK_GET_PRESENCE_INVITE_ID` | jhash |
| NETWORK | `_0x19EC65D9` | `NETWORK_GET_PRESENCE_INVITE_INVITER` | jhash |
| NETWORK | `_0xC5E0C989` | `NETWORK_GET_PRESENCE_INVITE_SESSION_ID` | jhash |
| NETWORK | `_0xA4302183` | `NETWORK_GET_PRESENCE_INVITE_CONTENT_ID` | jhash |
| NETWORK | `_0x51B2D848` | `NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH` | jhash |
| NETWORK | `_0x4677C656` | `NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT` | jhash |
| NETWORK | `_0xF5E3401C` | `NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN` | jhash |
| NETWORK | `_0x7D593B4C` | `NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT` | jhash |
| NETWORK | `_0xE96CFE7D` | `NETWORK_HAS_FOLLOW_INVITE` | jhash |
| NETWORK | `_0xAB969F00` | `NETWORK_ACTION_FOLLOW_INVITE` | jhash |
| NETWORK | `_0x3242F952` | `NETWORK_CLEAR_FOLLOW_INVITE` | jhash |
| NETWORK | `_0x9773F36A` | `NETWORK_REMOVE_AND_CANCEL_ALL_INVITES` | jhash |
| NETWORK | `_0xF7134E73` | `NETWORK_REMOVE_ALL_TRANSITION_INVITE` | jhash |
| NETWORK | `_0xC47352E7` | `NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES` | jhash |
| NETWORK | `_0xEC651BC0` | `NETWORK_HAS_INVITED_GAMER` | jhash |
| NETWORK | `_0x0808D4CC` | `NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU` | jhash |
| NETWORK | `_0x11378777` | `NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU` | jhash |
| NETWORK | `USING_NETWORK_WEAPONTYPE` | `REFRESH_PLAYER_LIST_STATS` | jhash |
| NETWORK | `_0xA812B6CB` | `NETWORK_IS_IN_PLATFORM_PARTY` | jhash |
| NETWORK | `_0xF30E5814` | `NETWORK_GET_PLATFORM_PARTY_MEMBERS` | jhash |
| NETWORK | `_0xC6609191` | `NETWORK_IS_IN_PLATFORM_PARTY_CHAT` | jhash |
| NETWORK | `_0x51367B34` | `NETWORK_IS_CHATTING_IN_PLATFORM_PARTY` | jhash |
| NETWORK | `_0x9156EFC0` | `NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN` | jhash |
| NETWORK | `_0x8FA6EE0E` | `NETWORK_IS_QUEUING_FOR_SESSION_JOIN` | jhash |
| NETWORK | `_0x7F70C15A` | `NETWORK_SEND_QUEUED_JOIN_REQUEST` | jhash |
| NETWORK | `_0x41702C8A` | `NETWORK_SEED_RANDOM_NUMBER_GENERATOR` | jhash |
| NETWORK | `_0x208DD848` | `NETWORK_GET_RANDOM_INT` | jhash |
| NETWORK | `_0xF9B6426D` | `NETWORK_GET_RANDOM_INT_RANGED` | jhash |
| NETWORK | `_0x1720ABA6` | `NETWORK_PLAYER_GET_CHEATER_REASON` | jhash |
| NETWORK | `_0xA19708E3` | `NETWORK_PLAYER_IS_BADSPORT` | jhash |
| NETWORK | `_0x4C2C6B6A` | `BAD_SPORT_PLAYER_LEFT_DETECTED` | jhash |
| NETWORK | `_0x4818ACD0` | `NETWORK_APPLY_PED_SCAR_DATA` | jhash |
| NETWORK | `_0xCCD8C02D` | `NETWORK_GET_MAX_NUM_PARTICIPANTS` | jhash |
| NETWORK | `_0x3E25A3C5` | `NETWORK_GET_NUM_PARTICIPANTS` | jhash |
| NETWORK | `_0xA71A1D2A` | `NETWORK_FINISH_BROADCASTING_DATA` | jhash |
| NETWORK | `_0x0B739F53` | `NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA` | jhash |
| NETWORK | `_0x40DBF464` | `NETWORK_GET_PLAYER_INDEX_FROM_PED` | jhash |
| NETWORK | `_0xF4F13B06` | `NETWORK_GET_TOTAL_NUM_PLAYERS` | jhash |
| NETWORK | `NET_BUT` | `NETWORK_IS_HOST_OF_THIS_SCRIPT` | jhash |
| NETWORK | `_0x8F7D9F46` | `NETWORK_GET_NUM_SCRIPT_PARTICIPANTS` | jhash |
| NETWORK | `_0xDB8B5D71` | `NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT` | jhash |
| NETWORK | `_0xCEA55F4C` | `NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT` | jhash |
| NETWORK | `_0x8DCFE77D` | `NETWORK_PREVENT_SCRIPT_HOST_MIGRATION` | jhash |
| NETWORK | `_0x331D9A27` | `NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT` | jhash |
| NETWORK | `_0x28A45454` | `NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY` | jhash |
| NETWORK | `_0x8D27280E` | `NETWORK_DISABLE_INVINCIBLE_FLASHING` | jhash |
| NETWORK | `_0xB72F086D` | `NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT` | jhash |
| NETWORK | `_0xEDA68956` | `NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD` | jhash |
| NETWORK | `_0xD7F934F4` | `NETWORK_GET_ENTITY_IS_NETWORKED` | jhash |
| NETWORK | `_0x31A630A4` | `NETWORK_REGISTER_ENTITY_AS_NETWORKED` | jhash |
| NETWORK | `_0x5C645F64` | `NETWORK_UNREGISTER_NETWORKED_ENTITY` | jhash |
| NETWORK | `_0x4EC0D983` | `NETWORK_PLAYER_GET_USERID` | jhash |
| NETWORK | `_0xD265B049` | `NETWORK_PLAYER_INDEX_IS_CHEATER` | jhash |
| NETWORK | `CLEAR_PLAYER_BAILED_FROM_PLAYERICLE` | `NETWORK_IS_FRIEND_INDEX_ONLINE` | jhash |
| NETWORK | `GET_OBJ_ENTITY` | `NETWORK_GET_PLAYER_OWNS_WAYPOINT` | jhash |
| NETWORK | `_0x5C0AB2A9` | `NETWORK_SET_SCRIPT_AUTOMUTED` | jhash |
| NETWORK | `_0x9A176B6E` | `NETWORK_HAS_AUTOMUTE_OVERRIDE` | jhash |
| NETWORK | `_0x5C05B7E1` | `NETWORK_SET_LOOK_AT_TALKERS` | jhash |
| NETWORK | `_0x7685B333` | `NETWORK_AM_I_MUTED_BY_GAMER` | jhash |
| NETWORK | `_0x3FDCC8D7` | `NETWORK_IS_GAMER_BLOCKED_BY_ME` | jhash |
| NETWORK | `_0xD19B312C` | `NETWORK_AM_I_BLOCKED_BY_GAMER` | jhash |
| NETWORK | `_0x1A3EA6CD` | `NETWORK_REMAIN_IN_GAME_CHAT` | jhash |
| NETWORK | `_0xCAB21090` | `NETWORK_OVERRIDE_TRANSITION_CHAT` | jhash |
| NETWORK | `_0xC8CC9E75` | `NETWORK_OVERRIDE_TEAM_RESTRICTIONS` | jhash |
| NETWORK | `_0xC9DDA85B` | `NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT` | jhash |
| NETWORK | `_0xD33AFF79` | `NETWORK_SET_NO_SPECTATOR_CHAT` | jhash |
| NETWORK | `_0x4FFEFE43` | `NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM` | jhash |
| NETWORK | `_0x74EE2D8B` | `NETWORK_OVERRIDE_CHAT_RESTRICTIONS` | jhash |
| NETWORK | `_0x2F98B405` | `NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL` | jhash |
| NETWORK | `_0x95F1C60D` | `NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS` | jhash |
| NETWORK | `_0x6C344AE3` | `NETWORK_OVERRIDE_SEND_RESTRICTIONS` | jhash |
| NETWORK | `_0x1BCD3DDF` | `NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL` | jhash |
| NETWORK | `_0x9ECF722A` | `NETWORK_CLEAR_VOICE_CHANNEL` | jhash |
| NETWORK | `IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT` | `NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE` | jhash |
| NETWORK | `_0x7F9B9052` | `NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE` | jhash |
| NETWORK | `_0x7BBEA8CF` | `NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION` | jhash |
| NETWORK | `_0xE797A4B6` | `NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION` | jhash |
| NETWORK | `_0x92268BB5` | `NETWORK_GET_MUTE_COUNT_FOR_PLAYER` | jhash |
| NETWORK | `_0x017E6777` | `NETWORK_SET_RICH_PRESENCE_STRING` | jhash |
| NETWORK | `_0xE1F86C6A` | `NETWORK_GET_TIMEOUT_TIME` | jhash |
| NETWORK | `_NETWORK_RESPAWN_COORDS` | `NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP` | jhash |
| NETWORK | `_NETWORK_RESPAWN_PLAYER` | `NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE` | jhash |
| NETWORK | `_0xCEAE5AFC` | `REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY` | jhash |
| NETWORK | `_0xF5F4BD95` | `NETWORK_CLAN_SERVICE_IS_VALID` | jhash |
| NETWORK | `_0x54E79E9C` | `NETWORK_CLAN_IS_ROCKSTAR_CLAN` | jhash |
| NETWORK | `_0xF633805A` | `NETWORK_CLAN_GET_UI_FORMATTED_TAG` | jhash |
| NETWORK | `_0x807B3450` | `NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT` | jhash |
| NETWORK | `_0x3369DD1F` | `NETWORK_CLAN_GET_MEMBERSHIP_DESC` | jhash |
| NETWORK | `_0x83ED8E08` | `NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING` | jhash |
| NETWORK | `_0x40202867` | `NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE` | jhash |
| NETWORK | `_0xBDA90BAC` | `NETWORK_CLAN_CREWINFO_GET_STRING_VALUE` | jhash |
| NETWORK | `_0x8E952B12` | `NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE` | jhash |
| NETWORK | `_0x966C90FD` | `NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED` | jhash |
| NETWORK | `_0xBA672146` | `NETWORK_CLAN_GET_EMBLEM_TXD_NAME` | jhash |
| NETWORK | `_0x7963FA4D` | `NETWORK_CLAN_REQUEST_EMBLEM` | jhash |
| NETWORK | `_0x88B13CDC` | `NETWORK_CLAN_IS_EMBLEM_READY` | jhash |
| NETWORK | `_0xD6E3D5EA` | `NETWORK_CLAN_RELEASE_EMBLEM` | jhash |
| NETWORK | `_0xE22445DA` | `NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR` | jhash |
| NETWORK | `_0x455DDF5C` | `NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL` | jhash |
| NETWORK | `_0x89DB0EC7` | `NETWORK_GET_PRIMARY_CLAN_DATA_START` | jhash |
| NETWORK | `_0xA4EF02F3` | `NETWORK_GET_PRIMARY_CLAN_DATA_PENDING` | jhash |
| NETWORK | `_0x068A054E` | `NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS` | jhash |
| NETWORK | `_0x9B8631EB` | `NETWORK_GET_PRIMARY_CLAN_DATA_NEW` | jhash |
| NETWORK | `_0x4D15FDB1` | `SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER` | jhash |
| NETWORK | `_0x09CBC4B0` | `NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS` | jhash |
| NETWORK | `_0x00AE4E17` | `SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL` | jhash |
| NETWORK | `_0xEA5176C0` | `IS_NETWORK_ID_OWNED_BY_PARTICIPANT` | jhash |
| NETWORK | `_0x603FA104` | `GET_NUM_CREATED_MISSION_OBJECTS` | jhash |
| NETWORK | `_0xD8FEC4F8` | `GET_NUM_CREATED_MISSION_PEDS` | jhash |
| NETWORK | `_0x20527695` | `GET_NUM_CREATED_MISSION_VEHICLES` | jhash |
| NETWORK | `_0x8687E285` | `GET_MAX_NUM_NETWORK_OBJECTS` | jhash |
| NETWORK | `_0x744AC008` | `GET_MAX_NUM_NETWORK_PEDS` | jhash |
| NETWORK | `_0xC3A12135` | `GET_MAX_NUM_NETWORK_VEHICLES` | jhash |
| NETWORK | `_0x6A036061` | `GET_MAX_NUM_NETWORK_PICKUPS` | jhash |
| NETWORK | `_0x98AA48E5` | `GET_NETWORK_TIME_ACCURATE` | jhash |
| NETWORK | `_0x4538C4A2` | `HAS_NETWORK_TIME_STARTED` | jhash |
| NETWORK | `_0x50EF8FC6` | `IS_TIME_LESS_THAN` | jhash |
| NETWORK | `_0xBBB6DF61` | `IS_TIME_MORE_THAN` | jhash |
| NETWORK | `_0x8B4D1C06` | `IS_TIME_EQUAL_TO` | jhash |
| NETWORK | `_0x8218944E` | `GET_TIME_AS_STRING` | jhash |
| NETWORK | `_0xF2FDF2E0` | `GET_CLOUD_TIME_AS_INT` | jhash |
| NETWORK | `_0xBB7CCE49` | `CONVERT_POSIX_TIME` | jhash |
| NETWORK | `_0x54058F5F` | `NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED` | jhash |
| NETWORK | `_0xA7E36020` | `NETWORK_SET_IN_FREE_CAM_MODE` | jhash |
| NETWORK | `_0x64235620` | `NETWORK_SET_ANTAGONISTIC_TO_PLAYER` | jhash |
| NETWORK | `_0xEA235081` | `SET_NETWORK_VEHICLE_AS_GHOST` | jhash |
| NETWORK | `_0xBFFE8B5C` | `NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA` | jhash |
| NETWORK | `_0x16AED87B` | `NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID` | jhash |
| NETWORK | `_0x0679CE71` | `NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS` | jhash |
| NETWORK | `_0xC62E77B3` | `NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER` | jhash |
| NETWORK | `_0x74D6B13C` | `NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER` | jhash |
| NETWORK | `_0x90700C7D` | `NETWORK_QUERY_RESPAWN_RESULTS` | jhash |
| NETWORK | `_0x44BFB619` | `NETWORK_CANCEL_RESPAWN_SEARCH` | jhash |
| NETWORK | `_0x03287FD2` | `NETWORK_GET_RESPAWN_RESULT_FLAGS` | jhash |
| NETWORK | `_0x408A9436` | `NETWORK_START_SOLO_TUTORIAL_SESSION` | jhash |
| NETWORK | `_0xFFB2ADA1` | `NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION` | jhash |
| NETWORK | `_0x755A2B3E` | `NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION` | jhash |
| NETWORK | `_0xA003C40B` | `NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING` | jhash |
| NETWORK | `_0x5E1020CC` | `NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE` | jhash |
| NETWORK | `_0xE66A0B40` | `NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION` | jhash |
| NETWORK | `_0x72052DB3` | `NETWORK_CONCEAL_PLAYER` | jhash |
| NETWORK | `_0xB0313590` | `NETWORK_IS_PLAYER_CONCEALED` | jhash |
| NETWORK | `_0xC4AEAF49` | `NETWORK_CLEAR_CLOCK_TIME_OVERRIDE` | jhash |
| NETWORK | `_0x2465296D` | `NETWORK_IS_CLOCK_TIME_OVERRIDDEN` | jhash |
| NETWORK | `_0x4C2C2B12` | `NETWORK_ADD_CLIENT_ENTITY_AREA` | jhash |
| NETWORK | `_0x69956127` | `NETWORK_ENTITY_AREA_DOES_EXIST` | jhash |
| NETWORK | `_0xCB1CD6D3` | `NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED` | jhash |
| NETWORK | `_0xC6D53AA0` | `NETWORK_ENTITY_AREA_IS_OCCUPIED` | jhash |
| NETWORK | `_0x155465EE` | `NETWORK_USE_HIGH_PRECISION_BLENDING` | jhash |
| NETWORK | `_0xD760CAD5` | `NETWORK_REQUEST_CLOUD_TUNABLES` | jhash |
| NETWORK | `_0x231CFD12` | `NETWORK_GET_TUNABLE_CLOUD_CRC` | jhash |
| NETWORK | `_0xE4B3726A` | `NETWORK_ACCESS_TUNABLE_INT` | jhash |
| NETWORK | `_0x41E8912A` | `NETWORK_ACCESS_TUNABLE_FLOAT` | jhash |
| NETWORK | `_0x8A04E1FE` | `NETWORK_ACCESS_TUNABLE_BOOL` | jhash |
| NETWORK | `_0xA78571CA` | `NETWORK_GET_CONTENT_MODIFIER_LIST_ID` | jhash |
| NETWORK | `_0x053BB329` | `NETWORK_GET_BONE_ID_OF_FATAL_HIT` | jhash |
| NETWORK | `_0x17CBC608` | `NETWORK_GET_NUMBER_BODY_TRACKER_HITS` | jhash |
| NETWORK | `_0xBFAA349B` | `NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER` | jhash |
| NETWORK | `_0xBEB7281A` | `NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER` | jhash |
| NETWORK | `_0xBC54371B` | `NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME` | jhash |
| NETWORK | `_0x644141C5` | `NETWORK_OVERRIDE_COORDS_AND_HEADING` | jhash |
| NETWORK | `_0x53C9563C` | `NETWORK_SET_PLAYER_MENTAL_STATE` | jhash |
| NETWORK | `_0x6B97075B` | `NETWORK_SET_MINIMUM_RANK_FOR_MISSION` | jhash |
| NETWORK | `_0x965EA007` | `GET_NUM_COMMERCE_ITEMS` | jhash |
| NETWORK | `_0xEEFC8A55` | `IS_COMMERCE_DATA_VALID` | jhash |
| NETWORK | `_0x866D1B67` | `TRIGGER_COMMERCE_DATA_FETCH` | jhash |
| NETWORK | `_0xED4A272F` | `IS_COMMERCE_DATA_FETCH_IN_PROGRESS` | jhash |
| NETWORK | `_0x4ACF110C` | `GET_COMMERCE_ITEM_ID` | jhash |
| NETWORK | `_0x1AA3A0D5` | `GET_COMMERCE_ITEM_NAME` | jhash |
| NETWORK | `_0x37877757` | `GET_COMMERCE_PRODUCT_PRICE` | jhash |
| NETWORK | `_0x1CF89DA5` | `GET_COMMERCE_ITEM_NUM_CATS` | jhash |
| NETWORK | `_0x16E53875` | `GET_COMMERCE_ITEM_CAT` | jhash |
| NETWORK | `_0x365C50EE` | `OPEN_COMMERCE_STORE` | jhash |
| NETWORK | `_0x25E2DBA9` | `IS_COMMERCE_STORE_OPEN` | jhash |
| NETWORK | `_0x1FDC75DC` | `REQUEST_COMMERCE_ITEM_IMAGE` | jhash |
| NETWORK | `_0xCA7A0A49` | `RELEASE_ALL_COMMERCE_ITEM_IMAGES` | jhash |
| NETWORK | `_0x44A58B0A` | `GET_COMMERCE_ITEM_TEXTURENAME` | jhash |
| NETWORK | `_0xD32FA11F` | `IS_STORE_AVAILABLE_TO_USER` | jhash |
| NETWORK | `_0xA7FA70AE` | `DELAY_MP_STORE_OPEN` | jhash |
| NETWORK | `_0xCC7DCE24` | `RESET_STORE_NETWORK_GAME_TRACKING` | jhash |
| NETWORK | `_0x70F6D3AD` | `IS_USER_OLD_ENOUGH_TO_ACCESS_STORE` | jhash |
| NETWORK | `_0x2B7B57B3` | `CLOUD_DELETE_MEMBER_FILE` | jhash |
| NETWORK | `_0xBAF52DD8` | `CLOUD_HAS_REQUEST_COMPLETED` | jhash |
| NETWORK | `_0x9B9AFFF1` | `CLOUD_DID_REQUEST_SUCCEED` | jhash |
| NETWORK | `_0xC38E9DB0` | `CLOUD_CHECK_AVAILABILITY` | jhash |
| NETWORK | `_0x32A4EB22` | `CLOUD_IS_CHECKING_AVAILABILITY` | jhash |
| NETWORK | `_0x9262744C` | `CLOUD_GET_AVAILABILITY_CHECK_RESULT` | jhash |
| NETWORK | `_0x08243B79` | `UGC_COPY_CONTENT` | jhash |
| NETWORK | `_0x798D6C27` | `UGC_IS_CREATING` | jhash |
| NETWORK | `_0xE69E8D0D` | `UGC_HAS_CREATE_FINISHED` | jhash |
| NETWORK | `_0x742075FE` | `UGC_DID_CREATE_SUCCEED` | jhash |
| NETWORK | `_0xCE569932` | `UGC_GET_CREATE_RESULT` | jhash |
| NETWORK | `_0x82146BE9` | `UGC_GET_CREATE_CONTENT_ID` | jhash |
| NETWORK | `_0x133FF2D5` | `UGC_CLEAR_CREATE_RESULT` | jhash |
| NETWORK | `_0xCBA7242F` | `UGC_QUERY_MY_CONTENT` | jhash |
| NETWORK | `_0xDED82A6E` | `UGC_QUERY_BY_CONTENT_ID` | jhash |
| NETWORK | `_0x40CF0783` | `UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT` | jhash |
| NETWORK | `_0x4609D596` | `UGC_GET_BOOKMARKED_CONTENT` | jhash |
| NETWORK | `_0x4C2C0D1F` | `UGC_GET_MY_CONTENT` | jhash |
| NETWORK | `_0x9EFBD5D1` | `UGC_GET_FRIEND_CONTENT` | jhash |
| NETWORK | `_0xA6D8B798` | `UGC_GET_CREW_CONTENT` | jhash |
| NETWORK | `_0x67E74842` | `UGC_GET_GET_BY_CATEGORY` | jhash |
| NETWORK | `SET_BALANCE_ADD_MACHINE` | `UGC_GET_GET_BY_CONTENT_ID` | jhash |
| NETWORK | `SET_BALANCE_ADD_MACHINES` | `UGC_GET_GET_BY_CONTENT_IDS` | jhash |
| NETWORK | `_0x37F5BD93` | `UGC_GET_MOST_RECENTLY_CREATED_CONTENT` | jhash |
| NETWORK | `_0x1CFB3F51` | `UGC_GET_MOST_RECENTLY_PLAYED_CONTENT` | jhash |
| NETWORK | `_0x87D1E6BD` | `UGC_GET_TOP_RATED_CONTENT` | jhash |
| NETWORK | `_0x021D5A94` | `UGC_CANCEL_QUERY` | jhash |
| NETWORK | `_0x4908A514` | `UGC_IS_GETTING` | jhash |
| NETWORK | `_0x50296140` | `UGC_HAS_GET_FINISHED` | jhash |
| NETWORK | `_0x3970B0DA` | `UGC_DID_GET_SUCCEED` | jhash |
| NETWORK | `_0xC1487110` | `UGC_WAS_QUERY_FORCE_CANCELLED` | jhash |
| NETWORK | `_0xCC2356E3` | `UGC_GET_QUERY_RESULT` | jhash |
| NETWORK | `_0x2DE69817` | `UGC_GET_CONTENT_NUM` | jhash |
| NETWORK | `_0x81BD8D3B` | `UGC_GET_CONTENT_TOTAL` | jhash |
| NETWORK | `_0x8E1D8F78` | `UGC_GET_CONTENT_HASH` | jhash |
| NETWORK | `_0x0D35DD93` | `UGC_CLEAR_QUERY_RESULTS` | jhash |
| NETWORK | `_0x8F3137E6` | `UGC_GET_CONTENT_USER_ID` | jhash |
| NETWORK | `_0xB9137BA7` | `UGC_GET_CONTENT_USER_NAME` | jhash |
| NETWORK | `_0x9FEEAA9C` | `UGC_GET_CONTENT_IS_USING_SC_NICKNAME` | jhash |
| NETWORK | `_0x5E8A7559` | `UGC_GET_CONTENT_CATEGORY` | jhash |
| NETWORK | `_0x331AEABF` | `UGC_GET_CONTENT_ID` | jhash |
| NETWORK | `_0x0E5E8E5C` | `UGC_GET_ROOT_CONTENT_ID` | jhash |
| NETWORK | `_0xA5A0C695` | `UGC_GET_CONTENT_NAME` | jhash |
| NETWORK | `_0x91534C6E` | `UGC_GET_CONTENT_DESCRIPTION_HASH` | jhash |
| NETWORK | `_0x744A9EA5` | `UGC_GET_CONTENT_PATH` | jhash |
| NETWORK | `_0xA19A238D` | `UGC_GET_CONTENT_UPDATED_DATE` | jhash |
| NETWORK | `_0xFF7D44E6` | `UGC_GET_CONTENT_FILE_VERSION` | jhash |
| NETWORK | `_0xA2C5BD9D` | `UGC_GET_CONTENT_LANGUAGE` | jhash |
| NETWORK | `_0xA850DDE1` | `UGC_GET_CONTENT_IS_PUBLISHED` | jhash |
| NETWORK | `_0x8F6754AE` | `UGC_GET_CONTENT_IS_VERIFIED` | jhash |
| NETWORK | `_0x1E34953F` | `UGC_GET_CONTENT_RATING` | jhash |
| NETWORK | `_0x771FE190` | `UGC_GET_CONTENT_RATING_COUNT` | jhash |
| NETWORK | `_0x3276D9D3` | `UGC_GET_CONTENT_RATING_POSITIVE_COUNT` | jhash |
| NETWORK | `_0x41A0FB02` | `UGC_GET_CONTENT_RATING_NEGATIVE_COUNT` | jhash |
| NETWORK | `_0x11DC0F27` | `UGC_GET_CONTENT_HAS_PLAYER_RECORD` | jhash |
| NETWORK | `_0x0DEB3F5A` | `UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED` | jhash |
| NETWORK | `_0x84315226` | `UGC_REQUEST_CONTENT_DATA_FROM_INDEX` | jhash |
| NETWORK | `_0x38FC2EEB` | `UGC_REQUEST_CONTENT_DATA_FROM_PARAMS` | jhash |
| NETWORK | `_0x1C4F9FDB` | `UGC_REQUEST_CACHED_DESCRIPTION` | jhash |
| NETWORK | `_0xA69AE16C` | `UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS` | jhash |
| NETWORK | `_0xF50BC67A` | `UGC_HAS_DESCRIPTION_REQUEST_FINISHED` | jhash |
| NETWORK | `_0xB3BBD241` | `UGC_DID_DESCRIPTION_REQUEST_SUCCEED` | jhash |
| NETWORK | `_0x70A2845C` | `UGC_GET_CACHED_DESCRIPTION` | jhash |
| NETWORK | `_0x346B506C` | `UGC_RELEASE_CACHED_DESCRIPTION` | jhash |
| NETWORK | `_0x0095DB71` | `UGC_RELEASE_ALL_CACHED_DESCRIPTIONS` | jhash |
| NETWORK | `_0xAD334B40` | `UGC_PUBLISH` | jhash |
| NETWORK | `_0x980D45D7` | `UGC_SET_BOOKMARKED` | jhash |
| NETWORK | `_0x48CCC328` | `UGC_SET_DELETED` | jhash |
| NETWORK | `_0x8E664EFD` | `UGC_IS_MODIFYING` | jhash |
| NETWORK | `_0x611E0BE2` | `UGC_HAS_MODIFY_FINISHED` | jhash |
| NETWORK | `_0xF0211AC1` | `UGC_DID_MODIFY_SUCCEED` | jhash |
| NETWORK | `_0x1F0DD8AF` | `UGC_GET_MODIFY_RESULT` | jhash |
| NETWORK | `_0x405ECA16` | `UGC_CLEAR_MODIFY_RESULT` | jhash |
| NETWORK | `_0x9567392B` | `UGC_GET_CREATORS_BY_USER_ID` | jhash |
| NETWORK | `_0xF79FFF3C` | `UGC_HAS_QUERY_CREATORS_FINISHED` | jhash |
| NETWORK | `_0xA7F3F82B` | `UGC_DID_QUERY_CREATORS_SUCCEED` | jhash |
| NETWORK | `_0x410C61D1` | `UGC_GET_CREATOR_NUM` | jhash |
| NETWORK | `_0x0D4F845D` | `UGC_LOAD_OFFLINE_QUERY` | jhash |
| NETWORK | `_0xE13C1F7F` | `UGC_CLEAR_OFFLINE_QUERY` | jhash |
| NETWORK | `_0x213C6D36` | `UGC_SET_QUERY_DATA_FROM_OFFLINE` | jhash |
| NETWORK | `_0x511E6F50` | `UGC_SET_USING_OFFLINE_CONTENT` | jhash |
| NETWORK | `_0xB4668B23` | `UGC_IS_LANGUAGE_SUPPORTED` | jhash |
| NETWORK | `_0x30B51753` | `FACEBOOK_POST_COMPLETED_HEIST` | jhash |
| NETWORK | `_0x02DAD93F` | `FACEBOOK_POST_CREATE_CHARACTER` | jhash |
| NETWORK | `_0x2D947814` | `FACEBOOK_POST_COMPLETED_MILESTONE` | jhash |
| NETWORK | `_0x37A28C26` | `FACEBOOK_HAS_POST_COMPLETED` | jhash |
| NETWORK | `_0x11E8B5CD` | `FACEBOOK_DID_POST_SUCCEED` | jhash |
| NETWORK | `_0x429AEAB3` | `FACEBOOK_CAN_POST_TO_FACEBOOK` | jhash |
| NETWORK | `_0x1856D008` | `TITLE_TEXTURE_DOWNLOAD_REQUEST` | jhash |
| NETWORK | `_0x68C9AF69` | `UGC_TEXTURE_DOWNLOAD_REQUEST` | jhash |
| NETWORK | `_0xE4547765` | `TEXTURE_DOWNLOAD_HAS_FAILED` | jhash |
| NETWORK | `_0x03225BA3` | `GET_STATUS_OF_TEXTURE_DOWNLOAD` | jhash |
| NETWORK | `_0x4DEBC227` | `NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET` | jhash |
| NETWORK | `_0x5C065D55` | `NETWORK_IS_CABLE_CONNECTED` | jhash |
| NETWORK | `_0x0CA1167F` | `NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV` | jhash |
| NETWORK | `_0x424C6E27` | `NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV` | jhash |
| NETWORK | `_0xD3BBE42F` | `NETWORK_HAVE_ROS_BANNED_PRIV` | jhash |
| NETWORK | `_0xBDBB5948` | `NETWORK_HAVE_ROS_CREATE_TICKET_PRIV` | jhash |
| NETWORK | `_0x97287D68` | `NETWORK_HAVE_ROS_MULTIPLAYER_PRIV` | jhash |
| NETWORK | `_0xC6EA802E` | `NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV` | jhash |
| NETWORK | `_0xFD261E30` | `NETWORK_HAS_ROS_PRIVILEGE` | jhash |
| NETWORK | `_0x8570DD34` | `NETWORK_HAS_ROS_PRIVILEGE_END_DATE` | jhash |
| NETWORK | `_0x273C6180` | `NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE` | jhash |
| NETWORK | `_0x371BBA08` | `NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC` | jhash |
| NETWORK | `_0xA100CC97` | `NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND` | jhash |
| NETWORK | `_0xBB2D33D3` | `NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION` | jhash |
| NETWORKCASH | `_0x5AA379D9` | `NETWORK_CAN_SPEND_MONEY` | jhash |
| NETWORKCASH | `_0xC5D8B1E9` | `PROCESS_CASH_GIFT` | jhash |
| NETWORKCASH | `_0x8B755993` | `WITHDRAW_VC` | jhash |
| NETWORKCASH | `_0x8F266745` | `DEPOSIT_VC` | jhash |
| NETWORKCASH | `_0x531E4892` | `HAS_VC_WITHDRAWAL_COMPLETED` | jhash |
| NETWORKCASH | `_0xB96C7ABE` | `WAS_VC_WITHDRAWAL_SUCCESSFUL` | jhash |
| NETWORKCASH | `_0x66DA9935` | `NETWORK_INITIALIZE_CASH` | jhash |
| NETWORKCASH | `_0x19F0C471` | `NETWORK_CLEAR_CHARACTER_WALLET` | jhash |
| NETWORKCASH | `_0xA27B9FE8` | `NETWORK_CAN_SHARE_JOB_CASH` | jhash |
| NETWORKCASH | `_0x07C92F21` | `NETWORK_REFUND_CASH` | jhash |
| NETWORKCASH | `_0x8474E6F0` | `NETWORK_MONEY_CAN_BET` | jhash |
| NETWORKCASH | `_0xE3802533` | `NETWORK_CAN_BET` | jhash |
| NETWORKCASH | `_0x33C20BC4` | `NETWORK_EARN_FROM_GANGATTACK_PICKUP` | jhash |
| NETWORKCASH | `_0x30B3EC0A` | `NETWORK_EARN_FROM_ROB_ARMORED_CARS` | jhash |
| NETWORKCASH | `_0xEAF04923` | `NETWORK_EARN_FROM_CRATE_DROP` | jhash |
| NETWORKCASH | `_0x2BEFB6C4` | `NETWORK_EARN_FROM_CHALLENGE_WIN` | jhash |
| NETWORKCASH | `_0xF11FC458` | `NETWORK_EARN_FROM_IMPORT_EXPORT` | jhash |
| NETWORKCASH | `_0x866004A8` | `NETWORK_EARN_FROM_AI_TARGET_KILL` | jhash |
| NETWORKCASH | `_0xCC068380` | `NETWORK_EARN_FROM_NOT_BADSPORT` | jhash |
| NETWORKCASH | `_0x96B8BEE8` | `NETWORK_EARN_FROM_PERSONAL_VEHICLE` | jhash |
| NETWORKCASH | `_0xBE70849B` | `NETWORK_PAY_EMPLOYEE_WAGE` | jhash |
| NETWORKCASH | `_0x224A3488` | `NETWORK_PAY_MATCH_ENTRY_FEE` | jhash |
| NETWORKCASH | `_0x8957038E` | `NETWORK_SPENT_IN_STRIPCLUB` | jhash |
| NETWORKCASH | `_0x047547D4` | `NETWORK_BUY_HELI_STRIKE` | jhash |
| NETWORKCASH | `_0xDE7D398C` | `NETWORK_SPENT_BULL_SHARK` | jhash |
| NETWORKCASH | `_0xE792C4A5` | `NETWORK_SPENT_HIRE_MUGGER` | jhash |
| NETWORKCASH | `_0xE6AAA0D5` | `NETWORK_SPENT_ROBBED_BY_MUGGER` | jhash |
| NETWORKCASH | `_0x99CF02C4` | `NETWORK_SPENT_HIRE_MERCENARY` | jhash |
| NETWORKCASH | `_0x20DDCF2F` | `NETWORK_SPENT_BUY_OFFTHERADAR` | jhash |
| NETWORKCASH | `_0x2F7836E2` | `NETWORK_SPENT_BUY_REVEAL_PLAYERS` | jhash |
| NETWORKCASH | `_0x7E97C92C` | `NETWORK_SPENT_BUY_PASSIVE_MODE` | jhash |
| NETWORKCASH | `_0x78436D07` | `NETWORK_SPENT_PROSTITUTES` | jhash |
| NETWORKCASH | `_0x5AEE2FC1` | `NETWORK_SPENT_ARREST_BAIL` | jhash |
| NETWORKCASH | `_0x54198922` | `NETWORK_SPENT_FROM_ROCKSTAR` | jhash |
| NETWORKCASH | `_0x3D96A21C` | `NETWORK_SPENT_PLAYER_HEALTHCARE` | jhash |
| NETWORKCASH | `_0x2E51C61C` | `NETWORK_SPENT_NO_COPS` | jhash |
| NETWORKCASH | `_0xD57A5125` | `NETWORK_SPENT_REQUEST_JOB` | jhash |
| NETWORKCASH | `_0xD9622D64` | `NETWORK_BUY_FAIRGROUND_RIDE` | jhash |
| NETWORKCASH | `_0x16184FB5` | `NETWORK_GET_VC_BANK_BALANCE` | jhash |
| NETWORKCASH | `_0x4F5B781C` | `NETWORK_GET_VC_WALLET_BALANCE` | jhash |
| NETWORKCASH | `_0xADF8F882` | `NETWORK_GET_VC_BALANCE` | jhash |
| DLC1 | `_0x71D0CF3E` | `GET_NUM_TATTOO_SHOP_DLC_ITEMS` | jhash |
| DLC1 | `_0x2E9D628C` | `GET_TATTOO_SHOP_DLC_ITEM_DATA` | jhash |
| DLC1 | `_0xC937FF3D` | `SETUP_SHOP_PED_APPAREL_QUERY` | jhash |
| DLC1 | `_0x594E862C` | `SETUP_SHOP_PED_APPAREL_QUERY_TU` | jhash |
| DLC1 | `_0xC8A4BF12` | `GET_HASH_NAME_FOR_COMPONENT` | jhash |
| DLC1 | `_0x7D876DC0` | `GET_HASH_NAME_FOR_PROP` | jhash |
| DLC1 | `_0x159751B4` | `GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT` | jhash |
| DLC1 | `_0xE4FF7103` | `GET_VARIANT_COMPONENT` | jhash |
| DLC1 | `_0xCE70F183` | `GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT` | jhash |
| DLC1 | `_0xC560D7C0` | `GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT` | jhash |
| DLC1 | `_0x8E2C7FD5` | `DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG` | jhash |
| DLC1 | `_0x1ECD23E7` | `SETUP_SHOP_PED_OUTFIT_QUERY` | jhash |
| DLC1 | `_0xCAFE9209` | `GET_SHOP_PED_OUTFIT` | jhash |
| DLC1 | `_0x2798F56F` | `GET_SHOP_PED_OUTFIT_LOCATE` | jhash |
| DLC1 | `_0x6641A864` | `GET_SHOP_PED_OUTFIT_PROP_VARIANT` | jhash |
| DLC1 | `_0x818534AC` | `GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT` | jhash |
| DLC1 | `_0x2B757E6C` | `GET_NUM_DLC_WEAPONS` | jhash |
| DLC1 | `_0x476B23A9` | `GET_NUM_DLC_WEAPON_COMPONENTS` | jhash |
| DLC1 | `_0x06396058` | `IS_CONTENT_ITEM_LOCKED` | jhash |
| DLC1 | `_0x35BCA844` | `IS_DLC_VEHICLE_MOD` | jhash |
| DLC1 | `_0x59352658` | `GET_DLC_VEHICLE_MOD_LOCK_HASH` | jhash |
| DLC2 | `_0x881B1FDB` | `DLC_CHECK_CLOUD_DATA_CORRECT` | jhash |
| DLC2 | `_0xC2169164` | `GET_EXTRACONTENT_CLOUD_RESULT` | jhash |
| DLC2 | `_0xF79A97F5` | `DLC_CHECK_COMPAT_PACK_CONFIGURATION` | jhash |
| DLC2 | `_0xF69B729C` | `GET_EVER_HAD_BAD_PACK_ORDER` | jhash |
| DLC2 | `_0x517B601B` | `GET_IS_LOADING_SCREEN_ACTIVE` | jhash |
| DLC2 | `_0x6087C10C` | `HAS_CLOUD_REQUESTS_FINISHED` | jhash |
| SYSTEM | `_NULL_START_NEW_SCRIPT` | `START_NEW_SCRIPT_WITH_NAME_HASH` | jhash |
| SYSTEM | `_NULL_START_NEW_SCRIPT_WITH_ARGS` | `START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS` | jhash |
| DECORATOR | `_0xBBAEEF94` | `DECOR_SET_TIME` | jhash |
| DECORATOR | `_0x8E101F5C` | `DECOR_SET_BOOL` | jhash |
| DECORATOR | `_0xDBCE51E0` | `DECOR_GET_BOOL` | jhash |
| DECORATOR | `_0xDDDE59B5` | `DECOR_GET_INT` | jhash |
| DECORATOR | `_0x74EF9C40` | `DECOR_EXIST_ON` | jhash |
| DECORATOR | `_0xE0E2640B` | `DECOR_REMOVE` | jhash |
| DECORATOR | `_0x68BD42A9` | `DECOR_REGISTER` | jhash |
| DECORATOR | `_0x7CF0971D` | `DECOR_IS_REGISTERED_AS_TYPE` | jhash |
| DECORATOR | `_0x7F3F1C02` | `DECOR_REGISTER_LOCK` | jhash |
| UNK_SC | `_0x6BE5DF29` | `SC_INBOX_GET_TOTAL_NUM_MESSAGES` | jhash |
| UNK_SC | `_0x5ECF955D` | `SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX` | jhash |
| UNK_SC | `_0xD1ED1D48` | `SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX` | jhash |
| UNK_SC | `_0x19EE0CCB` | `SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX` | jhash |
| UNK_SC | `_0xEBE420A4` | `SC_INBOX_MESSAGE_DO_APPLY` | jhash |
| UNK_SC | `_0x2C959AF9` | `SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX` | jhash |
| UNK_SC | `_0x0B9A3512` | `SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST` | jhash |
| UNK_SC | `_0x75324674` | `SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST` | jhash |
| UNK_SC | `_0xAB3346B5` | `SC_INBOX_GET_BOUNTY_DATA_AT_INDEX` | jhash |
| UNK_SC | `_0x9A703A2B` | `SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST` | jhash |
| UNK_SC | `_0xD094F11A` | `SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST` | jhash |
| UNK_SC | `_0xAF3C081B` | `SC_EMAIL_SEND_EMAIL` | jhash |
| UNK_SC | `_0x2FB9F53C` | `SC_CACHE_NEW_ROCKSTAR_MSGS` | jhash |
| UNK_SC | `_0x6C5738AB` | `SC_HAS_NEW_ROCKSTAR_MSG` | jhash |
| UNK_SC | `_0x468668F0` | `SC_GET_NEW_ROCKSTAR_MSG` | jhash |
| UNK_SC | `_0x90C74343` | `SC_PRESENCE_ATTR_SET_INT` | jhash |
| UNK_SC | `_0x3ACE6D6B` | `SC_PRESENCE_ATTR_SET_STRING` | jhash |
| UNK_SC | `_0x579B4510` | `SC_PRESENCE_SET_ACTIVITY_RATING` | jhash |
| UNK_SC | `_0xDF45B2A7` | `SC_GAMERDATA_GET_BOOL` | jhash |
| UNK_SC | `_0xDF084A6B` | `SC_PROFANITY_CHECK_STRING` | jhash |
| UNK_SC | `_0xFFED3676` | `SC_PROFANITY_GET_CHECK_IS_VALID` | jhash |
| UNK_SC | `_0xA796D7A7` | `SC_PROFANITY_GET_CHECK_IS_PENDING` | jhash |
| UNK_SC | `_0x09497F31` | `SC_PROFANITY_GET_STRING_PASSED` | jhash |
| UNK_SC | `_0x4D8A6521` | `SC_PROFANITY_GET_STRING_STATUS` | jhash |
| UNK_SC | `_0x7AA36406` | `SC_LICENSEPLATE_CHECK_STRING` | jhash |
| UNK_SC | `_0xF379DCE4` | `SC_LICENSEPLATE_GET_CHECK_IS_VALID` | jhash |
| UNK_SC | `_0x65D84665` | `SC_LICENSEPLATE_GET_CHECK_IS_PENDING` | jhash |
| UNK_SC | `_0xC96456BA` | `SC_COMMUNITY_EVENT_IS_ACTIVE` | jhash |
| UNK_SC | `_0x8E7AEEB7` | `SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE` | jhash |
| UNK_SC | `_0xE778B2A7` | `SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID` | jhash |
| UNK_SC | `_0xCE7D50A8` | `SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID` | jhash |
| UNK_SC | `_0xD26CCA46` | `SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID` | jhash |
| UNK_SC | `_0x24D84334` | `SC_TRANSITION_NEWS_SHOW` | jhash |
| UNK_SC | `_0x8A023024` | `SC_TRANSITION_NEWS_SHOW_TIMED` | jhash |
| UNK_SC | `_0x1C65B038` | `SC_TRANSITION_NEWS_SHOW_NEXT_ITEM` | jhash |
| UNK_SC | `_0x4D4C37B3` | `SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU` | jhash |
| UNK_SC | `_0xAED95A6F` | `SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU` | jhash |
| UNK_SC | `_0x486867E6` | `SC_TRANSITION_NEWS_END` | jhash |
| UNK | `_RETURN_ZERO` | `LOBBY_AUTO_MULTIPLAYER_MENU` | jhash |
| UNK | `_RETURN_ZERO2` | `LOBBY_AUTO_MULTIPLAYER_FREEMODE` | jhash |
| UNK | `_0xC0B971EA` | `LOBBY_SET_AUTO_MULTIPLAYER` | jhash |
| UNK | `_0x94BCAC7C` | `LOBBY_AUTO_MULTIPLAYER_EVENT` | jhash |
| UNK | `_0x7D90EEE5` | `LOBBY_SET_AUTO_MULTIPLAYER_EVENT` | jhash |
| UNK | `_0x734CFEDA` | `LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB` | jhash |
| UNK | `_0x8C227332` | `LOBBY_SET_AUTO_MP_RANDOM_JOB` | jhash |

