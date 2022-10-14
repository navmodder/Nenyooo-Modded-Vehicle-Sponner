#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>
#include <ShlObj.h>
#include "attachment.h"
#include "../dirent.h"
#include "../Common.hpp"
#include "json.h"
using namespace std;
const int ARR_SIZE = 1024;
float NEARBY_DISTACE_ALL = 200.00f;

void JSON::UPGRADE_VEH(nlohmann::json JSO,Entity ent)
{
	int primary_color_S, primary_color_type_S, pearlescentColor_S, secondary_color_S, secondary_color_type_S,wheel,wheel_color,wheel_type,tint = 0;

	for (auto it = JSO.begin(); it != JSO.end(); ++it)
	{
		for (int q = 0; q < 49; q++)
		{
			string num_upgrade = (string)"Upgrade" + to_string(q);
			const char* num_up = num_upgrade.c_str();
			//	vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED][(char*)num_up] = (int)VEHICLE::GET_VEHICLE_MOD(Entity_Get_Veh[i], a);//.emplace(num_up, (int)a); //= (int)a;1
			if (it.key() == num_up) {
				//g_Logger->Info((string)num_up + " exist " + to_string((int)it.value()));
				//DRAW_LINE_FROM_ME_TO(Krox_Entity_Spawn_N_Attach_LAST);
				if (q == MOD_TURBO)
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(ent, MOD_TURBO, true);
				}
				else
					if (q == MOD_XENONLIGHTS)
					{
						VEHICLE::TOGGLE_VEHICLE_MOD(ent, MOD_XENONLIGHTS, true);

					}
					else {
						VEHICLE::SET_VEHICLE_MOD_KIT(ent, 0);
						VEHICLE::SET_VEHICLE_MOD(ent, q, (int)it.value(), false);
					}
			}

		}
		if (it.key() == "primary_color") {
			primary_color_S = (int)it.value();
		}
		if (it.key() == "primary_color_type") {
			primary_color_type_S = (int)it.value();

		}
		if (it.key() == "primary_color_pearlescent") {
			pearlescentColor_S = (int)it.value();

		}
		if (it.key() == "secondary_color") {
			secondary_color_S = (int)it.value();

		}
		if (it.key() == "secondary_color") {
			secondary_color_S = (int)it.value();

		}
		if (it.key() == "wheel_color") {
			wheel_color = (int)it.value();

		}
		if (it.key() == "secondary_color_type") {
			secondary_color_type_S = (int)it.value();

		}		
		if (it.key() == "wheel_type") {
			wheel_type = (int)it.value();

		}	
		if (it.key() == "wheel") {
			wheel = (int)it.value();

		}		
		if (it.key() == "tint_lvl") {
			tint = (int)it.value();
			VEHICLE::SET_VEHICLE_WINDOW_TINT(ent, tint);
		}
	}
	VEHICLE::SET_VEHICLE_COLOURS(ent, primary_color_S, secondary_color_S);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(ent, pearlescentColor_S, wheel_color);
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(ent, wheel_type);
	VEHICLE::SET_VEHICLE_MOD(ent, MOD_FRONTWHEELS, wheel, false);
	
}
void JSON::EXTRA_INFO(nlohmann::json JSO, Entity ent)
{
	bool visible, invincible,collsion;

	for (auto it = JSO.begin(); it != JSO.end(); ++it)
	{
		if (it.key() == "is_visible") {
			visible = (bool)it.value();
			ENTITY::SET_ENTITY_VISIBLE(ent, visible, 0);
		}
		if (it.key() == "is_invincible") {
			invincible = (bool)it.value();
			ENTITY::SET_ENTITY_INVINCIBLE(ent, invincible);
		}		
		if (it.key() == "has_collsion") {
			collsion = (bool)it.value();

				ENTITY::SET_ENTITY_COLLISION(ent, collsion, true);
		}

	}
}





