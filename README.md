# Fibonacci Heap Static Library
### Usage
```cpp
#include <FibonacciHeap/FibHeap.hpp>

int main() {
    //...   
}
```

### CMakeList.txt
- As subproject
${PATH} = path to the root directory that containe FibonacciHeap as submodule
```cmake
add_subdirectory(${PATH})
                                          	       # create target 
target_link_libraries(${TARGET} PRIVATE FibonacciHeap) # add include path to a compiler
```