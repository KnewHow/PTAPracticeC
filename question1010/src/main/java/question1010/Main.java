package question1010;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * 
 * @author ygh Jun 17, 2017
 */
public class Main {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String str = sc.nextLine();
		sc.close();
		String[] strs = str.split(" ");
		Num n1 = new Num();
		Num n2 = new Num();
		n1.setNumber(strs[0]);
		n2.setNumber(strs[1]);
		int tag = Integer.parseInt(strs[2]);
		Long radix = Long.parseLong(strs[3]);
		if (tag == 1) {
			n1.setRadix(radix);
		} else {
			n2.setRadix(radix);
		}
		if (n1.getRadix() != 0) {
			findRadix2(n1, n2);
		} else {
			findRadix2(n2, n1);
		}

	}

	/**
	 * Find the second number radix or print Impossible if the two number are
	 * impossible get equal.We guarantee n1's radix has been known.We set the
	 * radix upper limit is the {@link Num.getDecimal}+1
	 * 
	 * @param n1
	 * @param n2
	 */
	public static void findRadix(Num n1, Num n2) {
		n2.setRadix(findMinimalRadix(n2.getNumber()));
		if (n1.getDecimal() < n2.getDecimal()) {
			System.out.println("Impossible");
			return;
		} else {
			while (n2.getRadix() <= n1.getDecimal() + 1) {
				n2.setRadix(n2.getRadix() + 1);
				if (n1.getDecimal() == n2.getDecimal()) {
					System.out.println(n2.getRadix());
					return;
				}
			}
		}
		System.out.println("Impossible");
	}

	/**
	 * Find the second number radix or print Impossible if the two number are
	 * impossible get equal.We guarantee n1's radix has been known.We set the
	 * radix upper limit is the {@link Num.getDecimal}+1 In this case,we use
	 * halt search to improve our program effective
	 * 
	 * 
	 * @param n1
	 * @param n2
	 */
	public static void findRadix2(Num n1, Num n2) {
		n2.setRadix(findMinimalRadix(n2.getNumber()));
		if (n1.getDecimal() < n2.getDecimal()) {
			System.out.println("Impossible");
		} else {
			long mid = binarySearch(n1, n2);
			if (mid == -1) {
				System.out.println("Impossible");
			} else if (mid == 0) {
				System.out.println(mid + 1);
			} else {
				System.out.println(mid);
			}
		}

	}

	/**
	 * A method to implement binary search
	 * 
	 * @param n1
	 * @param n2
	 * @return
	 */
	public static long binarySearch(Num n1, Num n2) {

		long left = findMinimalRadix(n2.getNumber());
		long right = n1.getDecimal();
		if (right < left) {
			right = left + 35;
		}

		while (left <= right) {
			long mid = (left + right) / 2;
			n2.setRadix(mid);
			int flag = compare(n1, n2);
			if (flag == 0) {
				return mid;
			} else if (flag == -1) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return -1;
	}

	public static int compare(Num n1, Num n2) {
		if (n2.getDecimal() < 0) {
			return 1;
		}
		if (n2.getDecimal() < n1.getDecimal()) {
			return -1;
		}
		return (n1.getDecimal() == n2.getDecimal() ? 0 : 1);
	}

	/**
	 * Find a string number minimal radix,For example,"ab" the minimal radix is
	 * 11
	 * 
	 * @param number
	 * @return
	 */
	public static Long findMinimalRadix(String number) {
		char[] digits = number.toCharArray();
		char minimalRadix = digits[0];
		for (int i = 1; i < digits.length; i++) {
			if (digits[i] > minimalRadix) {
				minimalRadix = digits[i];
			}
		}
		int a = Mapping.mapping.get(minimalRadix + "");
		return (long) a;
	}
}

/**
 * A class to store a number
 * 
 * @author ygh Jun 17, 2017
 */
class Num {
	/**
	 * A string to stand for a number whose radix is don't know
	 */
	private String number;

	/**
	 * A radix to stand for this number radix
	 */
	private Long radix;

	public Num() {
		super();
		this.radix = 0L;
	}

	public Num(String number, Long radix, long decimal) {
		super();
		this.number = number;
		this.radix = radix;
	}

	public String getNumber() {
		return number;
	}

	public void setNumber(String number) {
		this.number = number;
	}

	public Long getRadix() {
		return radix;
	}

	public void setRadix(Long radix) {
		this.radix = radix;
	}

	public long getDecimal() {
		long deciaml = 0L;
		char[] digits = this.getNumber().toCharArray();
		for (int i = 0; i < digits.length; i++) {
			deciaml = deciaml * this.radix + (long) (Mapping.mapping.get(digits[i] + ""));
		}
		return deciaml;
	}

	@Override
	public String toString() {
		return "Num [number=" + number + ", radix=" + radix + "]";
	}

}

/**
 * A class to map number's char and integer
 * 
 * @author ygh Jun 17, 2017
 */
class Mapping {
	public static final Map<String, Integer> mapping = new HashMap<String, Integer>();
	static {
		for (int i = 0; i <= 9; i++) {
			mapping.put(i + "", i);
		}

		int temp = 10;
		for (char c = 'a'; c <= 'z'; c++) {
			mapping.put(c + "", temp++);
		}
	}
}
