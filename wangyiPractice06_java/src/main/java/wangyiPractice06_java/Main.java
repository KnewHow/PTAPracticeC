package wangyiPractice06_java;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String line = sc.nextLine();
		sc.close();
		char[] arr = line.toCharArray();
		int ans = Integer.parseInt(arr[0] + "");
		for (int i = 1; i < arr.length; i = i + 2) {
			if (arr[i] == '+') {
				ans = ans + Integer.parseInt(arr[i + 1] + "");
			} else if (arr[i] == '-') {
				ans = ans - Integer.parseInt(arr[i + 1] + "");
			} else {
				ans = ans * Integer.parseInt(arr[i + 1] + "");
			}
		}
		System.out.println(ans);
	}
}
