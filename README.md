# C-Data-Structures-and-Algorithms
Algorithms and data structures project
Consider a highway described as a sequence of service stations. Every gas station is located
at a distance from the start of the motorway expressed in kilometers by a positive or zero integer. Two service stations having the same distance don't exist: each service station is therefore uniquely identified by its distance from the start.
Each service station is equipped with a fleet of electric rental vehicles. Each vehicle is distinctive
by the autonomy given by one battery charge, expressed in kilometers, by a positive integer. The park vehicles of a single station include at most 512 vehicles. Renting a car from a station is possible
to reach all those whose distance from you is less than or equal to the car's range.
A trip is identified by a sequence of petrol stations where the driver stops. It then begins
at one service station and ends at another, passing through zero or more intermediate stations. Assume that the driver cannot turn back during the trip, and rent a new car every time he stops in
a petrol station. Therefore, given two consecutive stages s and t, t must be further and further from the start concerning s, and t must be reachable using one of the vehicles available in s.
The objective of the project is the following: given a pair of stations, plan the route with the fewest number of stages between them. If there are multiple routes with the same minimum number of stages (i.e. equal merit), the route that favors the stages with the shortest distance from the start of the motorway must be chosen. In other words, consider the set of n equal paths P = {p1, p2, . . . pn} where each path is a tuple of m elements pi = ⟨pi,1, pi,2, . . . pi,m⟩ which are equivalent to the distance from the start of the motorway of each stage in order of travel.
The only path must be chosen such that there is no other pj with the same k final stages preceded by one stage with shorter distance, i.e. ∄j, k: ⟨pi,m−k+1, . . . pi,m⟩ = ⟨pj,m−k+1, . . . pj,m⟩ ∧ pj,m−k < pi,m−k.
