# lock-based-concurrent-data-structures-cpp
OSTEP Book Chapter 29 Examples Translated from C to C++

POSIX is great and all, but windows do <i>not</i> have very good support for it,
so the point is to use std::thread over pthreads so these work on
windows.

Also a good opportunity for me to use this as an excuse to write
some code by hand, yay.

And I know, I know, <i>manually calling lock() and unlock() is not modern c++</i>!
You're right! It's not good modern practice! I'm still learning how to write
multithreaded programs, so give me some slack, to use more manual methods while
I'm still learning!