bool logattachements = false;
char get_model_attachment_Hash_Entity[200];
static attachment::attachment get_model_attachment_veh(int Object)
{
	attachment::attachment attachment;
	if (logattachements) { g_Logger->Info(1); }
	Vector3 Krox_Spawnner_Database_Attach_Veh_Bool_A_obj = ENTITY::GET_ENTITY_COORDS(Object, 0);
	if (logattachements) { g_Logger->Info(2); }
	Vector3 Krox_Spawnner_Database_Attach_Veh_Bool_A_loc = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Krox_Spawnner_Database_Attach_Veh_Bool_A_obj.x, Krox_Spawnner_Database_Attach_Veh_Bool_A_obj.y, Krox_Spawnner_Database_Attach_Veh_Bool_A_obj.z);
	if (logattachements) { g_Logger->Info(3); }
	Vector3 Krox_Reveal_Get_Obj_rot = ENTITY::GET_ENTITY_ROTATION(Object, 0);
	if (logattachements) { g_Logger->Info(4); }
	Vector3 Krox_Reveal_Get_veh_rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
	if (logattachements) { g_Logger->Info(5); }
	Vector3 Krox_Reveal_Real_Rot;
	if (logattachements) { g_Logger->Info(6); }
	Krox_Reveal_Real_Rot.x = (Krox_Reveal_Get_Obj_rot.x - Krox_Reveal_Get_veh_rot.x);
	Krox_Reveal_Real_Rot.y = (Krox_Reveal_Get_Obj_rot.y - Krox_Reveal_Get_veh_rot.y);
	Krox_Reveal_Real_Rot.z = (Krox_Reveal_Get_Obj_rot.z - Krox_Reveal_Get_veh_rot.z);
	if (logattachements) { g_Logger->Info(7); }
	bool DOES_ENTITY_HAS_COLLISION = !ENTITY::GET_ENTITY_COLLISION_DISABLED(Object);
	if (logattachements) { g_Logger->Info(8); }
	bool DOES_ENTITY_VISIBLE = ENTITY::IS_ENTITY_VISIBLE(Object);
	if (logattachements) { g_Logger->Info(9); }
	bool _IS_ENTITY_INVINCIBLE = Spooner::IS_ENTITY_INVINCIBLE(Object);
	if (logattachements) { g_Logger->Info(10); }
	sprintf(get_model_attachment_Hash_Entity, "0x%X", ENTITY::GET_ENTITY_MODEL(Object));
	if (logattachements) { g_Logger->Info(11); }
	stringstream GETHASH; GETHASH << std::hex << get_model_attachment_Hash_Entity;
	if (logattachements) { g_Logger->Info(12); }
	int primary_color,  seconadry_color = 0;
	if (logattachements) { g_Logger->Info(13); }
	unsigned int Realhashx;
	if (logattachements) { g_Logger->Info(14); }
	GETHASH >> Realhashx;
	if (logattachements) { g_Logger->Info(15); }
	return attachment = { 0,static_cast<uint32_t>(Realhashx), Krox_Spawnner_Database_Attach_Veh_Bool_A_loc,Krox_Reveal_Real_Rot,DOES_ENTITY_HAS_COLLISION ,DOES_ENTITY_VISIBLE ,_IS_ENTITY_INVINCIBLE};
	if (logattachements) { g_Logger->Info(16); }
	
}



