public abstract class IBPlusTreePagedData
{
    public RecordId rid = null;
    public RecordId leftDataRid = null;
    public RecordId rightDataRid = null;

    public IBPlusTreePagedData leftData = null;
    public IBPlusTreePagedData rightData = null;


    public void Save(PageBufferPool pageBufferPool)
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        SubclassSave(pageBufferPool);

        writer.WriteRecord(leftDataRid);
        writer.WriteRecord(rightDataRid);
    }

    public IBPlusTreePagedData Load(RecordId rid, PageBufferPool pageBufferPool)
    {
        IBPlusTreePagedData data = SubclassLoad(pageBufferPool);

        data.rid = rid;
        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
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
    public abstract void SubclassSave(PageBufferPool pageBufferPool);
    public abstract IBPlusTreePagedData SubclassLoad(PageBufferPool pageBufferPool);

    public abstract object GetData();
    public abstract string ToString();
}

public enum BPlusTreePaged_PageTypeEnum
{
    Tree,
    Node,
    Key
}

public static class BPlusTreePaged_PageTypeFactory
{
    public static PageType GetTreeType()
    {
        return new PageType((int)BPlusTreePaged_PageTypeEnum.Tree, 100);
    }

    public static PageType GetNodeType(int t)
    {
        int ridSize = 9;
        return new PageType((int)BPlusTreePaged_PageTypeEnum.Node, 50 + t * 4 * ridSize);
    }
}

public class BPlusTreePaged
{
    public RecordId rid = null;
    private int _t;
    private RecordId _rootRid = null;

    public Dictionary<RecordId, object> ridCache = new Dictionary<RecordId, object>();
    public PageBufferPool pageBufferPool = null;

