
# Data-Structure-and-Algorithm

## [BTree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTree.cs)
The B-tree generalizes the binary search tree, allowing for nodes with more than two children.
The B-tree is well suited for storage systems that read and write relatively large blocks of data, 
such as databases and file systems

![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/btree.png?raw=true)

## [B+Tree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTree.cs)
BTree with 2 diferences

 - Internal nodes of B+Tree store only key value and child pointer, the actual data is saved in leaf node
 - Leaf nodes are linked together (suitable for full scan and range scan)

![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/b+tree.png?raw=true)

## [B+TreePaged](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTreePaged.cs)

B+Tree that uses only constant memory space, load/store between memory/disk by utilizing [PageBufferPool](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C#/PageBufferPool/PageBufferPool.cs)
