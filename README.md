
# Data-Structure-and-Algorithm

## [MD5 Hash](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C/md5.c)

[MD5](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C/md5.c) that implements [pseudo code](https://r96922081.github.io/DSA/md5_pseudo.png) on [wiki](https://en.wikipedia.org/wiki/MD5). \
\
![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/md5_4.png?raw=true)

## [SHA256 Hash](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C/sha256.c)

[SHA256](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C/sha256.c) that implements [pseudo code](https://r96922081.github.io/DSA/sha256_pseudo.png) on [wiki](https://en.wikipedia.org/wiki/SHA-2)\
\
![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/sha256_3.png?raw=true)

## [Huffman Encoding](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/Compression/HuffmanEncoding.cs)

[Huffman Encoding](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/Compression/HuffmanEncoding.cs) that compress the novel [Alice's Adventures in Wonderland](https://github.com/google/snappy/blob/main/testdata/alice29.txt) with 57% compression ratio (not impressive)\
\
![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/huffman_coding.png?raw=true)

## [Lz77 Compression](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/Compression/Lz77Compression.cs)



[Lz77 Compression](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/Compression/Lz77Compression.cs) ([algorithm](https://medium.com/@vincentcorbee/lz77-compression-in-javascript-cd2583d2a8bd)) that compress the novel [Alice's Adventures in Wonderland](https://github.com/google/snappy/blob/main/testdata/alice29.txt) with 56% compression ratio (not impressive)\
\
![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/lz77.png?raw=true)

## [BTree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/BTree.cs)
The [BTree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/BTree.cs) generalizes the binary search tree, allowing for nodes with more than two children.
The Btree is well suited for storage systems that read and write relatively large blocks of data, 
such as databases and file systems

![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/btree.png?raw=true)

## [B+Tree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTree.cs)
[B+Tree](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTree.cs) = BTree + 2 features

 - Internal nodes of B+Tree store only key value and child pointer, the actual data is saved in leaf node
 - Leaf nodes are linked together (suitable for full scan and range scan)

![enter image description here](https://github.com/r96922081/r96922081.github.io/blob/main/DSA/b+tree.png?raw=true)

## [B+TreePaged](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTreePaged.cs)

[B+TreePaged](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/BTree/B%2BTreePaged.cs) = B+Tree uses constant memory.  It load/store between memory/disk by utilizing [PageBufferPool](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/PageBufferPool/PageBufferPool.cs)


## [MinPriorityQueue](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/MinPriorityQueue/MinPriorityQueue.cs)

[MinPriorityQueue](https://github.com/r96922081/Data-Structure-and-Algorithm/blob/main/DSA_C%23/MinPriorityQueue/MinPriorityQueue.cs) that supports Increase/Decrease key that was not supported in .net library PriorityQueue
