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
	}
	
	public void makeHeap(){
		for(int i = size/n; i >= 0; i--){
			siftDown(i);
		}
	}
	
	private int getMaxSonIndex(int index){
		int max = -1;
		if(n*index+1 < size){
			max = n*index+1;
		}
		else{
			return max;
		}
		for(int i = n*index+1; i <= n*index+n && i < size; i++){
			if(data.getElem(max) < data.getElem(i)){
				max = i;
			}
		}
		
		return max;
	}
	
	public void siftDown(int index){
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
	
//------------------------------	
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
