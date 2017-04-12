#include "FontResManager.h"

#include <TheCoffeeMaker/Console.h>

namespace CMaker{
	/* PATHS */
	const std::map< CMaker::Font, std::string > FontResManager::pathFonts = {
		{ Font::DEFAULT, "fonts/8bit.ttf"}
	};

	/*
		FONT ACCESS
	*/
	sf::Font & FontResManager::getFont(CMaker::Font _font)
	{
		auto it = resFonts.find(_font);
		if (it != resFonts.end()) {
			return it->second;
		}
		else {
			try{
				this->loadFont(_font);
				return getFont(_font);
			}
			catch (std::exception e) {
				C_DEBUG << "Exception when loading font: " << e.what() << std::endl;
			}
		}
	}

	void FontResManager::loadFont(CMaker::Font _font) {
		// Get path to this font
		std::string fontPath;

		auto it = pathFonts.find(_font);
		if (it != pathFonts.end()) {
			fontPath = it->second;
		}
		else {
			throw new std::exception("Path to this font not found.");
		}

		// Load and insert font
		sf::Font tmpFont;
		if (!tmpFont.loadFromFile(fontPath)) {
			std::string msg = "Font not found in given path: " + fontPath;
			throw new std::exception(msg.c_str());
		}

		resFonts.insert(std::make_pair(_font, tmpFont));
	}

	/*
		CONSTRUCTOR / DESTRUCTOR
	*/
	FontResManager::FontResManager()
	{
	}

	FontResManager::~FontResManager()
	{
	}
}