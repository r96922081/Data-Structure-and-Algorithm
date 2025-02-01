public interface IBPlusTreeValue
{
    IComparable GetKey();
    object GetData();
    string ToString();
}

public class BPlusTreeNode
{
    public BPlusTreeNode parent = null;
    public List<IBPlusTreeValue> keys = new List<IBPlusTreeValue>();
    public List<BPlusTreeNode> children = new List<BPlusTreeNode>();

    public BPlusTreeNode() { }

    public BPlusTreeNode(List<IBPlusTreeValue> keys)
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
        foreach (IBPlusTreeValue key in keys)
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

    public void Insert(IBPlusTreeValue key)
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

    private void InsertUpward(BPlusTreeNode node, IBPlusTreeValue key, BPlusTreeNode left, BPlusTreeNode right)
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

    private int GetKeyInsertPosition(BPlusTreeNode node, IBPlusTreeValue key)
    {
        int i = 0;
        for (; i < node.keys.Count; i++)
        {
            if (key.GetKey().CompareTo(node.keys[i].GetKey()) < 0)
                break;
        }
        return i;
    }

    private void FindLeafToInsert(BPlusTreeNode node, IBPlusTreeValue key)
    {
        int i = GetKeyInsertPosition(node, key);

        if (node.IsLeaf())
        {
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
        IBPlusTreeValue key = node.keys[t];

        BPlusTreeNode left = new BPlusTreeNode(node.keys.GetRange(0, t));
        BPlusTreeNode right = new BPlusTreeNode(node.keys.GetRange(t + 1, t - 1));

        if (node.children.Count > 0)
        {
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

    public List<IBPlusTreeValue> Find(IBPlusTreeValue key)
    {
        if (root == null)
            return new List<IBPlusTreeValue>();

        return FindInternal(root, key);
    }

    private List<IBPlusTreeValue> FindInternal(BPlusTreeNode node, IBPlusTreeValue key)
    {
        List<IBPlusTreeValue> found = new List<IBPlusTreeValue>();

        int start = 0;
        for (; start < node.keys.Count; start++)
        {
            if (key.GetKey().CompareTo(node.keys[start].GetKey()) <= 0)
                break;
        }
        int end = start + 1;
        for (; end < node.keys.Count; end++)
        {
            if (key.GetKey().CompareTo(node.keys[end].GetKey()) != 0)
                break;
        }

        if (node.IsInternal())
            found.AddRange(FindInternal(node.children[start], key));

        for (int i = start; i < end && i < node.keys.Count; i++)
        {
            if (key.GetKey().CompareTo(node.keys[i].GetKey()) == 0)
                found.Add(node.keys[i]);

            if (node.IsInternal())
                found.AddRange(FindInternal(node.children[i + 1], key));
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
