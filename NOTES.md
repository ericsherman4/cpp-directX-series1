# Classes
- constant keyword after a function decl (you also need in the cpp file as well) in a class means that the function will not change the internal state of an object (wont change any member variables)
- think about making getters and think even harder about making setter functions. an alternative is make a function such as like update() that will act on the private members of the class. see tutorial 12. Basically, try doing whole operations inside of member functions so that you don't need to do get and set. 

### Initializer lists and Constructors
If you have objects embedded in a class, you can initialize them in the class' constructor. 
i.e
```C++
class Game
{
private:
    Some_Other_Object obj1;
    Some_Other_Object obj2;
};

Game::Game()
    :
    obj1(args),
    obj2(args)
{
    // Constructor Body
}

```
**The order of the execution of the initializer list has nothing to do with the order in which they appear in the constructor, but purely depend on the order of which they the member variables are declared.**

What if you need to do some things in the constructor before initializing the object? 
If the "things" is in the form of creating other objects such as RNG and passing them in, you can make the RNGs private members of the Game class and then including them in the initializer list. 

What if you can't get around this? If you need some sort of logic before calling constructors? 

Say now we have: 

```C++
class Game
{
private:
    static constexpr nObj = 1000;
    Some_Other_Object objs[nObj];
};

Game::Game()
    :
    obj1(args), // Can no longer do this. 
    obj2(args) // Can no longer do this. 
{
    // Constructor Body
    // Now the default constructor (no args) (more details below about this) will be called on all of the Some_Other_Objects objects. 
}

```

In this case, it's best to provide an init function for the object that does the same thing as a constructor would do. 

TWO PROBLEMS WITH THIS:
1. breaks encapsulation. If an init function mostly initializes member variables, then this is allowing a way for an external thing to modify Poo internals directly. Same as basically just making a bunch of setter functions. 
One way around this is to make an private initialized variable that you check in the init method either through an if statement or using an assert statement.

**Note**: You want to avoid using assert's in production code as it slows things down (release vs debug mode in Visual Studio Community)
1. Leaves potential for you to make an object and forget to initialize it! You can add assert statements in objects other member functions to provide some checks against this. 

**However, there are ways to avoid all of this in the future.**

### More Initializer Things

You can initialize member variables directly with initializer lists like so:

```C++
Class Target
{
public:
    Target(int in_x, int in_y)
    :
    x (in_x),
    y(in_y)
    {
        //empty
    }

private:
    int x;
    int y;
}

```

#### Default Constructors

No arguments, automatically provided by the class, UNLESS, you provide a constructor that has arguments. If you do so, then there is no default constructor.


### Keyword Static

Data members that are static will not belong to any one object, they belong to the class (or all the objects).
A static function means a function that can be called without needing an object of the class to call it. You can just do `Class_Name.Static_Function();`

When specifying static on a function, you do not specify it in the definition, only specify static in the header file (the declaration).


### Access Specifiers
- Member data and functions are private by default if its not specified 


### Nested Classes
- They're a thing! Good for hiding implementation of a class from everything else, especially of only one other class depends on it. 
```C++
class Car
{
private:
    class Engine
    {
    private:
        //stuff
    };
    //stuff
};
```
- Note that if they are in the same header file, then in the cpp file, you will have to define the function using `Car::Engine::FunctionName()`. 

### Overloaded Functions

Example for operator+

```C++
class Vec2 {
    public:
        // Returns a new vector object.
        // const Vec2 & rhs
        // -> reference to a Vec2 object.
        // -> const because not modifying the reference.
        // const function because not modifying the calling vector object.
        Vec2 operator+(const Vec2 &rhs) const; 
};

```

You can also overload += and -=, etc. **Note** for these functions you *should* return a reference to the object.

Cool thing with the operator += and etc.

```C++
// One implementation
Vec2& Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

// A better implementation (given operator + has already been defined):
Vec2& Vec2::operator+=(const Vec2& rhs)
{
    // This seems to also work
    return *this + rhs;

    // But he suggested this
    return *this = *this + rhs;

    // I think latter returns a reference but the former might make a local Vec2 object and then it goes out of scope? But neither versions crashed the code though.
}

```


# Functions Parameters
When passing a reference to an object, you can specify constant which means you will not be editing any of the objects member variables, you will just be reading them.

# Types

#### struct
- Very similar to classes except that all the members default to public instead of private. struct is for simple objects that don't have much internal behavior.
- You can initialize structs with {} initializer if they have no private data and specify no constructors (you can have functions defined inside of structs!).
```C++
struct vec2
{
    int x;
    int y;
};

vec2 v = {10,10};
```

#### Floats
- If you want a float literal, place an `f` after the number or else the compiler will treat it as a double. If the number is an int on it's own, need to append `.0f` or you might get a compiler warning of converting int to float.


#### constexpr
-Means constant expression. The value or the return value (since it can be applied to functions and constructors) is constant and where possible is computed at compile time. 

#### auto

- Only really great for when you have stupidly long type names. Otherwise it's better to specify so that your code is more self documenting.



# Namespaces

Can shorten typing by doing something like:
```C++
std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
// |
// V
using std::chrono::steady_clock;
steady_clock::time_point start = steady_clock::now();
```
This will promote std::chrono::steady_clock to the scope of which `using` exists in.

- It is not recommended to ever use the `using` inside of a header file because it will be global to anything that includes that header file, therefore polluting the global namespace.

You can also do `using namespace std;` which will promote `std` to the namespace that the directive was used in. Not a great example but:

```C++
std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
// |
// V
using namespace std;
using chrono::steady_clock;
steady_clock::time_point start = steady_clock::now();
```

# Compiler, Linker, Preprocessor
This tutorial explains it insanely well: https://wiki.planetchili.net/index.php/Beginner_C%2B%2B_Game_Programming_Tutorial_18

Takeaways
- All cpp files go into the compiler as separate entities. Then it's the linker's job to connect all the pieces of assembly into one executable. This includes connecting the function calls from cpp files to each other and also any calls from external libraries / dependencies that are specified. 
- There was a cool note about specifying external libraries to link against in the source code using `#pragma comment(lib,"name_of_lib")` but there is a note in wiki about the downsides of that. 
  - This is a microsoft extension so other compiler may not support it. supported for clang (not for linux linker tho), and not supported by gcc. Best to use CMake!

# Loops

### For Loops
#### Range Based For Loops

Example
```C++

class Lines
{
};

Line bunch_of_lines[200];

// For loop returns a reference (could also do const reference if you want) to object in the bunch_of_lines array for you to do some actions on.
for( Line& l: bunch_of_lines)
{
    l.some_line_obj_function();
}
```
 