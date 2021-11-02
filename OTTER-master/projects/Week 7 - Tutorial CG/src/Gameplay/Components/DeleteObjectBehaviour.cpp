#include "Gameplay/Components/DeleteObjectBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Utils/GlmBulletConversions.h"
#include "Gameplay/Components/IComponent.h"

#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"

using namespace Gameplay::Physics;
DeleteObjectBehaviour::DeleteObjectBehaviour() :
	IComponent()
{ 
	//_scene = GetGameObject()->GetScene();
}
DeleteObjectBehaviour::~DeleteObjectBehaviour() = default;


void DeleteObjectBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody> & body)
{
	LOG_INFO("Body has entered our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = true;
	if (GetGameObject()->Get<RenderComponent>()->GetMaterial()->Name == "Block2")
	{
		//swap material and then pass
		
	}
	else
	{
		//delete self
		_scene = GetGameObject()->GetScene();
		//convoluted but whatever
		_scene->DeleteGameObject(_scene->FindObjectByGUID(GetGameObject()->GUID));
	}
	//bounce ball back in opposite direction
	
	
}

void DeleteObjectBehaviour::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody> & body) {
	LOG_INFO("Body has left our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = false;
}

void DeleteObjectBehaviour::RenderImGui() { }

nlohmann::json DeleteObjectBehaviour::ToJson() const {
	return { };
}

DeleteObjectBehaviour::Sptr DeleteObjectBehaviour::FromJson(const nlohmann::json & blob) {
	DeleteObjectBehaviour::Sptr result = std::make_shared<DeleteObjectBehaviour>();
	return result;
}
