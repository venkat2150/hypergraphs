# hypergraphs
Generating a reduced conformal hyper-graph from the given hyper-graph

Writing Credits: Mackenzie Dahlem, Willam Csont.

Coding Credits: 
              C++:  Venkata Kautilya Thanneeru.

G-Structures to C-Structures: 

Algorithm:

algorithm BronKerbosch2(R, P, X) is

    if P and X are both empty then
    
        report R as a maximal clique
	
    choose a pivot vertex u in P ⋃ X
    
    for each vertex v in P \ N(u) do
    
        BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
	
        P := P \ {v}
	
        X := X ⋃ {v}



Explanation:

For our project, we recognized that the main problem we needed to solve was figuring out all the maximal cliques of the given G-Structure. Once that step was completed, returning a C-Structure with the same primal graph would be very simple, as we were not changing any edges or vertices in the process of analyzing the G-Structure. For example, when given a G-Structure ‘12/23/13’, our program will return ‘123’ as the desired C-Structure; both of these hypergraphs have the same primal graphs- the same sets of edges and vertices- however it is much easier to see the relations between the vertices using the C-Structure. For this program, it was decided we would use the Bron-Kerbosch Algorithm, one that was briefly mentioned in the paper Clique Guided Community Detection [1].
  
  
  To elaborate on the Bron-Kerbosch Algorithm, it sorts the vertices of the graph into three sets. One set, the set of candidate vertices, includes the vertex the algorithm will focus on for one iteration, known as the pivot. The pivots are chosen in order to “minimize recursive calls” [2]. Of the other two sets, one is used to hold every vertex with an edge connecting it to the chosen pivot, while the other holds the discarded pivot when the iteration is completed. When beginning, there is no chosen vertex, and the set that contains all the vertices with an edge connecting it to the chosen pivot is simply a set that contains all vertices in the given structure. When choosing the pivot for the algorithm, the chosen vertex should have the highest degree- the highest number of edges, or connected vertices.


  There are three forms of this algorithm, one without pivoting, one with pivoting, and one that involves vertex ordering. The version of this algorithm without pivoting- one that does not involve the pivot above- was acknowledged by the creators, Bron and Kerbosch, to be largely inefficient when it came to graphs with a majority of non-maximal cliques [3]. This is because the algorithm would end up making recursive calls for every clique, even if it was not maximal. Due to this, it was decided that we would use the version of the algorithm with vertex pivoting- it is also much easier to understand and translate to code. The third version of this algorithm, the one with vertex ordering, is an alternative to the one with pivoting, as it instead orders the calls in order to minimize the set of candidates. This was decided to be too complex for our needs, so it was decided we were to use pivoting.
  
  
  To give a basic example of how the algorithm would work with pivoting, of a hypergraph ‘123/45/25’, the vertices chosen for the first set, named ‘X’ for this example, will be 1, 3, and 5, as they have the highest degrees. For the first iteration, the pivot will be 1. During this iteration, the second set, known as ‘I’ for this example, will contain every vertex connected to the pivot, 2 and 3. The third set, ‘J’, will contain nothing at the moment, as this is where the discarded pivot will end up at the end of this iteration. The algorithm then performs a recursive call on set ‘I’, choosing one of the vertices in ‘I’ to be the pivot, then again for the final vertex in the recursive call’s set ‘I’. Eventually, the program should return ‘123’ and place ‘1’ in ‘J’. The algorithm will then move on to the next vertex in ‘X’, making the pivot 3. This will end up returning no clique, as 1 is in ‘X’ and there is no maximal clique with 3 that does not contain 1. The algorithm then moves on to the next pivot in the initial set ‘X’, which would be 5. In the end, the algorithm should return ‘123’, ‘45’, and ‘25’.
  
  
  For the development of the program itself it is to be developed utilizing the C language. The program will start off prompting the user to put in how many total nodes there are present in the hypergraph. This will be stored in the variable, n. Then the program will retrieve information from the user, which will include how many different cliques are present in the hypergraph. From the hypergraph, there will be an integer matrix representing the adjacency matrix that is derived from the hypergraph given. After all of the information is gathered, the program will use the given information to perform the Bron-Kerbosch Algorithm to find the set of maximal cliques in the given G-Structure.
  
  From there the C-structure corresponding to the hypergraph given is found, the adjacency matrices are compared, and, if they match (as they should), the program is complete.
  
  
At the moment, as a group, we have discussed which algorithm we would use to find the maximal cliques for the given G-Structure and began implementing the creation of the initial G-Structure’s adjacency matrix given the user’s input. We have tested some extreme cases for the generation of the adjacency matrix and are satisfied with the results. We are beginning to implement the Bron-Kerbosch Algorithm, which is introducing new problems we had not previously thought of, such as figuring out which vertices have the highest degree in order to select the pivots. 



Citations

[1] D. Palsetia, M. M. A. Patwary, W. Hendrix, A. Agrawal, and A. Choudhary, “Clique guided community detection,” 2014 IEEE International Conference on Big Data (Big Data), 2014.

[2] C. Bron and J. Kerbosch, “Algorithm 457: finding all cliques of an undirected graph,” Communications of the ACM, vol. 16, no. 9, pp. 575–577, Jan. 1973.

[3] F. Cazals and C. Karande, “A note on the problem of reporting maximal cliques,” Theoretical Computer Science, vol. 407, no. 1-3, pp. 564–568, 2008.

[4] https://www.wikiwand.com/en/Bron%E2%80%93Kerbosch_algorithm
