package heap;
import myarr.*;

public class MaxHeap{
	private MyDynamicIntArray data;
	private int size;
	private int arr_size;
	private int n;
	
	public MaxHeap(int[] data, int n){
		this.data = new MyDynamicIntArray();
		for(int elem : data){
			this.data.add(elem);
		}
		size = this.data.getLength();
		arr_size = size;
		this.n = n;
		makeHeap();
	}
	
	private void makeHeap(){
		for(int i = size/n; i >= 0; i--){
			siftDown(i);
		}
	}
	
	private int getMaxSonIndex(int index){
		int max = -1;
		int[] col_nodes = new int[2];
		col_nodes[0] = index;
		
		System.out.println("---------------------------------------------");
		System.out.println("Let's find max son for this node with value " + data.getElem(index));
		printAsHeap(col_nodes, 1);
		System.out.println();
		
		if(n*index+1 < size){
			max = n*index+1;
		}
		else{
			System.out.println("This node has not got any sons!\n\n");
			return max;
		}
		
		System.out.println("First max son is the left son");
		for(int i = n*index+2; i <= n*index+n && i < size; i++){
			System.out.println("Current max son is node with value " + data.getElem(max) + ". It being compared with node with value " + data.getElem(i));
			col_nodes[0] = max;
			col_nodes[1] = i;
			printAsHeap(col_nodes, 2);
			
			if(data.getElem(max) < data.getElem(i)){
				max = i;
				System.out.println("New temporal max son found!. It is value is " + data.getElem(max));
			}
			else{
				System.out.println("Current max is still node with value " + data.getElem(max));
			}
			
			System.out.println();
		}
		
		col_nodes[0] = max;
		System.out.println("\nFinal max son is node with value " + data.getElem(max));
		printAsHeap(col_nodes, 1);
		System.out.print("\n\n");
		return max;
	}
	
	private void siftDown(int index){
		while(n*index + 1 < size){
			int max_son = getMaxSonIndex(index);
			if(max_son == -1){
				return;
			}
			if(data.getElem(index) < data.getElem(max_son)){
				int temp_val = data.getElem(index);
				data.replaceElem(data.getElem(max_son), index);
				data.replaceElem(temp_val, max_son);
				index = max_son;
			}
			else{
				return;
			}
		}
	}
	
	private int getHeight(){
		int height = 0;
		int node = 0;
		while(node < size){
			node = node*n + 1;
			height += 1;
		}
		
		return height;
	}
	
	public void heapSort(){
		while (size > 1){
			int temp_val = data.getElem(size - 1);
			data.replaceElem(data.getElem(0), size-1);
			data.replaceElem(temp_val, 0);
			size -= 1;
			siftDown(0);
		}
	}
	
	public int[] maxSonPath(){
		int root = 0;
		int[] way = new int[getHeight()];
		int i = 0;
		
		while(root < size && root != -1){
			way[i] = root;
			i += 1;
			root = getMaxSonIndex(root);
			printAsHeap(way, way.length);
		}
		
		return way;
	}
	
//------------------------------

	public void printNode(int node_value, int step, boolean is_col, char side){//выводит узел в консоль
		if(side == 'l' || side == 't'){
			for(int i = 0; i < step; i++){
				System.out.print(' ');
			}
		}
		else{
			for(int i = 0; i < step; i++){
				System.out.print("\033[1;32m");
				System.out.print('-');
			}
		}

		if(is_col){
			System.out.print("\033[1;30;41m");
		}
		else{
			System.out.print("\033[1;30;47m");
		}
		
		System.out.format("%-4d", node_value);
		System.out.print("\033[0m");

		if(side == 'r' || side == 't'){
			for(int i = 0; i < step; i++){
				System.out.print(' ');
			}
		}
		else{
			for(int i = 0; i < step; i++){
				System.out.print("\033[1;32m");
				System.out.print('-');
			}
		}
		System.out.print("\033[0m");
	}

	public void printAsHeap(int[] color_nodes, int col_size){
		if(size == 0){
			System.out.println("Empty heap!");
			return;
		}
		
		int lev = 0;
		int height = getHeight();
		boolean is_col = false;
		int j = 0;
		char side = 0;
			
		int step = 0;
		for(int i = 0; i < size; i++){
			step = (int)(3*2*(int)(Math.pow((double)n, (double)(height-1)))/(2*(int)(Math.pow((double)n, (double)lev)))-2);
				
			is_col = false;
			if(j < col_size){
				if(i == color_nodes[j]){
					is_col = true;
					j += 1;
				}
			}
				
			if(lev == 0){
				printNode(data.getElem(i), step, is_col, 't');
				lev += 1;
				System.out.print("|||||\n");
				continue;
			}

			if(i%n == 1){
				side = 'l';
			}
			
			if(i%n == 0 || i == size-1){
				side = 'r';
			}

			if(n == 1 || (i == size-1 && i%n == 1)){
				side = 't';
			}
			printNode(data.getElem(i), step, is_col, side);
			side = 0;

			if(i%((int)((double)(1.0-Math.pow((double)n, (double)(lev+1)))/(double)(1-n))-1) == 0 || n == 1){
				lev += 1;
				System.out.print("|||||\n");
			}
		}
		System.out.println();
		//System.out.println();
		//System.out.println();
	}
	
	
	public void printAll(){
		data.print(0, arr_size);
	}
	
	public void printHeap(){
		data.print(0, size);
	}
	
	public void printSorted(){
		data.print(size, arr_size);
	}
}
