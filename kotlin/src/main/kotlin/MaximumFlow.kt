import org.junit.Test
import java.util.*

class FordFulkerson {
    fun GetMaxFlowOfDfsPath(g: Graph, path : List<String>) : Int{
        var flow = Int.MAX_VALUE
        for (i in 1 until path.size) {
            var s = path[i-1]!!
            var t = path[i]!!

            var tempFlow = g.getEdge(s, t)
            if (tempFlow < flow) {
                flow = tempFlow
            }
        }
        return flow
    }

    fun UpdateResidualNetwork(g: Graph, path : List<String>, flow : Int) {
        for (i in 1 until path.size) {
            var s = path[i-1]!!
            var t = path[i]!!

            g.setEdge(s,t, g.getEdge(s, t) - flow)
            g.setEdge(t,s, g.getEdge(t, s) + flow)
        }
    }

    fun GetMaxFlow(g : Graph, source : String, sink : String) : Int {

        // use bfs to implement Edmonds-Karp algorithm
        var path = bfs(g, source, sink)
        while (path != null) {
            var flow = GetMaxFlowOfDfsPath(g, path)
            UpdateResidualNetwork(g, path, flow)
            path = bfs(g, "s", "t")
        }

        var maxFlow = 0
        for (t in g.vertexToIndex.keys) {
            maxFlow += g.getEdge(t, source)
        }
        return maxFlow
    }
}

public class MaximumFlowUt {
    @Test
    public fun test1() {
        val g = Graph()

        g.setEdge("s", "1", 16)
        g.setEdge("s", "2", 13)
        g.setEdge("1", "3", 12)
        g.setEdge("2", "1", 4)
        g.setEdge("2", "4", 14)
        g.setEdge("3", "2", 9)
        g.setEdge("3", "t", 20)
        g.setEdge("4", "3", 7)
        g.setEdge("4", "t", 4)

        kotlin.check(FordFulkerson().GetMaxFlow(g, "s", "t") == 23)
    }
}