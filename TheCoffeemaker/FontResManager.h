#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

namespace CMaker {

	/* FONTS */
	enum class Font {
		DEFAULT
	};

	/* Fonts managment */
	class FontResManager
	{
	public:
		sf::Font& getFont(CMaker::Font _font);

		FontResManager();
		~FontResManager();

	private:
		void loadFont(CMaker::Font _font);

		std::map< CMaker::Font, sf::Font > resources;
		static const std::map< CMaker::Font, std::string > paths;
	};

}