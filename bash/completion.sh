#!/bin/bash

# Bash completion
#
# How it works:
# - <Tab> is handled by readline. Bash takes the command name (first word) and looks up the
#   completion spec ("compspec") registered for it with the builtin `complete`.
# - No compspec: default completion, i.e. command names for the first word, file names otherwise.
# - A compspec says where candidates come from, e.g.
#     -W "words"  a word list
#     -F func     a shell function that computes the candidates
#     -C cmd      an external command that prints the candidates
#     -A action   built-in generators: file, directory, hostname, command, variable, ...
#     -o option   behaviour tweaks: -o default (fall back to file names), -o nospace, ...
# - The candidates are filtered by the word being completed. One match: bash inserts it.
#   Several matches: bash inserts the common prefix, a second <Tab> lists them all.
# - The -W word list is expanded each time <Tab> is pressed, so with single quotes
#   complete -W '$(cmd)' runs cmd on every <Tab>; with double quotes it runs once at definition.
# - `compgen` takes the same options as `complete` but prints the matches to stdout.
#   Use it inside completion functions, or to test a compspec on the command line.
# - Completion functions run in the current shell: keep them fast and don't change global state.
# - The bash-completion package (sourced from ~/.bashrc) ships completions for many commands in
#   /usr/share/bash-completion/completions/. It loads them lazily: on the first <Tab> for a
#   command it sources the file named after the command, looking first in
#   ~/.local/share/bash-completion/completions/.
#
# Try it:     source completion.sh, then type "greet <Tab><Tab>" or "deploy_demo -b <Tab><Tab>"
# Permanent:  put the complete line (and function) into ~/.local/share/bash-completion/completions/<command>.

# 1) Static word list: same candidates for every argument
greet() { echo "Hello $*"; }
complete -W "alice bob carol" greet   # registers a compspec for the command "greet" that offers the three names as candidates

# 2) Completion function: candidates depend on the previous word
#    $2         word being completed
#    $3         previous word
#    COMP_WORDS all words on the command line, COMP_CWORD index of the word being completed
#    COMPREPLY  array of candidates bash offers
#    compgen -W "words" -- "$2" filters the words that start with $2
deploy_demo() { echo "deploying $*"; }
complete_deploy_demo() {
  case $3 in
    -b) COMPREPLY=($(compgen -W "intercom router" -- "$2")) ;;
    *)  COMPREPLY=($(compgen -W "-b gas-daemon camera-daemon" -- "$2")) ;;
  esac
}
complete -F complete_deploy_demo deploy_demo

# Show what is registered for a command: complete -p deploy_demo
