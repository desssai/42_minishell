# minishell

## Overview

## Usage

1. Install `readline` library for your cpu architecture by downloading source files or by using brew.
```
brew install readline
```
2. Clone the repository.
3. Change the following lines in the Makefile to wherever your readline library is.
```
RL_LIB	=	/opt/homebrew/opt/readline/lib
RL_INC	=	/opt/homebrew/opt/readline/include
```
3. Compile the program using Makefile.
4. Launch the program.

![Installing](https://user-images.githubusercontent.com/75085822/205630953-c8e02e04-f3f7-49a9-935e-e2f33eeb4f95.gif)

The Makefile rules are as follows:

| Rule | Despription |
| ---- | ----------- |
| ALL | Compiles the program using GCC. |
| BONUS | Compiles the program the same way 'ALL' does. |
| CLEAN | Removes object files leaving only the executable present. |
| FCLEAN | Removes both the executable and object files. |
| RE | Recompiles the program using **CLEAN** and **ALL** Makefile rules |

## Features

The program works with all of the redirection modes.
| Mode | Despription |
| ---- | ----------- |
| << | Read from standard input until LIMITER. If here_doc keywoard is used for the input_file. |
| < | Read from an input file. |
| \> | Erase the file's content and write to an output file. |
| \>> | Append to an output file. |

- `minishell` is able to parse input with both single quotes `' '` and double quotes `" "`.
All of the possible combinations of them are handled by the program.

- The program doen't interpret unclosed quotes or special characters such as `\` (backslash), `;`
(semicolon), `&&` and `||` (with parenthesis for priorities.). Parsing error is thrown if a quote 
is not closed or if a special character is read.

- The program has a working history of commands.

- The program supports pipes `|`. Every command inside `minishell` is executed in a child process with
the parent process overseeing the execution. The output of each command in the pipeline is
connected to the input of the next command via a pipe.

- Internally, `minishell` stores a clone of environment variables. Therefore, all the environment variables ($ followed by
a sequence of characters which should expand to their values) are handled by the program. Setting, changing or 
deleting environment variables inside `minishell` doesn't affect those of your terminal's shell.

- `$?` expands to the exit status of the most recently executed foreground pipeline.

- Wildcards in the current working directory `*` are also supported.

- The program handles signals such as `ctrl-C`, `ctrl-D` and `ctrl-\` which behave like in bash.

minishell has several built-in executables:
| Function | Description |
| -------- | ----------- |
| echo with option -n | displays a line of text/string in standard output. -n flag does it with a newline. |
| cd with a relative or an absolute path | changes the current directory. |
| pwd with no options | prints working directory. |
| export with no options | sets or amends an environment variable. |
| unset with no options | unsets an environment variable. |
| env with no options or arguments | lists all the current environment variables. |
| exit with no options | exits minishell. |

Other commands are executed using execve with their appropriate path. 
In case there is no such command, an error is displayed in the terminal.
