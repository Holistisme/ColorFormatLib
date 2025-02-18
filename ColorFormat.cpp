#include "ColorFormat.hpp"

/* ############################################################################################## */

/**
 * @file ColorFormat.cpp
 * @brief Implementation of the ColorFormat class.
 * 
 * This file contains the function implementations for the ColorFormat class,
 * which provides functionality to apply color formatting, styles, and rainbow effects
 * to terminal text output.
 * 
 * @author aheitz
 * @date Created: 2025-02-17
 * @date Last Modified: 2025-02-18
 */

/* ############################################################################################## */

/*
 * This file is part of the ColorFormat library.
 *
 * Copyright (C) 2025 aheitz <alexy.pa.heitz@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* ############################################################################################## */

/**
 * @brief ANSI color escape codes.
 * 
 * This array stores the available text colors mapped to their corresponding ANSI escape codes.
 * Only one color can be applied at a time.
 */
const std::string ColorFormat::_colors[8][2] = {
	{"red",		"\033[31m"}, {"green", "\033[32m"},
	{"yellow",	"\033[33m"}, {"blue",  "\033[34m"}, 
	{"magenta", "\033[35m"}, {"cyan",  "\033[36m"},
	{"white",	"\033[37m"}, {"black", "\033[30m"} };

/**
 * @brief ANSI text style escape codes.
 * 
 * This array contains available text styles mapped to their ANSI escape codes.
 * Multiple styles can be applied together.
 */
const std::string ColorFormat::_styles[5][2] = {
	{"bold",		  "\033[1m"},
	{"underline",	  "\033[4m"},
	{"italic",		  "\033[3m"},
	{"strikethrough", "\033[9m"},
	{"blink",		  "\033[5m"} };

/* ############################################################################################## */

/**
 * @brief Constructs a ColorFormat object.
 * @param string The text to be formatted.
 * @param firstFormat The first formatting option (e.g., "bold", "red").
 * @param secondFormat The second formatting option (optional).
 * @param thirdFormat The third formatting option (optional).
 * @param fourthFormat The fourth formatting option (optional).
 * @param fifthFormat The fifth formatting option (optional).
 */
ColorFormat::ColorFormat(const std::string &string,
	const std::string &firstFormat,
	const std::string &secondFormat,
	const std::string &thirdFormat,
	const std::string &fourthFormat,
	const std::string &fifthFormat) : _formattedString(formatString(string, firstFormat, secondFormat, thirdFormat, fourthFormat, fifthFormat)) {}

/**
 * @brief Copy constructor.
 * 
 * Creates a new `ColorFormat` object as an exact copy of another.
 * @param source The ColorFormat object to copy from.
 */
ColorFormat::ColorFormat(const ColorFormat &source) : _formattedString(source._formattedString) {}

/**
 * @brief Assignment operator.
 * 
 * Assigns the contents of another `ColorFormat` object to this one.
 * Ensures self-assignment safety.
 * 
 * @param source The `ColorFormat` object to assign from.
 * @return Reference to this object.
 */
ColorFormat &ColorFormat::operator=(const ColorFormat &source) {
	if (this != &source)
		_formattedString = source._formattedString;
	return *this;
}

/**
 * @brief Destructor.
 * 
 * Destroys the `ColorFormat` object and frees any allocated resources.
 */
ColorFormat::~ColorFormat(void) {}

/* ############################################################################################## */

/**
 * @brief Removes all ANSI formatting codes from the given string.
 * 
 * This function detects and removes ANSI escape sequences (e.g., colors, styles)
 * from the provided text, ensuring a clean, unformatted string.
 * 
 * @param string The string to clean from previous formatting.
 */
void ColorFormat::removePreviousFormats(std::string &string) {
	size_t start = 0;

	while ((start = string.find("\033[")) != std::string::npos) {
		size_t end = string.find('m', start);
		if (end != std::string::npos)
			string.erase(start, end - start + 1);
		else
			break;
	}
}

/* ############################################################################################## */

/**
 * @brief Retrieves the formatted string.
 * 
 * This function returns the string that has been formatted with the selected
 * color and/or styles.
 * 
 * @return std::string The formatted string with ANSI escape sequences.
 */
const std::string ColorFormat::getFormattedString(void) const { return _formattedString; }

