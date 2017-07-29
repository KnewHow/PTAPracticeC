package demo1;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int k = sc.nextInt();
		int arr[][] = new int[1][n];
		for (int i = 0; i < n; i++) {
			arr[0][i] = sc.nextInt();
		}
		sc.close();

		int mul[][] = new int[n][n];
		for (int i = 0; i < n; i++) {
			if (i < n - 1) {
				mul[i][i] = 1;
				mul[i + 1][i] = 1;
			} else {
				mul[i][i] = 1;
				mul[0][i] = 1;
			}
		}

		for (; k > 0; k >>= 1) {
			if((k&1)==1){
				arr = core(arr, mul);
			}
			mul = core(mul, mul);
		}
		
		/**
         * 输出结果
         */
        int i;
        for (i = 0; i < n - 1; i ++) {
            System.out.print(arr[0][i] + " ");
        }
        System.out.println(arr[0][i]);

	}

	@SuppressWarnings("unused")
	private static void toString(int arr[][]) {
		for (int i = 0; i < arr.length; i++) {
			for (int j = 0; j < arr[0].length; j++) {
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println("=====================");
	}

	private static int[][] core(int[][] a, int b[][]) {

		int rowRes = a.length;
		int columnRes = b[0].length;
		int columnA = a[0].length; // a[0].length == b.length; 矩阵相乘的条件
		int[][] c = new int[rowRes][columnRes];
		for (int i = 0; i < rowRes; i++) {
			for (int j = 0; j < columnRes; j++) {
				for (int k = 0; k < columnA; k++) {
					if (a[i][k] == 0 || b[k][j] == 0) {
						continue; // 剪枝
					}
					c[i][j] += a[i][k] * b[k][j];
				}
				// 100取余运算
				if (c[i][j] >= 100) {
					c[i][j] %= 100;
				}
			}
		}
		return c;

	}
}