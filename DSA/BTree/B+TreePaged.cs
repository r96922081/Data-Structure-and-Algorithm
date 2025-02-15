public abstract class IBPlusTreePagedData
{
    public RecordId rid = null;
    public RecordId leftDataRid = null;
    public RecordId rightDataRid = null;

    public IBPlusTreePagedData leftData = null;
    public IBPlusTreePagedData rightData = null;


    public void Save(BPlusTreePagedPageController pc)
    {
        RecordStreamWriter writer = pc.GetRecordStreamWriter(rid);
        SubclassSave(pc);

        writer.WriteRecord(leftDataRid);
        writer.WriteRecord(rightDataRid);
    }

    public IBPlusTreePagedData Load(RecordId rid, BPlusTreePagedPageController pc)
    {
        IBPlusTreePagedData data = SubclassLoad(pc);

        data.rid = rid;
        RecordStreamReader reader = pc.GetRecordStreamReader(rid);
        data.leftDataRid = reader.ReadRecord();
        data.rightDataRid = reader.ReadRecord();

        return data;
    }

    public void SetLeftData(IBPlusTreePagedData leftData)
    {
        if (leftData == null)
        {
            this.leftData = null;
            leftDataRid = null;
        }
        else
        {
            this.leftData = leftData;
            leftDataRid = leftData.rid;
        }
    }

    public void SetRightData(IBPlusTreePagedData rightData)
    {
        if (rightData == null)
        {
            this.rightData = null;
            rightDataRid = null;
        }
        else
        {
            this.rightData = rightData;
            rightDataRid = rightData.rid;
        }
    }

    public abstract IComparable GetKey();
    public abstract IBPlusTreePagedData CloneKeyOnly();
    public abstract void SubclassSave(BPlusTreePagedPageController pc);
    public abstract IBPlusTreePagedData SubclassLoad(BPlusTreePagedPageController pc);

    public abstract object GetData();
    public abstract string ToString();
}

public enum PageTypeEnum
{
    Tree,
    Node,
    Key
}

public class BPlusTreePagedPageController
{
    private int ridSize = 8 + 1; // 1 = bool indicate null or not

    PageBufferPool pm = null;

    public BPlusTreePagedPageController(string filePath, int t)
    {
        PageType treeType = new PageType((int)PageTypeEnum.Tree, 20);
        PageType nodeType = new PageType((int)PageTypeEnum.Node, 50 + t * 4 * ridSize);

        pm = PageBufferPool.Create(filePath, 1024 * 10, 100, new List<PageType>() { treeType, nodeType });
    }

    public void Close()
    {
        pm.Close();
    }

    public BPlusTreePaged CreateTree(int t)
    {
        BPlusTreePaged tree = new BPlusTreePaged(t, this);
        tree.rid = pm.AllocateRecord((int)PageTypeEnum.Tree);
        tree.Save(this);

        return tree;
    }

    public RecordId AllocateRecord(int type)
    {
        return pm.AllocateRecord(type);
    }

    public BPlusTreePagedNode CreateNode(List<IBPlusTreePagedData> keys)
    {
        RecordId rid = pm.AllocateRecord((int)PageTypeEnum.Node);
        BPlusTreePagedNode node = new BPlusTreePagedNode(keys, rid);
        return node;
    }

    public RecordStreamReader GetRecordStreamReader(RecordId rid)
    {
        return pm.GetRecordStreamReader(rid);
    }

    public RecordStreamWriter GetRecordStreamWriter(RecordId rid)
    {
        return pm.GetRecordStreamWriter(rid);
    }
}

public class BPlusTreePaged
{
    public RecordId rid = null;
    public int t;

    public RecordId rootRid = null;
    public BPlusTreePagedNode root = null;

    public Dictionary<RecordId, object> ridCache = new Dictionary<RecordId, object>();

    public BPlusTreePagedPageController pc = null;

    public BPlusTreePaged(int t, BPlusTreePagedPageController pc)
    {
        this.t = t;
        this.pc = pc;
    }

    public void Insert(IBPlusTreePagedData key)
    {
        if (t < 2)
            throw new Exception();

        if (GetRoot() == null)
            SetRoot(new BPlusTreePagedNode(new List<IBPlusTreePagedData>(), pc.AllocateRecord((int)PageTypeEnum.Node)));

        FindLeafToInsert(GetRoot(), key);
    }

    public BPlusTreePagedNode GetRoot()
    {
        root = GetNode(rootRid);
        return root;
    }

