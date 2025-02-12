public abstract class IBPlusTreePagedData
{
    public IBPlusTreePagedData leftData = null;
    public IBPlusTreePagedData rightData = null;

    public abstract IComparable GetKey();
    public abstract IBPlusTreePagedData CloneKeyOnly();
    public abstract object GetData();
    public abstract string ToString();
}

public class BPlusTreePagedNode
{
    public BPlusTreePagedNode parent = null;
    public BPlusTreePagedNode left = null;
    public BPlusTreePagedNode right = null;
    public List<IBPlusTreePagedData> keys = new List<IBPlusTreePagedData>();
    public List<BPlusTreePagedNode> children = new List<BPlusTreePagedNode>();

    public BPlusTreePagedNode() { }

    public BPlusTreePagedNode(List<IBPlusTreePagedData> keys)
    {
        this.keys = keys;
    }

    public bool IsLeaf()
    {
        return children.Count == 0;
    }

    public bool IsInternal()
    {
        return !IsLeaf();
    }

    public override string ToString()
    {
        string s = "[";
        foreach (IBPlusTreePagedData key in keys)
        {
            if (s != "[")
            {
                s += ", ";
            }
            s += key.ToString();
        }
        s += "]";
        return s;
    }
}

public class BPlusTreePaged
{
    public int t;
    public BPlusTreePagedNode root = null;

    public BPlusTreePaged()
    {

    }

    public BPlusTreePaged(int t)
    {
        this.t = t;
    }

    public void Insert(IBPlusTreePagedData key)
    {
        if (t < 2)
            throw new Exception();

        if (root == null)
        {
            BPlusTreePagedNode node = new BPlusTreePagedNode();
            root = node;
        }

        FindLeafToInsert(root, key);
    }

    private void InsertUpward(BPlusTreePagedNode node, IBPlusTreePagedData key, BPlusTreePagedNode left, BPlusTreePagedNode right)
    {
        int i = GetKeyInsertPosition(node, key);

        node.keys.Insert(i, key);

        if (node.children.Count != 0)
            node.children.RemoveAt(i);

        node.children.Insert(i, left);
        node.children.Insert(i + 1, right);

        if (node.keys.Count == 2 * t)
        {
            Split(node);
        }
    }

    private int GetKeyInsertPosition(BPlusTreePagedNode node, IBPlusTreePagedData key)
    {
        int i = 0;
        for (; i < node.keys.Count; i++)
        {
            if (key.GetKey().CompareTo(node.keys[i].GetKey()) < 0)
                break;
        }
        return i;
    }

    private void FindLeafToInsert(BPlusTreePagedNode node, IBPlusTreePagedData key)
    {
        int i = GetKeyInsertPosition(node, key);

        if (node.IsLeaf())
        {
            if (node.keys.Count > 0)
            {
                if (i == node.keys.Count)
                {
                    IBPlusTreePagedData leftData = node.keys[i - 1];
                    if (leftData.rightData != null)
                        leftData.rightData.leftData = key;

                    key.rightData = leftData.rightData;
                    key.leftData = leftData;
                    leftData.rightData = key;
                }
                else
                {
                    IBPlusTreePagedData originalData = node.keys[i];

                    if (originalData.leftData != null)
                        originalData.leftData.rightData = key;

                    key.leftData = originalData.leftData;
                    key.rightData = originalData;
                    originalData.leftData = key;
                }
            }


            node.keys.Insert(i, key);

            if (node.keys.Count == 2 * t)
            {
                Split(node);
            }
        }
        else
        {
            FindLeafToInsert(node.children[i], key);
        }
    }

    private void Split(BPlusTreePagedNode node)
    {
        IBPlusTreePagedData key = node.keys[t];

        BPlusTreePagedNode left = null;
        BPlusTreePagedNode right = null;

        // leaf
        if (node.children.Count == 0)
        {
            left = new BPlusTreePagedNode(node.keys.GetRange(0, t));
            right = new BPlusTreePagedNode(node.keys.GetRange(t, t));
            key = key.CloneKeyOnly();
        }
        else // internal node works in the same way as BTree
        {
            left = new BPlusTreePagedNode(node.keys.GetRange(0, t));
            right = new BPlusTreePagedNode(node.keys.GetRange(t + 1, t - 1));

            left.children.AddRange(node.children.GetRange(0, t + 1));
            right.children.AddRange(node.children.GetRange(t + 1, t));

            foreach (BPlusTreePagedNode child in left.children)
                child.parent = left;
            foreach (BPlusTreePagedNode child in right.children)
                child.parent = right;
        }

        if (node.parent == null)
        {
            root = new BPlusTreePagedNode();
            node.parent = root;
        }
        left.parent = node.parent;
        right.parent = node.parent;

        InsertUpward(node.parent, key, left, right);
    }

