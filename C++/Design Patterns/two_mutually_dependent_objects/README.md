# Two mutually dependent Objects

There are two objects running concurrently (for instance in separate threads) and they need to communicate with each other, call methods on each other.


## Suggested Solution

Use channels: For the two objects A and B there are two channels, for communication from A to B and B to A. 
When A wants to inform B, A passes its message to the channel to B, where it might be stored in a queue, and when B has time to deal with a message it can retrieve it from the channel.

Using channels to decouple objects from one another makes it possible for these objects to run isolated from each other, yet still enables communication
and, in this case, eliminates the cyclic dependency between those two objects.

