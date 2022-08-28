## Motive
I like this type of code in `python`
```python
# loop from 0 to 10
for i in range(10):
    print(i)

# loop from 5 to 10 with step=2
for i in range(5, 20, 2):
    print(i)
```

Meanwhile in `C++`
```cpp
// loop from 5 to 10
for (int i = 0; i < 10; i++)
    std::cout << i;

// loop from 5 to 10 with step=2
for (int i = 5; i < 10; i+=2)
    std::cout << i;
 ```
 
Nah, it looks like legacy `C` to me, why be so ugly?
## Now we can do this instead

```cpp
// loop from 0 to 10
for (auto i : range(10))
    std::cout << i;

// loop from 0 to 10 with step=2
for (auto i : range(10).step(2))
    std::cout << i;

// loop from 5 to 10
for (auto i : range(5, 10))
    std::cout << i;

// loop from 5 to 10 with step=2
for (auto i : range(5, 10, 2))
    std::cout << i;
 ```

 Check out [main.cpp](./main.cpp) for more examples

 ## Overhead?

 I don't think so, in this [benchmark](https://quick-bench.com/q/sH-grx17ViJT8NZ0bi7ovOx-UXw), `RangedIterator` is even faster than a normal for-loop (optimization flag set to `-O1`, you won't build your code without any optimization, will you?)
 
 Anyway it's just sugar syntax, most compilers will opimize it away.
