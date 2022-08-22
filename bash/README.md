# Shell scripts

## Links
[The Shell Scripting Tutorial](https://www.shellscript.sh/index.html)

## Commands

echo "Put the output of $(cmd)" right there."

Don't confuse `$()` with `${}`. The latter is for distinguishing between `${var}text` and `$vartext`.

## Special Variables

- `$0` Name of the script.
- `$?` Exit status of the most recent command.
- `$!` Process Id of the most recent command placed in background.
- `$*` Parameters as one single string.
- `$@` Parameters as individual strings (to be passed to a function).
- `$#` Nr. of parameters.