minishell is a 42 team project aimed at developing a mini bash. i was responsible for building the parser, some of the built-in commands, handling signals and garbage collection, and tetsing

## the requirements
- custom prompt and history: shows that the user is using minishell and waits for user input, up arrow key displays previous prompt
- command execution: supports both system commands (`ls`, `grep`, etc.) and
- built-in commands:
  - `echo` (with `-n` support)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- pipes (`|`) and **redirections** including here documents (`<`, `>`, `>>`, `<<`)
- environment variables with proper expansion (`$USER`, `$PATH`, `$?`, etc.)
- signal handling for **`ctrl-c`**, **`ctrl-d`**, and **`ctrl-\`**
- error handling for invalid syntax and edge cases

## [42_minishell_tester](https://github.com/zstenger93/42_minishell_tester) result

<img width="579" alt="tester result" src="https://github.com/user-attachments/assets/b8c73eb5-1ccc-4f13-9a24-9cea6977771f" />
