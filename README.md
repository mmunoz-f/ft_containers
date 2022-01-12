# ft_containers

The containers of the STL (standard template library) let us work with data structure and functions, such as vectors, maps, lists… etc. These containers are really useful and you will find them in many other projects, not only in C/C++ but also in many JS or python code.

Here I reimplemented the basics of four of them:

- The vector/stack container let us work with a dynamic array of elements, it stores any type of data as it is a template, allocating it on the dynamic memory, reallocating and deleting it when necessary, it allows the programmer to store a non specified amount of elements in the same structure.

- The map/set stores the data in different nodes which are connected between them creating a binary tree, in this case I use a red black tree, which regulates itself in order to avoid the branches to be unbalanced, this means it will find elements more efficiently, see how red blacck trees work for more info.
