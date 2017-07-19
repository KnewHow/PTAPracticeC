package question1016;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.junit.Test;

public class TestListSort {
	@Test
	public void fun1(){
		List<Integer> list = new ArrayList<>();
		list.add(5);
		list.add(4);
		list.add(3);
		list.add(2);
		list.add(1);
		Collections.sort(list);
		System.out.println(list.toString());
	}
}
