#include "Gameplay/Components/TriggerVolumeEnterBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Utils/GlmBulletConversions.h"
#include "Utils/GlmBulletConversions.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Physics/RigidBody.h"

using namespace Gameplay::Physics;
TriggerVolumeEnterBehaviour::TriggerVolumeEnterBehaviour() :
	IComponent()
{ }
TriggerVolumeEnterBehaviour::~TriggerVolumeEnterBehaviour() = default;


void TriggerVolumeEnterBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	LOG_INFO("Body has entered our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = true;
	const glm::vec3 wForce = glm::vec3(0.0f, 0.0f, 1.0f); //multiply by bodies velocity
	//body->ApplyImpulse(wForce);
	//wForce * body->getLinearVelocity().normalize();
	GetGameObject()->Get<RigidBody>()->ApplyImpulse(wForce);
	GetGameObject()->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
}

void TriggerVolumeEnterBehaviour::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) {
	LOG_INFO("Body has left our trigger volume: {}", body->GetGameObject()->Name);
	_playerInTrigger = false;
	//ballM->SetPostion(glm::vec3(ballM->GetPosition().x, 0.0f, ballM->GetPosition().z));
	GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, 0.0f, GetGameObject()->GetPosition().z));
	GetGameObject()->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	

}

void TriggerVolumeEnterBehaviour::RenderImGui() { }

nlohmann::json TriggerVolumeEnterBehaviour::ToJson() const {
	return { };
}

TriggerVolumeEnterBehaviour::Sptr TriggerVolumeEnterBehaviour::FromJson(const nlohmann::json& blob) {
	TriggerVolumeEnterBehaviour::Sptr result = std::make_shared<TriggerVolumeEnterBehaviour>();
	return result;
}
