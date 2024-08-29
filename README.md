# Minishell

`Minishell` is a simple shell application developed in C, mimicking some of the functionalities of the **Bash** shell. This project is part of the 42 school curriculum and is designed to deepen your understanding of system programming, process management, and the use of system calls in a UNIX-like operating environment.

## Table of Contents
- [Minishell](#minishell)
	- [Table of Contents](#table-of-contents)
	- [About the Project](#about-the-project)
	- [Features](#features)
	- [Built-in Commands](#built-in-commands)
	- [Getting Started](#getting-started)
		- [Prerequisites](#prerequisites)
		- [Installation](#installation)

## About the Project

The goal of the `Minishell` project is to create a basic shell that interprets and executes user commands in a UNIX environment. The project serves as an introduction to shell scripting and system programming, involving concepts such as process creation, input/output redirection, pipes, environment management, and signal handling.

## Features

- Display a prompt and wait for user input.
- Parse and execute commands with arguments.
- Handle the following operators: `;`, `&&`, `||`, `|`.
- Support for single quotes `'` and double quotes `"`.
- Input/output redirection using `<` and `>`.
- Implement environment variable expansion using `$`.
- Signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- Custom error handling and messaging.

## Built-in Commands

`Minishell` includes several built-in commands, including:

- `echo` - Display a line of text
- `cd` - Change the current directory
- `pwd` - Print the current working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display the current environment variables
- `exit` - Exit the shell

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- **gcc** or another C compiler installed
- **Make** build tool
- **readline** library installed (if used for input management)

### Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/4b93f/Minishell.git
   cd Minishell
