# Shell scripts

## Links
- [The Shell Scripting Tutorial](https://www.shellscript.sh/index.html)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)

## Commands
`cmd1 && cmd2` execute `cmd2` only if `cmd1` was successful.
`cmd1 || cmd2` execute `cmd2` only if `cmd1` failed.

echo "Put the output of $(cmd)" right there."

Don't confuse `$()` with `${}`. The latter is for distinguishing between `${var}text` and `$vartext`.

### Redirections

## Quoting

- Single quotes: 'no substitution'
- Double quotes: "$variables will be substituted"

## Differences between: () (()) [] [[]]

- `[[` can do everything `[` can. Try to use `[[`.
- `$(cmd)` substitute command output.
- `( cmd1, cmd2 )` group commands and run them in a subshell (note the spaces!).
- `{ cmd1, cmd2 }` group commands and run them in the current shell (note the spaces!).
- `((` compound command for evaluating arithmetic expressions `$((3 + 2))`.
- `{h,d}ump` expands to hump, dump.


## Special Variables

- `$0` Name of the script.
- `$?` Exit status of the most recent command.
- `$!` Process Id of the most recent command placed in background.
- `$*` Parameters as one single string.
- `$@` Parameters as individual strings (to be passed to a function).
- `$#` Nr. of parameters.

## Shell Builtin Commands
- [Bash Reference Manual - 4.3.1 The Set Builtin](https://www.gnu.org/software/bash/manual/bash.html#The-Set-Builtin)

- `set -e` Exit immediately on error.
- `set -x` Print trace info (Useful for debugging).
- `set -m` Enable Job Control.

## Job Control
- [Bash Reference Manual - 7 Job Control](https://www.gnu.org/software/bash/manual/html_node/Job-Control.html)

All processes of the same pipeline are members of the same job.