/**
 * @brief Formats a string with specified styles and colors.
 * 
 * This function applies color and text styles to a given string.
 * The first detected color is applied, while multiple styles can be combined.
 * If multiple colors are provided, an exception is thrown.
 * 
 * @param string The text to format.
 * @param firstFormat The first formatting option (e.g., "bold", "red").
 * @param secondFormat The second formatting option (optional).
 * @param thirdFormat The third formatting option (optional).
 * @param fourthFormat The fourth formatting option (optional).
 * @param fifthFormat The fifth formatting option (optional).
 * @param sixthFormat The sixth formatting option (optional).
 * @return std::string The formatted string with ANSI escape sequences.
 * 
 * @throws std::invalid_argument If multiple colors or unknown formats are detected.
 */
const std::string ColorFormat::formatString(std::string string,
											const std::string &firstFormat,
											const std::string &secondFormat,
											const std::string &thirdFormat,
											const std::string &fourthFormat,
											const std::string &fifthFormat,
											const std::string &sixthFormat) {
	std::string color			= "";
	std::string formats			= "";
	std::string parameters[6]	= {firstFormat, secondFormat, thirdFormat, fourthFormat, fifthFormat, sixthFormat};
	bool		activeStyles[5] = {false};

	if (string.empty())
		return "";

	for (size_t i = 0 ; i < 6 ; i++) {
		bool done = parameters[i].empty() ? true : false;
		if (!done) {
			for (size_t j = 0 ; j < 8 ; j++) {
				if (parameters[i] == _colors[j][0]) {
					if (!color.empty())
						throw std::invalid_argument("❌ Multiple colors detected. Only one is allowed.");
					color = _colors[j][1];
					done = true;
					break;
				}
			}
			if (!done) {
				for (size_t j = 0 ; j < 5 ; j++)
					if (parameters[i] == _styles[j][0]) {
						if (activeStyles[j])
							throw std::invalid_argument("❌ Duplicate style detected: " + parameters[i] + '.');
						activeStyles[j] = true;
						formats += _styles[j][1];
						done = true;
						break;
					}
			}
			if (!done)
				throw std::invalid_argument("❌ Unknown format detected: " + parameters[i]);
		}
	}

	if (!color.empty() or !formats.empty())
		removePreviousFormats(string);

	return color + formats + string + "\033[0m";
}

/**
 * @brief Formats a numeric value with styles and colors.
 * 
 * Applies ANSI styles and colors while formatting numbers with thousand separators.
 *
 * @param number The unsigned integer to format.
 * @param firstFormat First formatting option (e.g., "bold", "red").
 * @param secondFormat Optional second formatting option.
 * @param thirdFormat Optional third formatting option.
 * @param fourthFormat Optional fourth formatting option.
 * @param fifthFormat Optional fifth formatting option.
 * @return The formatted number as a string.
 * @throws std::invalid_argument if multiple colors are used or an invalid style is detected.
 */
const std::string ColorFormat::formatUnsignedInteger(unsigned int number,
													 const std::string &firstFormat,
													 const std::string &secondFormat,
													 const std::string &thirdFormat,
													 const std::string &fourthFormat,
													 const std::string &fifthFormat,
													 const std::string &sixthFormat) {
	std::string formattedUnsignedInteger = "";
	size_t		commaCount = 0;

	do {
		if (!formattedUnsignedInteger.empty() and !((formattedUnsignedInteger.size() - commaCount) % 3)) {
			formattedUnsignedInteger.insert(0, ",");
			++commaCount;
		}
		formattedUnsignedInteger.insert(0, 1, static_cast<char>('0' + number % 10));
		number /= 10;
	} while (number);

	return formatString(formattedUnsignedInteger, firstFormat, secondFormat, thirdFormat, fourthFormat, fifthFormat, sixthFormat);
}

/**
 * @brief Formats an unsigned integer with a color gradient from red to green.
 * 
 * The color varies from red (low values) to green (high values) based on the 
 * given range [minimum, maximum]. If `minimum > maximum`, the gradient is reversed.
 * 
 * If `number` is outside of the range, it will blink in red (if too low) or green (if too high).
 * 
 * @param number The unsigned integer to format.
 * @param minimum The lower bound of the gradient.
 * @param maximum The upper bound of the gradient.
 * @param firstFormat Optional text style (e.g., "bold", "underline").
 * @param secondFormat Optional text style.
 * @param thirdFormat Optional text style.
 * @param fourthFormat Optional text style.
 * @param fifthFormat Optional text style.
 * 
 * @return std::string The formatted string with ANSI color codes.
 * 
 * @throws std::invalid_argument If a color is provided as a parameter (only styles are allowed).
 */
