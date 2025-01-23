# Minishell

Minishell is a minimal implementation of a Unix shell, built as part of the 1337 common core curriculum. It was developed collaboratively by [ohssineabdelfatah](https://github.com/ohssineabdelfatah) and [ilaasri](https://github.com/iliass-laa). This project showcases our understanding of process management, system calls, and shell scripting.

## Features

- **Command Execution**: Executes commands with arguments (e.g., `ls -l`, `echo Hello`).
- **Pipes**: Supports pipes to link commands (e.g., `ls | grep minishell`).
- **Redirections**: Handles input and output redirection (e.g., `cat < file.txt > output.txt`).
- **Environment Variables**: Supports export, unset, and variable expansion (e.g., `export VAR=value`, `echo $VAR`).
- **Heredoc**: Implements here-document syntax (e.g., `cat << EOF`).
- **Builtin Commands**: Implements built-in commands like `cd`, `pwd`, `env`, `export`, `unset`, and `exit`.
- **Signal Handling**: Properly handles `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- **Error Handling**: Provides descriptive error messages for invalid commands or syntax.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```
2. Compile the shell:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

## Usage

Minishell behaves like a typical Unix shell. Here are some examples:

- Run a command:
  ```bash
  minishell$ ls -l
  ```

- Use pipes:
  ```bash
  minishell$ cat file.txt | grep keyword
  ```

- Redirect input/output:
  ```bash
  minishell$ grep minishell < input.txt > output.txt
  ```

- Export and use environment variables:
  ```bash
  minishell$ export NAME=Minishell
  minishell$ echo $NAME
  Minishell
  ```

- Use here-documents:
  ```bash
  minishell$ cat << EOF
  > Hello, world!
  > EOF
  Hello, world!
  ```

## Project Structure

- `src/`: Source code files for Minishell.
- `includes/`: Header files.
- `Makefile`: Build system for the project.

## Acknowledgments

This project was completed as part of the 1337 common core curriculum. Special thanks to the 42 Network for the inspiration and guidance.

## Authors

- [ohssineabdelfatah](https://github.com/ohssineabdelfatah)
- [ilaasri](https://github.com/iliass-laa)

## License

This project is licensed under the [MIT License](LICENSE).

## Contributing

Contributions are welcome! Feel free to fork the repository and submit a pull request.
