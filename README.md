# nclass

[tested on Linux and Mac]

Orthodox Canonical Class Form generator. Made to make my life a bit easier by letting it generate the basic setup stuff of C++ classes for me.

Usage:

`nclass [options] [classname]`

To get a promt to enter classname and members:

`nclass`

To quickly generate a class with .h and .cpp file:

`nclass ClassName`

To overwrite previously existing file add the '-o' flag:

`nclass -o ClassName`

Possible future plans:

- auto includes
- default values for members
- generate more constructors
