# Event Bus Assignment

Problem statement (versions 0, 1, 2) in the doc folder.

## Assumptions

Environmental:

* Linux as a target deployment platform;
* toolchain present.

Requirements:

* subsequent calls to EventBus::add( ename, ehandler )
for the same ename may have different values for ehandler;
* EventBus::invoke( ename ) does NOT remove the
handlers registered with EventBus::add( ename, ehandler );
* EventBus extension:
EventBus::invoke("AddAttachment", "path/to/attachment")
argument is assumed to be const;

## HOWTO

While in this directory:


```
$ cmake -S . -B build
$ cmake --build build
$ ./build/EventBus0_test
$ ./build/EventBus1_test
$ ./build/EventBus2_test

```

# FIXME

This is still not a production code.  Missing:

* Better understanding of the usage scenarios, e.g. is multithreading
that important? Are calls to EventBus::add and EventBus::invoke
overlapped?  Have a separate test for every scenario. Multiprocessing?
* Measure performance in events/sec;
* Current EventBus synchronization implementation is nothing but primitive.
No need to lock the entire bus when adding ehandler to the existing list.
Each vector would have to have a separate mutex though.
* More tests to cover event handler cancellation.
