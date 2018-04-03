package merge_sort

func Merge(a, b []int) (l []int) {
        //var L= len(a)+len(b)

				//var moitier =L/2
				var i=0
				var i1=0

				for i < len(a) && i1 < len(b){
					if a[i]<b[i1]{
					l=append(l,a[i])
					i++
					}else{
						l=append(l,b[i1])
						i1++}
				}
				if i <len(a){
					l = append(l,a[i:]...)
				}
				if i1 <len(b){
					l= append(l,b[i1:]...)
				}
				return 
}
func MergeSort(l []int) []int {
		var size =len(l)/2
		if len(l) < 2{
			return l}
		var a =	MergeSort(l[0:size])
		var b =	MergeSort(l[size:len(l)])
		return Merge(a,b)
}
