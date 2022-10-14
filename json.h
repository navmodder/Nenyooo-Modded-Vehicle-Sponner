using namespace std;

#include "../nlohmann/json.hpp"

namespace JSON
{
	void UPGRADE_VEH(nlohmann::json JSO, Entity ent);
	void EXTRA_INFO(nlohmann::json JSO, Entity ent);
	extern int GET_NUMBER_OF_VEHICLES_ATTACHED;
	extern nlohmann::json Save_Info();
	extern nlohmann::json Outfit_Save();
	Vehicle Krox_Entity_Vehicle_SpawnJ(Hash toSpawn, Ped player, nlohmann::json JSO);
	Entity Krox_Entity_Object_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO,bool use);
	Entity Krox_Entity_Vehicle_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO);
	Entity Krox_Entity_Ped_Spawn_N_Attach(Hash Krox_toSpawn, Vector3 Krox_Coordinates, Entity Kropx_p, float K_Posx, float K_Posy, float K_Posz, float K_Rotx, float K_Roty, float K_Rotz, nlohmann::json JSO);
	//void Spawn_Json_Veh(string File_Name);
	void Spawn_Json_Veh2(string File_Name);
	void Load_Saved_Outfit(string File_Name);
	//void Spawn_Json_Veh2();
}
