package question1008;

import java.util.Scanner;

/**
 * 
 * @author ygh Jun 16, 2017
 */
public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int sum = 0, now = 0;
		sc.nextInt();
		while (sc.hasNextInt()) {
			int floor = sc.nextInt();
			if (floor > now) {
				sum += 6 * (floor - now);
			} else {
				sum += 4 * (now - floor);
			}
			now = floor;
			sum += 5;
		}
		sc.close();
		System.out.println(sum);
	}
}
