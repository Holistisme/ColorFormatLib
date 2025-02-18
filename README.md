# 🎨 ColorFormat Library
A simple C++ library to colorize and style text in the terminal using ANSI escape codes.
It allows applying colors, styles, and even a rainbow effect 🌈.

## 📌 Features
✔️ Apply colors (red, green, blue, etc.)
✔️ Apply styles (bold, italic, underline, etc.)
✔️ Combine multiple styles and colors
✔️ Dynamic display with a rainbow effect
✔️ Advanced number formatting
✔️ Automatic gradient between red 🔴 and green 🟢 for numerical values
✔️ Detailed error and exception handling

## 🚀 Installation
### Clone the repository:
```sh
git clone https://github.com/Holistisme/ColorFormatLib.git
cd ColorFormatLib
```

### Compile your project:
```sh
g++ -std=c++98 main.cpp ColorFormat.cpp -o my_program
```

## 📜 Usage
### 1️⃣ Basic Formatting
```cpp 
#include "ColorFormat.hpp"
#include <iostream>

int main() {
    std::cout << ColorFormat("Hello in red!", "red") << std::endl;
    std::cout << ColorFormat("Bold and Blue!", "bold", "blue") << std::endl;
    return 0;
}
```

### 2️⃣ Rainbow Effect
```cpp
#include "ColorFormat.hpp"
#include <iostream>

int main() {
    std::cout << ColorFormat::rainbow("Colorful text!") << std::endl;
    return 0;
}
```

### 3️⃣ Gradient Coloring for Numbers
```cpp
#include "ColorFormat.hpp"
#include <iostream>

int main() {
    unsigned int value = 75;
    std::cout << ColorFormat::formatGradientUnsignedInteger(value, 0, 100) << std::endl;
    return 0;
}
```

## 📖 API Reference
### ColorFormat::ColorFormat(const std::string &text, const std::string &firstFormat = "", const std::string &secondFormat = "", ...)
Applies formatting to a string.

### std::string ColorFormat::formatString(...)
Applies multiple styles and a color to text.

### std::string ColorFormat::rainbow(...)
Transforms text into a dynamic rainbow effect.

### std::string ColorFormat::formatUnsignedInteger(unsigned int number, ...)
Formats numbers by adding thousand separators.

### std::string ColorFormat::formatGradientUnsignedInteger(unsigned int number, unsigned int min, unsigned int max, ...)
Formats a number with a gradient from red to green based on a given range.

## 📝 License
This project is licensed under **GNU GPL v3**.
See [LICENSE](https://www.gnu.org/licenses/gpl-3.0.html) for details.

## 👤 Author
**Name**: Alexy Heitz
**GitHub**: [@Holistisme](https://github.com/holistisme)
**Email**: 📧 alexy.pa.heitz@gmail.com
**Created on**: 📆 2025-02-17
**Last Updated**: 📆 2025-02-18

## ⭐ Contributing
Found a bug or an improvement?
Feel free to open an issue or submit a pull request.