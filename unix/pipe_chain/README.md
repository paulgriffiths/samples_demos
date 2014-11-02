# Pipe Chain

This program forks two children, and pipes the standard output of
one of them to the standard input of the other. Specifically, it:

* Invokes `cat` to read a file containing a list of words, some of
which are repeated; and

* Pipes the output to `uniq`, which prints the count of words in
the file.
