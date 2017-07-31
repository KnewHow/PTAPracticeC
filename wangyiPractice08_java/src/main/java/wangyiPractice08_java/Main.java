package wangyiPractice08_java;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		sc.nextLine();
		String str = sc.nextLine();
		sc.close();
		String[] strs = str.split(" ");
		Set<String> set = new HashSet<>();
		for (int i = 0; i < strs.length; i++) {
			set.add(strs[i]);
		}
		for(String s:set){
			System.out.print(s+" ");
		}
	}
}
