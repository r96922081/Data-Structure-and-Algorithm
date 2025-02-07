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
        if (root == null)
        {
            BPlusTreeNode node = new BPlusTreeNode();
            root = node;
        }

        FindLeafToInsert(root, key);
    }

    private BPlusTreeNode MergeNode(BPlusTreeNode node, int keyIndex)
    {
        BPlusTreeNode mergedNode = new BPlusTreeNode();
        mergedNode.keys.AddRange(node.children[keyIndex].keys);
        mergedNode.keys.Add(node.keys[keyIndex]);
        mergedNode.keys.AddRange(node.children[keyIndex + 1].keys);
        mergedNode.children.AddRange(node.children[keyIndex].children);
        mergedNode.children.AddRange(node.children[keyIndex + 1].children);
        mergedNode.parent = node;

        node.keys.RemoveAt(keyIndex);
        node.children.RemoveAt(keyIndex + 1);
        node.children.RemoveAt(keyIndex);

        node.children.Insert(keyIndex, mergedNode);

        if (node == root && node.keys.Count == 0)
            root = mergedNode;

        return mergedNode;
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
        List<IBPlusTreeData> found = new List<IBPlusTreeData>();

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
            return found;

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
