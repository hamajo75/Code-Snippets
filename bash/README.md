# Shell scripts

## Links
[The Shell Scripting Tutorial](https://www.shellscript.sh/index.html)
[Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)

## Commands
`cmd1 && cmd2`   execute `cmd2` only if `cmd1` was successful.
`cmd1 || cmd2`   execute `cmd2` only if `cmd1` failed.

echo "Put the output of $(cmd)" right there."

Don't confuse `$()` with `${}`. The latter is for distinguishing between `${var}text` and `$vartext`.

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