#include <iostream>

// Forward declaration
template <typename ItemType, int capacity>
class RingQueue;



template <typename ItemType, int capacity>
class RingQueue {

    // Nested Forward declaration of RingQueue<ItemType, capacity>::iterator
    // This is needed if one plans to turn this home-made iterator into
    // one of the special categories of iterators (e.g., input, output,
    // forward, etc.).
public:
    class iterator;

    // Aliases.
    typedef ItemType* pointer;
    typedef ItemType& reference;


    // Definition of RingQueue<ItemType, capacity>::iterator
public:
    class iterator {
    private:
        // A link to the parent container
        RingQueue* parent;

        // The position within the RingQueue is determined
        // by how far ahead we are from the begining of the
        // queue.
        int offset;

    private:
        // Main iterator constructor
        iterator(RingQueue* _parent, int _offset = 0): parent(_parent), offset(_offset) { }


        // It is quite common for Containers and their iterators
        // to be friends. After all, they should work closely together.
        friend class RingQueue<ItemType, capacity>;


    public:
        //Dereferencing operator (*)
        ItemType& operator*() {
            return parent->buffer[(parent->begin_index + offset)% capacity];
        }

        //Pre-incrementing
        iterator& operator++() {
            ++(offset);
            return *this;
        }

        //Post-incrementing
        iterator operator++(int unused) {
            iterator copy(*this); //creating a copy of original
            ++(*this);
            return copy;
        }

        //Comparison operator (==)
        bool operator==(const iterator& rhs) const {
            //Both the offset and parent must be equal in order for them to be completely equal
            return ((rhs.offset == offset) && (rhs.parent == parent));
        }
        //Comparison operator (!=)
        bool operator!=(const iterator& rhs) const {
            //Either the offset or the parent must be equal in order for them to be unequal
                return (!(*this == rhs));
        }

    };

//CONST_ITERATOR CLASS WITH MEMBER FUNCTIONS/OPERATION OVERLOADS

    class const_iterator{

        private:
        RingQueue* parent;
        int offset;

        // It is quite common for Containers and their iterators
        // to be friends. After all, they should work closely together.
        friend class RingQueue<ItemType, capacity>;

        public:
        // Main iterator constructor
        const_iterator(RingQueue* _parent, int _offset = 0): parent(_parent), offset(_offset) { }

        //Dereferencing operator (*)
        ItemType& operator*() {
        return parent->buffer[(parent->begin_index + offset)% capacity];
        }

        //Pre-incrementing
        const_iterator& operator++() {
        ++(offset);
        return *this;
        }

        //Post-incrementing
        const_iterator operator++(int unused) {
        const_iterator copy(*this); //creating a copy of original
        ++(*this);
        return copy;
        }

        //Comparison operator (==)
        bool operator==(const const_iterator& rhs) const {
        //Both offset and parent must be equal in order for them to be completely equal
        return (rhs.offset == offset && rhs.parent == parent);
        }

        //Comparison operator (!=)
        bool operator!=(const const_iterator& rhs) const {
        //Either the offset or the parent must be equal in order for them to be unequal
        return (!(*this == rhs));
        }

    };

    // Friendship goes both ways here.
    friend class iterator;
    friend class const_iterator;



private:
    // A fixed-size static array with constant capacity that represents
    // the RingQueue
    ItemType buffer[capacity];

    // The starting index. It changes according to a very
    // specific set of rules (below).
    int begin_index;

    // The actual size of the RingQueue. Not to be confused with
    // its capacity.
    int ring_size;



    // A helper function that computes the index of 'the end'
    // of the RingQueue
    int end_index() const {
        // Replace the line(s) below with your code.
        return ((begin_index + ring_size) % capacity);
    }



public:
    // Constructor
    RingQueue() : begin_index(0), ring_size(0) { }

    // Accessors. Note: 'back()' is not considered part of the array.
    ItemType front() const {
        if (ring_size == 0) std::cerr << "Warning: Empty ring!\n";

//        else {
            return buffer[begin_index];
//        }

        // Replace the line(s) below with your code.
 //       return buffer[0];
    }
    ItemType back() const {
        if (ring_size == 0) std::cerr << "Warning: Empty ring!\n";

        else {
            return buffer[((begin_index + ring_size) % capacity)-1];
        }
    }



    // Mutators
    void push_back(const ItemType& value) {
        //if the ring has reached max capacity
        if (ring_size == capacity) {
            //push to the beginning of ring
            buffer[begin_index] = value;
            ++(begin_index); //moves the beginning index if there is an overlap of elements
        }
        else {
            //push to the end of ring and increase ring size
            buffer[(begin_index + ring_size) % capacity] = value;
            ++(ring_size);
        }
    }
    //NEW STUFF
    void pop_front() { //added this
        if(ring_size==0) {
            std::cout << "You cannot pop_front an empty queue!" << std::endl;
        }
        else {

        }
        --ring_size;
        ++begin_index;

    }

    // Functions that return iterators
    iterator begin() {
        return iterator(this, 0); //offset must be 0 in order to retrieve first element
    }
    iterator end() {
        return iterator(this, ring_size); //offset must be the size of the queue
    }

    //// Functions that return const_iterators
    //const_iterator begin() {
    //	return const_iterator(this, 0); //offset must be 0 in order to retrieve first element
    //}
    //const_iterator end() {
    //	return const_iterator(this, ring_size); //offset must be the size of the queue
    //}

    // Miscellaneous functions
    size_t size() const {
        return ring_size;
    }

    // Debugging functions
    void dump_queue() const {
        std::cout << "Raw queue...\n";
        for (size_t i = 0; i < capacity; ++i)
            std::cout << "Val: " << buffer[i] << ", at: " << buffer + i << '\n';
        std::cout << '\n';
        return;
    }

};

int main() {
    RingQueue<int, 7> rq;

    rq.dump_queue(); //this current dump_queue is being weird

    for (int i = 0; i < 8; ++i)
        rq.push_back(i + 1);

    rq.dump_queue();

    std::cout << rq.front() << std::endl; //should be 2
    std::cout << rq.back() << std::endl; //should be 8

    rq.pop_front();

    rq.dump_queue();


    //std::cout << "Queue via size: \n";

    RingQueue<int,7>::iterator it = rq.begin() ;
    //auto it = rq.begin();
//    for (size_t i = 0; i < rq.size(); ++i) {
//        std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
//        ++it;
//    }
//    std::cout << '\n';



    // Uncomment the block below only when you have a working
    //implementation of RingQueue<ItemType,int>::end().
    // If the implementation is not correct, it might result in
    // an infinite loop.

    std::cout << "Queue via iterators: \n";
    for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
    std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
    }
    std::cout << '\n';

    std::cout << rq.front() << std::endl; //should be 3
    std::cout << rq.back() << std::endl; //should be 8


    //rq.dump_queue();

    std::cin.get();
    std::cin.get();

    return 0;
}
