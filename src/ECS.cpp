#include "ECS.h"

Component::~Component() {

}

void Component::Init() {

}

void Component::Update() {

}

void Component::Draw() {

}

// ------------------------------------------------------------------------------------------

void Entity::Update() {
	for (auto& c : components) c->Update();
	for (auto& c : components) c->Draw();
}

void Entity::Draw() {

}

// ------------------------------------------------------------------------------------------

void EntityManager::Update() { for (auto& e : entities) e->Update(); }
void EntityManager::Draw() { for (auto& e : entities) e->Draw(); }

// Function to remove inactive entities from the entity manager
void EntityManager::Refresh() {
	// Use std::remove_if to move inactive entities to the end of the vector
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity) {
			// Lambda function to check if the entity is active
			return !mEntity->isActive();
		}),
		// Erase the inactive entities from the vector
		std::end(entities));
}

Entity& EntityManager::AddEntity() {
	// Create a new entity
	Entity* e = new Entity();
	// Create a unique pointer to manage the entity's memory
	std::unique_ptr<Entity> uPtr{ e };
	// Add the unique pointer to the list of entities
	entities.emplace_back(std::move(uPtr));

	// Return a reference to the newly added entity
	return *e;
}