    public int KeyCount()
    {
        if (root == null)
            return 0;

        return KeyCountInternal(root);
    }

    private int KeyCountInternal(BPlusTreePagedNode node)
    {
        int keyCount = node.keys.Count;
        foreach (BPlusTreePagedNode n in node.children)
            keyCount += KeyCountInternal(n);

        return keyCount;
    }

    public List<IBPlusTreePagedData> Find(IComparable key)
    {
        if (root == null)
            return new List<IBPlusTreePagedData>();

        return FindInternal(root, key);
    }

    private List<IBPlusTreePagedData> FindInternal(BPlusTreePagedNode node, IComparable key)
    {
        while (node != null && !node.IsLeaf())
        {
            int childIndex = 0;
            while (childIndex < node.keys.Count && key.CompareTo(node.keys[childIndex].GetKey()) >= 0)
                childIndex++;

            node = node.children[childIndex];
        }

        int keyIndex = 0;
        while (keyIndex < node.keys.Count && key.CompareTo(node.keys[keyIndex].GetKey()) < 0)
            keyIndex++;

        if (keyIndex >= node.keys.Count || key.CompareTo(node.keys[keyIndex].GetKey()) != 0)
            return new List<IBPlusTreePagedData>();

        List<IBPlusTreePagedData> found = new List<IBPlusTreePagedData>();

        IBPlusTreePagedData firstFound = node.keys[keyIndex];

        IBPlusTreePagedData leftData = firstFound.leftData;
        while (leftData != null)
        {
            if (key.CompareTo(leftData.GetKey()) != 0)
                break;

            found.Insert(0, leftData);
            leftData = leftData.leftData;
        }

        found.Add(firstFound);

        IBPlusTreePagedData rightData = firstFound.rightData;
        while (rightData != null)
        {
            if (key.CompareTo(rightData.GetKey()) != 0)
                break;

            found.Insert(0, rightData);
            rightData = rightData.rightData;
        }

        return found;
    }

    public int Delete(IComparable key)
    {
        int count = 0;
        while (DeleteInternal(root, key))
            count++;

        return count;
    }

    private bool DeleteFromLeaf(BPlusTreePagedNode node, IComparable key)
    {
        int index = 0;
        for (; index < node.keys.Count; index++)
        {
            if (key.CompareTo(node.keys[index].GetKey()) < 0)
                return false;

            if (key.CompareTo(node.keys[index].GetKey()) == 0)
                break;
        }
        if (index == node.keys.Count)
            return false;

        IBPlusTreePagedData left = node.keys[index].leftData;
        IBPlusTreePagedData right = node.keys[index].rightData;

        if (left == null && right == null)
        {

        }
        else if (left != null && right != null)
        {
            left.rightData = right;
            right.leftData = left;
        }
        else if (left != null && right == null)
        {
            left.rightData = null;
        }
        else if (left == null && right != null)
        {
            right.leftData = null;
        }

        node.keys.RemoveAt(index);

        if (node == root && node.keys.Count == 0)
            root = null;

        return true;
    }

    private void Merge(BPlusTreePagedNode node, int leftChildIndex, int rightChildIndex)
    {
        BPlusTreePagedNode left = node.children[leftChildIndex];
        BPlusTreePagedNode right = node.children[rightChildIndex];

        if (!left.IsLeaf())
        {
            BPlusTreePagedNode max = left.children[left.children.Count - 1];
            while (!max.IsLeaf())
                max = max.children[max.children.Count - 1];
            left.keys.Add(max.keys[max.keys.Count - 1].CloneKeyOnly());
        }
        left.keys.AddRange(right.keys);
        left.children.AddRange(right.children);
        node.keys.RemoveAt(rightChildIndex - 1);
        node.children.RemoveAt(rightChildIndex);

        // root case
        if (node == root && node.keys.Count == 0)
            root = left;
    }

