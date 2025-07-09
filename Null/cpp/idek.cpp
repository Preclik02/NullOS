#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <thread>

// Terminal editor - Improved minimal elegant CLI IDE with smoother cursor behavior

// Enable raw input mode (disable canonical and echo)
void enableRawMode(termios& orig_termios) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);     // Disable line buffering and echo
    raw.c_cc[VMIN] = 1;                  // Minimum number characters for noncanonical read
    raw.c_cc[VTIME] = 0;                 // Timeout for noncanonical read (tenths of seconds)
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Restore terminal settings when exiting
void disableRawMode(termios& orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// Read one character from stdin
char getch() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

// Clear terminal screen (ANSI escape sequence)
void clearScreen() {
    std::cout << "\033[2J\033[H";
}

// Move cursor to specific row, col (0-based)
void moveCursor(int row, int col) {
    std::cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
}

// Draw a status bar at bottom of the viewport with filename and cursor info
void drawStatusBar(const std::string& filename, int row, int col, int totalRows, int cols) {
    std::cout << "\033[7m"; // Invert background and foreground for status bar
    std::string status = " File: " + filename + " | Ln " + std::to_string(row + 1) + ", Col " + std::to_string(col + 1);
    std::string instructions = " ESC:Save & Run | Ctrl+C:Exit ";
    std::string fullStatus = status + instructions;

    if ((int)fullStatus.size() < cols) {
        fullStatus += std::string(cols - fullStatus.size(), ' ');
    } else {
        fullStatus = fullStatus.substr(0, cols);
    }

    std::cout << fullStatus;
    std::cout << "\033[0m"; // Reset color/style
}

// Load file lines into buffer vector (empty line if file not found or empty)
void loadFile(const std::string& filename, std::vector<std::string>& buffer) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            buffer.push_back(line);
        }
        file.close();
    }
    if (buffer.empty()) {
        buffer.push_back("");
    }
}

// Save buffer back to file
void saveFile(const std::string& filename, const std::vector<std::string>& buffer) {
    std::ofstream file(filename);
    for (const auto& line : buffer) {
        file << line << "\n";
    }
    file.close();
}

// Compile and run source file, show message after
void compileAndRun(const std::string& filename) {
    std::string command = "g++ \"" + filename + "\" -o temp.out && ./temp.out";
    system(command.c_str());
}