char get_model_attachment_Hash_Entity_My_Car[200];
int JSON::GET_NUMBER_OF_VEHICLES_ATTACHED = 0;
nlohmann::json JSON::Save_Info()
{
	Vehicle my_car = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	if (logattachements) { g_Logger->Info(17); }
	nlohmann::json vehicle_json;
	if (logattachements) { g_Logger->Info(18); }
	GET_NUMBER_OF_VEHICLES_ATTACHED = 0;
	if (logattachements) { g_Logger->Info(19); }
	sprintf(get_model_attachment_Hash_Entity_My_Car, "0x%X", ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())));
	if (logattachements) { g_Logger->Info(20); }
	stringstream Hash; Hash << std::hex << get_model_attachment_Hash_Entity_My_Car;
	if (logattachements) { g_Logger->Info(21); }
	unsigned int Realhash;
	if (logattachements) { g_Logger->Info(22); }
	Hash >> Realhash;
	if (logattachements) { g_Logger->Info(23); }
	vehicle_json["Hash Model Vehicle"] = static_cast<uint32_t>(Realhash);
	if (logattachements) { g_Logger->Info(24); }

	for (int a = 0; a < 49; a++)
	{
		if (logattachements) { g_Logger->Info((string)"49 "); }
		if (logattachements) { g_Logger->Info(a); }

		string num_upgrade = (string)"Upgrade" + to_string(a);
		const char* num_up = num_upgrade.c_str();
		if (a == 23)//wheel
		{
			vehicle_json["wheel"] = (int)VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), a);

		}
		else
		{

			vehicle_json[num_up] = (int)VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), a);
		}
	}
	if (logattachements) { g_Logger->Info(25); }

	int primary_color, primary_color_type, pearlescentColor, secondary_color, secondary_color_type, wheels_color,wheel_type;
	if (logattachements) { g_Logger->Info(26); }
	VEHICLE::GET_VEHICLE_MOD_COLOR_1(my_car, &primary_color_type, &primary_color, &pearlescentColor);
	if (logattachements) { g_Logger->Info(27); }
	VEHICLE::GET_VEHICLE_MOD_COLOR_2(my_car, &secondary_color_type, &secondary_color);
	if (logattachements) { g_Logger->Info(28); }
	VEHICLE::GET_VEHICLE_COLOURS(my_car, &primary_color, &secondary_color);
	if (logattachements) { g_Logger->Info(29); }
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(my_car, &pearlescentColor, &wheels_color);
	if (logattachements) { g_Logger->Info(30); }
	vehicle_json["primary_color"] = primary_color;
	if (logattachements) { g_Logger->Info(31); }
	vehicle_json["primary_color_type"] = primary_color_type;
	if (logattachements) { g_Logger->Info(32); }
	vehicle_json["primary_color_pearlescent"] = pearlescentColor;
	if (logattachements) { g_Logger->Info(33); }
	vehicle_json["secondary_color"] = secondary_color;
	if (logattachements) { g_Logger->Info(34); }
	vehicle_json["secondary_color_type"] = secondary_color_type;
	if (logattachements) { g_Logger->Info(35); }
	vehicle_json["wheel_color"] = wheels_color;
	if (logattachements) { g_Logger->Info(36); }
	vehicle_json["wheel_type"] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(my_car);
	if (logattachements) { g_Logger->Info(37); }
	vehicle_json["tint_lvl"] = VEHICLE::GET_VEHICLE_WINDOW_TINT(my_car);
	if (logattachements) { g_Logger->Info(38); }
	vehicle_json["is_visible"] = ENTITY::IS_ENTITY_VISIBLE(my_car);
	if (logattachements) { g_Logger->Info(39); }
	vehicle_json["is_invincible"] = Spooner::IS_ENTITY_INVINCIBLE(my_car);
	if (logattachements) { g_Logger->Info(40); }

	int K_VEHICLE = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID());
	int Entity_Get_Number;
	Entity Entity_Get_Veh[ARR_SIZE];
	if (logattachements) { g_Logger->Info(41); }

	Entity_Get_Number = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, Entity_Get_Veh);
	if (logattachements) { g_Logger->Info(42); }
	if (logattachements) { g_Logger->Info("--------------------veh-----------------------"); }

	for (int i = 0; i < Entity_Get_Number; i++)
	{
		g_Logger->Info(i);
		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(Entity_Get_Veh[i], PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())))
		{
			if (Functions::DISTANCE_BETWEEN_ENTITIES(Entity_Get_Veh[i], PLAYER::PLAYER_PED_ID(), true) < NEARBY_DISTACE_ALL)
			{

				g_Logger->Info(i);
				GET_NUMBER_OF_VEHICLES_ATTACHED = GET_NUMBER_OF_VEHICLES_ATTACHED + 1;
				attachment::attachment get_info = get_model_attachment_veh(Entity_Get_Veh[i]);


				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_hash"] = get_info.model_hash;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_type"] = 0;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_x"] = get_info.position.x;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_y"] = get_info.position.y;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_z"] = get_info.position.z;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_x"] = get_info.rotation.x;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_y"] = get_info.rotation.y;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_z"] = get_info.rotation.z;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["has_collsion"] = get_info.collision;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["is_visible"] = get_info.visible;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["is_invincible"] = get_info.invincible;
				int primary_color_s, primary_color_type_S, pearlescentColor_S, secondary_color_S, secondary_color_type_S, wheels_color_S;
				VEHICLE::GET_VEHICLE_MOD_COLOR_1(Entity_Get_Veh[i], &primary_color_type_S, &primary_color_s, &pearlescentColor_S);
				VEHICLE::GET_VEHICLE_MOD_COLOR_2(Entity_Get_Veh[i], &secondary_color_type_S, &secondary_color_S);
				VEHICLE::GET_VEHICLE_COLOURS(Entity_Get_Veh[i], &primary_color_s, &secondary_color_S);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(Entity_Get_Veh[i], &pearlescentColor_S, &wheels_color_S);
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["primary_color"] = primary_color_s;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["primary_color_type"] = primary_color_type_S;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["primary_color_pearlescent"] = pearlescentColor_S;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["secondary_color"] = secondary_color_S;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["secondary_color_type"] = secondary_color_type_S;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["wheel_color"] = wheels_color_S;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["wheel_type"] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(Entity_Get_Veh[i]);
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["tint_lvl"] = VEHICLE::GET_VEHICLE_WINDOW_TINT(Entity_Get_Veh[i]);


				for (int a = 0; a < 49; a++)
				{
					string num_upgrade = (string)"Upgrade" + to_string(a);
					const char* num_up = num_upgrade.c_str();
					if (a == 23)//wheels
					{
						vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED][(char*)"wheel"] = (int)VEHICLE::GET_VEHICLE_MOD(Entity_Get_Veh[i], a);//.emplace(num_up, (int)a); //= (int)a;1
					}
					else
					{
						vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED][(char*)num_up] = (int)VEHICLE::GET_VEHICLE_MOD(Entity_Get_Veh[i], a);//.emplace(num_up, (int)a); //= (int)a;1

					}

				}



			}
		}

	}
	if (logattachements) { g_Logger->Info("--------------------obj-----------------------"); }

	Entity Entity_Get_Obj[ARR_SIZE];
	Entity_Get_Number = rage::GetAllWorld(PoolTypeObject, ARR_SIZE, Entity_Get_Obj);
	for (int c = 0; c < Entity_Get_Number; c++)
	{
		if (Functions::DISTANCE_BETWEEN_ENTITIES(Entity_Get_Obj[c], PLAYER::PLAYER_PED_ID(), true) < NEARBY_DISTACE_ALL)
		{

			g_Logger->Info(c);
			if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(Entity_Get_Obj[c], PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())))
			{
				GET_NUMBER_OF_VEHICLES_ATTACHED = GET_NUMBER_OF_VEHICLES_ATTACHED + 1;
				attachment::attachment get_info = get_model_attachment_veh(Entity_Get_Obj[c]);
				g_Logger->Info(c);

				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_hash"] = get_info.model_hash;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_type"] = 2;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_x"] = get_info.position.x;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_y"] = get_info.position.y;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_z"] = get_info.position.z;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_x"] = get_info.rotation.x;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_y"] = get_info.rotation.y;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_z"] = get_info.rotation.z;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["has_collsion"] = get_info.collision;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["is_visible"] = get_info.visible;
				vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["is_invincible"] = get_info.invincible;



			}


		}
	}
	if (logattachements) { g_Logger->Info("--------------------ped-----------------------"); }

	Entity Entity_Get_PED[ARR_SIZE];
	Entity_Get_Number = rage::GetAllWorld(PoolTypePed, ARR_SIZE, Entity_Get_PED);
	for (int f = 0; f < Entity_Get_Number; f++)
	{
		if (Functions::DISTANCE_BETWEEN_ENTITIES(Entity_Get_PED[f], PLAYER::PLAYER_PED_ID(), true) < NEARBY_DISTACE_ALL)
		{

			g_Logger->Info(f);

			if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(Entity_Get_PED[f], PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())))
			{
				if (PED::IS_PED_A_PLAYER(Entity_Get_PED[f]))
				{
				}
				else {
					GET_NUMBER_OF_VEHICLES_ATTACHED = GET_NUMBER_OF_VEHICLES_ATTACHED + 1;
					attachment::attachment get_info = get_model_attachment_veh(Entity_Get_PED[f]);
					g_Logger->Info(f);

					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_hash"] = get_info.model_hash;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["model_type"] = 1;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_x"] = get_info.position.x;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_y"] = get_info.position.y;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["position_z"] = get_info.position.z;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_x"] = get_info.rotation.x;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_y"] = get_info.rotation.y;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["rotation_z"] = get_info.rotation.z;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["has_collsion"] = get_info.collision;
					vehicle_json["Model Attachments"][GET_NUMBER_OF_VEHICLES_ATTACHED]["is_invincible"] = get_info.invincible;

				}

			}


		}
		if (logattachements) { g_Logger->Info("--------------------finish-----------------------"); }
		return vehicle_json;
		if (logattachements) { g_Logger->Info("--------------------finiseh-----------------------"); }


	}

}

