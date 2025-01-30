# Common Lisp

## Install
See: https://lisp-lang.org/learn/getting-started/

Common Lisp Implementation (Steel Bank Common Lisp)

    apt install sbcl

Packet Manager Quicklisp

    curl -o /tmp/ql.lisp http://beta.quicklisp.org/quicklisp.lisp
    sbcl --no-sysinit --no-userinit --load /tmp/ql.lisp \
         --eval '(quicklisp-quickstart:install :path "~/.quicklisp")' \
         --eval '(ql:add-to-init-file)' \
         --quit

This will install Quicklisp to the ~/.quicklisp/ directory.

## Syntax
- Syntax is made up of symbolic expressions (S-expressions).
- An S-expression is either an atom or a list.

**Basic Elements**
- Atoms: numbers, keywords, symbols
- Lists: Enclosed in (), e.g. `(func arg1 arg 2)`

**Quoting**
- Prevent evaluation

        '(1 2 3)  ;use as data only, dont eval

