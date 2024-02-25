import org.junit.Test

fun Partition(a : ArrayList<Int>, low : Int, high : Int) : Int{
    var pivot = a[high]
    var i = low - 1

    for (j in low until high){
        if (a[j] < pivot){
            i++
            var temp = a[i]
            a[i] = a[j]
            a[j] = temp
        }
    }

    var temp = a[i + 1]
    a[i + 1] = a[high]
    a[high] = temp

    return i + 1
}


fun QucikSort(a : ArrayList<Int>, low : Int, high : Int) {
    if (low < high) {
        var pi = Partition(a, low, high)

        QucikSort(a, low, pi - 1)

        QucikSort(a, pi + 1, high)

    }
}

public class SortingUt {
    @Test
    public fun test1() {
        val a = ArrayList<Int>()

        for (i in 0..9) {
            a.add((0..100).random())
        }

        println(a)
        QucikSort(a, 0, a.size - 1)
        println(a)
    }
}