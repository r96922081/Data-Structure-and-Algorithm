import org.junit.Test

class DisjointSetNode {
    var name: String = ""
    // Rank is upper bound of height. not exactly the height.  That's why we don't update it in path compression in find()
    var rank: Int = 0
    var parent : DisjointSetNode? = null

    constructor(name : String) {
        this.name = name
    }

    fun find() : DisjointSetNode {
        if (parent == null)
            return this
        parent = parent!!.find()
        return parent!!
    }

    fun union(b : DisjointSetNode) {
        var root = find()
        var root2 = b.find()

        if (root.rank > root2.rank) {
            root2.parent = root
        } else if (root.rank == root2.rank) {
            root2.parent = root
            root.rank++
        } else {
            root.parent = root2
        }
    }

    override fun toString() : String{
        var ret = "name = $name, height = $rank, parent = "
        if (parent != null)
            ret += parent!!.name
        else
            ret += "null"
        return ret
    }
}

public class DisjointSetUt {
    @Test
    public fun test1() {
        val a = DisjointSetNode("a")
        val b = DisjointSetNode("b")
        val c = DisjointSetNode("c")
        a.union(b)
        a.union(c)
        kotlin.check(a.rank == 1 && b.rank == 0 && c.rank == 0)

        val d = DisjointSetNode("d")
        val e = DisjointSetNode("e")
        val f = DisjointSetNode("f")
        d.union(e)
        d.union(f)

        d.union(b)
        kotlin.check(a.find() == b.find() && b.find() == c.find() && c.find() == d.find() && d.find() == e.find())
    }
}