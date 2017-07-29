package wangyiPractice_05_java;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int w = sc.nextInt();
		int x = sc.nextInt();
		int y = sc.nextInt();
		int z = sc.nextInt();

		int count = getCount(w, x, y, z);
		System.out.println(count);
		sc.close();
	}

	private static int getCount(int w, int x, int y, int z) {
		Set<Double> set = new HashSet<>();
		for (int i = w; i <= x; i++) {
			for (int j = y; j <= z; j++) {
				set.add(i * 1.0 / j);
			}
		}
		return set.size();
	}
}
