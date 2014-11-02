# Pipe Three Chain

This program forks three children, and chains them together in a
series of pipes. Specifically, it:

* Invokes `cat` to read a file containing a list of words, some of
which are repeated; and

* Pipes the output to `uniq`, which outputs the count of words in
the file; and then

* Pipes the output of `uniq` to `sort`, which sorts that count of words
and writes it to standard output.
