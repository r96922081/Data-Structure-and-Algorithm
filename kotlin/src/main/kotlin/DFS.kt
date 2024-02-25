private fun dfs2(g : Graph, s : Int, t : Int, visited : MutableList<Boolean>, path : MutableList<Int>) : Boolean {
    if (s == t) {
        path.add(s)
        return true
    }
    if (visited[s])
        return false

    visited[s] = true

    for (e in g.edgeAdjList[s]!!) {
        var found = dfs2(g, e.index, t, visited, path)
        if (found) {
            path.add(0, s)
            return true
        }
    }

    return false
}

fun dfs(g : Graph, src : String, dest : String) : List<String>? {
    var s = g.vertexToIndex[src]!!
    var t = g.vertexToIndex[dest]!!
    var visited = mutableListOf<Boolean>()
    var path = mutableListOf<Int>()

    for (i in 0 until g.vertexCount) {
        visited.add(false)
    }

    var found = dfs2(g, s, t, visited, path)
    if (!found)
        return null

    var path2 = mutableListOf<String>()
    for (p in path) {
        path2.add(g.getVertex(p))
    }
    return path2
}