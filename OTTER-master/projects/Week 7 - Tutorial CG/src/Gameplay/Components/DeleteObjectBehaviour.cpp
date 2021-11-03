#include "Gameplay/Components/DeleteObjectBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Utils/GlmBulletConversions.h"
#include "Gameplay/Components/IComponent.h"

#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"

using namespace Gameplay::Physics;
DeleteObjectBehaviour::DeleteObjectBehaviour() :
	IComponent(), EnterMaterial(nullptr),
	ExitMaterial(nullptr)
{ 
	
}
DeleteObjectBehaviour::~DeleteObjectBehaviour() = default;


void DeleteObjectBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody> & body)
{
	LOG_INFO("Body has entered our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = true;
	//get our scene, delete this line later
	_scene = GetGameObject()->GetScene();
	if (GetGameObject()->Get<RenderComponent>()->GetMaterial() == EnterMaterial)
	{
		canBreak = false;
		//swap material and then pass
		GetGameObject()->Get<RenderComponent>()->SetMaterial(ExitMaterial);
		//bounce ball back in opposite direction
		glm::vec3 dir = body->GetGameObject()->GetPosition() - GetGameObject()->GetPosition();
		//normalize
		glm::float1 len = sqrt(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));
		dir = dir / len;
		//this needs to be better?
		if (body->GetLinearVelocity().z > 0) //positive, going up
		{
			const glm::vec3 wForce = glm::vec3(dir.x, 0.0f, -10.0f);
			body->SetLinearVelocity(glm::vec3(0.0, 0.0, 0.0));
			body->GetGameObject()->Get<RigidBody>()->ApplyImpulse(wForce);
		}
		else //negative, going down
		{
			const glm::vec3 wForce = glm::vec3(dir.x, 0.0f, 10.0f);
			body->SetLinearVelocity(glm::vec3(0.0, 0.0, 0.0));
			body->GetGameObject()->Get<RigidBody>()->ApplyImpulse(wForce);
		}
	}
	else if (canBreak)
	{
		//delete self
		//bounce ball back in opposite direction
		glm::vec3 dir = body->GetGameObject()->GetPosition() - GetGameObject()->GetPosition();
		//normalize
		glm::float1 len = sqrt(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));
		dir = dir / len;
		//this needs to be better?
		if (body->GetLinearVelocity().z > 0) //positive, going up
		{
			const glm::vec3 wForce = glm::vec3(dir.x, 0.0f, -10.0f);
			body->SetLinearVelocity(glm::vec3(0.0, 0.0, 0.0));
			body->GetGameObject()->Get<RigidBody>()->ApplyImpulse(wForce);
		}
		else //negative, going down
		{
			const glm::vec3 wForce = glm::vec3(dir.x, 0.0f, 10.0f);
			body->SetLinearVelocity(glm::vec3(0.0, 0.0, 0.0));
			body->GetGameObject()->Get<RigidBody>()->ApplyImpulse(wForce);
		}
		//convoluted but whatever
		_scene->DeleteGameObject(_scene->FindObjectByGUID(GetGameObject()->GUID));
	}
	
	
	//increment points here
	_scene->score += 1;
	
}

void DeleteObjectBehaviour::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody> & body) {
	LOG_INFO("Body has left our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = false;
	canBreak = true;
	//bounce ball back in opposite direction
	glm::vec3 dir = body->GetGameObject()->GetPosition() - GetGameObject()->GetPosition();
	//normalize
	glm::float1 len = sqrt(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));
	dir = dir / len;
	glm::vec3 wForce;
	//this needs to be better?
	if (body->GetLinearVelocity().z > 0) //positive, going up
	{
		wForce = glm::vec3(dir.x, 0.0f, -1.0f);
	}
	else //negative, going down
	{
		wForce = glm::vec3(dir.x, 0.0f, 1.0f);
	}

	body->ApplyImpulse(wForce);
}

void DeleteObjectBehaviour::RenderImGui() { }

nlohmann::json DeleteObjectBehaviour::ToJson() const {
	return { };
}

DeleteObjectBehaviour::Sptr DeleteObjectBehaviour::FromJson(const nlohmann::json & blob) {
	DeleteObjectBehaviour::Sptr result = std::make_shared<DeleteObjectBehaviour>();
	return result;
}
