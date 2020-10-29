import Updatable;
import Scene;
#include <memory>

std::shared_ptr<Scene> Updatable::scene()
{
	return const_pointer_cast<Scene>(
		static_cast<const Updatable&>(*this).scene());
}

Composition<Scene, System>& Updatable::systems()
{
	return const_cast<Composition<Scene, System>&>(
		static_cast<const Updatable&>(*this).systems());
}

const Composition<Scene, System>& Updatable::systems() const
{
	return scene()->systems();
}

std::shared_ptr<Entity> Updatable::create_entity(const id_type id)
{
	return scene()->create_entity(id);
}

std::shared_ptr<Entity> Updatable::find_entity(const id_type id) const
{
	return scene()->find_entity(id);
}

std::shared_ptr<Entity> Updatable::get_entity(const unsigned int id)
{
	auto entity = find_entity(id);
	if (!entity)
		entity = create_entity(id);
	return entity;
}
