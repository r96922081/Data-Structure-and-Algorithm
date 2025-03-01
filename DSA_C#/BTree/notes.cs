/*
BTree vs. B+Tree:

1. Internal nodes of B+Tree store only key value and child pointer, the actual data is saved in leaf node

2. Leaf nodes are linked together (suitable for full scan and range scan)

Advantage of B+Tree

1. Internal nodes do not save actual data, so they require less space, more internal nodes can fit on a page 
that will reduce cache miss. (You may consider load entire internal nodes into memory)

2. Because leaf nodes are linked together, full scan and range scan require just on pass to the left most leaf node, then you can 
traverse all leaf node by the link

Advantage of BTree

1. You can elevate freuqently access node to root, so it will require less comparisons to get that data


Relational DB Aspect:

1. Primary Key Index (Clustered Index)

ex:
CREATE TABLE Orders (
    id INT PRIMARY KEY,
    value1 INT,
    value2 INT,
);

actual rows (value1, value2) are stored in leaf

2. Secondary Index

ex:
CREATE INDEX index_id2 ON Orders(id2);

Leaf stores pointer to actual row

======

A node in a BTree is located by Page number + slot number

 */ 