// Render the editor viewport with line numbers, current line highlight, and cursor highlight with blinking effect
void render(const std::vector<std::string>& buffer, int cursorRow, int cursorCol, int scrollOffset, int viewportHeight, int viewportWidth, bool blinkOn) {
    clearScreen();
    int endLine = std::min(scrollOffset + viewportHeight, static_cast<int>(buffer.size()));

    for (int i = scrollOffset; i < endLine; ++i) {
        // Print line number padded right, dim color
        std::string lineNum = std::to_string(i + 1);
        const int lineNumWidth = 5;
        if ((int)lineNum.size() < lineNumWidth)
            lineNum = std::string(lineNumWidth - lineNum.size(), ' ') + lineNum;

        // Highlight current line background with faint gray if i == cursorRow
        if (i == cursorRow) {
            std::cout << "\033[48;5;250m"; // light gray background for current line
        }

        std::cout << "\033[90m" << lineNum << " \033[0m";  // Gray color for line numbers

        const std::string& line = buffer[i];
        if (i == cursorRow) {
            // Print line with cursor highlighted character + blinking
            int len = (int)line.size();
            if (cursorCol > len) cursorCol = len;
            std::cout << "\033[48;5;250m\033[37m"; // keep current line bg + light gray text

            if (cursorCol > 0)
                std::cout << line.substr(0, cursorCol);

            if (cursorCol < len) {
                if (blinkOn) {
                    // Highlight character under cursor: white text on subtle blue background
                    std::cout << "\033[1m\033[44m" << line[cursorCol] << "\033[0m\033[48;5;250m\033[37m";
                } else {
                    // Show cursor char normal when blink off (invisible effect)
                    std::cout << line[cursorCol];
                }
                std::cout << line.substr(cursorCol + 1);
            } else {
                // Cursor at line end: show blinking underscore cursor with highlight
                if (blinkOn) {
                    std::cout << "\033[1m\033[44m_\033[0m\033[48;5;250m\033[37m";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "\033[0m\n";
        } else {
            // Print line normally in dim text with no bg
            std::cout << "\033[0m" << line << "\n";
        }
    }

    // Fill the rest of viewport with ~ in dim gray with no background
    for (int i = endLine; i < scrollOffset + viewportHeight; ++i) {
        std::string lineNum = std::to_string(i + 1);
        const int lineNumWidth = 5;
        if ((int)lineNum.size() < lineNumWidth)
            lineNum = std::string(lineNumWidth - lineNum.size(), ' ') + lineNum;
        std::cout << "\033[90m" << lineNum << " \033[0m";
        std::cout << "\033[90m~\033[0m\n";
    }

    // Move cursor accounting for line number width + 1 space = 6 cols offset
    moveCursor(cursorRow - scrollOffset, cursorCol + 6);

    // Draw status bar (assume viewport width available)
    drawStatusBar("YourFile", cursorRow, cursorCol, (int)buffer.size(), viewportWidth);
}

int main() {
    termios orig_termios;
    enableRawMode(orig_termios);

    std::cout << R"(
 _     _      _     
(_)   | |    | |    
 _  __| | ___| | __ 
| |/ _` |/ _ \ |/ / 
| | (_| |  __/   <  
|_|\__,_|\___|_|\_\
)" << std::endl << std::endl;

    std::string filename;
    std::cout << "Filename: ";
    std::getline(std::cin, filename);

    std::vector<std::string> buffer;
    loadFile(filename, buffer);

    int row = 0;
    int col = (buffer.empty() ? 0 : (int)buffer[0].size());
    const int viewportHeight = 25;
    const int viewportWidth = 80; // Fixed width for now, could be dynamic
    int scrollOffset = 0;

    bool blinkOn = true;
    auto lastBlink = std::chrono::steady_clock::now();

    render(buffer, row, col, scrollOffset, viewportHeight, viewportWidth, blinkOn);

    while (true) {
        // Check and toggle blink every ~500ms
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> diff = now - lastBlink;
        if (diff.count() >= 500) {
            blinkOn = !blinkOn;
            lastBlink = now;
            render(buffer, row, col, scrollOffset, viewportHeight, viewportWidth, blinkOn);
        }

        // Use non-blocking check for input available using select with 100ms timeout
        fd_set set;
        struct timeval timeout;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100ms

        int rv = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout);
        if (rv == -1) {
            // Error reading input
            disableRawMode(orig_termios);
            std::cerr << "Error reading input" << std::endl;
            break;
        } else if (rv == 0) {
            // Timeout - no input, continue blinking loop
            continue;
        }

        char ch = getch();

        if (ch == '\033') { // Handle arrow keys and ESC
            char next1 = getch();
            if (next1 == '[') {
                char dir = getch();
                switch (dir) {
                    case 'A': if (row > 0) row--; break;            // Up
                    case 'B': if (row < (int)buffer.size() - 1) row++; break; // Down
                    case 'D': if (col > 0) col--; break;            // Left
                    case 'C': if (col < (int)buffer[row].size()) col++; break; // Right
                }
            } else {
                // ESC pressed alone = save, compile, run, then exit
                saveFile(filename, buffer);
                clearScreen();
                std::cout << "Saved. Compiling...\n\n";
                disableRawMode(orig_termios);
                compileAndRun(filename);
                std::cout << "\n\nDone. Press Enter to exit.\n";
                std::cin.get();
                break;
            }
        } else if (ch == 3) { // Ctrl+C exit without saving
            clearScreen();
            disableRawMode(orig_termios);
            std::cout << "Editor exited without saving." << std::endl;
            break;
        } else if (ch == 127 || ch == 8) { // Backspace
            if (col > 0) {
                buffer[row].erase(col - 1, 1);
                col--;
            } else if (row > 0) {
                col = (int)buffer[row - 1].size();
                buffer[row - 1] += buffer[row];
                buffer.erase(buffer.begin() + row);
                row--;
            }
        } else if (ch == '\n' || ch == '\r') { // Enter key
            std::string newLine = buffer[row].substr(col);
            buffer[row] = buffer[row].substr(0, col);
            buffer.insert(buffer.begin() + row + 1, newLine);
            row++;
            col = 0;
        } else if (ch == '\t') { // Tab inserts 2 spaces
            buffer[row].insert(col, "  ");
            col += 2;
        } else if (isprint(ch)) {
            buffer[row].insert(buffer[row].begin() + col, ch);
            col++;
        }

        // Clamp cursor positions
        if (row < 0) row = 0;
        if (row >= (int)buffer.size()) row = (int)buffer.size() - 1;
        if (col < 0) col = 0;
        if (col > (int)buffer[row].size()) col = (int)buffer[row].size();

        // Smooth scrolling: keep cursor line centered as possible with edge bounds
        int halfView = viewportHeight / 2;
        if (row < halfView) {
            scrollOffset = 0;
        } else if (row > (int)buffer.size() - halfView) {
            scrollOffset = std::max(0, (int)buffer.size() - viewportHeight);
        } else {
            scrollOffset = row - halfView;
        }

        render(buffer, row, col, scrollOffset, viewportHeight, viewportWidth, blinkOn);
    }

    return 0;
}


