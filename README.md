# mcl
A hackable macro-generated container library for C.

This library was spawned by a scenario that I'm sure all readers can sympathise with:

> An ambitious young(-ish) software engineer is inspired to tackle Advent of Code 2022 in pure C, only to find that their enthusiasm is gradually eroded by the need to reinvent various
> containers (list, stack, binary tree) for different types.

> Where are the templates? Where is the STL? What am I doing with my life?

> The engineer gets to roughly Day 20 before calling it a day, though not before deciding that next year they will attempt the same feat, but will be more prepared...

The mcl is a (WIP) attempt to aid the aforementioned software engineer by creating a library that roughly mirrors C++'s STL. C does not have a means of generating code for different types at compile time (AKA C++ templates) so to achieve this the preprocessor is used instead (I did briefly explore using void pointers everywhere, but it quickly got complicated, and I spent too much time worrying about lifetimes).

To use this library the basic pattern is to make a single macro call specifying the type you're interested in, which then generates a full set of functions for interacting with that type.

For example, the macro call ```MCL_BT(int)``` would generate the structure for a binary tree ```struct mcl_bt_int``` and the functions for interacting with this struct: ```mcl_bt_insert_int```, ```mcl_bt_delete_int```, ```mcl_bt_contains_int``` etc.

Currently supported types:
* ```MCL_DA``` for dynamically sized arrays (C++ vector)
* ```MCL_BT``` for binary trees (C++ set)

Planned stuff:
* ```MCL_LL``` for linked lists (C++ list)
* ```MCL_PQ``` for priority queues (C++ priority_queue)
