public enum BPlusTreePaged_PageTypeEnum
{
    Tree,
    Node,
    Key,
    Data
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

    public static PageType GetKeyType()
    {
        int ridSize = 9;
        return new PageType((int)BPlusTreePaged_PageTypeEnum.Key, 10 * ridSize);
    }

    public static PageType GetDataType(int size)
    {
        return new PageType((int)BPlusTreePaged_PageTypeEnum.Data, size);
    }
}

public class BPlusTreePaged
{
    public RecordId rid = null;
    private int _t;
    private RecordId _rootRid = null;

    public PageBufferPool pageBufferPool = null;
    public IBPlusTreePagedData dummyData;

    private BPlusTreePaged()
    {

    }

    public BPlusTreePaged(int t, PageBufferPool pageBufferPool, IBPlusTreePagedData dummyData)
    {
        rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Tree, this);
        this.pageBufferPool = pageBufferPool;
        SetT(t);
        this.dummyData = dummyData;
    }

    public void Save()
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteInt(GetT());
        writer.WriteRecord(GetRootRid());
    }

    public static BPlusTreePaged Load(PageBufferPool pageBufferPool, IBPlusTreePagedData dummyData)
    {
        BPlusTreePaged tree = new BPlusTreePaged();
        tree.rid = new RecordId(0, 0);
        tree.pageBufferPool = pageBufferPool;
        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(tree.rid);
        tree._t = reader.ReadInt();
        tree._rootRid = reader.ReadRecord();
        tree.dummyData = dummyData;

        return tree;
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

    public void Insert(BPlusTreePagedKey key)
    {
        if (GetT() < 2)
            throw new Exception();

        if (GetRootRid() == null)
        {
            BPlusTreePagedNode node = new BPlusTreePagedNode(pageBufferPool, new List<RecordId>(), dummyData);
            SetRootRid(node.rid);
        }

        FindLeafToInsert(GetNode(GetRootRid()), key);
    }

    public BPlusTreePagedNode GetNode(RecordId rid)
    {
        if (rid == null)
            return null;

        object cached = pageBufferPool.GetCachedRecord(rid);

        if (cached != null)
            return (BPlusTreePagedNode)cached;
        else
            return BPlusTreePagedNode.Load(pageBufferPool, rid, dummyData);
    }

    public BPlusTreePagedKey GetKey(RecordId rid)
    {
        if (rid == null)
            return null;

        object cached = pageBufferPool.GetCachedRecord(rid);

        if (cached != null)
            return (BPlusTreePagedKey)cached;
        else
            return BPlusTreePagedKey.Load(pageBufferPool, rid, dummyData);
    }

    private void InsertUpward(BPlusTreePagedNode node, BPlusTreePagedKey key, BPlusTreePagedNode left, BPlusTreePagedNode right)
    {
        int i = GetKeyInsertPosition(node, key);

        node.InsertKey(i, key.rid);

        if (node.GetChildrenCount() != 0)
            node.RemoveChildAt(i);

        node.InsertChild(i, left.rid);
        node.InsertChild(i + 1, right.rid);

        if (node.GetKeyCount() == 2 * GetT())
        {
            Split(node);
        }
    }

    private int GetKeyInsertPosition(BPlusTreePagedNode node, BPlusTreePagedKey key)
    {
        int i = 0;
        for (; i < node.GetKeyCount(); i++)
        {
            if (key.GetComparableKey().CompareTo(GetKey(node.GetKeyAt(i)).GetComparableKey()) < 0)
                break;
        }
        return i;
    }

    private void FindLeafToInsert(BPlusTreePagedNode node, BPlusTreePagedKey key)
    {
        int i = GetKeyInsertPosition(node, key);

        if (node.IsLeaf())
        {
            if (node.GetKeyCount() > 0)
            {
                if (i == node.GetKeyCount())
                {
                    BPlusTreePagedKey leftData = GetKey(node.GetKeyAt(i - 1));
                    if (leftData.GetRight() != null)
                        GetKey(leftData.GetRight()).SetLeft(key.rid);

                    key.SetRight(leftData.GetRight());
                    key.SetLeft(leftData.rid);
                    leftData.SetRight(key.rid);
                }
                else
                {
                    BPlusTreePagedKey originalData = GetKey(node.GetKeyAt(i));

                    if (originalData.GetLeft() != null)
                        GetKey(originalData.GetLeft()).SetRight(key.rid);

                    key.SetLeft(originalData.GetLeft());
                    key.SetRight(originalData.rid);
                    originalData.SetLeft(key.rid);
                }
            }


            node.InsertKey(i, key.rid);

            if (node.GetKeyCount() == 2 * GetT())
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
        BPlusTreePagedKey key = GetKey(node.GetKeyAt(GetT()));

        BPlusTreePagedNode left = null;
        BPlusTreePagedNode right = null;

        // leaf
        if (node.GetChildrenCount() == 0)
        {
            left = new BPlusTreePagedNode(pageBufferPool, node.GetKeyRange(0, GetT()), dummyData);
            right = new BPlusTreePagedNode(pageBufferPool, node.GetKeyRange(GetT(), GetT()), dummyData);
            key = GetKey(key.CloneKeyOnly());
        }
        else // internal node works in the same way as BTree
        {
            left = new BPlusTreePagedNode(pageBufferPool, node.GetKeyRange(0, GetT()), dummyData);
            right = new BPlusTreePagedNode(pageBufferPool, node.GetKeyRange(GetT() + 1, GetT() - 1), dummyData);

            left.AddChildrenRange(node.GetChildrenRange(0, GetT() + 1));
            right.AddChildrenRange(node.GetChildrenRange(GetT() + 1, GetT()));

            for (int i = 0; i < left.GetChildrenCount(); i++)
                GetNode(left.GetChild(i)).SetParentRid(left.rid);
            for (int i = 0; i < right.GetChildrenCount(); i++)
                GetNode(right.GetChild(i)).SetParentRid(right.rid);
        }

        if (GetNode(node.GetParentRid()) == null)
        {
            BPlusTreePagedNode n = new BPlusTreePagedNode(pageBufferPool, new List<RecordId>(), dummyData);
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
        int keyCount = node.GetKeyCount();
        for (int i = 0; i < node.GetChildrenCount(); i++)
            keyCount += KeyCountInternal(GetNode(node.GetChild(i)));

        return keyCount;
    }

    public List<BPlusTreePagedKey> Find(IComparable key)
    {
        if (GetRootRid() == null)
            return new List<BPlusTreePagedKey>();

        return FindInternal(GetNode(GetRootRid()), key);
    }

    private List<BPlusTreePagedKey> FindInternal(BPlusTreePagedNode node, IComparable key)
    {
        while (node != null && !node.IsLeaf())
        {
            int childIndex = 0;
            while (childIndex < node.GetKeyCount() && key.CompareTo(GetKey(node.GetKeyAt(childIndex)).GetComparableKey()) >= 0)
                childIndex++;

            node = GetNode(node.GetChild(childIndex));
        }

        int keyIndex = 0;
        while (keyIndex < node.GetKeyCount() && key.CompareTo(GetKey(node.GetKeyAt(keyIndex)).GetComparableKey()) < 0)
            keyIndex++;

        if (keyIndex >= node.GetKeyCount() || key.CompareTo(GetKey(node.GetKeyAt(keyIndex)).GetComparableKey()) != 0)
            return new List<BPlusTreePagedKey>();

        List<BPlusTreePagedKey> found = new List<BPlusTreePagedKey>();

        BPlusTreePagedKey firstFound = GetKey(node.GetKeyAt(keyIndex));

        BPlusTreePagedKey leftData = GetKey(firstFound.GetLeft());
        while (leftData != null)
        {
            if (key.CompareTo(leftData.GetComparableKey()) != 0)
                break;

            found.Insert(0, leftData);
            leftData = GetKey(leftData.GetLeft());
        }

        found.Add(firstFound);

        BPlusTreePagedKey rightData = GetKey(firstFound.GetRight());
        while (rightData != null)
        {
            if (key.CompareTo(rightData.GetComparableKey()) != 0)
                break;

            found.Insert(0, rightData);
            rightData = GetKey(rightData.GetRight());
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
        for (; index < node.GetKeyCount(); index++)
        {
            if (key.CompareTo(GetKey(node.GetKeyAt(index)).GetComparableKey()) < 0)
                return false;

            if (key.CompareTo(GetKey(node.GetKeyAt(index)).GetComparableKey()) == 0)
                break;
        }
        if (index == node.GetKeyCount())
            return false;

        RecordId left = GetKey(node.GetKeyAt(index)).GetLeft();
        RecordId right = GetKey(node.GetKeyAt(index)).GetRight();

        if (left == null && right == null)
        {

        }
        else if (left != null && right != null)
        {
            GetKey(left).SetRight(right);
            GetKey(right).SetLeft(left);
        }
        else if (left != null && right == null)
        {
            GetKey(left).SetRight(null);
        }
        else if (left == null && right != null)
        {
            GetKey(right).SetLeft(null);
        }

        node.RemoveKeyAt(index);

        if (node.rid == GetRootRid() && node.GetKeyCount() == 0)
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
            left.AddKey(GetKey(max.GetKeyAt(max.GetKeyCount() - 1)).CloneKeyOnly());
        }
        left.AddKeyRange(right.GetKeyRange(0, right.GetKeyCount()));
        left.AddChildrenRange(right.GetChildrenRange(0, right.GetChildrenCount()));
        node.RemoveKeyAt(rightChildIndex - 1);
        node.RemoveChildAt(rightChildIndex);

        // root case
        if (node.rid == GetRootRid() && node.GetKeyCount() == 0)
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

        while (firstChildIndex < node.GetKeyCount() && key.CompareTo(GetKey(node.GetKeyAt(firstChildIndex)).GetComparableKey()) >= 0)
        {
            // Consider both side if equal  
            //        [2]
            //   [1]      [2]
            // [0]  [2] [2]  [3]

            if (key.CompareTo(GetKey(node.GetKeyAt(firstChildIndex)).GetComparableKey()) == 0)
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

        if (childNode.GetKeyCount() >= GetT() - 1)
            return true;

        if (childIndex == node.GetKeyCount())
        {
            BPlusTreePagedNode leftSibling = GetNode(node.GetChild(childIndex - 1));

            // merge
            if (leftSibling.GetKeyCount() == GetT() - 1)
            {
                Merge(node, childIndex - 1, childIndex);
            }
            // borrow from left
            else
            {
                if (leftSibling.IsLeaf())
                {
                    childNode.InsertKey(0, leftSibling.GetKeyAt(leftSibling.GetKeyCount() - 1));
                    node.SetKeyAt(childIndex - 1, GetKey(childNode.GetKeyAt(0)).CloneKeyOnly());
                    leftSibling.RemoveKeyAt(leftSibling.GetKeyCount() - 1);
                }
                else
                {
                    BPlusTreePagedNode max = GetNode(leftSibling.GetChild(leftSibling.GetChildrenCount() - 1));
                    while (!max.IsLeaf())
                        max = GetNode(max.GetChild(max.GetChildrenCount() - 1));
                    childNode.InsertKey(0, GetKey(max.GetKeyAt(max.GetKeyCount() - 1)).CloneKeyOnly());
                    childNode.InsertChild(0, leftSibling.GetChild(leftSibling.GetChildrenCount() - 1));
                    node.SetKeyAt(childIndex - 1, leftSibling.GetKeyAt(leftSibling.GetKeyCount() - 1));

                    leftSibling.RemoveChildAt(leftSibling.GetChildrenCount() - 1);
                    leftSibling.RemoveKeyAt(leftSibling.GetKeyCount() - 1);
                }
            }
        }
        else
        {
            BPlusTreePagedNode rightSibling = GetNode(node.GetChild(childIndex + 1));

            // merge
            if (rightSibling.GetKeyCount() == GetT() - 1)
            {
                Merge(node, childIndex, childIndex + 1);
            }
            // borrow from right
            else
            {
                if (rightSibling.IsLeaf())
                {
                    childNode.AddKey(rightSibling.GetKeyAt(0));
                    node.SetKeyAt(childIndex, GetKey(rightSibling.GetKeyAt(1)).CloneKeyOnly());
                    rightSibling.RemoveKeyAt(0);
                }
                else
                {
                    BPlusTreePagedNode min = GetNode(rightSibling.GetChild(0));
                    while (!min.IsLeaf())
                        min = GetNode(min.GetChild(0));
                    childNode.AddKey(GetKey(min.GetKeyAt(0)).CloneKeyOnly());
                    childNode.AddChild(rightSibling.GetChild(0));
                    node.SetKeyAt(childIndex, rightSibling.GetKeyAt(0));

                    rightSibling.RemoveChildAt(0);
                    rightSibling.RemoveKeyAt(0);
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

    public List<RecordId> _keys = new List<RecordId>();
    public List<RecordId> _children = new List<RecordId>();
    private PageBufferPool pageBufferPool = null;
    private IBPlusTreePagedData dummyData = null;

    private BPlusTreePagedNode()
    {

    }

    public BPlusTreePagedNode(PageBufferPool pageBufferPool, List<RecordId> keys, IBPlusTreePagedData dummyData)
    {
        rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Node, this);
        this.pageBufferPool = pageBufferPool;
        this.dummyData = dummyData;
        AddKeyRange(keys);
    }

    public void Save()
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteRecord(GetParentRid());

        writer.WriteInt(_keys.Count);
        for (int i = 0; i < _keys.Count; i++)
            writer.WriteRecord(_keys[i]);

        writer.WriteInt(_children.Count);
        for (int i = 0; i < _children.Count; i++)
            writer.WriteRecord(_children[i]);
    }

    public static BPlusTreePagedNode Load(PageBufferPool pageBufferPool, RecordId rid, IBPlusTreePagedData dummyData)
    {
        BPlusTreePagedNode n = new BPlusTreePagedNode();
        n.pageBufferPool = pageBufferPool;
        n.rid = rid;
        n.dummyData = dummyData;

        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
        // do not use:   n.SetParentRid(reader.ReadRecord())
        // Because it will call Save(), then write keyCount = 0 to page buffer, and next time you read will get 0
        n._parentRid = reader.ReadRecord();

        int keyCount = reader.ReadInt();
        for (int i = 0; i < keyCount; i++)
            n._keys.Add(reader.ReadRecord());

        int childCount = reader.ReadInt();
        for (int i = 0; i < childCount; i++)
            n.AddChild(reader.ReadRecord());

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

    public void SetKeyAt(int i, RecordId rid)
    {
        _keys[i] = rid;
        Save();
    }

    public RecordId GetKeyAt(int i)
    {
        return _keys[i];
    }

    public int GetKeyCount()
    {
        return _keys.Count;
    }

    public List<RecordId> GetKeyRange(int start, int count)
    {
        return _keys.GetRange(start, count);
    }

    public void InsertKey(int i, RecordId key)
    {
        _keys.Insert(i, key);
        Save();
    }

    public void RemoveKeyAt(int i)
    {
        _keys.RemoveAt(i);
        Save();
    }

    public void AddKey(RecordId key)
    {
        _keys.Add(key);
        Save();
    }

    public void AddKeyRange(List<RecordId> keys)
    {
        _keys.AddRange(keys);
        Save();
    }

    public bool IsLeaf()
    {
        return GetChildrenCount() == 0;
    }

    public bool IsInternal()
    {
        return !IsLeaf();
    }

    public BPlusTreePagedKey GetKey(RecordId rid)
    {
        if (rid == null)
            return null;

        object cached = pageBufferPool.GetCachedRecord(rid);

        if (cached != null)
            return (BPlusTreePagedKey)cached;
        else
            return BPlusTreePagedKey.Load(pageBufferPool, rid, dummyData);
    }

    public override string ToString()
    {
        string s = "[";
        foreach (RecordId key2 in _keys)
        {
            BPlusTreePagedKey key = GetKey(key2);
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

public class BPlusTreePagedKey
{
    public RecordId rid = null;
    private RecordId _leftRid = null;
    private RecordId _rightRid = null;
    private RecordId _dataRid = null;
    private IBPlusTreePagedData dummyData;

    PageBufferPool pageBufferPool;

    private BPlusTreePagedKey()
    {
    }

    public BPlusTreePagedKey(PageBufferPool pageBufferPool, RecordId dataRid, IBPlusTreePagedData dummyData)
    {
        rid = pageBufferPool.AllocateRecord((int)BPlusTreePaged_PageTypeEnum.Key, this);
        this.pageBufferPool = pageBufferPool;
        SetData(dataRid);
        this.dummyData = dummyData;
    }

    public void Save()
    {
        RecordStreamWriter writer = pageBufferPool.GetRecordStreamWriter(rid);
        writer.WriteRecord(_leftRid);
        writer.WriteRecord(_rightRid);
        writer.WriteRecord(_dataRid);
    }

    public static BPlusTreePagedKey Load(PageBufferPool pageBufferPool, RecordId rid, IBPlusTreePagedData dummyData)
    {
        RecordStreamReader reader = pageBufferPool.GetRecordStreamReader(rid);
        BPlusTreePagedKey key = new BPlusTreePagedKey();
        key.pageBufferPool = pageBufferPool;
        key.dummyData = dummyData;

        key._leftRid = reader.ReadRecord();
        key._rightRid = reader.ReadRecord();
        key._dataRid = reader.ReadRecord();
        key.rid = rid;

        return key;
    }

    public RecordId CloneKeyOnly()
    {
        return new BPlusTreePagedKey(pageBufferPool, GetData().CloneKeyOnly(), dummyData).rid;
    }

    public IComparable GetComparableKey()
    {
        return GetData().GetComparableKey();
    }

    public IBPlusTreePagedData GetData()
    {
        if (_dataRid == null)
            return null;

        object cached = pageBufferPool.GetCachedRecord(_dataRid);

        if (cached != null)
            return (IBPlusTreePagedData)cached;
        else
            return dummyData.Load(pageBufferPool, _dataRid);
    }

    public object GetDataValue()
    {
        if (_dataRid == null)
            return null;

        return GetData().GetData();
    }

    public void SetData(RecordId dataRid)
    {
        _dataRid = dataRid;
        Save();
    }

    public void SetLeft(RecordId leftRid)
    {
        _leftRid = leftRid;
        Save();
    }

    public void SetRight(RecordId rightRid)
    {
        _rightRid = rightRid;
        Save();
    }

    public RecordId GetLeft()
    {
        return _leftRid;
    }

    public RecordId GetRight()
    {
        return _rightRid;
    }

    public override string ToString()
    {
        IBPlusTreePagedData data = dummyData.Load(pageBufferPool, _dataRid);
        return data.ToString();
    }
}

public interface IBPlusTreePagedData
{
    public IComparable GetComparableKey();
    public RecordId CloneKeyOnly();
    public void Save(PageBufferPool pageBufferPool);
    public IBPlusTreePagedData Load(PageBufferPool pageBufferPool, RecordId rid);
    public RecordId GetRid();
    public object GetData();
    public string ToString();
}