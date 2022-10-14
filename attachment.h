#pragma once

#include "../natives.hpp"
#include "../nlohmann/json.hpp"

namespace attachment
{
	struct attachment
	{
		int model_type;
		Hash model_hash;
		Vector3 position;
		Vector3 rotation;
		bool collision;
		bool visible;
		bool invincible;

	};
	void to_json(nlohmann::json& j, const attachment& attachment) {
						 
		j = nlohmann::json{ {"model_type", attachment.model_type} ,{"model_hash", attachment.model_hash},
							{"position_x", attachment.position.x}, {"position_y", attachment.position.y}, {"position_z", attachment.position.z},
							{"rotation_x", attachment.rotation.x}, {"rotation_y", attachment.rotation.y}, {"rotation_z", attachment.rotation.z},
			{"has_collsion", attachment.collision},
			{"is_visible", attachment.visible},
			{"is_invincible", attachment.invincible}
		
		};
	}

	void from_json(const nlohmann::json& j, attachment& attachment) {
		j.at("model_type").get_to(attachment.model_type);
		j.at("model_hash").get_to(attachment.model_hash);
		j.at("position_x").get_to(attachment.position.x); j.at("position_y").get_to(attachment.position.y); j.at("position_z").get_to(attachment.position.z);
		j.at("rotation_x").get_to(attachment.rotation.x); j.at("rotation_y").get_to(attachment.rotation.y); j.at("rotation_z").get_to(attachment.rotation.z);
		j.at("has_collsion").get_to(attachment.collision);
		j.at("is_visible").get_to(attachment.visible);
		j.at("is_invincible").get_to(attachment.invincible);
	}
};
namespace Outfits
{
	struct Outfits
	{
		int componet;
		int var;
		int texture;
	};
	void to_json(nlohmann::json& j, const Outfits& attachment) {
		j = nlohmann::json{ {"Componet", attachment.componet} ,
							{"Varient", attachment.var},
							{"Texture", attachment.texture}
		};
	}

	void from_json(const nlohmann::json& j, Outfits& attachment) {
		j.at("Componet").get_to(attachment.componet);
		j.at("Varient").get_to(attachment.var);
		j.at("Texture").get_to(attachment.texture);
	}
};