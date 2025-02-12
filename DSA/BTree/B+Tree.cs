public abstract class IBPlusTreeData
{
    public IBPlusTreeData leftData = null;
    public IBPlusTreeData rightData = null;

    public abstract IComparable GetKey();
    public abstract IBPlusTreeData CloneKeyOnly();
    public abstract object GetData();
    public abstract string ToString();
}

public class BPlusTreeNode
{
    public BPlusTreeNode parent = null;
    public BPlusTreeNode left = null;
    public BPlusTreeNode right = null;
    public List<IBPlusTreeData> keys = new List<IBPlusTreeData>();
    public List<BPlusTreeNode> children = new List<BPlusTreeNode>();

    public BPlusTreeNode() { }

    public BPlusTreeNode(List<IBPlusTreeData> keys)
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
        foreach (IBPlusTreeData key in keys)
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

public class BPlusTree
{
    public int t;
    public BPlusTreeNode root = null;

    public BPlusTree()
    {

    }

    public BPlusTree(int t)
    {
        this.t = t;
    }

    public void Insert(IBPlusTreeData key)
    {
        if (t < 2)
            throw new Exception();

        if (root == null)
        {
            BPlusTreeNode node = new BPlusTreeNode();
            root = node;
        }

        FindLeafToInsert(root, key);
    }

    private void InsertUpward(BPlusTreeNode node, IBPlusTreeData key, BPlusTreeNode left, BPlusTreeNode right)
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

    private int GetKeyInsertPosition(BPlusTreeNode node, IBPlusTreeData key)
    {
        int i = 0;
        for (; i < node.keys.Count; i++)
        {
            if (key.GetKey().CompareTo(node.keys[i].GetKey()) < 0)
                break;
        }
        return i;
    }

    private void FindLeafToInsert(BPlusTreeNode node, IBPlusTreeData key)
    {
        int i = GetKeyInsertPosition(node, key);

        if (node.IsLeaf())
        {
            if (node.keys.Count > 0)
            {
                if (i == node.keys.Count)
                {
                    IBPlusTreeData leftData = node.keys[i - 1];
                    if (leftData.rightData != null)
                        leftData.rightData.leftData = key;

                    key.rightData = leftData.rightData;
                    key.leftData = leftData;
                    leftData.rightData = key;
                }
                else
                {
                    IBPlusTreeData originalData = node.keys[i];

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

    private void Split(BPlusTreeNode node)
    {
        IBPlusTreeData key = node.keys[t];

        BPlusTreeNode left = null;
        BPlusTreeNode right = null;

        // leaf
        if (node.children.Count == 0)
        {
            left = new BPlusTreeNode(node.keys.GetRange(0, t));
            right = new BPlusTreeNode(node.keys.GetRange(t, t));
            key = key.CloneKeyOnly();
        }
        else // internal node works in the same way as BTree
        {
            left = new BPlusTreeNode(node.keys.GetRange(0, t));
            right = new BPlusTreeNode(node.keys.GetRange(t + 1, t - 1));

            left.children.AddRange(node.children.GetRange(0, t + 1));
            right.children.AddRange(node.children.GetRange(t + 1, t));

            foreach (BPlusTreeNode child in left.children)
                child.parent = left;
            foreach (BPlusTreeNode child in right.children)
                child.parent = right;
        }

        if (node.parent == null)
        {
            root = new BPlusTreeNode();
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

    private int KeyCountInternal(BPlusTreeNode node)
    {
        int keyCount = node.keys.Count;
        foreach (BPlusTreeNode n in node.children)
            keyCount += KeyCountInternal(n);

        return keyCount;
    }

    public List<IBPlusTreeData> Find(IComparable key)
    {
        if (root == null)
            return new List<IBPlusTreeData>();

        return FindInternal(root, key);
    }

    private List<IBPlusTreeData> FindInternal(BPlusTreeNode node, IComparable key)
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
            return new List<IBPlusTreeData>();

        List<IBPlusTreeData> found = new List<IBPlusTreeData>();

        IBPlusTreeData firstFound = node.keys[keyIndex];

        IBPlusTreeData leftData = firstFound.leftData;
        while (leftData != null)
        {
            if (key.CompareTo(leftData.GetKey()) != 0)
                break;

            found.Insert(0, leftData);
            leftData = leftData.leftData;
        }

        found.Add(firstFound);

        IBPlusTreeData rightData = firstFound.rightData;
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

    private bool DeleteFromLeaf(BPlusTreeNode node, IComparable key)
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

        IBPlusTreeData left = node.keys[index].leftData;
        IBPlusTreeData right = node.keys[index].rightData;

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

    private void Merge(BPlusTreeNode node, int leftChildIndex, int rightChildIndex)
    {
        BPlusTreeNode left = node.children[leftChildIndex];
        BPlusTreeNode right = node.children[rightChildIndex];

        if (!left.IsLeaf())
        {
            BPlusTreeNode max = left.children[left.children.Count - 1];
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

    private bool DeleteInternal(BPlusTreeNode node, IComparable key)
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

        BPlusTreeNode childNode = node.children[childIndex];

        if (childNode.keys.Count >= t - 1)
            return true;

        if (childIndex == node.keys.Count)
        {
            BPlusTreeNode leftSibling = node.children[childIndex - 1];

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
                    BPlusTreeNode max = leftSibling.children[leftSibling.children.Count - 1];
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
            BPlusTreeNode rightSibling = node.children[childIndex + 1];

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
                    BPlusTreeNode min = rightSibling.children[0];
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

    private int getString(int level, BPlusTreeNode currentNode, List<List<string>> nodeStringByLevel)
    {
        if (level == nodeStringByLevel.Count)
            nodeStringByLevel.Add(new List<string>());

        string currentNodeString = currentNode.ToString();
        int childrenWidth = 0;
        foreach (BPlusTreeNode child in currentNode.children)
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
