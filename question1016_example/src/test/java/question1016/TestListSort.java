package question1016;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import org.junit.Test;

public class TestListSort {
	@Test
	public void fun1() {
		List<Integer> list = new ArrayList<>();
		list.add(5);
		list.add(4);
		list.add(3);
		list.add(2);
		list.add(1);
		Collections.sort(list);
		System.out.println(list.toString());
	}

	@Test
	public void fun2() {
		Map<String, Integer> map = new TreeMap<>(new Comparator<String>() {

			@Override
			public int compare(String o1, String o2) {
				return o2.compareTo(o1);
			}

		});
		map.put("ab", 2);
		map.put("c", 3);
		map.put("aa", 1);
		map.put("d", 4);
		System.out.println(map.toString());
	}

	@Test
	public void fun3() {
		List<Integer> list = new ArrayList<>();
		list.add(5);
		list.add(4);
		list.add(3);
		list.add(2);
		list.add(1);
		list.remove(0);
		System.out.println(list.get(0));
	}
}