    public BPlusTreePagedNode GetNode(RecordId rid)
    {
        if (rid == null)
            return null;

        if (ridCache.ContainsKey(rid))
            return (BPlusTreePagedNode)ridCache[rid];
        else
        {
            BPlusTreePagedNode n = BPlusTreePagedNode.Load(rid, pc);
            ridCache[rid] = n;
            return n;
        }
    }

    private void SetRoot(BPlusTreePagedNode n)
    {
        if (n == null)
        {
            root = null;
            rootRid = null;
        }
        else
        {
            root = n;
            rootRid = n.rid;
        }
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
                        leftData.rightData.SetLeftData(key);

                    key.SetRightData(leftData.rightData);
                    key.SetLeftData(leftData);
                    leftData.SetRightData(key);
                }
                else
                {
                    IBPlusTreePagedData originalData = node.keys[i];

                    if (originalData.leftData != null)
                        originalData.leftData.SetRightData(key);

                    key.SetLeftData(originalData.leftData);
                    key.SetRightData(originalData);
                    originalData.SetLeftData(key);
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
            left = new BPlusTreePagedNode(node.keys.GetRange(0, t), pc.AllocateRecord((int)PageTypeEnum.Node));
            right = new BPlusTreePagedNode(node.keys.GetRange(t, t), pc.AllocateRecord((int)PageTypeEnum.Node));
            key = key.CloneKeyOnly();
        }
        else // internal node works in the same way as BTree
        {
            left = new BPlusTreePagedNode(node.keys.GetRange(0, t), pc.AllocateRecord((int)PageTypeEnum.Node));
            right = new BPlusTreePagedNode(node.keys.GetRange(t + 1, t - 1), pc.AllocateRecord((int)PageTypeEnum.Node));

            left.children.AddRange(node.children.GetRange(0, t + 1));
            right.children.AddRange(node.children.GetRange(t + 1, t));

            foreach (BPlusTreePagedNode child in left.children)
                child.SetParent(left);
            foreach (BPlusTreePagedNode child in right.children)
                child.SetParent(right);
        }

        if (node.parent == null)
        {
            SetRoot(new BPlusTreePagedNode(new List<IBPlusTreePagedData>(), pc.AllocateRecord((int)PageTypeEnum.Node)));
            node.SetParent(root);
        }
        left.SetParent(node.parent);
        right.SetParent(node.parent);

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
            SetRoot(null);

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
            SetRoot(left);
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

    public void Save(BPlusTreePagedPageController pc)
    {
        RecordStreamWriter writer = pc.GetRecordStreamWriter(rid);
        writer.WriteInt(t);
        writer.WriteRecord(rid);
        writer.WriteRecord(rootRid);
    }

    public static BPlusTreePaged LoadTree(BPlusTreePagedPageController pc)
    {
        RecordId rid = new RecordId(0, 0);

        RecordStreamReader reader = pc.GetRecordStreamReader(rid);
        int t = reader.ReadInt();
        BPlusTreePaged tree = new BPlusTreePaged(t, pc);
        tree.rid = reader.ReadRecord();
        tree.rootRid = reader.ReadRecord();

        return tree;
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

public class BPlusTreePagedNode
{
    // Serialized fields
    public RecordId rid = null;
    public RecordId parentRid = null;

    public BPlusTreePagedNode parent = null;
    public List<IBPlusTreePagedData> keys = new List<IBPlusTreePagedData>();
    public List<BPlusTreePagedNode> children = new List<BPlusTreePagedNode>();

    // Non-Serialized fields
    public BPlusTreePagedPageController pc;

    public BPlusTreePagedNode(RecordId rid)
    {
        this.rid = rid;
    }

    public BPlusTreePagedNode(List<IBPlusTreePagedData> keys, RecordId rid)
    {
        this.rid = rid;
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

    public void Save(BPlusTreePagedPageController pc)
    {
        RecordStreamWriter writer = pc.GetRecordStreamWriter(rid);
        writer.WriteRecord(parentRid);

        writer.WriteInt(keys.Count);
        for (int i = 0; i < keys.Count; i++)
            keys[i].Save(pc);

        writer.WriteInt(children.Count);
        for (int i = 0; i < children.Count; i++)
            writer.WriteRecord(children[i].rid);
    }

    public static BPlusTreePagedNode Load(RecordId rid, BPlusTreePagedPageController pc)
    {
        BPlusTreePagedNode n = new BPlusTreePagedNode(rid);
        RecordStreamReader reader = pc.GetRecordStreamReader(rid);
        n.parentRid = reader.ReadRecord();

        return n;
    }

    public void SetParent(BPlusTreePagedNode parent)
    {
        if (parent == null)
        {
            this.parent = null;
            parentRid = null;
        }
        else
        {
            this.parent = parent;
            parentRid = parent.rid;
        }
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