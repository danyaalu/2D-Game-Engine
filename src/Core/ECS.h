#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// Forward declaration of Entity class
class Entity;
class Component;

// ------------------------------------------------------------------------------------------

// Type alias for the component IDs
using ComponentID = std::size_t;

// Type alias for the group IDs
using Group = std::size_t;

// Function to generate unique component IDs
inline ComponentID getComponentTypeID() {
	// Static variable to keep track of the last assigned ID
	static ComponentID lastID = 0u;
	// Return the current ID and increment it for the next call
	return lastID++;
}

// Template function to get a unique component ID for a specific component
template<typename T> inline ComponentID getComponentTypeID() noexcept {
	// Static variable to store the unique ID for this component type
	static ComponentID typeID = getComponentTypeID();
	// Return the unique ID for this component type
	return typeID;
}

// Maximum number of components that an entity can have
constexpr std::size_t maxComponents = 32;

// Maximum number of groups that an entity can belong to
constexpr std::size_t maxGroups = 32;

// Bitset to keep track of which components an entity has
using ComponentBitset = std::bitset<maxComponents>;

// Bitset to keep track of which groups an entity belongs to
using GroupBitset = std::bitset<maxGroups>;

// Array to store pointers to the components of an entity
using ComponentArray = std::array<Component*, maxComponents>;

// ------------------------------------------------------------------------------------------

class Component {
public:
	Entity* entity = nullptr; // Initialize to nullptr

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class EntityManager {
public:
	void Update();
	void Draw();
	void Refresh();

	void AddToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getGroup(Group mGroup);

	Entity& AddEntity();

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};

class Entity {
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray{};
	ComponentBitset componentBitset;
	GroupBitset groupBitset;

public:
	EntityManager& manager;
	Entity(EntityManager& mManager) : manager(mManager) {}

	void Update();
	void Draw();

	bool isActive() const { return active; }
	void Destroy() { active = false; }

	bool hasGroup(Group mGroup) {
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup) {
		if (!groupBitset[mGroup]) {
			groupBitset[mGroup] = true;
			manager.AddToGroup(this, mGroup);
		}
	}

	void deleteGroup(Group mGroup) {
		if (groupBitset[mGroup]) {
			groupBitset[mGroup] = false;
			// Optionally, remove from manager's group list if needed
		}
	}

	// Template function to check if the entity has a specific component type
	template<typename T> bool hasComponent() const {
		return componentBitset[getComponentTypeID<T>()];
	}

	// Template function to add a component to the entity
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->Init();

		return *c;
	}

	// Template function to get a reference to a specific component type
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

