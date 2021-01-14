export module Command;

export import TimeStep;

export template <typename value_type>
class Command
{
public:
	virtual void update(TimeStep timestep) = 0;
protected:
	[[nodiscard]] virtual value_type poll() const = 0;
};