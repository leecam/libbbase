# BBase C Library

BBase is a C library that provides simple primitives and data containers, similar to the C++ Standard Template Library.

### Why not just use C++?
BBase provides a pure C API consisting solely of simple functions, no user facing complex types such as structs or classes.
As such, BBase offers greater ABI stability over direct C++ linkage. Internally BBase is coded in C++ but this is not exposed to the user.

### BBase Types

BBase has a number of object types used to represent different data structures

* BData
* BString
* BNumber
* BVector
* BMap
* BPtr

These types are all opaque pointers, their internal structure is not exposed and is only accessed via the BBase API.

### API Naming

Each type has a set of functions associated with them and they prefixed with the type name. For example the `BVector` functions include :  

    BVector_create  
    BVector_size

### Common Functions

Some function can be applied to any BBase type. They are prefixed with `BBASE_`.

The type of a BBase object can be determined at run time.

    int BBase_type(void* obj);

This will return one of the following:

    BTYPE_INVALID 0
    BTYPE_STRING  1
    BTYPE_VECTOR  2
    BTYPE_DATA    3
    BTYPE_NUMBER  4
    BTYPE_MAP     5

BBase types can also be compared using:

    // Returns non-zero if lhs == rhs.
    // Values of different types are not equal.
    int BBase_equal(void* lhs, void* rhs);

    int BBase_compare(void* lhs, void* rhs);


### Vectors and Maps

Vectors and Maps are a pain in C. Returning a list of strings from a function is fiddly and the caller has a hard time freeing it.

BBase makes this simple. A Vector can store any BBase type, including other BVector or BMap objects.

Vectors can be created using:

    BAutoFree BVector vec = BVector_create();

Once created BBase objects can be added it, e.g:

    BAutoFree BString str_obj = BString_create("YO");
    BVector_pushBack(vec, str_obj);

Vectors take a reference to the objects contained within it, not a copy. This is to avoid the needless copying that would happen in C during the common paradigm of creating an object then adding it to a vector.

Maps work in a similar way. The following can be used to add a data buffer to a map with a BString key.

    BAutoFree BString key = BString_create("key");
    BAutoFree BData val = BData_create(buf, len);

    BAutoFree BMap map = BMap_create();
    BMap_insert(map, key, val);

Keys and values can be of any BBase type. Values can be looked up by key

    BData ref1 = BMap_find(map, key);

### JSON
Any of the BBase types can be converted to JSON using:

    BString BBase_createJson(void* obj);

This works well for `BMap` and `BVector` types.
See the example code which converts a map containing a vector list of maps.

### Memory Management
Once created BBase types need to be freed. Memory is assigned when the API calls have create in the name. Anytime you obtain an object via a create call it needs to be freed. When obtaining an object via non-create calls, such as `BVector_at()`, the values need not be freed.

Internally BBase will automatically manage references. So if a BString is created and then added to a BVector it is safe to free the BString and the BVector will continue to hold a reference. When the BVector is freed the BString within it will be then freed (if no other object holds a reference)

Once a object is created it can freed in two ways.

* Manually by the called using BBase_free().


    BString obj = BString_create("YO");
    BBase_free(obj);

* Automatically using BAutoFree


    BAutoFree BString obj = BString_create("YOI");

BAutoFree can be used when declaring any BBase type and will automatically free a BBase object when it goes out of scope. Do not use this on non-BBase types.

See Example code and unit tests where BAutoFree is used throughout.
