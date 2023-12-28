#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#include "DirectedGraph.h"

class AdjacencyMatrixGraph : public DirectedGraph {
protected:
   std::vector<Vertex*> vertices;
   
   // If matrixRows[X][Y] is true, then an edge exists from vertices[X] to
   // vertices[Y]
   std::vector<std::vector<bool>> matrixRows;
   
   // Your additional code here, if desired
   
public:    
   virtual ~AdjacencyMatrixGraph() {
      for (Vertex* vertex : vertices) {
         delete vertex;
      }
   }

   // Creates and adds a new vertex to the graph, provided a vertex with the
   // same label doesn't already exist in the graph. Returns the new vertex on
   // success, nullptr on failure.
   virtual Vertex* AddVertex(std::string newVertexLabel) override {
      // Your code here (remove placeholder line below)
      return nullptr;
   }
   
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      // Your code here (remove placeholder line below)
      return false;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual std::vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      // Your code here (remove placeholder line below)
      return std::vector<Edge>();
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual std::vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      // Your code here (remove placeholder line below)
      return std::vector<Edge>();
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(std::string vertexLabel) override {
      // Your code here (remove placeholder line below)
      return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      // Your code here (remove placeholder line below)
      return false;
   }
};

#endif