module;
#include <memory>
#include <SFML/Graphics.hpp>
export module Crash;

import StackTrace;

export struct Crash
{
public:
    std::vector<std::string> messages;
    std::unique_ptr<StackTrace> stack;
    sf::RenderTexture screenshot;
    std::exception exception;
};