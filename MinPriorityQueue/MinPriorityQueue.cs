public class MinPriorityQueue<T> where T : IComparable<T>
{
    private List<T> heap;
    private Dictionary<T, int> indexMap;

    public MinPriorityQueue()
    {
        heap = new List<T>();
        indexMap = new Dictionary<T, int>();
    }

    public void Insert(T key)
    {
        heap.Add(key);
        int index = heap.Count - 1;
        indexMap[key] = index;
        HeapifyUp(index);
    }

    public T Minimum()
    {
        if (heap.Count == 0)
            throw new InvalidOperationException("Priority queue is empty.");
        return heap[0];
    }

    public T ExtractMin()
    {
        if (heap.Count == 0)
            throw new InvalidOperationException("Priority queue is empty.");

        T min = heap[0];
        indexMap.Remove(min);

        if (heap.Count > 1)
        {
            heap[0] = heap[heap.Count - 1];
            indexMap[heap[0]] = 0;
            heap.RemoveAt(heap.Count - 1);
            HeapifyDown(0);
        }
        else
        {
            heap.RemoveAt(0);
        }

        return min;
    }

    public void DecreaseKey(T obj)
    {
        if (!indexMap.ContainsKey(obj))
            throw new ArgumentException("Object not found in the priority queue.");

        int index = indexMap[obj];
        HeapifyUp(index);
    }

    private void HeapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index].CompareTo(heap[parent]) >= 0)
                break;

            Swap(index, parent);
            index = parent;
        }
    }

    private void HeapifyDown(int index)
    {
        int left, right, smallest;

        while (true)
        {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < heap.Count && heap[left].CompareTo(heap[smallest]) < 0)
                smallest = left;

            if (right < heap.Count && heap[right].CompareTo(heap[smallest]) < 0)
                smallest = right;

            if (smallest == index)
                break;

            Swap(index, smallest);
            index = smallest;
        }
    }

    private void Swap(int i, int j)
    {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        indexMap[heap[i]] = i;
        indexMap[heap[j]] = j;
    }
}