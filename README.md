# Astro OS - Interactive Adventure Operating System

**Astro OS** is a simple, interactive, and adventure-driven operating system designed to provide a series of challenges and activities for the user. Each task in this operating system simulates real-world operations like file creation, deletion, and basic games such as Tic Tac Toe and Hangman. The OS is designed to run on a terminal, offering an intuitive menu-based interface for users to explore various features.

## Features

- **Tower of Hanoi Challenge** - Solve the Tower of Hanoi puzzle and test your problem-solving skills.
- **Calculator** - Perform basic arithmetic operations.
- **Hangman** - Guess the letters to uncover a word and save the stick figure.
- **Number Guessing** - Guess a secret number and win rewards.
- **Video Player** - Play videos directly from the OS.
- **Quotes** - Get inspired with motivational quotes.
- **File Operations**:
  - **Create File** - Start a new digital masterpiece by creating a file.
  - **Delete File** - Delete a file and free up space.
  - **Copy File** - Copy important files and back them up.
  - **Rename File** - Give your files new identities.
- **Calendar** - Plan your days and stay organized with the built-in calendar.
- **Clock** - Check the time in real-time.
- **Tic Tac Toe** - Play against a friend in this classic game.
- **Kernel Mode** - A special feature for advanced users to interact with the system.

## Getting Started

To get started with **Astro OS**, follow the instructions below:

### Prerequisites

- **g++**: The program requires a C++ compiler to compile certain features.
- **gnome-terminal**: For terminal-based activities and managing different tasks.

### Installation

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/omi1215/https://github.com/omi1215/OS-Simulation.git
   cd astro-os
   ```

2. Compile the necessary programs:

   ```bash
   g++ -o create create.cpp
   g++ -o delete delete.cpp
   g++ -o copy copy.cpp
   g++ -o calender calender.cpp
   g++ -o clock clock.cpp
   g++ -o tictac tictac.cpp
   g++ -o rename rename.cpp
   g++ -o notepad notepad.cpp
   g++ -o kernel kernel.cpp
   ```

3. Run the program:

   ```bash
   g++ -pthread -o obj astro.cpp -lcurses
   ./obj
   ```

### Usage

- The program will prompt you with a menu of tasks to perform. Choose the number corresponding to the task you want to run.
- If the task requires additional files, the system will attempt to compile them automatically.
- You can perform file operations (create, delete, copy, rename), play games (Tic Tac Toe, Hangman), and interact with other features like the calculator, calendar, and clock.

### Example Main Menu

```text
------------------------------------------------------------
--------------- WELCOME TO THE ASTRO OS MAIN MENU ---------------
------------------------------------------------------------

Welcome to the Interactive Adventure OS!

Choose your next adventure...

Enter 1 for the Tower of Hanoi challenge! Test your skills and conquer the mystical towers!
Enter 2 for the Calculator. Let's crunch some numbers and solve equations!
Enter 3 for Hangman. Guess the word and save the poor stick figure!
Enter 4 for Number Guessing. Can you predict the secret number?
Enter 5 for the Video Player. Dive into a world of entertainment with movies and shows!
Enter 6 for to see a Quote. Get Inspired!
Enter 7 to Create a File. Unleash your creativity and start a new digital masterpiece!
Enter 8 to Delete a File. Say goodbye to the old and make room for fresh beginnings!
Enter 9 to Copy a File. Duplicate and preserve your precious memories!
Enter 10 for the Calendar. Stay organized and plan your days like a pro!
Enter 11 for the Clock. Keep track of time in style and never miss a beat!
Enter 12 for Tic Tac Toe. Challenge a friend and become the ultimate champion!
Enter 13 to Rename a File. Give your files a brand new identity!
Enter 14 for Notepad. Express your thoughts, ideas, and dreams in digital ink!
Enter 15 for Kernel Mode lets get authorized!
Enter 16 to terminate the OS. Goodbye for now!

Enter your choice: 

### Contributing

If you'd like to contribute to **Astro OS**, feel free to fork the repository, make changes, and submit a pull request. We welcome contributions to improve the features, functionality, or documentation of the project.