static Outfits::Outfits Outfit_Saver_struct(int compontid,int var,int tex)
{
	Outfits::Outfits outfit = { compontid,var,tex };
	return outfit;
}
nlohmann::json JSON::Outfit_Save()
{
	nlohmann::json Outfit_Json;

	{
		std::vector<nlohmann::json> Outfitsvec;
		for (std::uint32_t i = 0; i < 12; ++i)
		{
			if (i == 0)
			{
//				Lists::PED_COMPPONET_INT_Saver = 0;
			}
			else
			{
//				Lists::PED_COMPPONET_INT_Saver = Lists::PED_COMPPONET_INT_Saver + 1;

			}
//		int	VARIATION_INT = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), Lists::PED_COMPPONET_INT_Saver);
//		int	TEXURE_ID_INT = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), Lists::PED_COMPPONET_INT_Saver);

//			Outfitsvec.push_back(Outfit_Saver_struct(Lists::PED_COMPPONET_INT_Saver, VARIATION_INT, TEXURE_ID_INT));
			Outfit_Json["Outfits"] = Outfitsvec;
			Outfit_Json["Z"] = "0";

		}
		return Outfit_Json;
	}
}





Entity Krox_Entity_Vehicle_Spawn_MAIN;
Vehicle JSON::Krox_Entity_Vehicle_SpawnJ(Hash toSpawn, Ped player, nlohmann::json JSO) {
	Vector3 Krox_My_Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0,10,0);
	float heading = ENTITY::GET_ENTITY_HEADING(player);
	//	Entity Krox_Created_Vehicle = VEHICLE::CREATE_VEHICLE_Krox(Krox_Vehicle_Model, Krox_My_Coords, heading, true, false);
	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x9090;
	Entity Created_Veh = VEHICLE::CREATE_VEHICLE_NENYOOO(toSpawn, Krox_My_Coords, heading, true, true);
	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
	auto KROX_NET_ID = NETWORK::VEH_TO_NET(Created_Veh);
	DECORATOR::DECOR_SET_INT(Created_Veh, (char*)"MPBitset", 0);
	NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Created_Veh);
	ENTITY::_SET_ENTITY_SOMETHING(Created_Veh, true);
	if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Created_Veh))
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Created_Veh, true, true);
	//UPGRADES
	UPGRADE_VEH(JSO, Created_Veh);
	//if (Krox_Entity_Vehicle_SPAWN_IN_VEHICLE)
	{
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Created_Veh, -1);
	}
	Blip Krox_IconLogo = 197;
	Blip Krox_BlipVehicle = HUD::ADD_BLIP_FOR_ENTITY(Created_Veh);
	HUD::SET_BLIP_DISPLAY(Krox_BlipVehicle, 8);
	HUD::SET_BLIP_SPRITE(Krox_BlipVehicle, Krox_IconLogo);
	ENTITY::SET_ENTITY_LOD_DIST(Created_Veh, 0xFFFF);
	EXTRA_INFO(JSO, Created_Veh);

	std::stringstream o;
	o << "Vehicle: " << Created_Veh;
	std::string b = o.str();
	Spooner::Spawned_Entitys[Spooner::Spawned_Entity_C] = Created_Veh;
	Spooner::Spawned_Entitys_Names[Spooner::Spawned_Entity_C] = (char*)b.c_str();
	Spooner::Spawned_Entity_C++;
	return Created_Veh;

}
Entity Krox_Entity_Spawn_N_Attach_LAST;
Entity JSON::Krox_Entity_Object_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO, bool use) {
	
	Hash Krox_Ped_Model = Krox_toSpawn;
	Krox_Coordinates.x + 5;
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x9090;
			 Krox_Entity_Spawn_N_Attach_LAST = OBJECT::CREATE_OBJECT(Krox_Ped_Model, Krox_Coordinates.x, Krox_Coordinates.y, Krox_Coordinates.z, true, true, 0);
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;

			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);
			NETWORK::NETWORK_FADE_OUT_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, false, true);
			auto KROX_NET_ID = NETWORK::OBJ_TO_NET(Krox_Entity_Spawn_N_Attach_LAST);
			DECORATOR::DECOR_SET_INT(Krox_Entity_Spawn_N_Attach_LAST, (char*)"MPBitset", 0);
			NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST);
			ENTITY::_SET_ENTITY_SOMETHING(Krox_Entity_Spawn_N_Attach_LAST, true);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true);

			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, true, true);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, Kropx_p, 0, K_Posx, K_Posy, K_Posz, K_Rotx, K_Roty, K_Rotz, false, false, false, true, 0, true);
			Blip Krox_IconLogo = 197;
			Blip Krox_BlipVehicle = HUD::ADD_BLIP_FOR_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);
			HUD::SET_BLIP_DISPLAY(Krox_BlipVehicle, 8);
			HUD::SET_BLIP_SPRITE(Krox_BlipVehicle, Krox_IconLogo);
			ENTITY::SET_ENTITY_LOD_DIST(Krox_Entity_Spawn_N_Attach_LAST,0xFFFF);
			if (use)
			{
				EXTRA_INFO(JSO, Krox_Entity_Spawn_N_Attach_LAST);
			}
			else {
			}
			std::stringstream o;
			o << "Object: " << Krox_Ped_Model;
			std::string b = o.str();
			Spooner::Spawned_Entitys[Spooner::Spawned_Entity_C] = Krox_Entity_Spawn_N_Attach_LAST;
			Spooner::Spawned_Entitys_Names[Spooner::Spawned_Entity_C] = (char*)b.c_str();
			Spooner::Spawned_Entity_C++;
			return Krox_Entity_Spawn_N_Attach_LAST;

}

