To-do List
==========

- Reduce STL dependence.
- Robustify against out-of-memory conditions:
    - Replace std::string with something that doesn't have to allocate heap mem.
    - Replace exceptions that allocate e.g. std::strings with others.
    - Use our own allocator which shall retain a small buffer to keep essential
    allocations succeeding in an OOM condition.