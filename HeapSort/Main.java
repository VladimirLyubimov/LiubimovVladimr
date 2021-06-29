import myarr.*;
import heap.*;

public class Main{
	public static void main(String[] args){
		int[] arr = new int[] {18, 145, 54, -985, 554, 32, 8, 1, 2, 3, 6, 5, 4, 9, 8, 7, 1, 23, 6448, 35, 185, 188, 61, -8, -9, 3, -5, 0, 1452};
		MaxHeap tree = new MaxHeap(arr, 2);
		tree.printAll();
		//tree.makeHeap();
		tree.printAll();
		tree.printAsHeap(null, 0);
		//tree.heapSort();
		//tree.printAll();
		tree.maxSonPath();
	}
}