    public BPlusTreePaged(int t, PageBufferPool pageBufferPool)
    {
        rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Tree);
        this.pageBufferPool = pageBufferPool;
        SetT(t);
    }

    public void SetT(int t)
    {
        _t = t;
        Save();
    }

    public int GetT()
    {
        return _t;
    }

    public RecordId GetRootRid()
    {
        return _rootRid;
    }

    public void SetRootRid(RecordId rid)
    {
        _rootRid = rid;
        Save();
    }

    public void Insert(IBPlusTreePagedData key)
    {
        if (GetT() < 2)
            throw new Exception();

        if (GetRootRid() == null)
        {
            BPlusTreePagedNode node = BPlusTreePagedNode.CreateForNew(pageBufferPool, new List<IBPlusTreePagedData>());
            SetRootRid(node.rid);
        }

        FindLeafToInsert(GetNode(GetRootRid()), key);
    }

    public BPlusTreePagedNode GetNode(RecordId rid)
    {
        if (rid == null)
            return null;

        if (ridCache.ContainsKey(rid))
            return (BPlusTreePagedNode)ridCache[rid];
        else
        {
            BPlusTreePagedNode n = BPlusTreePagedNode.Load(rid, pageBufferPool);
            ridCache[rid] = n;
            return n;
        }
    }

    private void InsertUpward(BPlusTreePagedNode node, IBPlusTreePagedData key, BPlusTreePagedNode left, BPlusTreePagedNode right)
    {
        int i = GetKeyInsertPosition(node, key);

        node.keys.Insert(i, key);

        if (node.GetChildrenCount() != 0)
            node.RemoveChildAt(i);

        node.InsertChild(i, left.rid);
        node.InsertChild(i + 1, right.rid);

        if (node.keys.Count == 2 * GetT())
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

            if (node.keys.Count == 2 * GetT())
            {
                Split(node);
            }
        }
        else
        {
            FindLeafToInsert(GetNode(node.GetChild(i)), key);
        }
    }

    private void Split(BPlusTreePagedNode node)
    {
        IBPlusTreePagedData key = node.keys[GetT()];

        BPlusTreePagedNode left = null;
        BPlusTreePagedNode right = null;

        // leaf
        if (node.GetChildrenCount() == 0)
        {
            left = BPlusTreePagedNode.CreateForNew(pageBufferPool, node.keys.GetRange(0, GetT()));
            right = BPlusTreePagedNode.CreateForNew(pageBufferPool, node.keys.GetRange(GetT(), GetT()));
            key = key.CloneKeyOnly();
        }
        else // internal node works in the same way as BTree
        {
            left = BPlusTreePagedNode.CreateForNew(pageBufferPool, node.keys.GetRange(0, GetT()));
            right = BPlusTreePagedNode.CreateForNew(pageBufferPool, node.keys.GetRange(GetT() + 1, GetT() - 1));

            left.AddChildrenRange(node.GetChildrenRange(0, GetT() + 1));
            right.AddChildrenRange(node.GetChildrenRange(GetT() + 1, GetT()));

            for (int i = 0; i < left.GetChildrenCount(); i++)
                GetNode(left.GetChild(i)).SetParentRid(left.rid);
            for (int i = 0; i < right.GetChildrenCount(); i++)
                GetNode(right.GetChild(i)).SetParentRid(right.rid);
        }

        if (GetNode(node.GetParentRid()) == null)
        {
            BPlusTreePagedNode n = BPlusTreePagedNode.CreateForNew(pageBufferPool, new List<IBPlusTreePagedData>());
            SetRootRid(n.rid);
            node.SetParentRid(GetRootRid());
        }
        left.SetParentRid(node.GetParentRid());
        right.SetParentRid(node.GetParentRid());

        InsertUpward(GetNode(node.GetParentRid()), key, left, right);
    }

    public int KeyCount()
    {
        if (GetRootRid() == null)
            return 0;

        return KeyCountInternal(GetNode(GetRootRid()));
    }

    private int KeyCountInternal(BPlusTreePagedNode node)
    {
        int keyCount = node.keys.Count;
        for (int i = 0; i < node.GetChildrenCount(); i++)
            keyCount += KeyCountInternal(GetNode(node.GetChild(i)));

        return keyCount;
    }

    public List<IBPlusTreePagedData> Find(IComparable key)
    {
        if (GetRootRid() == null)
            return new List<IBPlusTreePagedData>();

        return FindInternal(GetNode(GetRootRid()), key);
    }

    private List<IBPlusTreePagedData> FindInternal(BPlusTreePagedNode node, IComparable key)
    {
        while (node != null && !node.IsLeaf())
        {
            int childIndex = 0;
            while (childIndex < node.keys.Count && key.CompareTo(node.keys[childIndex].GetKey()) >= 0)
                childIndex++;

            node = GetNode(node.GetChild(childIndex));
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
        while (DeleteInternal(GetNode(GetRootRid()), key))
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

        if (node == GetNode(GetRootRid()) && node.keys.Count == 0)
            SetRootRid(null);

        return true;
    }

    private void Merge(BPlusTreePagedNode node, int leftChildIndex, int rightChildIndex)
    {
        BPlusTreePagedNode left = GetNode(node.GetChild(leftChildIndex));
        BPlusTreePagedNode right = GetNode(node.GetChild(rightChildIndex));

        if (!left.IsLeaf())
        {
            BPlusTreePagedNode max = GetNode(left.GetChild(left.GetChildrenCount() - 1));
            while (!max.IsLeaf())
                max = GetNode(max.GetChild(max.GetChildrenCount() - 1));
            left.keys.Add(max.keys[max.keys.Count - 1].CloneKeyOnly());
        }
        left.keys.AddRange(right.keys);
        left.AddChildrenRange(right.GetChildrenRange(0, right.GetChildrenCount()));
        node.keys.RemoveAt(rightChildIndex - 1);
        node.RemoveChildAt(rightChildIndex);

        // root case
        if (node == GetNode(GetRootRid()) && node.keys.Count == 0)
            SetRootRid(left.rid);
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

        if (DeleteInternal(GetNode(node.GetChild(firstChildIndex)), key))
        {
            childIndex = firstChildIndex;
        }
        else if (secondChildIndex != -1 && DeleteInternal(GetNode(node.GetChild(secondChildIndex)), key))
        {
            childIndex = secondChildIndex;
        }

        if (childIndex == -1)
            return false;

        BPlusTreePagedNode childNode = GetNode(node.GetChild(childIndex));

        if (childNode.keys.Count >= GetT() - 1)
            return true;

        if (childIndex == node.keys.Count)
        {
            BPlusTreePagedNode leftSibling = GetNode(node.GetChild(childIndex - 1));

            // merge
            if (leftSibling.keys.Count == GetT() - 1)
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
                    BPlusTreePagedNode max = GetNode(leftSibling.GetChild(leftSibling.GetChildrenCount() - 1));
                    while (!max.IsLeaf())
                        max = GetNode(max.GetChild(max.GetChildrenCount() - 1));
                    childNode.keys.Insert(0, max.keys[max.keys.Count - 1].CloneKeyOnly());
                    childNode.InsertChild(0, leftSibling.GetChild(leftSibling.GetChildrenCount() - 1));
                    node.keys[childIndex - 1] = leftSibling.keys[leftSibling.keys.Count - 1];

                    leftSibling.RemoveChildAt(leftSibling.GetChildrenCount() - 1);
                    leftSibling.keys.RemoveAt(leftSibling.keys.Count - 1);
                }
            }
        }
        else
        {
            BPlusTreePagedNode rightSibling = GetNode(node.GetChild(childIndex + 1));

            // merge
            if (rightSibling.keys.Count == GetT() - 1)
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
                    BPlusTreePagedNode min = GetNode(rightSibling.GetChild(0));
                    while (!min.IsLeaf())
                        min = GetNode(min.GetChild(0));
                    childNode.keys.Add(min.keys[0].CloneKeyOnly());
                    childNode.AddChild(rightSibling.GetChild(0));
                    node.keys[childIndex] = rightSibling.keys[0];

                    rightSibling.RemoveChildAt(0);
                    rightSibling.keys.RemoveAt(0);
                }
            }
        }

        return true;
    }

    public void Save()
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteInt(GetT());
        writer.WriteRecord(GetRootRid());
    }

    public static BPlusTreePaged LoadTree(PageBufferPool pageBufferPool)
    {
        RecordId rid = new RecordId(0, 0);

        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
        int t = reader.ReadInt();
        BPlusTreePaged tree = new BPlusTreePaged(t, pageBufferPool);
        tree.rid = rid;
        tree.SetRootRid(reader.ReadRecord());

        return tree;
    }

    private int getString(int level, BPlusTreePagedNode currentNode, List<List<string>> nodeStringByLevel)
    {
        if (level == nodeStringByLevel.Count)
            nodeStringByLevel.Add(new List<string>());

        string currentNodeString = currentNode.ToString();
        int childrenWidth = 0;
        for (int i = 0; i < currentNode.GetChildrenCount(); i++)
            childrenWidth += getString(level + 1, GetNode(currentNode.GetChild(i)), nodeStringByLevel);

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

        if (GetRootRid() == null)
            return ret;

        List<List<string>> nodeStringByLevel = new List<List<string>>();
        getString(0, GetNode(GetRootRid()), nodeStringByLevel);

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

    public RecordId rid = null;
    private RecordId _parentRid = null;

    public List<IBPlusTreePagedData> keys = new List<IBPlusTreePagedData>();

    public List<RecordId> _children = new List<RecordId>();

    private PageBufferPool pageBufferPool = null;

    private BPlusTreePagedNode(PageBufferPool pageBufferPool)
    {
        this.pageBufferPool = pageBufferPool;
    }

    public static BPlusTreePagedNode CreateForLoad(PageBufferPool pageBufferPool, RecordId rid)
    {
        BPlusTreePagedNode n = new BPlusTreePagedNode(pageBufferPool);
        n.pageBufferPool = pageBufferPool;

        n.rid = rid;
        return n;
    }

    public RecordId GetParentRid()
    {
        return _parentRid;
    }

    public void SetParentRid(RecordId parentRid)
    {
        _parentRid = parentRid;
        Save();
    }

    public RecordId GetChild(int i)
    {
        return _children[i];
    }

    public int GetChildrenCount()
    {
        return _children.Count;
    }

    public List<RecordId> GetChildrenRange(int start, int count)
    {
        return _children.GetRange(start, count);
    }

    public void InsertChild(int i, RecordId child)
    {
        _children.Insert(i, child);
        Save();
    }

    public void RemoveChildAt(int i)
    {
        _children.RemoveAt(i);
        Save();
    }

    public void AddChild(RecordId child)
    {
        _children.Add(child);
        Save();
    }

    public void AddChildrenRange(List<RecordId> children)
    {
        _children.AddRange(children);
        Save();
    }

    public static BPlusTreePagedNode CreateForNew(PageBufferPool pageBufferPool, List<IBPlusTreePagedData> keys)
    {
        BPlusTreePagedNode n = new BPlusTreePagedNode(pageBufferPool);
        n.rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Node);
        n.keys = keys;

        return n;
    }

    public bool IsLeaf()
    {
        return GetChildrenCount() == 0;
    }

    public bool IsInternal()
    {
        return !IsLeaf();
    }

    public void Save()
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteRecord(GetParentRid());

        writer.WriteInt(keys.Count);
        for (int i = 0; i < keys.Count; i++)
            keys[i].Save(pageBufferPool);

        writer.WriteInt(_children.Count);
        for (int i = 0; i < _children.Count; i++)
            writer.WriteRecord(_children[i]);
    }

    public static BPlusTreePagedNode Load(RecordId rid, PageBufferPool pageBufferPool)
    {
        BPlusTreePagedNode n = BPlusTreePagedNode.CreateForLoad(pageBufferPool, rid);
        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
        n.SetParentRid(reader.ReadRecord());

        int keyCount = reader.ReadInt();
        for (int i = 0; i < keyCount; i++)
        {
            IBPlusTreePagedData key = null;
            key = key.Load(reader.ReadRecord(), pageBufferPool);
            n.keys.Add(key);
        }

        int childCount = reader.ReadInt();
        for (int i = 0; i < childCount; i++)
        {
            RecordId childRid = reader.ReadRecord();
            n.AddChild(childRid);
        }

        return n;
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