    private bool DeleteInternal(BPlusTreePagedNode node, IComparable key)
    {
        if (node == null)
            return false;

        if (node.IsLeaf())
            return DeleteFromLeaf(node, key);

        int firstChildIndex = 0;
        int secondChildIndex = -1;

        while (firstChildIndex < node.keys.Count && key.CompareTo(node.keys[firstChildIndex].GetKey()) >= 0)
        {
            // Consider both side if equal  
            //        [2]
            //   [1]      [2]
            // [0]  [2] [2]  [3]

            if (key.CompareTo(node.keys[firstChildIndex].GetKey()) == 0)
            {
                secondChildIndex = firstChildIndex + 1;
                break;
            }

            firstChildIndex++;
        }

        int childIndex = -1;

        if (DeleteInternal(node.children[firstChildIndex], key))
        {
            childIndex = firstChildIndex;
        }
        else if (secondChildIndex != -1 && DeleteInternal(node.children[secondChildIndex], key))
        {
            childIndex = secondChildIndex;
        }

        if (childIndex == -1)
            return false;

        BPlusTreePagedNode childNode = node.children[childIndex];

        if (childNode.keys.Count >= t - 1)
            return true;

        if (childIndex == node.keys.Count)
        {
            BPlusTreePagedNode leftSibling = node.children[childIndex - 1];

            // merge
            if (leftSibling.keys.Count == t - 1)
            {
                Merge(node, childIndex - 1, childIndex);
            }
            // borrow from left
            else
            {
                if (leftSibling.IsLeaf())
                {
                    childNode.keys.Insert(0, leftSibling.keys[leftSibling.keys.Count - 1]);

                    node.keys[childIndex - 1] = childNode.keys[0].CloneKeyOnly();

                    leftSibling.keys.RemoveAt(leftSibling.keys.Count - 1);
                }
                else
                {
                    BPlusTreePagedNode max = leftSibling.children[leftSibling.children.Count - 1];
                    while (!max.IsLeaf())
                        max = max.children[max.children.Count - 1];
                    childNode.keys.Insert(0, max.keys[max.keys.Count - 1].CloneKeyOnly());
                    childNode.children.Insert(0, leftSibling.children[leftSibling.children.Count - 1]);

                    node.keys[childIndex - 1] = leftSibling.keys[leftSibling.keys.Count - 1];

                    leftSibling.children.RemoveAt(leftSibling.children.Count - 1);
                    leftSibling.keys.RemoveAt(leftSibling.keys.Count - 1);
                }
            }
        }
        else
        {
            BPlusTreePagedNode rightSibling = node.children[childIndex + 1];

            // merge
            if (rightSibling.keys.Count == t - 1)
            {
                Merge(node, childIndex, childIndex + 1);
            }
            // borrow from right
            else
            {
                if (rightSibling.IsLeaf())
                {
                    childNode.keys.Add(rightSibling.keys[0]);

                    node.keys[childIndex] = rightSibling.keys[1].CloneKeyOnly();

                    rightSibling.keys.RemoveAt(0);
                }
                else
                {
                    BPlusTreePagedNode min = rightSibling.children[0];
                    while (!min.IsLeaf())
                        min = min.children[0];
                    childNode.keys.Add(min.keys[0].CloneKeyOnly());
                    childNode.children.Add(rightSibling.children[0]);

                    node.keys[childIndex] = rightSibling.keys[0];

                    rightSibling.children.RemoveAt(0);
                    rightSibling.keys.RemoveAt(0);
                }
            }
        }

        return true;
    }

    private int getString(int level, BPlusTreePagedNode currentNode, List<List<string>> nodeStringByLevel)
    {
        if (level == nodeStringByLevel.Count)
            nodeStringByLevel.Add(new List<string>());

        string currentNodeString = currentNode.ToString();
        int childrenWidth = 0;
        foreach (BPlusTreePagedNode child in currentNode.children)
            childrenWidth += getString(level + 1, child, nodeStringByLevel);

        for (int i = 0; currentNodeString.Length < childrenWidth; i++)
        {
            if (i % 2 == 0)
                currentNodeString = " " + currentNodeString;
            else
                currentNodeString = currentNodeString + " ";
        }

        nodeStringByLevel[level].Add(currentNodeString);

        return childrenWidth >= currentNodeString.Length ? childrenWidth : currentNodeString.Length;
    }

    public override string ToString()
    {
        string ret = "";

        if (root == null)
            return ret;

        List<List<string>> nodeStringByLevel = new List<List<string>>();
        getString(0, root, nodeStringByLevel);

        foreach (List<string> level in nodeStringByLevel)
        {
            foreach (string nodeString in level)
            {
                ret += nodeString;
            }
            ret += "\n";
        }

        return ret;
    }
}

