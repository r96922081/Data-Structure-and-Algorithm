private fun bfs2(g : Graph, s : Int, t : Int, visited : MutableList<Boolean>, prev : MutableList<Int>, path : MutableList<Int>) : Boolean {

    var queue = ArrayDeque<Int>()
    queue.addFirst(s)
    visited[s] = true

    while (queue.isNotEmpty()) {
        var v = queue.last()
        queue.removeLast()

        if (v == t) {
            var prevIndex = v
            do  {
                path.add(0, prevIndex)
                prevIndex = prev[prevIndex]
            } while (prevIndex != -1)

            return true
        }

        for (next in g.edgeAdjList[v]) {
            var v2 = next.index
            if (visited[v2])
                continue

            visited[v2] = true
            prev[v2] = v
            queue.addFirst(v2)
        }
    }

    return false
}

fun bfs(g : Graph, src : String, dest : String) : List<String>? {
    var s = g.vertexToIndex[src]!!
    var t = g.vertexToIndex[dest]!!
    var visited = mutableListOf<Boolean>()
    var prev = mutableListOf<Int>()
    var path = mutableListOf<Int>()


    for (i in 0 until g.vertexCount) {
        visited.add(false)
        prev.add(-1)
    }

    var found = bfs2(g, s, t, visited, prev, path)
    if (!found)
        return null

    var path2 = mutableListOf<String>()
    for (p in path) {
        path2.add(g.getVertex(p))
    }
    return path2
}