## Week 1 (11/6 - 11/12) Development Log Feedback

### Overall Comments

Nice work! It seems like you are making good progress and most of the overall algorithm/testing logic seems
to be near completion.

Your code seems very thorough so far.

### Response to Questions

1) The professor might have missed the 4th one while grading but regardless you do need 5 total datasets of varying
magnitudes. Make sure that they are of different magnitude of sizes (something like 10, 100, 1000, ...,
doesn't have to be factors of 10 could also be factors of 5).

2) Are both of you working within the Docker environment? If so, it's really weird that you are seeing a
difference of running it on Windows versus running it on another OS. Maybe make sure there is no randomness
seeping into your test somewhere (run it with Valgrind to see if there is some uninitialized variable that
might explain why this is happening).
