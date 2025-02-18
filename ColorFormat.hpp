#pragma once

/* ############################################################################################## */

/**
 * @file ColorFormat.hpp
 * @brief Declaration of the ColorFormat class for text formatting and coloring in terminal.
 * 
 * The ColorFormat class provides methods to apply ANSI escape sequences to style
 * and colorize text dynamically. It supports color formatting, styles (bold, underline, etc.),
 * and even rainbow-colored output.
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

#include <cstdlib>
#include <iostream>
#include <sstream>

/* ############################################################################################## */

/**
 * @brief Provides text styling with ANSI escape codes.
 *
 * This class allows text formatting using ANSI codes, including colors, styles, and rainbow effects.
 */
class ColorFormat {
	private:
		std::string _formattedString;

		/** ANSI escape codes for colors */
		static const std::string _colors[8][2];

		/** ANSI escape codes for styles */
		static const std::string _styles[5][2];

		/**
		 * @brief Removes all ANSI escape sequences from a string.
		 * 
		 * This function ensures that no previous formatting (e.g., colors, styles)
		 * interferes with new formatting applied.
		 * 
		 * @param string The string to clean.
		 */
		static void removePreviousFormats(std::string &string);
	public:
		/**
		 * @brief Constructs a formatted text with the given styles and colors.
		 * @param string The text to format.
		 * @param firstFormat First formatting option (e.g., "bold", "red").
		 * @param secondFormat Optional second formatting option.
		 * @param thirdFormat Optional third formatting option.
		 * @param fourthFormat Optional fourth formatting option.
		 * @param fifthFormat Optional fifth formatting option.
		 */
		ColorFormat(const std::string &string		= "",
					const std::string &firstFormat	= "",
					const std::string &secondFormat = "",
					const std::string &thirdFormat	= "",
					const std::string &fourthFormat = "",
					const std::string &fifthFormat	= "");
		ColorFormat(const ColorFormat &source);
		ColorFormat &operator=(const ColorFormat &source);
		~ColorFormat(void);

		/**
		 * @brief Retrieves the formatted string.
		 * @return The formatted string with applied ANSI escape codes.
		 */
		const std::string getFormattedString(void) const;

		/**
		 * @brief Formats a string with the given styles and colors.
		 * @param string The text to format.
		 * @param firstFormat First formatting option (e.g., "bold", "red").
		 * @param secondFormat Optional second formatting option.
		 * @param thirdFormat Optional third formatting option.
		 * @param fourthFormat Optional fourth formatting option.
		 * @param fifthFormat Optional fifth formatting option.
		 * @param sixthFormat Optional sixth formatting option.
		 * @return The formatted string with applied styles and colors.
		 * @throws std::invalid_argument if multiple colors are used or an invalid style is detected.
		 */
		static const std::string formatString(std::string 		string		  = "",
											  const std::string &firstFormat  = "",
											  const std::string &secondFormat = "",
											  const std::string &thirdFormat  = "",
											  const std::string &fourthFormat = "",
											  const std::string &fifthFormat  = "",
											  const std::string &sixthFormat  = "");

		
	    /**
		 * @brief Formats an unsigned integer with thousand separators.
		 * 
		 * This function automatically inserts commas for better readability.
		 * 
		 * Example:
		 * ```
		 * formatUnsignedInteger(1000000, "bold") → "1,000,000" (in bold)
		 * ```
		 * 
		 * @param number The unsigned integer to format.
		 * @param firstFormat Optional text style.
		 * @param secondFormat Optional text style.
		 * @param thirdFormat Optional text style.
		 * @param fourthFormat Optional text style.
		 * @param fifthFormat Optional text style.
		 * 
		 * @return std::string The formatted number as a string.
		 */
		static const std::string formatUnsignedInteger(unsigned int number,
													   const std::string &firstFormat  = "",
													   const std::string &secondFormat = "",
													   const std::string &thirdFormat  = "",
													   const std::string &fourthFormat = "",
													   const std::string &fifthFormat  = "",
													   const std::string &sixthFormat  = "");

		/**
		 * @brief Applies a gradient color to an unsigned integer based on its value.
		 * 
		 * The function colors the number from red (low values) to green (high values), with yellow in between.
		 * If the value is outside the range, it blinks red (too low) or green (too high).
		 * The function prevents users from applying an additional color manually.
		 */
		static const std::string formatGradientUnsignedInteger(unsigned int number,
															   unsigned int minimum, unsigned int maximum,
															   const std::string &firstFormat  = "",
															   const std::string &secondFormat = "",
															   const std::string &thirdFormat  = "",
															   const std::string &fourthFormat = "",
															   const std::string &fifthFormat  = "");

		/**
		 * @brief Generates a rainbow-colored text.
		 * @param firstArgument The text or first style to apply.
		 * @param secondArgument Optional second formatting option.
		 * @param thirdArgument Optional third formatting option.
		 * @param fourthArgument Optional fourth formatting option.
		 * @param fifthArgument Optional fifth formatting option.
		 * @return The rainbow-colored formatted text.
		 * @throws std::invalid_argument if too many text arguments are provided.
		 */
		static const std::string rainbow(const std::string &firstArgument  = "",
										 const std::string &secondArgument = "",
										 const std::string &thirdArgument  = "",
										 const std::string &fourthArgument = "",
										 const std::string &fifthArgument  = "");
};