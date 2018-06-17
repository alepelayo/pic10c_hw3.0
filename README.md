## Ring Queue

The ring queue, similarly to a regular queue, contains functions `size`, `pop_front`, `push_back`, `front`, and `back. However, since
this specific queue is a ring rather than a stack-like container, the starting element of a ring queue can continuously change. 

In order to keep track of this changing starting element, the use of `buffer`, an int for the number of elements from the starting element, 
is changed and handled with. 

### Iterator/Const_Iterator Classes

In addition to the usual "pic10A" way to go through queue where a for loop goes up to `ring_queue.size()`, this ring queue allows 
`iterators` and `const_iterators` to be used when looping through the entire ring. 

Because of the creation of the `iterator` and `const_iterator` classes, this ring queue also contains `.begin()` and `.end()` member functions
which can easily find the first and last element of the ring queue. 

In addition to `.begin()` and `.end()` member functions, both `iterator` and `const_iterators` classes contain the more common operators:

- `operator!=()`: Comparison operator
- `operator++()`: incrimentation operator
- `operator*()`: dereferencing operator


Original assignment description:
- http://pic.ucla.edu/~rsalazar/pic10c/assignments/hw3/index.html