Entity JSON::Krox_Entity_Vehicle_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO) {

	Hash Krox_Ped_Model = Krox_toSpawn;
	Krox_Coordinates.x + 5;
	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x9090;
	Krox_Entity_Spawn_N_Attach_LAST = VEHICLE::CREATE_VEHICLE_NENYOOO(Krox_Ped_Model, Krox_Coordinates, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false);

	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;

	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);

	//UPGRADES
	UPGRADE_VEH(JSO, Krox_Entity_Spawn_N_Attach_LAST);

	NETWORK::NETWORK_FADE_OUT_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, false, true);
	auto KROX_NET_ID = NETWORK::VEH_TO_NET(Krox_Entity_Spawn_N_Attach_LAST);
	DECORATOR::DECOR_SET_INT(Krox_Entity_Spawn_N_Attach_LAST, (char*)"MPBitset", 0);
	NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST);
	ENTITY::_SET_ENTITY_SOMETHING(Krox_Entity_Spawn_N_Attach_LAST, true);
	if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST))
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, true, true);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, Kropx_p, 0, K_Posx, K_Posy, K_Posz, K_Rotx, K_Roty, K_Rotz, false, false, false, true, 0, true);
	Blip Krox_IconLogo = 197;
	Blip Krox_BlipVehicle = HUD::ADD_BLIP_FOR_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);
	HUD::SET_BLIP_DISPLAY(Krox_BlipVehicle, 8);
	HUD::SET_BLIP_SPRITE(Krox_BlipVehicle, Krox_IconLogo);
	EXTRA_INFO(JSO, Krox_Entity_Spawn_N_Attach_LAST);
	ENTITY::SET_ENTITY_LOD_DIST(Krox_Entity_Spawn_N_Attach_LAST, 0xFFFF);
	std::stringstream o;
	o << "Vehicle: " << Krox_Ped_Model;
	std::string b = o.str();
	Spooner::Spawned_Entitys[Spooner::Spawned_Entity_C] = Krox_Entity_Spawn_N_Attach_LAST;
	Spooner::Spawned_Entitys_Names[Spooner::Spawned_Entity_C] = (char*)b.c_str();
	Spooner::Spawned_Entity_C++;
	return Krox_Entity_Spawn_N_Attach_LAST;
}

	

