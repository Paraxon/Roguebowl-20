export module Observer;

import Event;
import std.core;

export class Observer
{
public:
	virtual void on_event(const Event& args) = 0;
};