# NUMP

A small (and pretty bad to be honest) numerical programming library made for `Numerical Programming` at Technische Universität München.

## Notes

If for some reason you are still interested in using this library (why?), there are some things you should know.

### Matrices

Mostly because I still have PTSD from using raw pointers in C for representing matrices at Universitat de Barcelona (yes, raw pointers), I implemented a nice class that represents a matrix together with a bunch of helpful methods, including: addition, product, equality, etc. OK, now let's go quickly over some things that should be kept in mind.

* What types can it contain? Only `double`. In the future I might implement templating for more types (e.g. float) but, honestly, probably not.
* It uses 1-based indexing :smiling_imp:. Converting all the 1-based indexed algorithms to 0 based makes my head hurt and, as I said before, this is just for me. If it makes you feel better it doesn't use the _ignore the first element_ strategy sugested during the "raw C pointers" course.

