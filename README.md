# Advent-of-Code-2024

Solutions to AoC 2024 in C++

## Add a new day

In the `/aoc` build file add a new binary output:

```
cc_binary(
    name = "day-x",
    srcs = glob(["day-x/*.cpp", "day-x/*.h", "io/*.h", "io/*.cpp"]),
)
```

If there is an input file add it to `io/day-x`, and you can use the filepath relative to this base directory, e.g. `./io/day-1/input.txt`. Similar for output.

To build and run your day:

```
bazel build //aoc:day-x && bazel-bin/aoc/day-x
```
