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

For answering questions about a specific airport (i.e. "Where are the cheapest travel
locations within two stops of Los Angeles?"), we use a tree conversion of the route map,
where the root of the tree is the starting airport.

For questions that consider price, we use priority queues to sort flights by lowest cost
to highest cost.

(We also prevent repeating airports in the tree and limit the maximum depth.)
