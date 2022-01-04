// GRPHBSIC.H
// Implementation of basic graph functions. Handles both directed and
// non-directed graphs.
//
// This code implements a single graph.
//
// Note: This violates my rule that headers should only have definitions and
// manifests, not actual code. But this code is meant for ease of compiling
// by students.
//
// This version creates single global data structure for graph. Prior to
// including this header, the manifest MAXVERTEX must be defined.  MAXVERTEX indicates
// MAXVERTEXimum number of vertices that this code will keep track of. For example:
//	#define MAXVERTEX 7
//	#include "grphbsic.h"
//
// This code also expects that a global variable verbose is declared. This
// variable will determine whether this code prints various progress messages
// as it does its work. It is declared here as an extern, just to make life
// easier if you decide to do separate compiles/
extern int	verbose;

#ifndef MAXVERTEX
#error Must define MAXVERTEX before including this file
#endif



// Symbolic names for states vertex can be in while search is underway
typedef enum vrtx_state {GREEN, GREY, RED}	VertexState;

// Graph vertex contains both vertex label and flag if visited.
typedef struct {
	char		label;		// only single character label for vertex
	VertexState	visited;	// state while search underway
} Vertex, *pVertex;


// graph variables. Note that all arrays are constant size based on whatever
// MAXVERTEX manifest is.

Vertex	*Vertices[MAXVERTEX];		// array of pointers to vertices
int		adjMatrix[MAXVERTEX][MAXVERTEX];// contains edge information for all possible edges
int		vertexCount = 0;	// actual vertex count - updated as vertices added


// Basic graph functions

void resetGraph (void)
// Initialize adjacency matrix to have no edges.
// Initialize vertexCount to 0, effectively discarding any vertex information.
{
	int		row;
	for(row=0; row<MAXVERTEX; row++)	{
		int		col;
		for(col=0; col<MAXVERTEX; col++)	adjMatrix[row][col] = 0;
		}
	vertexCount = 0;
}//initGraph()


void printAdjMatrix (void)
// print simple version of adjacency matrix
{
	int		row;
	for(row=0; row<vertexCount; row++)	{
		int		col;
		for(col=0; col<vertexCount; col++)	
			printf (" %5d", adjMatrix[row][col]);
		putchar ('\n');
		}
	putchar ('\n');
}//printAdjMatrix (void)


void resetVisitFlags (void)
// Reset visited flag in all vertices
{
	int	i;
	for (i=0; i<vertexCount; i++)	Vertices[i]->visited = GREEN;
}//resetVisitFlags()


void addVertex(char label)
// Add vertex with value label to vertex list
{
	Vertex	*vertex = (Vertex*) malloc(sizeof(Vertex));
	vertex->label = label;  
	vertex->visited = GREEN;
	if (verbose)	printf ("  Add vertex %c index %d\n", label, vertexCount);   
	Vertices[vertexCount++] = vertex;
}//addVertex()


// Code to add edges to graph. Code here can add unweighted or weighted,
// directed or non-directed edge to adjacency matrix.

#define	INVALID_NDX		(-1)

int vertex_index_from_label (char label)
// Given vertex name - its label - find it in vertex list, returning index.
// Returns -1 if label not found.
{
	int		i;
	for (i=0; i<vertexCount; i++)
		if (Vertices[i]->label == label)	return i;
	return INVALID_NDX;
}//vertex_index_from_label()


void addWeightedDirectedEdge (int start, int end, int weight)
// Add directed edge from start to end in edge array
{
	// verify indices within bounds
	if (start >= 0 && start < vertexCount &&
		end >= 0 && end <= vertexCount)	{
		adjMatrix[start][end] = weight;
		if (verbose)	{
			printf ("--Add edge between %c (%d) and %c (%d) with weight %d\n",
				Vertices[start]->label, start,
				Vertices[end]->label, end,
				weight);
			}
		}
}//addWeightedDirectedEdge()


void addWeightedDirectedEdgeByLabel (char startlabel, char endlabel, int wgt)
// Add directed edge from startlabel to endlabel. Function does lookup to get
// indices for labels, and then calls routine above. (Note that our checking
// here is unnecessary, because the routine above does verification.)
{
	int		start, end;
	start = vertex_index_from_label (startlabel);
	end = vertex_index_from_label (endlabel);
	if (start == INVALID_NDX || end == INVALID_NDX)	return;
	addWeightedDirectedEdge (start, end, wgt);
}//addWeightedDirectedEdgeByLabel()


void addWeightedEdge (int start, int end, int weight)
// Add edge to edge array with weight
{
	addWeightedDirectedEdge (start, end, weight);
	addWeightedDirectedEdge (end, start, weight);
}//addWeightedEdge ()


void addEdge(int start, int end)
// Add edge to edge array. This is for unweighted graphs. Calls routine that
// adds weighted directed edge with weight of 1, in both directions.
{
	addWeightedEdge (start, end, 1);
}// addEdge()


void addEdgeByLabel (char startlbl, char endlbl)
{
	int		start, end;
	start = vertex_index_from_label (startlbl);
	end = vertex_index_from_label (endlbl);
	if (start == INVALID_NDX || end == INVALID_NDX)	return;
	addEdge (start, end);
}//addEdgeByLabel ()


void addDirectedEdge (int start, int end)
// Add directed edge from start to end in edge array
{
	addWeightedDirectedEdge (start, end, 1);
}//addDirectedEdge


void displayVertex (int vertexIndex)
// Display one vertex label with trailing blank.
{
	printf("%c ",Vertices[vertexIndex]->label);
}// displayVertex()     


void addVertexLabels (char *p)
// Add multiple single character labels to vertex list, from string of labels.
{
	if (p)	{while (*p)	addVertex (*p++);}
}//addVertexLabels()


int getAdjUnvisitedVertex(int vertexIndex)
// Get adjacent unvisted vertex.
// Go through adjacency matrix vertexIndex row to find first neighbour that has
// not yet been visited.
{
	int i;
	for (i=0; i<vertexCount; i++)	{
	if	(adjMatrix[vertexIndex][i] > 0 && (Vertices[i]->visited == GREEN))	{
		return i;
		}
	}//endfor       
	return INVALID_NDX;
}// getAdjUnvisitedVertex()
