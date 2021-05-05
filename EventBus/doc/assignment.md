# Event Bus System in C++

## Problem Description

For this system to operate you will need two functions, add and invoke.
How these should be grouped and organized is part of the exercise.

* The `add` function must take an event name and a function to be
executed later.
* The `invoke` function takes an event name and when called, results in
each function previously added (if any) with the matching event name, to
be called once.

## Sample Pseudocode

In the pseudo-code below:

```
add("NewEmail", executeNew)
add("TrashEmail", executeTrash)
add("NewEmail", executeNew)
add("ReplyEmail", executReply)
invoke("NewEmail")
invoke("TrashEmail")
```

We would expect the following:

* `executeNew` to be called twice
* `executeTrash` to be called once
* `executeReply` to not be executed at all.

## Add an Extension to the System

So far so good? Now, please extend the system to allow the event functions
to take a string argument. For example, consider the pseudocode below:

```
add("AddAttachment", executeAttachment)
invoke("AddAttachment", "path/to/attachment")
```

When invoke method is called, `executeAttachment` will be called with
`"path/to/attachment"` as its argument.

## Final Upgrade

As a final feature update, please extend the system to allow event
functions to cancel subsequent events in the queue.

For example:
```
add("AddAttachment", executeAttachment1)
add("AddAttachment", executeAttachmentWithCancel)
add("AddAttachment", executeAttachment2)
invoke("AddAttachment", "path/to/attachment")
```

We would expect the following:

* `executeAttachment1` and `executeAttachmentWithCancel` should both run
* but `executeAttachment2` should not.

## Coding instructions

* All code written for this test should be considered to be production
ready and forward looking with regards to its API design and use of
language features. So please take care that you are happy with
both the maintainability, quality and performance of this code as if it
were going to be deployed in production.
* Please don't put your name or any identifying comments in your code. This
will ensure that all candidates are evaluated anonymously.
* All API design and data structure choices are left up to you. It should
be assumed that this system will continue to evolve, and care should be
taken to allow further extensibility.
* If you make any assumptions, please make sure they are documented.
* Additionally, please provide examples that prove the system works as
prescribed.

## Submission instructions

1. Compress any and all files into a zip.
2. To avoid adobe's email system blocking the email, please change the
extension of the zip file to .zipped
3. Email the .zipped file back to Adobe
4. Now go enjoy a cup of coffee!
