#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Entity;
class Component;

// ------------------------------------------------------------------------------------------

// Type alias for the component IDs
using ComponentID = std::size_t;

// Function to generate unique component IDs
inline ComponentID getComponentTypeID() {
	// Static varibale to keep track of the last assigned ID
	static ComponentID lastID = 0;
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

// Bitset to keep track of which components an entity has
using ComponentBitset = std::bitset<maxComponents>;

// Array to store pointers to the components of an entity
using ComponentArray = std::array<Component*, maxComponents>;

// ------------------------------------------------------------------------------------------

class Component {
public:
	Entity* entity;

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual ~Component();
};

class Entity {
public:
	void Update();
	void Draw();

	bool isActive() const { return active; }
	void Destroy() { active = false; }

	// Template function to check if the entity has a specific component type
	template<typename T> bool hasComponent() const {
		// Check if the bit corresponding to the component type ID is set
		return ComponentBitset[getComponentTypeID<T>()];
	}

	// Template function to add a component to the entity
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		// Create a new component of type T with the provided arguments
		T* c(new T(std::forward<TArgs>(mArgs)...));
		// Set the entity pointer of the component to this entity
		c->entity = this;
		// Create a unique pointer to manage the component's memory
		std::unique_ptr<Component> uPtr{ c };
		// Add the component to the list of components
		components.emplace_back(std::move(uPtr));

		// Store the component in the component array and set the bitset
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		// Call initialiser function
		c->Init();

		// Return a reference to the newly added component
		return *c;
	}

	// Template function to get a reference to a specific component type
	template<typename T> T& getComponent() const {
		// Retrieve the pointer to the component from the component array
		auto ptr(componentArray[getComponentTypeID<T>()]);
		// Cast the pointer to the correct component type and return a reference to it
		return *static_cast<T*>(ptr);
	}


private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitset componentBitset;
};

class EntityManager {
public:
	void Update();
	void Draw();
	void Refresh();

	Entity& AddEntity();

private:
	std::vector<std::unique_ptr<Entity>> entities;

};