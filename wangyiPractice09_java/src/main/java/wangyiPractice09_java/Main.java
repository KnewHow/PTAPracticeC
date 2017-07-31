package wangyiPractice09_java;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		sc.nextLine();
		char[][] arr = new char[n][n];
		for (int i = 0; i < n; i++) {
			String str = sc.nextLine();
			arr[i] = str.toCharArray();
		}

		int max=0;
		for (int i = 0; i < n; i++) {
			int maxw = 0;
			int maxb = 0;
			for (int j = 0; j < n; j++) {
				if (arr[j][i] == 'B') {
					maxb++;
				} else {
					maxw++;
				}
			}
			int tempMax = Math.max(maxw, maxb);
			max = Math.max(tempMax, max);
		}
		System.out.println(max);
		sc.close();
	}
}
