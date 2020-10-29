#include <iostream>
#include <memory>
#include <Windows.h>
import Logger;
import Terminal;

constexpr Terminal::Colour::operator WORD() const
{
	return _background << 4 | _foreground;
}

void Terminal::write(const std::string& message)
{
	SetConsoleTextAttribute(_handle, Colour::Gray);
	std::cout << ++_index << ' ';
	SetConsoleTextAttribute(_handle, _colour);
	std::cout << message;
}

std::unique_ptr<Logger::Channel> Terminal::clone() const
{
	return std::make_unique<Terminal>();
}

void Terminal::load(const pugi::xml_node& source)
{
	source;
}