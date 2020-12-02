# Final project source code for CSCI 2275

- Professor Hoenigman
- Andrew Schwartz
- Fall 2020

## Summary

This project provides information about flight destinations and routes.
Using flight data scraped from Kayak, this answers questions like, "Where can
I travel for under $300?" and, "Where can I fly non-stop from Atlanta?"

### Implementation

We use a directional graph to implement the route network, where nodes represent airports
and edges represent flights. The edge weight is equal to the ticket cost for a flight.

For questions that consider price, we use priority queues to sort flights by lowest cost
to highest cost.

## How to Run

Run the code with `./run.sh`. If run.sh is not an executable, try `chmod +x run.sh`.

## Dependencies

None.

## System Requirements

This code should be OS-independent. If you want to generate flight data, you will
need to use python 3. C++ is based on C++11.

## Team Members

* Andrew Schwartz ([@schwartzadev](https://github.com/schwartzadev/))

## Contributors

See [contributors](https://github.com/schwartzadev/csci-2275-final/graphs/contributors).

## Open issues/bugs
See [issues](https://github.com/schwartzadev/csci-2275-final/issues).
