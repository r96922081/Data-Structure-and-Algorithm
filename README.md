# Data-Structure-and-Algorithm

## BTree

**Insertion**

 - Always insert to the leaf
 - Split middle key to parent recurisively if key count > 2t - 1

Example of btree with t = 2.
![enter image description here](https://r96922081.github.io/images/btree/insert1.png)
insert 4.  It split middle key = 2 to parent
![enter image description here](https://r96922081.github.io/images/btree/insert2.png)
\
\
Example of btree with t = 2,  insert 13
![enter image description here](https://r96922081.github.io/images/btree/insert3.png)
insert 4.  It split middle key = 11 to parent, and recursively, split middle key 8 to parent 
![enter image description here](https://r96922081.github.io/images/btree/insert4.png)

