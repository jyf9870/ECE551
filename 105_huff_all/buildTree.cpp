#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() != 1) {
    Node * nodeA = pq.top();
    pq.pop();
    Node * nodeB = pq.top();
    pq.pop();
    Node * combinenode = new Node(nodeA, nodeB);
    pq.push(combinenode);
  }
  Node * root = pq.top();
  pq.pop();
  return root;
}
