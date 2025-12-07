# C++ Console Multi-Wordle

A terminal-based game where a single player tackles multiple, simultaneous Wordle boards at once. Test your vocabulary and deductive reasoning skills by managing several word puzzles in a single command-line interface session!

## 🚀 Features

*   **Simultaneous Boards:** Play multiple, independent Wordle games displayed stacked in your console.
*   **Classic Wordle Mechanics:** Use color-coded feedback (e.g., green, yellow, grey text) to guess letters.
*   **Configurable Difficulty:** The number of simultaneous boards can be changed.
*   **Pure C++ Console App:** Lightweight and self-contained, requiring no external dependencies or internet connection.

## ⬇️ Installation and Setup

To play the game, you need to download and run the pre-compiled executable for your operating system.

### Prerequisites

*   A compatible operating system (Linux).
*   A terminal or command prompt application with support for ANSI color codes for optimal viewing (most modern terminals support this).

### How to Run the Game

1.  **Download:** Get the latest executable from the [Releases page](https://github.com/Aaron-c/lilyPython) or download it directly from the [itch.io page](ADD_YOUR_ITCH_IO_URL_HERE).
2.  **Navigate:** Open your terminal or command prompt and go to the directory where you downloaded the executable.
3.  **Execute:** Run the game using the appropriate command for your system:
    *   **Linux:**
        ```bash
        ./multi_wordle_linux
        # If necessary, first make it executable with: chmod +x multi_wordle_linux
        ```

    ```bash
    .\multi_wordle_win.exe words.txt
    ```

## 🎮 How to Play

The objective is to solve all active Wordle boards simultaneously.

*   **Input:** Type a 5-letter word and press `Enter`. This single guess is applied to *all* active boards at the same time.
*   **Feedback:** Each board updates independently with standard Wordle feedback:
    *   **Green:** Correct letter in the correct spot.
    *   **Yellow:** Correct letter in the wrong spot.
    *   **Grey:** Letter is not in the word.
*   **Winning:** Continue guessing until all boards successfully reveal their hidden words within the maximum number of attempts.
