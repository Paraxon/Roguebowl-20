module;
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <string>
#include <Windows.h>
export module Terminal;

import Logger;
import Serialization;
import StaticFactory;

export class Terminal : public Logger::Channel
{
public:
	/* Colour is an 8-bit word where each bit corresponds to the presence or
	abscence of that colour channel in either the foreground or background
	https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#_win32_font_attributes
	http://www.cplusplus.com/forum/beginner/5830/
	bit 0 - foreground blue
	bit 1 - foreground green
	bit 2 - foreground red
	bit 3 - foreground intensity

	bit 4 - background blue
	bit 5 - background green
	bit 6 - background red
	bit 7 - background intensity*/
	struct Colour
	{
	public:
		[[nodiscard]] constexpr Colour(WORD foreground = Colour::White, WORD background = Colour::Black)
			: _foreground(foreground), _background(background) {};
		[[nodiscard]] constexpr operator WORD() const;
		//Serializable
		constexpr void load(const std::string& source);
		//Named Colours
		static constexpr WORD White = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		static constexpr WORD Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		static constexpr WORD Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		static constexpr WORD Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
		static constexpr WORD Gray = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		static constexpr WORD Black = 0;
		static constexpr WORD Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		static constexpr WORD Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		static constexpr WORD Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	private:
		WORD _foreground, _background;
	};
	[[nodiscard]] Terminal(WORD foreground = Colour::White, WORD background = Colour::Black) 
		: _handle(GetStdHandle(STD_OUTPUT_HANDLE)), _colour(foreground, background) {};
	void write(const std::string & message) override;
	//Cloneable
	[[nodiscard]] std::unique_ptr<Logger::Channel> clone() const override;
	//Serializable
	void load(const pugi::xml_node & source) override;
private:
	inline static int _index = 0;
	Colour _colour;
	HANDLE _handle;
};