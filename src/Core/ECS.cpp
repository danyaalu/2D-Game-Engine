#include "ECS.h"

// ------------------------------------------------------------------------------------------

void Entity::Update() {
	for (auto& c : components) c->Update();
}

void Entity::Draw() {
	for (auto& c : components) c->Draw();
}
// ------------------------------------------------------------------------------------------

void EntityManager::Update() { for (auto& e : entities) e->Update(); }
void EntityManager::Draw() { for (auto& e : entities) e->Draw(); }

// Function to remove inactive entities from the entity manager
void EntityManager::Refresh() {
	for (auto i(0u); i < maxGroups; i++) {
		auto& v(groupedEntities[i]);
		v.erase(std::remove_if(std::begin(v), std::end(v),
			[i](Entity* mEntity) {
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
			std::end(v));
	}

	// Use std::remove_if to move inactive entities to the end of the vector
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity) {
			// Lambda function to check if the entity is active
			return !mEntity->isActive();
		}),
		// Erase the inactive entities from the vector
		std::end(entities));
}

void EntityManager::AddToGroup(Entity* mEntity, Group mGroup) {
	groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& EntityManager::getGroup(Group mGroup) {
	return groupedEntities[mGroup];
}

Entity& EntityManager::AddEntity() {
	// Create a new entity with the EntityManager reference
	Entity* e = new Entity(*this);
	// Create a unique pointer to manage the entity's memory
	std::unique_ptr<Entity> uPtr{ e };
	// Add the unique pointer to the list of entities
	entities.emplace_back(std::move(uPtr));

	// Return a reference to the newly added entity
	return *e;
}
