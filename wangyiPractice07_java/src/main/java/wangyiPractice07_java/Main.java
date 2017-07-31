package wangyiPractice07_java;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		sc.nextLine();
		String str = sc.nextLine();
		Set<String> set1 = new HashSet<>();
		Set<String> set2 = new HashSet<>();
		String[] strs = str.split(" ");
		int i = 0;
		for (; i < n; i++) {
			set1.add(strs[i]);
		}
		
		for (; i < strs.length; i++) {
			set2.add(strs[i]);
		}
		int sum=0;
		for(String s:set2){
			if(set1.contains(s)){
				sum = sum+(int)Math.pow(s.length(), 2);
			}
		}
		System.out.println(sum);
		sc.close();
	}
}