Entity JSON::Krox_Entity_Ped_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO) {

	Hash Krox_Ped_Model = Krox_toSpawn;
	Krox_Coordinates.x + 5;
	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x9090;
	Krox_Entity_Spawn_N_Attach_LAST = PED::CREATE_PED(26, Krox_toSpawn, Krox_Coordinates.x, Krox_Coordinates.y, Krox_Coordinates.z, 0, true, true);
	*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);
	EXTRA_INFO(JSO, Krox_Entity_Spawn_N_Attach_LAST);

	NETWORK::NETWORK_FADE_OUT_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, false, true);
	auto KROX_NET_ID = NETWORK::VEH_TO_NET(Krox_Entity_Spawn_N_Attach_LAST);
	DECORATOR::DECOR_SET_INT(Krox_Entity_Spawn_N_Attach_LAST, (char*)"MPBitset", 0);
	NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST);
	ENTITY::_SET_ENTITY_SOMETHING(Krox_Entity_Spawn_N_Attach_LAST, true);
	if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Krox_Entity_Spawn_N_Attach_LAST))
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, true, true);
	NETWORK::NETWORK_FADE_IN_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, 1, true);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(Krox_Entity_Spawn_N_Attach_LAST, Kropx_p, 0, K_Posx, K_Posy, K_Posz, K_Rotx, K_Roty, K_Rotz, false, false, false, true, 0, true);
	Blip Krox_IconLogo = 197;
	Blip Krox_BlipVehicle = HUD::ADD_BLIP_FOR_ENTITY(Krox_Entity_Spawn_N_Attach_LAST);
	HUD::SET_BLIP_DISPLAY(Krox_BlipVehicle, 8);
	HUD::SET_BLIP_SPRITE(Krox_BlipVehicle, Krox_IconLogo);
	std::stringstream o;
	o << "Ped: " << Krox_Ped_Model;
	std::string b = o.str();
	Spooner::Spawned_Entitys[Spooner::Spawned_Entity_C] = Krox_Entity_Spawn_N_Attach_LAST;
	Spooner::Spawned_Entitys_Names[Spooner::Spawned_Entity_C] = (char*)b.c_str();
	Spooner::Spawned_Entity_C++;

	return Krox_Entity_Spawn_N_Attach_LAST;
}

	

