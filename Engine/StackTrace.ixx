module;
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
export module StackTrace;

export class StackTrace
{
public:
	struct Frame
	{
	public:
		std::string name;
		std::optional<std::filesystem::path> source;
		std::optional<int> line;
	};
	//Rule of 5
	StackTrace(const StackTrace&) = delete;
	StackTrace(StackTrace&&) = delete;
	StackTrace& operator=(const StackTrace&) = delete;
	StackTrace& operator=(StackTrace&&) = delete;
	virtual ~StackTrace() = default;
	//Frames
	std::vector<Frame> & frames() { return _frames; };
	//Iterators
	auto begin() const { return _frames.begin(); };
	auto end() const { return _frames.end(); };
protected:
	StackTrace() = default;
private:
	std::vector<Frame> _frames;
};