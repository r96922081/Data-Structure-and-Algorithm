import org.junit.Test

/*
Represent graph by linked-list cannot get edge between 2 nodes in O(1)
Represent graph by matrix, When traverse adjacent nodes of 1 node, it cannot skip non-adjacent nodes
This class is designed to do both
 */

open class Graph {
    data class AdjListData(var index: Int, var weight: Int)

    var vertexCount = 0
    var edgeMatrix = mutableListOf<MutableList<Int>>()
    var edgeAdjList = mutableListOf<MutableList<AdjListData>>()
    var vertexToIndex = mutableMapOf<String, Int>()
    var indexToVertex = mutableMapOf<Int, String>()


    // O(E)
    private fun enlargeEdgeMatrixBy1() {
        for (i in 0 until vertexCount - 1) {
            edgeMatrix[i]!!.add(0)
        }
        var newList = mutableListOf<Int>()
        edgeMatrix.add(newList)
        for (i in 0 until vertexCount) {
            newList.add(0)
        }
    }

    // O(E)
    protected open fun addVertex(s : String) {
        var index = vertexCount
        vertexToIndex[s] = index
        indexToVertex[index] = s
        vertexCount++

        edgeAdjList.add(mutableListOf())
        enlargeEdgeMatrixBy1()
    }

    // O(E)
    fun setEdge(sString : String, tString :String, weight :Int)
    {
        if (!vertexToIndex.contains(sString)) {
            addVertex(sString)
        }

        if (!vertexToIndex.contains(tString)) {
            addVertex(tString)
        }

        var s = vertexToIndex[sString]!!
        var t = vertexToIndex[tString]!!
        edgeMatrix[s][t] = weight

        var adjListOfS = edgeAdjList[s]!!

        var found = false
        for (i in 0 until adjListOfS.size) {
            if (adjListOfS[i].index== t) {
                found = true
                adjListOfS[i].weight = weight
                if (adjListOfS[i].weight == 0) {
                    adjListOfS.removeAt(i)
                }
                break;
            }
        }
        if (!found && weight != 0)
            adjListOfS.add(AdjListData(t, weight))
    }

    // O(1)
    fun getEdge(s: String, t: String): Int {
        return edgeMatrix[vertexToIndex[s]!!][vertexToIndex[t]!!]
    }

    // O(1)
    fun getEdge(s: Int, t: Int): Int {
        return edgeMatrix[s][t]
    }

    // O(logE)
    fun getIndex(vertex : String) : Int {
        return vertexToIndex[vertex]!!
    }

    // O(logE)
    fun getVertex(index : Int) : String {
        return indexToVertex[index]!!
    }
}

public class GraphUt {
    @Test
    public fun test1() {
        val g = Graph()
        g.setEdge("a", "b", 1)
        kotlin.check(g.getEdge("a", "b") == 1)
        kotlin.check(g.edgeAdjList[g.vertexToIndex["a"]!!].size == 1)
        g.setEdge("a", "b", 0)
        kotlin.check(g.edgeAdjList[g.vertexToIndex["a"]!!].size == 0)
        kotlin.check(g.getEdge("a", "b") == 0)

        g.setEdge("a", "c", 2)
        g.setEdge("a", "b", 3)
        kotlin.check(g.getEdge("a", "b") == 3)
        kotlin.check(g.getEdge("b", "c") == 0)
        g.setEdge("b", "c", 4)
        kotlin.check(g.getEdge("b", "c") == 4)
    }
}