const std::string ColorFormat::formatGradientUnsignedInteger(const unsigned int number,
															 const unsigned int minimum, const unsigned int maximum,
															 const std::string &firstFormat,
															 const std::string &secondFormat,
															 const std::string &thirdFormat,
															 const std::string &fourthFormat,
															 const std::string &fifthFormat) {
	std::string parameters[5] = {firstFormat, secondFormat, thirdFormat, fourthFormat, fifthFormat};
	for (size_t i = 0 ; i < 5 ; i++)
		if (!parameters[i].empty())
			for (size_t j = 0 ; j < 8 ; j++)
				if (parameters[i] == _colors[j][0])
					throw std::invalid_argument("❌ No color is aurotized with the gradiation function.");

	if ((number <  minimum and minimum <  maximum) or
		(number >  minimum and minimum >  maximum) or
		(number != maximum and minimum == maximum))
		return formatUnsignedInteger(number, "red", "blink", "bold");
	if ((number > maximum and maximum > minimum) or
		(number < maximum and maximum < minimum))
		return formatUnsignedInteger(number, "green", "blink", "bold");

	const bool	 reversed = minimum > maximum;
	const double progress = reversed ? (double)(number  - maximum) : (double)(number  - minimum);
	const double field	  = reversed ? (double)(minimum - maximum) : (double)(maximum - minimum);
	double		 ratio	  = field != 0.0 ? progress / field : 1.0;

	if (ratio < 0.0) ratio = 0.0;
	if (ratio > 1.0) ratio = 1.0;
	if (reversed)	 ratio = 1.0 - ratio;

	int red   = (ratio < 0.5) ? 255					   : (int)(255 * (1.0 - (ratio - 0.5) * 2));
	int green = (ratio < 0.5) ? (int)(255 * ratio * 2) : 255;
	int blue  = 0;

	std::ostringstream color;
	color << "\033[38;5;" << 16 + (red / 51) * 36 + (green / 51) * 6 + (blue / 51) << "m";
	return color.str() + formatUnsignedInteger(number, firstFormat, secondFormat, thirdFormat, fourthFormat, fifthFormat) + "\033[0m";
}

/**
 * @brief Applies a rainbow effect to the text.
 * 
 * This function cycles through different colors to give a rainbow effect to the text.
 * If no text is provided, a default rainbow symbol "🌈" is returned.
 * 
 * @param firstArgument The first formatting argument (style or text).
 * @param secondArgument The second formatting argument (optional).
 * @param thirdArgument The third formatting argument (optional).
 * @param fourthArgument The fourth formatting argument (optional).
 * @param fifthArgument The fifth formatting argument (optional).
 * @return std::string The text with a rainbow color effect applied.
 * 
 * @throws std::invalid_argument If multiple text arguments are provided.
 */
const std::string ColorFormat::rainbow(const std::string &firstArgument,
									   const std::string &secondArgument,
									   const std::string &thirdArgument,
									   const std::string &fourthArgument,
									   const std::string &fifthArgument) {
	std::string string		 = "";
	std::string format		 = "";
	std::string arguments[5] = {firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument};
	for (size_t i = 0 ; i < 5 ; i++) {
		if (!arguments[i].empty()) {
			for (size_t j = 0 ; j < 5 ; j++) {
				if (arguments[i] == _styles[j][0]) {
					format += _styles[j][1];
					arguments[i] = "";
					break;
				}
			}
			if (!arguments[i].empty())
				(string.empty()) ? string = arguments[i] : throw std::invalid_argument("❌ Too many text arguments for rainbow().");
		}
		else
			break;
	}

	if (string.empty())
		return "🌈";
	
	std::string colors[6] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};
	std::string randomColors[8];
	for (size_t i = 0 ; i < 6 ; i++) {
		size_t randomIndex = std::rand() % (6 - i % 6);
		randomColors[i] = colors[randomIndex];
		colors[randomIndex] = colors[5 - i];
	}

	std::string rainbowString = "";
	removePreviousFormats(string);
	for (size_t i = 0 ; i < string.size() ; i++) {
		if (string[i] == '\033' && i + 1 < string.size() && string[i + 1] == '[') {
			while (i < string.size() && string[i] != 'm') {
				rainbowString += string[i++];
			}
			rainbowString += 'm';
			continue;
		}
		rainbowString += randomColors[i % 6] + string[i];
	}

	return format + rainbowString + "\033[0m";
}