Entity MAIN_CR_CAR;
using json = nlohmann::json;
//0 = veh
//1 = ped
//2 = obj
Entity LAST_ENTITY_CREATED;
void JSON::Spawn_Json_Veh2(string File_Name)
{

	Vector3 Krox_To_Spawn_C = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
	//	std::ifstream jsonFile(Krox_Vehicle_Load_Modded_Veh2());
	std::ifstream jsonFile(MAIN_LOADING_DIC() +"Modded Vehicles//" + File_Name);
	nlohmann::json Krox_Json;
	jsonFile >> Krox_Json;
	int Main_Vehicle_Spawn = Krox_Json["Hash Model Vehicle"];
	string Main_Vehicle_Spawn_STR = to_string(Main_Vehicle_Spawn);
	Hash Krox_Vehicle = Main_Vehicle_Spawn;

	Player Krox_Self_Player = PLAYER::PLAYER_PED_ID();
	g_CallbackScript->AddCallback<ModelCallback>(Krox_Vehicle, [=] {
		MAIN_CR_CAR = JSON::Krox_Entity_Vehicle_SpawnJ(Krox_Vehicle, Krox_Self_Player, Krox_Json);
		});
	


	nlohmann::json data = Krox_Json["Model Attachments"];
	//g_Logger->Info((string)"Number of items in Data: " + to_string(data.size()));
	for (std::uint32_t i = 0; i < data.size(); ++i)
	{
		Hash SPAWN_HASH = data[i]["model_hash"];
		if ((int)data[i]["model_type"] == 0)//VEHICLE
		{
			g_CallbackScript->AddCallback<ModelCallback>((Hash)data[i]["model_hash"], [=] {
				JSON::Krox_Entity_Vehicle_Spawn_N_Attach((Hash)data[i]["model_hash"], ENTITY::GET_ENTITY_COORDS(Krox_Self_Player, 0), MAIN_CR_CAR, (float)data[i]["position_x"], (float)data[i]["position_y"], (float)data[i]["position_z"], (float)data[i]["rotation_x"], (float)data[i]["rotation_y"], (float)data[i]["rotation_z"], data[i]);
				});
		}

		if ((int)data[i]["model_type"] == 1)// PED
		{
			g_CallbackScript->AddCallback<ModelCallback>((Hash)data[i]["model_hash"], [=] {
				JSON::Krox_Entity_Ped_Spawn_N_Attach((Hash)data[i]["model_hash"], ENTITY::GET_ENTITY_COORDS(Krox_Self_Player, 0), MAIN_CR_CAR, (float)data[i]["position_x"], (float)data[i]["position_y"], (float)data[i]["position_z"], (float)data[i]["rotation_x"], (float)data[i]["rotation_y"], (float)data[i]["rotation_z"], data[i]);
				});

		}
		if ((int)data[i]["model_type"] == 2)// OBJECT
		{
			g_CallbackScript->AddCallback<ModelCallback>((Hash)data[i]["model_hash"], [=] {
				JSON::Krox_Entity_Object_Spawn_N_Attach((Hash)data[i]["model_hash"], ENTITY::GET_ENTITY_COORDS(Krox_Self_Player, 0), MAIN_CR_CAR, (float)data[i]["position_x"], (float)data[i]["position_y"], (float)data[i]["position_z"], (float)data[i]["rotation_x"], (float)data[i]["rotation_y"], (float)data[i]["rotation_z"], data[i],true);// g_Logger->Info("20");
				});

		}
		//has_collsion

	}
}	

void JSON::Load_Saved_Outfit(string File_Name)
{

	std::ifstream jsonFile(MAIN_LOADING_DIC() + File_Name);
	nlohmann::json jf;
	jsonFile >> jf;
	std::vector<nlohmann::json> attachment_vector = jf["Outfits"];

	for (nlohmann::json attachment_json : attachment_vector)
	{
		auto attachment = attachment_json.get<Outfits::Outfits>(); 
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), attachment.componet, attachment.texture, attachment.var, 2);
	}
}
